/*
Title: enemy.cpp
Description: Deals with enemy sprites behavoir and collision with player.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#include "enemy.h"

using namespace std;

/*
	Update the enemies position on the sccreen. Also generates the enemies in the game.
	Param:
		buffer 	  - A bitmap that is being drawn to.
		enemies   - An array of sprites that represents all the enemies in the game.
		mapWidth  - An integer that represents the on screen map width
		mapHeight - An integer that represents the on screen map height
	Return:
		N/A
*/
void updateEnemies (BITMAP * buffer, sprites * enemies[MAX_ENEMIES], int mapWidth, int mapHeight) {
	// update/draw alien enemies
	for (int n = 0; n < MAX_ENEMIES; n++) {
		// Checks to see if the enemy is alive
		if (enemies[n] -> getAlive ()) {
			enemies[n] -> moveSprite (enemies[n] -> getXSpeed (), enemies[n] -> getYSpeed ()); // Moves the sprite
			enemies[n] -> updateAnimation(); // updates the sprite animation

			// Get the x and y position of the sprite
			int x = enemies[n] -> getX ();
			int y = enemies[n] -> getY();

			// Checks to see if the enemy is on screen
			if (!((x < -(enemies[n]-> getWidth())) || (x > mapWidth) || (y < 0) || (y > mapHeight))) {
				 enemies[n] -> drawframe (buffer); // Draws the sprite to the bitmap
			}
			else
				enemies[n] -> setAlive (0); // Turns off the enemy if not on screen
		}
		else {
			enemies[n] -> setAlive (1); // Generate a new enemy
			enemies[n] -> setX (rand() % 450 + 350); // Set new x position
			enemies[n] -> setY (150); // Set new y position
		}
	}
}

/*
	Checks to see if the enemy has collided with the player. If so, kill enemy but decrease
	player's life by one for each enemy. Plays player's death sound if player has died.
	Param:
		player 			- A sprite that represents the player
		enemies 		- An array of sprites that represents all the enemies in the game.
		blood 			- A sprite that represents player's death animation.
		life	 		- A life that represents the number of life/soldiers the player has left
		soundCtrl 		- A sound object that controls the volume, pan and pitch of music/sound
		playerDeath 	- A sample object that represents the sonund when the player dies
	Return:
		N/A
*/
void enemyCollision (sprites * player, sprites * enemies[MAX_ENEMIES], sprites * blood, int & life, 
					 sound soundCtrl, SAMPLE * playerDeath) {
	// Determine the center of the player's sprite in the x/y coordinates
	int x = player -> getX () + player-> getWidth ()/2;
	int y = player -> getY () + player-> getHeight ()/2;

	for (int n = 0; n < MAX_ENEMIES; n++) {
		if (enemies[n] -> getAlive ()) {	// If enemy is alive
			
			//Determines the enemies bounding box
			int x1 = enemies[n] -> getX();
			int y1 = enemies[n] -> getY ();
			int x2 = x1 + enemies[n] -> getWidth ();
			int y2 = y1 + enemies[n] -> getHeight ();

			if (enemies[n] -> inside (x, y, x1, y1, x2, y2)) { // Check to see if player is inside enemy's bounding box.
				enemies[n] -> setAlive (0);			// Kill enemy
				blood -> setAlive (1);				// Start player's death animation
				blood -> setX (player -> getX());	// Set at player's position
				blood -> setY (player -> getY());
				life--;								// Player lose a life/soldier
				// Plays death sound
				play_sample(playerDeath, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE); // Plays intro Music
			}
		}
	}
}
