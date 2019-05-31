#include "load.h"

using namespace std;

int initialize () {
	int check = allegro_init ();
	if (check != 0) {
		std::cerr << "Allegro library failed to initialize!" << std::endl;
		return 1;
	}

	check = install_timer ();
	if (check != 0) {
		std:: cerr << "Timer failed to install!" << std:: endl;
		return 1;
	}
	
	check = install_keyboard ();
	if (check != 0) {
		std:: cerr << "Keyboard failed to install!" << std::endl;
		return 1;
	}

	set_color_depth (16);
	srand(time(NULL));
	check = set_gfx_mode (MODE, WIDTH, HEIGHT, 0,0);
	if (check != 0) {
		allegro_message ("%s\n", allegro_error);
		return 1;
	}

	return 0;
}

vector <string> getLvls () {
	vector<string> list;	// Holds the file list from the directory
	DIR * dir;				// Used to 
	struct dirent * ent;
	
	//Opens the directory
	if ((dir = opendir (PATH)) != NULL) {
		// gets all files and directories in the folder
		while ((ent = readdir (dir)) != NULL) {
			string temp (ent -> d_name);
			string completePath = PATH;
			completePath += temp;
			
			// Checks to see if there is a file in the directory.
			if ((temp != ".") && (temp != "..")) {
				list.push_back (completePath); // Stores the file name in the list.
			}
		}
		closedir (dir); // closes directories
	}

	return list;
}

int initSprite (sprites *& player, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES]) {
	player = new sprites ();
	player -> setX (80);
	player -> setY (HEIGHT/2 + 130);
	player ->  setWidth (50);
	player -> setHeight (58);
	player -> setCurFrame (0);
	player -> setFrameCount (0);
	player -> setFrameDelay (2);
	player -> setMaxFrame (6);
	player -> setAnimDir (1);
	player -> setAnimColumns (3);
	player -> setAnimStartX (0);
	player -> setAnimStartY (0);
	player -> setFacing (1);
	player -> setJump (JUMPIT);
	player -> setFireCount (0);
	player -> setFireDelay (10);
	if (!(player -> load ((char*)"Resources/Original/Space Marine(50x58)(3 columns).bmp"))) {
		allegro_message("Error loading player's sprite!");
		return 0;
	}

	for (int n = 0; n < MAX_BULLETS; n++) {
		bullets[n] = new sprites ();
		bullets[n] -> setAlive (0);
		bullets[n] -> setX (0);
		bullets[n] -> setY (0);
		bullets[n] -> setWidth (34);
		bullets[n] -> setHeight (14);
		bullets[n] -> setXSpeed (10);
		bullets[n] -> setYSpeed (0);
		bullets[n] -> setCurFrame (0);
		bullets[n] -> setFrameCount (0);
		bullets[n] -> setFrameDelay (0);
		bullets[n] -> setMaxFrame (0);
		bullets[n] -> setAnimDir (1);
		bullets[n] -> setAnimColumns (1);
		bullets[n] -> setAnimStartX (0);
		bullets[n] -> setAnimStartY (0);
		bullets[n] -> setFacing (1);
		if (!(bullets[n] -> load ((char*)"Resources/Sprites/bullet.bmp"))) {
			allegro_message("Error loading bullet's sprite!");
			return 0;
		}
	}

	for (int n = 0; n < MAX_ENEMIES; n++) {
		enemies[n] = new sprites ();
		enemies[n] -> setX (rand() % 250 + 300);
		enemies[n] -> setY (100);
		enemies[n] -> setWidth (133);
		enemies[n] -> setHeight (118);
		enemies[n] -> setXSpeed (-(rand() % 3 + 1));
		enemies[n] -> setYSpeed (0);
		enemies[n] -> setCurFrame (0);
		enemies[n] -> setFrameCount (0);
		enemies[n] -> setFrameDelay (0);
		enemies[n] -> setMaxFrame (0);
		enemies[n] -> setAnimDir (1);
		enemies[n] -> setAnimColumns (2);
		enemies[n] -> setAnimStartX (0);
		enemies[n] -> setAnimStartY (0);
		enemies[n] -> setFacing (1);
		if (!(enemies[n] -> load ((char*)"Resources/Sprites/tyranids(133x118)(2 columns).bmp"))) {
			allegro_message("Error loading enemies's sprite!");
			return 0;
		}
	}

	return 1;
}