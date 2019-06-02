#ifndef ENEMY_H
#define ENEMY_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"

void updateEnemies (BITMAP * buffer, sprites * enemies[MAX_ENEMIES], int mapWidth, int mapHeight);

void enemyCollision (sprites * player, sprites * enemies[MAX_ENEMIES], sprites * blood, int & life);

#endif
