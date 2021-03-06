/*
Title: load.cpp
Description: Deals loading resources for the game.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#include "load.h"

using namespace std;

/*
	Initializes the library and Loads the necessary library components.

	Param:
		N/A
	Return:
		1 if something has gone wrong.
		0 otherwise.
*/
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

	//install a digital sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) 
    {
        std::cerr <<"Error initializing sound system" << std::endl;
        return 1;
    }

	return 0;
}

/*
	Gets a list of map files from the resource folder. Must be
	at least one map in the Resources/Map folder.

	Param:
		N/A
	Return;
		A list containing the name for all the available maps for the game.
*/
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

/*
	Initializes all the available sprites for the game.

	Param:
		player 			- A reference to a sprite that represents the player's sprite.
		bullets 		- An array of sprites that represents bullets
		enemies     	- An array of sprites that represents all the enemies in the game.
		explosion 		- An array of sprites that represents all the explosion in the game
		blood 			- A reference to a sprite that represents player's death animation.
	Return:
		0 if one of the bitmaps for the sprite does not load.
		1 if everything is all right.
*/
int initSprite (sprites *& player, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES], 
				sprites * explosions [MAX_EXPLOSIONS], sprites *& blood) {
	
	// Initializes the player's sprite
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
	player -> setFireDelay (6);
	if (!(player -> load ((char*)"Resources/Original/Space Marine(50x58)(3 columns).bmp"))) {
		allegro_message("Error loading player's sprite!");
		return 0;
	}

	// Initializes the bullet sprites
	for (int n = 0; n < MAX_BULLETS; n++) {
		bullets[n] = new sprites ();
		bullets[n] -> setAlive (0);
		bullets[n] -> setX (0);
		bullets[n] -> setY (0);
		bullets[n] -> setWidth (34);
		bullets[n] -> setHeight (14);
		bullets[n] -> setXSpeed (12);
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

	// Initializes the enemies sprites
	for (int n = 0; n < MAX_ENEMIES; n++) {
		enemies[n] = new sprites ();
		enemies[n] -> setAlive (0);
		enemies[n] -> setX (rand() % 250 + 300);
		enemies[n] -> setY (100);
		enemies[n] -> setWidth (133);
		enemies[n] -> setHeight (118);
		enemies[n] -> setXSpeed (-(rand() % 3 + 1));
		enemies[n] -> setYSpeed (0);
		enemies[n] -> setCurFrame (0);
		enemies[n] -> setFrameCount (0);
		enemies[n] -> setFrameDelay (2);
		enemies[n] -> setMaxFrame (3);
		enemies[n] -> setAnimDir (1);
		enemies[n] -> setAnimColumns (2);
		enemies[n] -> setAnimStartX (0);
		enemies[n] -> setAnimStartY (0);
		enemies[n] -> setFacing (1);
		enemies[n] -> setJump (JUMPIT);
		if (!(enemies[n] -> load ((char*)"Resources/Sprites/tyranids(133x118)(2 columns).bmp"))) {
			allegro_message("Error loading enemies's sprite!");
			return 0;
		}
	}

	// Initalizes the explosion sprites
	for (int n = 0; n < MAX_EXPLOSIONS; n++) {
		explosions [n] = new sprites ();
		explosions [n] -> setAlive (0);
		explosions [n] -> setX(0);
		explosions [n] -> setY(0);
		explosions [n] -> setWidth (130);
		explosions [n] -> setHeight (130);
		explosions [n] -> setXDelay (8);
		explosions [n] -> setYDelay (0);
		explosions [n] -> setXCount (0);
		explosions [n] -> setYCount (0);
		explosions [n] -> setXSpeed (-1);
		explosions [n] -> setYSpeed (0);
		explosions [n] -> setCurFrame (0);
		explosions [n] -> setMaxFrame (6);
		explosions [n] -> setFrameCount (0);
		explosions [n] -> setFrameDelay (2);
		explosions [n] -> setAnimDir (1);
		explosions [n] -> setAnimColumns (7);
		explosions [n] -> setAnimStartX (0);
		explosions [n] -> setAnimStartY (0);
		explosions [n] -> setFacing (1);
		if (!(explosions[n] -> load ((char*)"Resources/Sprites/bigexplosion(130x130)(7 columns).bmp"))) {
			allegro_message("Error loading explosions's sprite!");
			return 0;
		}
	}

	//Initializes the player's death sprite
	blood = new sprites  ();
	blood -> setAlive (0);
	blood -> setX (0);
	blood -> setY (0);
	blood -> setWidth (64);
	blood -> setHeight (64);
	blood -> setXDelay (0);
	blood -> setYDelay (0);
	blood -> setXCount (0);
	blood -> setYCount (0);
	blood -> setXSpeed (-1);
	blood -> setYSpeed (0);
	blood -> setCurFrame (0);
	blood -> setMaxFrame (15);
	blood -> setFrameCount (0);
	blood -> setFrameDelay (1);
	blood -> setAnimDir (1);
	blood -> setAnimColumns (4);
	blood -> setAnimStartX(0);
	blood -> setAnimStartY(0);
	blood -> setFacing (1);
	if (!(blood -> load ((char*)"Resources/Sprites/playersDeath(64x64)(4 columns).bmp"))) {
			allegro_message("Error loading blood's sprite!");
			return 0;
		}

	return 1;
}
