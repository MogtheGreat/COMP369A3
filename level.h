/*
Title: level.h
Description: An object that represents a game level. Holds all behavior and functionality
			 to run a game level.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/

#ifndef LEVEL_H
#define LEVEL_H
#include <allegro.h>
#include <iostream>
#include <vector>
#include <string>
#include "mappyal.h"

#define DEBUG 0

class Levels {
	int mapxoff;
	int mapyoff;
	int curLvl;
	int numLvls;
public:
	Levels (): mapxoff (0), mapyoff (0), curLvl (0), numLvls (0) {}
	void initGlobals (int mapx, int mapy, int numLvls);
	void resetCameraPos (int mapx, int mapy);
	int loadLevel (std::vector<std::string> list);
	void drawLevel (BITMAP * buffer, int width, int height);
	
	//boolean functions
	int collided (int x, int y);
	int hitCeiling (int x, int y);
	int levelEnd (int playerX, int screenWidth);
	int anotherLevel ();
	int doneGame ();
	
	//GET Functions
	int getMapXOff ();
	int getMapYOff ();
	int getCurLvl ();
	int getNumLvls ();
	
	//SET Functions
	void setMapXOff (int setTo);
	void setMapYOff (int setTo);
	void setCurLvl (int setTo);
	void setNumLvls (int setTo);

	//ADD TO Functions
	void adjustYScroll (int playerY, int playerHeight);
	int shiftScreen ();
	void incrementCurLvl();
};

#endif
