#ifndef LOAD_H
#define LOAD_H
#include <allegro.h>
#include <iostream>
#include <dirent.h>
#include <string>
#include <vector>
#include "sprites.h"

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 600
#define PATH "Resources/Map/"

int initialize ();

std::vector <std::string> getLvls ();

int initSprite (sprites *& player, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES], sprites * explosions [MAX_EXPLOSIONS]);

#endif