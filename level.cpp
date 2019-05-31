#include "level.h"

using namespace std;  

/*SCREEN Functions*/

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

/*Environment Functions*/

int Levels::loadLevel (vector<string> list) {
	if (MapLoad ((char *) list[curLvl].c_str()) != 0) {
		set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
		allegro_message ("Can't find a valid .fmp file.");
		return 0;
	}
	else
		return 1;
}

void Levels::drawLevel (BITMAP * buffer, int width, int height) {
	if (DEBUG)
		cout << "Drawing background and foreground to buffer..." << endl;

	//draw the background tiles
	MapDrawBG(buffer, mapxoff, mapyoff, 0, 0, width-1, height-1);

	//draw foreground tiles
	MapDrawFG(buffer, mapxoff, mapyoff, 0, 0, width-1, height-1, 0);
}

/*Environment Physic Functions*/

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

	if ((blockdata -> tl >= 1) || (blockdata -> bl >= 1) || (blockdata -> br >= 1))
		return 1;
	else
		return 0;
}


/******GET Functions******/

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

/*****SET Functions*****/

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

/*****ADD TO Functions*****/

void Levels :: adjustYScroll (int playerY, int playerHeight) {
	static int oldY = mapyoff;
	if (playerY < 284)
		mapyoff -= 1; // mapyoff - ((284 - abs(playerY))/50);
	else if (mapyoff < oldY)
		mapyoff += 2;
	else if (mapyoff > oldY)
		mapyoff -= 1;
}

void Levels::shiftScreen () {
	if (DEBUG) cout << "Shift screen to left." << endl;
	if (mapxoff < ((mapblockwidth * mapwidth) - 575)) mapxoff += 4;
	if (DEBUG) cout << "mapxoff: " << mapxoff << endl;
}
