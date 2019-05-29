#include <allegro.h>	//Needed for mappyal to work. Don't touch!
#include <string>
#include "auxi.h"
#include "level.h"

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
	lvl.initGlobals (0, HEIGHT/2 + 10, mapList.size());
	
	/*//Loads the first map
	if (MapLoad ((char *) mapList[0].c_str()) != 0) {
		set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
		allegro_message ("Can't find a valid .fmp file.");
		return 1;
	} */

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
		
		if (!gameOver && (!key[KEY_ESC])) {
			lvl.resetCameraPos (0, HEIGHT/2 + 10);
			if (lvl.loadLevel (mapList))
				return 1;
			
			//Gameplay loop
			while (!gameOver && (!key[KEY_ESC])) {
				lvl.drawLevel (buffer, WIDTH, HEIGHT);
		
				//blit the double buffer 
				vsync();
				acquire_screen();
				blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
       		 	release_screen();
       		 	
       		 	lvl.shiftScreen (); //Moves the screen along
       		 	ticks++; 
			}

			MapFreeMem ();
		}
		ticks++;
	}
	destroy_bitmap (buffer);
	allegro_exit ();
	return 0;
}
END_OF_MAIN()