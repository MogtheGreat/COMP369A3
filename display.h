#ifndef DISPLAY_H
#define DISPLAY_H
#include <allegro.h>
#include "sound.h"

#define PATHFONT "Resources/Font/"
#define PATHBACK "Resources/Background/"
#define BLACK makecol(0,0,0)
#define WHITE makecol (255, 255, 255)
#define BLUE makecol (0,0,205)
#define RED makecol (128,0,0)

void displayStart (BITMAP * dest, int screenWidth, int screenHeight);

void displayLevelStart (BITMAP * dest, FONT * statusFont, int screenWidth, int screenHeight, int curLevel);

void displayStatus (BITMAP * dest, FONT * statusFont, FONT * optionFont, int screenWidth, int life, int score, bool music);

void displayHelp (BITMAP * dest, FONT * statusFont, FONT * optionFont, int screenWidth, int screenHeight);

void displayLevelEnd (BITMAP * dest, FONT * statusFont, int screenWidth, int screenHeight, int curLevel, int & score);

void displayEnd (BITMAP * dest, int score, int & highScore, int life, int screenWidth, int screenHeight);

#endif