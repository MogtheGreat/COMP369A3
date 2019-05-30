#include <allegro.h>	//Needed for mappyal to work. Don't touch!
#include <string>
#include "auxi.h"
#include "level.h"
#include "sprite.h"
#include "action.h"

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

int main (int argc, char * argv[]) {
	int debug = checkDebug (argc, argv);
	Levels lvl (debug);
	SPRITE * player;
	bool gameOver = false;

	if (debug) {
		cout << "Starting Debug Session! \n Starting initialization..." << endl;
	}

	//If 1, then something failed to install or initialize
	if (initialize ()) {
		return 1;
	}

	if (debug)
		cout << "Start map collecting and first map load..." << endl;

	vector <string> mapList = getLvls (); //Loads names of all available map levels from folder
	lvl.initGlobals (0, HEIGHT/2 + 10, mapList.size()); //Initializes the levels global variables
	player = new SPRITE (80, HEIGHT/2 + 60, 50, 58, 0, 0, 6, 6, 3); // Loads player's sprite into program
	if (!(player -> load ((char*)"Resources/Original/Space Marine(50x58)(3 columns).bmp"))) {
		allegro_message("Error loading player's sprite!");
		return 1;
	}

	BITMAP * buffer = create_bitmap (WIDTH, HEIGHT); // Set up secondary buffer
	clear (buffer);

	if (debug)
		cout << "Locking timer variables..." << endl;

	//identify variables used by interupt function
	LOCK_VARIABLE (counter);
	LOCK_VARIABLE (framerate);
	LOCK_VARIABLE (ticks);
	LOCK_FUNCTION (timer1);

	//create new interrupt handler
	install_int (timer1, 1000);

	if (debug)
		cout << "Beginning main game loop..." << endl;

	//Main game loop
	while (!key[KEY_ESC]){
		
		if (!gameOver && (!key[KEY_ESC])) {
			lvl.resetCameraPos (0, HEIGHT/2 + 10);
			if (lvl.loadLevel (mapList))
				return 1;
			
			//Gameplay loop
			while (!gameOver && (!key[KEY_ESC])) {
				lvl.adjustYScroll (player -> getY (), player -> getHeight ());
				lvl.drawLevel (buffer, WIDTH, HEIGHT);
				player -> drawframe(buffer, debug);
				playerInput (player, lvl);
		
				//blit the double buffer 
				vsync();
				acquire_screen();
				blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
       		 	release_screen();
       		 	
       		 	lvl.shiftScreen (); //Moves the screen along
       		 	player -> moveSprite (-2, 0);
       		 	ticks++; 
			}

			MapFreeMem ();
		}
		ticks++;
	}

	if (debug)
		cout << "Exited main game loop...\n Releasing memory..." << endl;

	delete player;
	destroy_bitmap (buffer);
	allegro_exit ();
	return 0;
}
END_OF_MAIN()