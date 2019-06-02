#include "sprites.h"
#include "load.h"
#include "level.h"
#include "movement.h"
#include "weapons.h"
#include "enemy.h"
#include "display.h"
#include "sound.h"

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 600
#define PATH "Resources/Map/"

using namespace std;

//Timer variables.
volatile int counter;
volatile int ticks;
volatile int framerate;

//calculate framerate every second
void timer1 (void) {
	counter++;
	framerate = ticks;
	ticks = 0;
	rest(2);
}
END_OF_FUNCTION (timer1)

int checkDebug (int argc, char * argv[]) {
	if (argc == 1) return 0;
	else if (strcmp(argv[1],"-d") == 0) return 1;
	return 0;
}

int main (int argc, char * argv[])  {
	int debug = checkDebug (argc, argv);

	if (initialize()) {
		return 1;
	}

	// Create the sprites for the game
	sprites * player;
	sprites * bullets[MAX_BULLETS];
	sprites * enemies[MAX_ENEMIES];
	sprites * explosions [MAX_EXPLOSIONS];
	sprites * blood;
	if (!(initSprite (player, bullets, enemies, explosions, blood))) // If one the sprites images does not load, exit the game
		return 1;

	//Main Gameplay Variables
	bool gameOver = false;
	bool levelOver = false;
	int life = 20;
	int score = 0;
	Levels lvl;		//Deals with level environment and scrolling

	vector <string> mapList = getLvls (); //Loads names of all available map levels from folder
	lvl.initGlobals (0, HEIGHT/8 + 10, mapList.size()); //Initializes the levels global variables
	BITMAP * buffer = create_bitmap (WIDTH, HEIGHT); // Set up secondary buffer
	clear (buffer);

	//identify variables used by interupt function
	LOCK_VARIABLE (counter);
	LOCK_VARIABLE (framerate);
	LOCK_VARIABLE (ticks);
	LOCK_FUNCTION (timer1);

	//create new interrupt handler
	install_int (timer1, 1000);

	//Main game loop
	while (!key[KEY_ESC]){
		//Main Game Play Branch
		if (!gameOver && (!key[KEY_ESC])) {
			lvl.resetCameraPos (0, 75); // Resets camera to the beginning of the game
			if (!lvl.loadLevel (mapList))	// Loads next level if there is one.
				return 1;

			//Gameplay loop
			while (!gameOver && !levelOver &&(!key[KEY_ESC])) {
				lvl.drawLevel (buffer, WIDTH, HEIGHT); // Draws environment to buffer
				player -> drawframe(buffer);	// Draws player's sprite
				playerInput (player, bullets, lvl); // Gets player's inpute and move sprite accordingly
				
				updatebullets (buffer, bullets, enemies, explosions, WIDTH-1, score); // Moves bullets and draws to buffer
				updateEnemies (buffer, enemies, WIDTH-1, HEIGHT-1); // Moves enemies and draws to buffer
				updateExplosion (buffer, explosions, blood); //Moces the explosion sprites
				
				enemyPhysic (enemies, lvl);	// Allows enemies to interact with the environment
				enemyCollision (player, enemies, blood, life); //Check to see if enemy has killed player

				//blit the double buffer 
				vsync();
				acquire_screen();
				blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
       			release_screen();

       			ticks++;
       			player -> incrementFireCount (); // Allows player to fire.
       			onScreen (player, WIDTH - player -> getWidth()); // Keeps player on screen
       			//Scrolls the screen and ajust the player and enemy sprites
	       		if (lvl. shiftScreen ()) {
	       			player -> moveSprite (-2, 0);
	       			for (int n = 0; n < MAX_ENEMIES; n++) {
	       				enemies[n] -> moveSprite (-4,0);
	       			}
	       		}

	       		//Check for level End
	       		if (lvl.levelEnd (player -> getX(), WIDTH - player -> getWidth()))
	       			levelOver = true;
	       		if (life < 0)
	       			gameOver = true;
			}
			
			if (debug)
				cout << "END OF LEVEL OR GAME" << endl;
			
			MapFreeMem ();
			
			if (!gameOver) {
				if (debug)
					cout << "END OF LEVEL" << endl;
				
				lvl.incrementCurLvl(); // Get next Level
				score += 1000;

				if (debug) {
					cout << "curLvl: " << lvl. getCurLvl () << endl;
					cout << "lvl. anotherLevel (): " << lvl. anotherLevel () << endl;
				}

				//Checks to make sure there is another level
				if (!lvl. anotherLevel ()) {
					levelOver = false;
					cout << "levelOver: " << levelOver << endl;
				}

				//If there is no more lvels, then game is over
				if (lvl. doneGame ()) {
					gameOver = true;

					if (debug)
						cout << "LAST LEVEL DONE! GAME OVER!" << endl;
				}
			}
		} // End of Main Gameplay Branch

       	ticks++;
	}

	if (debug)
		cout << "FREEING STUFF!" << endl;

	delete player;
	for (int n = 0; n < MAX_BULLETS; n++)
		delete bullets[n];
	for (int n = 0; n < MAX_ENEMIES; n++)
		delete enemies[n];
	for (int n = 0; n < MAX_EXPLOSIONS; n++)
		delete explosions[n];
	delete blood;
	
	allegro_exit ();
	return 0;
}
END_OF_MAIN()