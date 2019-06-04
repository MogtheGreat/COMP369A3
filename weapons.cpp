/*
Title: weapons.cpp
Description: Deals with weapon sprites behavoir and collision. 
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#include "weapons.h"

using namespace std;

/*
	Generate bullets.

	Param:
		bullets 	- An array of sprites that represents bullets
		x 			- An integer that represents the bullets starting position
		y 			- An integer that represents the bullets starting position
*/
void fireatenemy (sprites * bullets[MAX_BULLETS], int x, int y) {
	for (int n = 0; n < MAX_BULLETS; n++) {
		if (!(bullets[n] -> getAlive())) {
			bullets[n] -> setAlive (1);			// Generate bullet
			//Set bullet initial position at player's sprite gun location
			bullets[n] -> setX (x + WEAPONLOC);
			bullets[n] -> setY (y + WEAPONLOC);
			return;
		}
	}
}

/*
	Updates the bullets position on the screen.

	Param:
		buffer 		- A bitmap that is being drawn to.
		bullets 	- An array of sprites that represents bullets
		enemies     - An array of sprites that represents all the enemies in the game.
		explosion 	- An array of sprites that represents all the explosion in the game
		mapWidth    - An integer that represents the on screen map width
		score 		- A reference to an integer that represents the player's score
		sndCtrl 	- An object that represents the volume, pan, pitch controls of the game's music/sound
		alienDeath  - A sample object that represents a death of the alien
		lvl 		- A level object that represents the levels of the game
	Return:
		N/A
*/
void updatebullets (BITMAP * buffer, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES], 
					sprites * explosions [MAX_EXPLOSIONS], int mapWidth, int & score, sound sndCtrl,
					SAMPLE * alienDeath, Levels lvl) {
	// Go through all the live bullets, update their position and draw to buffer.
	for (int n = 0; n < MAX_BULLETS; n++) {
		if (bullets[n] -> getAlive()) {
			updatebullet (bullets[n], enemies, explosions, mapWidth, score, sndCtrl, alienDeath, lvl);
			bullets[n] -> drawframe (buffer);
		}
	}
}

/*
	Updates a bullets position. If leave screen, dead. If hit enemy, kill enemy and bullet. If hit object
	on map, kill bullet.

	Param:
		bullet 			- A sprite that reperesents a live bullet.
		enemies     - An array of sprites that represents all the enemies in the game.
		explosion 	- An array of sprites that represents all the explosion in the game
		mapWidth    - An integer that represents the on screen map width
		score 		- A reference to an integer that represents the player's score
		sndCtrl 	- An object that represents the volume, pan, pitch controls of the game's music/sound
		alienDeath  - A sample object that represents a death of the alien
		lvl 		- A level object that represents the levels of the game
	Return:
		N/A
*/
void updatebullet (sprites * bullet, sprites * enemies[MAX_ENEMIES], sprites * explosions [MAX_EXPLOSIONS], 
				   int mapWidth, int & score, sound sndCtrl, SAMPLE * alienDeath, Levels lvl) {

	//move the bullet
	bullet -> moveSprite (bullet -> getXSpeed (), bullet -> getYSpeed ());

	// If leaves screen, kill bullet
	if ((bullet -> getX () < 0) || (bullet-> getX() > mapWidth)) {
		bullet -> setAlive (0);
		return;
	}

	// Check bullet against all live enemies.
	for (int n = 0; n < MAX_ENEMIES; n++) {
		if (enemies[n] -> getAlive ()) {
			// Get bullets position on screen
			int x = bullet -> getX ();
			int y = bullet -> getY ();

			//Get enemy alien bounding rectangle
			int x1 = enemies [n] -> getX ();
			int y1 = enemies [n] -> getY ();
			int x2 = x1 + enemies[n] -> getWidth ();
			int y2 = y1 + enemies[n] -> getHeight ();

			//check for collision
			if (enemies[n] -> inside (x, y, x1, y1, x2, y2)) {
				//kill enemy and bullet
				enemies[n] -> setAlive (0);
				bullet -> setAlive (0);

				// Create explosion
				startExplosion (explosions, enemies[n]-> getX (),enemies[n]-> getY());
				// Play alien death sound
				play_sample(alienDeath, sndCtrl. getVolume (), sndCtrl. getPan(), sndCtrl. getPitch(), FALSE); // Plays intro Music
				score += 100;
				break;
			}
			// If bullet has hit a wall, kill bullet
			if (lvl.collided (bullet-> getX() + (bullet -> getWidth ()), bullet-> getY() + (bullet-> getHeight())))
				bullet -> setAlive (0);
		}
	}
}

/*
	Generate an explosion at the desired location.

	Param:
		explosion 	- An array of sprites that represents all the explosion in the game
		x 			- An integer that represents the explosion starting position
		y 			- An integer that represents the explosion starting position
*/
void startExplosion (sprites * explosions [MAX_EXPLOSIONS], int x, int y) {
	for (int n = 0; n < MAX_EXPLOSIONS; n++) {
		if (!(explosions[n] -> getAlive())) {
			explosions[n] -> setAlive (1); // Generate the explosion
			// Set the location
			explosions[n] -> setX (x);
			explosions[n] -> setY (y);
			break;
		}
	}
}

/*
	Update the explosion animation. Kills it once reaches last frame

	Param:
		buffer 		- A bitmap that is being drawn to.
		explosion 	- An array of sprites that represents all the explosion in the game
		blood 		- A sprite that represents the player's death animation
	Return:
		N/A
*/
void updateExplosion (BITMAP * buffer, sprites * explosions [MAX_EXPLOSIONS], sprites * blood) {
	for (int n = 0; n < MAX_EXPLOSIONS; n++) {
		if (explosions[n] -> getAlive()) {	// if explosion is alive
			explosions[n] -> updateSprite ();	// Update the explosion position and animation
			explosions[n] -> drawframe (buffer);	// draw to buffer

			// Kill explosion if reached last frame
			if (explosions[n] -> getCurFrame () >= explosions[n] -> getMaxFrame ()) {
				explosions[n] -> setCurFrame (0);
				explosions[n] -> setAlive (0);
			}
		}
	}

	if (blood -> getAlive()) { // if player has died
		blood -> updateSprite ();	// Update death animation
		blood -> drawframe (buffer); // Draw to buffer

		// Kill blood animation if reached last frame
		if (blood -> getCurFrame () >= blood -> getMaxFrame ()) {
			blood -> setCurFrame (0);
			blood -> setAlive (0);
		}
	}
}
