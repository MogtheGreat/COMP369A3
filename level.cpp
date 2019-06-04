/*
Title: level.cpp
Description: An object that represents a game level. Holds all behavior and functionality
			 to run a game level.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/

#include "level.h"

using namespace std;  

/****************SCREEN Functions****************/

/*
	Sets the initial 'global' variables for the level. Originally
	was initializing global variable until they were encased in a
	class.

	Param:
		mapx 		- x offset for the screen
		mapy 		- y offset for the screen
		numLevels 	- Number of levels for the game.
	Return:
		N/A
*/
void Levels::initGlobals (int mapx, int mapy, int numLevels) {
	if (DEBUG)
		cout << "Initializing global variables" << endl;

	mapxoff = mapx;
	mapyoff = mapy;
	curLvl = 0;
	numLvls = numLevels;

	if (DEBUG) {
		cout << "mapxoff: " << mapxoff << endl;
		cout << "mapyoff: " << mapyoff << endl;
		cout << "curLvl: " << curLvl << endl;
		cout << "numLvls: " << numLevels << endl;
	}
}

/*
	Resets the camera postion to the desired position.

	Param:
		mapx 		- x offset for the screen
		mapy 		- y offset for the screen
	Return:
		N/A
*/
void Levels::resetCameraPos (int mapx, int mapy) {
	if (DEBUG)
		cout << "Resetting the map camera position..." << endl;

	mapxoff = mapx;
	mapyoff = mapyoff;

	if (DEBUG) {
		cout << "mapxoff: " << mapxoff << endl;
		cout << "mapyoff: " << mapyoff << endl;
	}
}

/****************Environment Functions****************/

/*
	Loads a level into mappyal from a list of levels.

	Param:
		list 	- A list containing the name of all the map files
	Return:
		0 if can't find a vlid map file
		1 if everything is okay.
*/
int Levels::loadLevel (vector<string> list) {
	if (MapLoad ((char *) list[curLvl].c_str()) != 0) {
		set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
		allegro_message ("Can't find a valid .fmp file.");
		return 0;
	}
	else
		return 1;
}

/*
	Draws the map to the screen.

	Param:
		buffer		- the bitmap being drawn to.
		width 		- How wide the screen is
		height 		- How tall the screen is
	Return:
		N/A
*/
void Levels::drawLevel (BITMAP * buffer, int width, int height) {
	if (DEBUG)
		cout << "Drawing background and foreground to buffer..." << endl;

	//draw the background tiles
	MapDrawBG(buffer, mapxoff, mapyoff, 0, 0, width-1, height-1);

	//draw foreground tiles
	MapDrawFG(buffer, mapxoff, mapyoff, 0, 0, width-1, height-1, 0);
}

/***************Boolean Functions***************/

/*
	Checks for collision between a sprite and a tile.

	Param:
		x 		- sprite's x position
		y 		- sprite's y position
	Return:
		1 if collision. 0 otherwise
*/
int Levels::collided (int x, int y) {
	BLKSTR * blockdata;
	blockdata = MapGetBlock ((x + mapxoff)/mapblockwidth, (y + mapyoff)/mapblockheight);

	if (DEBUG) {
		cout << "mapxoff: " << mapxoff << endl;
		cout << "mapyoff: " << mapyoff << endl;
		cout << "x: " << x <<  endl;
		cout << "y: " << y << endl;
		cout << "blockdata -> tl: " << (int) blockdata -> tl << endl;
		cout << "blockdata -> tr: " << (int) blockdata -> tr << endl;
		cout << "blockdata -> bl: " << (int) blockdata -> bl << endl;
		cout << "blockdata -> br: " << (int) blockdata -> br << endl;
		cout << "blockdata -> user1: " << blockdata -> user1 << endl;
	}

	if ((blockdata -> tl >= 1) || (blockdata -> tr >= 1))
		return 1;
	else
		return 0;
}

/*
	Checks for collision with between a sprite and a ceiling tile.

	Param:
		x 		- sprite's x position
		y 		- sprite's y position
	Return:
		1 if collision. 0 otherwise
*/
int Levels :: hitCeiling (int x, int y) {
	BLKSTR * blockdata;
	blockdata = MapGetBlock ((x + mapxoff)/mapblockwidth, (y + mapyoff)/mapblockheight);
	if ((((int)blockdata -> tl) >= 1) || (((int)blockdata -> tr) >= 1))
		return 1;
	else
		return 0;
}

/*
	Checks to see if the player has reached the end of the level.

	Param:
		playerX 		- player's x position
		screenWidth 	- How wide the screen is
	Return:
		1 if player is at the end. 0 otherwise.
*/
int Levels :: levelEnd (int playerX, int screenWidth) {
	if (mapxoff >= ((mapblockwidth * mapwidth) - 700)){
		if (playerX > screenWidth)
			return 1;
	}

	return 0;
}

/*
	Checks to see if there is another level
	Param:
		N/A
	Return:
		0 if yes. 1 Otherwise
*/
int Levels :: anotherLevel () {
	if (curLvl < numLvls)
		return 0;
	return 1;
}

/*
	Checks to see if the game is done.
	Param:
		N/A
	Return:
		1 if yes. 0 Otherwise
*/
int Levels :: doneGame () {
	if (curLvl >= numLvls)
		return 1;
	return 0;
}

/***************GET fuctutions***************/
// Get functions return one of the variables from the object

int Levels :: getMapXOff () {
	return mapxoff;
}

int Levels :: getMapYOff () {
	return mapyoff;
}

int Levels :: getCurLvl () {
	return curLvl;
}

int Levels :: getNumLvls () {
	return numLvls;
}

/******************SET Functions******************/
// Set functions changes the value of one of the variables in the object

void Levels :: setMapXOff (int setTo) {
	mapxoff = setTo;
}

void Levels :: setMapYOff (int setTo) {
	mapyoff = setTo;
}

void Levels :: setCurLvl (int setTo) {
	curLvl = setTo;
}

void Levels :: setNumLvls (int setTo) {
	numLvls = setTo;
}

/******************ADD To functions******************/

/*
	Adjust the y Scroll of the game. NOT USED.

	Param:
		playerY 		- player's Y position
		playerHeight 	- player sprite's height
	Return:
		N/A
*/
void Levels :: adjustYScroll (int playerY, int playerHeight) {
	static int oldY = mapyoff;
	if (playerY < 284)
		mapyoff -= 1;
	else if (mapyoff < oldY)
		mapyoff += 2;
	else if (mapyoff > oldY)
		mapyoff -= 1;
}

/*
	Shift the screen to the right.

	Param:
		N/A
	Return:
		1 if not at the end of the level.
		0 if at the end.
*/
int Levels::shiftScreen () {
	if (DEBUG) cout << "Shift screen to left." << endl;
	if (mapxoff < ((mapblockwidth * mapwidth) - 675)){
	 	mapxoff += 4;
	 	return 1;
	}
	if (DEBUG) cout << "mapxoff: " << mapxoff << endl;
	return 0;
}

/*
	Increment the curLvl variable.
	Param:
		N/A
	Return:
		N/A
*/
void Levels :: incrementCurLvl() {
	curLvl++;
}