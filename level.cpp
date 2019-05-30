#include "level.h"

using namespace std;  

void Levels::initGlobals (int mapx, int mapy, int numLevels) {
	if (debug)
		cout << "Initializing global variables" << endl;

	mapxoff = mapx;
	mapyoff = mapy;
	curLvl = 0;
	numLvls = numLevels;

	if (debug) {
		cout << "mapxoff: " << mapxoff << endl;
		cout << "mapyoff: " << mapyoff << endl;
		cout << "curLvl: " << curLvl << endl;
		cout << "numLvls: " << numLevels << endl;
	}
}

void Levels::resetCameraPos (int mapx, int mapy) {
	if (debug)
		cout << "Resetting the map camera position..." << endl;

	mapxoff = mapx;
	mapyoff = mapyoff;

	if (debug) {
		cout << "mapxoff: " << mapxoff << endl;
		cout << "mapyoff: " << mapyoff << endl;
	}
}

int Levels::loadLevel (vector<string> list) {
	if (MapLoad ((char *) list[curLvl].c_str()) != 0) {
		set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
		allegro_message ("Can't find a valid .fmp file.");
		return 1;
	}
	else
		return 0;
}

void Levels::drawLevel (BITMAP * buffer, int width, int height) {
	if (debug)
		cout << "Drawing background and foreground to buffer..." << endl;

	//draw the background tiles
	MapDrawBG(buffer, mapxoff, mapyoff, 0, 0, width-1, height-1);

	//draw foreground tiles
	MapDrawFG(buffer, mapxoff, mapyoff, 0, 0, width-1, height-1, 0);
}

void Levels::shiftScreen () {
	if (debug) cout << "Shift screen to left." << endl;
	if (mapxoff < ((mapblockwidth * mapwidth) - 575)) mapxoff += 6;
	if (debug) cout << "mapxoff: " << mapxoff << endl;
}

int Levels :: getMapXOff () {
	return mapxoff;
}

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

	if ((blockdata -> tl >= 1) || (blockdata -> bl >= 1))
		return 1;
	else
		return 0;
	//return blockdata -> tl;
}

void Levels :: adjustYScroll (int playerY, int playerHeight) {

}
