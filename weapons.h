#ifndef WEAPONS_H
#define WEAPONS_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"
#include "sound.h"

#define WEAPONLOC 21 	// Adjust position of bullets so coming from gun on sprite

void fireatenemy (sprites * bullets[MAX_BULLETS], int x, int y);

void updatebullets (BITMAP * buffer, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES], sprites * explosions [MAX_EXPLOSIONS], int mapWidth, int & score, sound sndCtrl);

void updatebullet (sprites * bullet, sprites * enemies[MAX_ENEMIES], sprites * explosions [MAX_EXPLOSIONS], int mapWidth, int & score, sound sndCtrl);

void startExplosion (sprites * explosions [MAX_EXPLOSIONS], int x, int y);

void updateExplosion (BITMAP * buffer, sprites * explosions [MAX_EXPLOSIONS], sprites * blood);

#endif