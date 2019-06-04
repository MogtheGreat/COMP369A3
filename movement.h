/*
Title: movement.h
Description: Deals with sprite movement and collision with environment.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"
#include "level.h"
#include "weapons.h"

#define DEBUG2 0

void playerInput (sprites * player, sprites * bullets[MAX_BULLETS], Levels lvl, 
				  bool & music, bool & pause, sound sndCtrl, SAMPLE * shoot,
				  SAMPLE * jump);

void enemyPhysic (sprites * enemies[MAX_ENEMIES], Levels lvl);

void handleJump (sprites * spr, Levels lvl);

void handleWall (sprites * spr, Levels lvl, int oldX, int oldY);

void onScreen (sprites * player, int width);

#endif