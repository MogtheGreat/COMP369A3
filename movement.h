#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <allegro.h>
#include <iostream>
#include "sprites.h"
#include "level.h"
#include "weapons.h"

#define DEBUG2 0

void playerInput (sprites * player, sprites * bullets[MAX_BULLETS], Levels lvl);

void handleJump (sprites * spr, Levels lvl);

void handleWall (sprites * spr, Levels lvl, int oldX, int oldY);

#endif