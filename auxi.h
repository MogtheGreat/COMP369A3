#ifndef AUXI_H
#define AUXI_H
#include <allegro.h>
#include <iostream>
#include <string.h>
#include <string>
#include <dirent.h>
#include <vector>

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 448
#define PATH "Resources/Map/"

int checkDebug (int argc, char * argv[]);

int initialize ();

std::vector <std::string> getLvls ();

#endif