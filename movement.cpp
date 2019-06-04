/*
Title: movement.cpp
Description: Deals with sprite movement and collision with environment.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#include "movement.h"

using namespace std;

/*
	Gets player's input and produce the desired action on screen. Handles player's sprite
	collision with the environment.

	Param:
		player 			- A sprite object that represents the player's sprite on screen
		bullets 		- An array of sprites that represents bullets
		lvl 			- A level object that represents the levels of the game
		music 			- A boolean that represents whatever the music is on or off
		pause 			- A boolean that represents whatever the game is paused or not
		sndCtrl		 	- An object that represents the volume, pan, pitch controls of the game's music/sound
		shoot 			- A sample object that represents the sound a gun makes
		jump 			- A sample object thtat represents the sound of jumping
	Return:
		N/A
*/
void playerInput (sprites * player, sprites * bullets[MAX_BULLETS], Levels lvl, bool & music, 
				  bool & pause, sound sndCtrl, SAMPLE * shoot, SAMPLE * jump) {
	int oldX = player -> getX ();
	int oldY = player -> getY ();

	if (DEBUG2){
		cout << "Player x and y before function..." << endl;
		cout << "player -> x: " << oldX << endl;
		cout << "player -> y: " << oldY << endl;
	}

	// Player turns and moves to the right
	if (key[KEY_RIGHT]) {
		player -> setFacing (1);
		player -> updateAnimation ();
		player -> moveSprite (6,0);
	}
	// Players turns and moves to the left
	else if (key[KEY_LEFT]) {
		player -> setFacing (0);
		player -> updateAnimation ();
		player -> moveSprite (-6,0);
	}
	else
		player -> setCurFrame (0); // Player is standing still

	//Controls shooting
	if (key[KEY_SPACE]) {
		if ((player -> getFireCount ()) > (player -> getFireDelay())) { // Breaks up the firing sequence
			player -> setFireCount (0);// restart the sequence
			fireatenemy (bullets, player -> getX (), player -> getY ()); // Generate a bullet at the player's position
			play_sample(shoot, sndCtrl. getVolume (), sndCtrl. getPan(), sndCtrl. getPitch(), FALSE); // Plays shooting sound effects
		}
	}

	// if Player press ctrl-m, turn music on/off
	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && (key[KEY_M])) {
        if (music)
    		music = false;
        else
            music = true;
	}

    //If player press crtrl-h, pause game
	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && (key[KEY_H])) {
        if (pause)
            pause = false;
        else
            pause = true;
        readkey (); //Clears input buffer
	}

	//Start jumping
	if (player -> getJump () == JUMPIT) {
		//If player is no longer on solid ground, start falling sequence
		if (!lvl.collided (player-> getX() + (player -> getWidth ()), player-> getY() + (player-> getHeight())))
			player -> setJump (0);

		//Player is on solid ground and jumps
		if (key[KEY_UP]) {
			player -> setJump (30);
			play_sample(jump, sndCtrl. getVolume (), sndCtrl. getPan(), sndCtrl. getPitch(), FALSE); // Plays intro Music
		}
	}

	handleJump (player, lvl); // handles the rest of the jumping mechanics
	handleWall (player, lvl, oldX, oldY); // handles the wall collision mechanics

	if (DEBUG2){
		cout << "Player x and y after function..." << endl;
		cout << "player -> x: " << player -> getX () << endl;
		cout << "player -> y: " << player -> getY () << endl;
	}
}

/*
	Handles enemy collision with ground, ceiling and wall.

	Param:
		enemies     - An array of sprites that represents all the enemies in the game.
		lvl 		- A level object that represents the levels of the game
	Return:
		N/A
*/
void enemyPhysic (sprites * enemies[MAX_ENEMIES], Levels lvl) {
	for (int n = 0; n < MAX_ENEMIES; n++) {
		// Checks to see if the enemy is in the middle of the air.
		if (enemies[n] -> getJump () == JUMPIT) {
			if (!lvl.collided (enemies[n]-> getX() + (enemies[n] -> getWidth ()), enemies[n]-> getY() + (enemies[n]-> getHeight())))
			enemies[n] -> setJump (0);
		}

		handleJump (enemies[n], lvl); // Handles the falling mechanism 
		handleWall (enemies[n], lvl, enemies[n] -> getX(), enemies[n] -> getY ()); // Checks for wall collision
	}
}

/*
	Handles the jumping and falling mechanism. Detects when hits the hits the floor
	or the ceiling of a tile.

	Param:
		spr 		- A sprite object that can represent any sprite in the game
		lvl 			- A level object that represents the levels of the game
	Return:
		N/A
*/
void handleJump (sprites * spr, Levels lvl) {
	//Moves sprite up based on jump value
	if (spr -> getJump () != JUMPIT) {
		spr -> moveSprite (0, -(spr-> getJump()/3));
		spr -> addToJump (-1);
	}

	// If sprite hits the ceiling while jumping, set jump to zero and move sprite down 2
	if ((spr -> getJump () > 0)) {
		if (lvl.hitCeiling (spr-> getX() + (spr -> getWidth ()), spr-> getY() + (spr-> getHeight()) + 5)) {
			spr -> setJump (0);
			spr -> moveSprite (0, 2);
		}
	}

	// If sprite is falling check for collision with floor.
	else if (spr -> getJump () < 0) {
		if (lvl.collided (spr-> getX() + (spr -> getWidth ()), spr-> getY() + (spr-> getHeight())))
		{
			spr -> setJump(JUMPIT);

			// If moved past floor, adjust sprite until on top
			while (lvl.collided (spr-> getX() + (spr -> getWidth ()), spr-> getY() + (spr-> getHeight())))
				spr -> moveSprite (0, -2);
		}
	}
}

/*
	Checks to see if sprite hits the wall from the right or the left

	Param:
		spr 		- A sprite object that can represent any sprite in the game
		lvl 		- A level object that represents the levels of the game
		oldX 		- Previous X position of the spr
		oldY 		- Previous Y position of the spr
	Return:
		N/A
*/
void handleWall (sprites * spr, Levels lvl, int oldX, int oldY) {
	if (!spr -> getFacing ()) { // Facing towards the right
		if (lvl.collided (spr-> getX(), spr-> getY() + (spr-> getHeight()))) {
			spr -> setX (oldX);
			spr -> setY (oldY);
		}
	}
	else { // Facing towards the left
		if (lvl.collided (spr-> getX() + (spr -> getWidth ()), spr-> getY() + (spr-> getHeight()))) {
			spr -> setX (oldX);
			spr -> setY (oldY);
		}
	}
}

/*
	Used to keep the player's sprite on the screen.

	Param:
		player 			- A sprite object that represents the player's sprite on screen
		mapWidth   		- An integer that represents the on screen map width
	Return:
		N/A
*/
void onScreen (sprites * player, int mapWidth) {
	if (player -> getX() < 0)
		player -> moveSprite (4,0);		//Blocks the left side of the screen
	if (player -> getX() > mapWidth)
		player -> moveSprite (-4,0);	//Blocks the right side of the screen
}
