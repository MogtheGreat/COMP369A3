#include "sprites.h"
#include "load.h"
#include "level.h"
#include "movement.h"
#include "weapons.h"
#include "enemy.h"
#include "display.h"
#include "sound.h"

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
	int life = 30;
	int score = 0;
	int highscore = 0;
	bool pause = false;
	bool music = false;
	bool once = false;
	Levels lvl;		//Deals with level environment and scrolling

	//Initialize Fonts for Game
	PALETTE palette;	// Color palette for fonts.
	FONT * statusFont = load_font (PATHFONT"Space Marine (24).pcx", palette, NULL);
	FONT * optionFont = load_font (PATHFONT"COMPUTER Robot (14).pcx", palette, NULL);

	//Loads the sound effects and music
	SAMPLE * introMusic = load_sample (PATHMUSIC"Two Steps From Hell - Protectors of the Earth.wav");
	SAMPLE * mainMusic = load_sample(PATHMUSIC"Strength of a Thousand Men - Two Steps from Hell .wav");
	SAMPLE * badEnd = load_sample (PATHMUSIC"Warhammer 40,000 Eternal Crusade Soundtrack Tyranids - Theme.wav");
	SAMPLE * goodEnd = load_sample (PATHMUSIC"Audiomachine - Dauntless (Epic Powerful Heroic Music).wav");

	vector <string> mapList = getLvls (); //Loads names of all available map levels from folder
	lvl.initGlobals (0, HEIGHT/8 + 10, mapList.size()); //Initializes the levels global variables
	sound soundCtrl;
	BITMAP * buffer = create_bitmap (WIDTH, HEIGHT); // Set up secondary buffer
	clear (buffer);

	//identify variables used by interupt function
	LOCK_VARIABLE (counter);
	LOCK_VARIABLE (framerate);
	LOCK_VARIABLE (ticks);
	LOCK_FUNCTION (timer1);

	//create new interrupt handler
	install_int (timer1, 1000);

	displayStart (screen, WIDTH-1, HEIGHT-1);
	play_sample(introMusic, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE); // Plays intro Music
	while (!keypressed()); // Wait for player to press any key
	readkey(); // clears buffer
	stop_sample(introMusic); // Stops sample from playing

	//Main game loop
	while (!key[KEY_ESC]){
		if (debug)
			cout << "Starting main game loop." << endl;
	
		if (!gameOver)
			play_sample(mainMusic, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), TRUE); // Plays main game Music
	
		//Main Game Play Branch
		if (!gameOver && (!key[KEY_ESC])) {
			lvl.resetCameraPos (0, 75); // Resets camera to the beginning of the game
			player -> setX(80); // Resets players position
			if (!lvl.loadLevel (mapList))	// Loads next level if there is one.
				return 1;

			displayLevelStart (screen, statusFont, WIDTH-1, HEIGHT-1, lvl. getCurLvl()+1);

			//Gameplay loop
			while (!gameOver && !levelOver &&(!key[KEY_ESC])) {
				if (!pause) {
					lvl.drawLevel (buffer, WIDTH, HEIGHT); // Draws environment to buffer
					player -> drawframe(buffer);	// Draws player's sprite
					playerInput (player, bullets, lvl, music, pause, soundCtrl); // Gets player's inpute and move sprite accordingly
				
					updatebullets (buffer, bullets, enemies, explosions, WIDTH-1, score, soundCtrl); // Moves bullets and draws to buffer
					updateEnemies (buffer, enemies, WIDTH-1, HEIGHT-1); // Moves enemies and draws to buffer
					updateExplosion (buffer, explosions, blood); //Moces the explosion sprites
				
					enemyPhysic (enemies, lvl);	// Allows enemies to interact with the environment
					enemyCollision (player, enemies, blood, life); //Check to see if enemy has killed player

					displayStatus (buffer, statusFont, optionFont, WIDTH-1, life, score, music);

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
	       			
	       			if (music)
	       				soundCtrl. musicOn ();
	       			else
	       				soundCtrl. musicOff ();
	       			adjust_sample (introMusic, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE); // Plays intro Music
				}
				else {
					displayHelp (screen, statusFont, optionFont, WIDTH-1, HEIGHT-1);
					while (!keypressed()); // Wait for player to press any key
					readkey (); // clears input buffer
					pause = false; // restart game
				}
			} // end of game loop
			
			if (debug)
				cout << "END OF LEVEL OR GAME" << endl;
			
			MapFreeMem ();
			
			if ((!gameOver) && (!key[KEY_ESC])) {
				if (debug)
					cout << "END OF LEVEL" << endl;
				
				score += 1000;
				displayLevelEnd (screen, statusFont, WIDTH-1, HEIGHT-1, lvl. getCurLvl()+1, score);
				lvl.incrementCurLvl(); // Get next Level

				if (debug) {
					cout << "curLvl: " << lvl. getCurLvl () << endl;
					cout << "lvl. anotherLevel (): " << lvl. anotherLevel () << endl;
				}

				//Checks to make sure there is another level
				if (!lvl. anotherLevel ()) {
					levelOver = false;

					if (debug)
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

		if ((gameOver) && (!key[KEY_ESC])) {
				stop_sample(mainMusic); // Stops sample from playing

				if (!once) {
					displayEnd (screen, score, highscore, life, WIDTH-1, HEIGHT-1);
					
					//Plays the right music for the ending
					if (life >= 0)
						play_sample(goodEnd, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE); // Plays good End
					else
						play_sample(badEnd, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE); // Plays good End
					once = true;
				}

				if (key[KEY_Y]) {
					life = 30;
					score = 0;
					levelOver = false;
					gameOver = false;
					lvl. setCurLvl (0);

					if (life >= 0)
						stop_sample(goodEnd); // Stops sample from playing
					else
						stop_sample(badEnd); // Stops sample from playing
				}
			}

       	ticks++;
	}

	if (debug)
		cout << "FREEING STUFF!" << endl;

	//Frees sprites
	delete player;
	for (int n = 0; n < MAX_BULLETS; n++)
		delete bullets[n];
	for (int n = 0; n < MAX_ENEMIES; n++)
		delete enemies[n];
	for (int n = 0; n < MAX_EXPLOSIONS; n++)
		delete explosions[n];
	delete blood;
	
	//Frees font
	destroy_font (statusFont);
	destroy_font (optionFont);

	// Frees samples
	destroy_sample (introMusic);
	destroy_sample (mainMusic);
	destroy_sample (badEnd);
	destroy_sample (goodEnd);

	allegro_exit ();
	return 0;
}
END_OF_MAIN()