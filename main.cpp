#include "sprites.h"
#include "load.h"
#include "level.h"
#include "movement.h"
#include "weapons.h"

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
	if (!(initSprite (player, bullets, enemies))) // If one the sprites images does not load, exit the game
		return 1;

	//Main Gameplay Variables
	bool gameOver = false;
	bool levelOver = false;
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
			lvl.resetCameraPos (0, 75);
			if (!lvl.loadLevel (mapList))
				return 1;

			//Gameplay loop
			while (!gameOver && !levelOver &&(!key[KEY_ESC])) {
				lvl.drawLevel (buffer, WIDTH, HEIGHT);
				player -> drawframe(buffer);
				playerInput (player, bullets, lvl);
				
				updatebullets (buffer, bullets, enemies, WIDTH-1);

				//blit the double buffer 
				vsync();
				acquire_screen();
				blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
       			release_screen();

       			ticks++;
       			player -> incrementFireCount ();
       			lvl. shiftScreen ();
       			player -> moveSprite (-2, 0);
       			
			}
			MapFreeMem (); 
		} // End of Main Gameplay Branch

       	ticks++;
	}

	delete player;
	for (int n = 0; n < MAX_BULLETS; n++)
		delete bullets[n];
	for (int n = 0; n < MAX_ENEMIES; n++)
		delete enemies[n];
	
	allegro_exit ();
	return 0;
}
END_OF_MAIN()