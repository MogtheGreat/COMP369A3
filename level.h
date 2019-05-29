#ifndef LEVEL_H
#define LEVEL_H
#include <allegro.h>
#include <iostream>
#include <vector>
#include <string>
#include "mappyal.h"

//Load next level
//Check to see if last lvl
//Load Game Over (lost) screen
//Load Game Over (won) screen
//Collision?

class Levels {
	int mapxoff;
	int mapyoff;
	int curLvl;
	int numLvls;
	int debug;
public:
	Levels (): mapxoff (0), mapyoff (0), curLvl (0), numLvls (0), debug (0) {}
	Levels (int dbug) : mapxoff (0), mapyoff (0), curLvl (0), numLvls (0), debug (dbug) {}
	void initGlobals (int mapx, int mapy, int numLvls);
	void resetCameraPos (int mapx, int mapy);
	int loadLevel (std::vector<std::string> list);
	void drawLevel (BITMAP * buffer, int width, int height);
	void shiftScreen ();
	int collided (int x, int y);
};

#endif
