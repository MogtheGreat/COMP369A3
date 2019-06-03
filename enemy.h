/*
Title: enemy.h
Description: Deals with enemy sprites behavoir and collision with player.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#ifndef ENEMY_H
#define ENEMY_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"
#include "sound.h"

void updateEnemies (BITMAP * buffer, sprites * enemies[MAX_ENEMIES], int mapWidth, int mapHeight);

void enemyCollision (sprites * player, sprites * enemies[MAX_ENEMIES], sprites * blood, int & life, 
					sound soundCtrl, SAMPLE * playerDeath);

#endif
