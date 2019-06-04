/*
Title: weapons.h
Description: Deals with weapon sprites behavoir and collision. 
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#ifndef WEAPONS_H
#define WEAPONS_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"
#include "sound.h"
#include "level.h"

#define WEAPONLOC 21 	// Adjust position of bullets so coming from gun on sprite

void fireatenemy (sprites * bullets[MAX_BULLETS], int x, int y);

void updatebullets (BITMAP * buffer, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES], 
					sprites * explosions [MAX_EXPLOSIONS], int mapWidth, int & score, sound sndCtrl, 
					SAMPLE * alienDeath, Levels lvl);

void updatebullet (sprites * bullet, sprites * enemies[MAX_ENEMIES], sprites * explosions [MAX_EXPLOSIONS], 
				   int mapWidth, int & score, sound sndCtrl, SAMPLE * alienDeath, Levels lvl);

void startExplosion (sprites * explosions [MAX_EXPLOSIONS], int x, int y);

void updateExplosion (BITMAP * buffer, sprites * explosions [MAX_EXPLOSIONS], sprites * blood);

#endif