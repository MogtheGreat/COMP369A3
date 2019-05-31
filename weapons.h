#ifndef WEAPONS_H
#define WEAPONS_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"

#define WEAPONLOC 21 	// Adjust position of bullets so coming from gun on sprite

void fireatenemy (sprites * bullets[MAX_BULLETS], int x, int y);

void updatebullets (BITMAP * buffer, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES], int mapWidth);

void updatebullet (sprites * bullet, sprites * enemies[MAX_ENEMIES], int mapWidth);

#endif