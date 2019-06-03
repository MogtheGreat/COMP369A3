#include "display.h"

void displayStart (BITMAP * dest, int screenWidth, int screenHeight) {
	PALETTE palette;	// Color palette for fonts.
	FONT * titleFont = load_font (PATHFONT"Space Marine (36).pcx", palette, NULL);
	FONT * infoFont = load_font (PATHFONT"GiantRobotArmy Med (18).pcx", palette, NULL);
	FONT * optionFont = load_font (PATHFONT"Space Marine (24).pcx", palette, NULL);
	FONT * copyRight = load_font (PATHFONT"TimesNewRoman.pcx", palette, NULL);
	BITMAP * background = load_bitmap (PATHBACK"start.bmp", NULL);

	if (background)
		blit (background, dest, 0,0,0,0, screenWidth, screenHeight);
	textprintf_ex (dest, titleFont, 0, 0, BLUE, -1, "Battle Of Ichar IV");
	textprintf_ex (dest, copyRight, screenWidth/3, 30, BLUE, -1, "copy righted 2019");
	textprintf_ex (dest, infoFont, 0, 50, BLUE, -1, "The Ultramarines have been called on to put down a rebellion");
	textprintf_ex (dest, infoFont, 0, 75, BLUE, -1, "on the planet Ichar IV.");
	textprintf_ex (dest, infoFont, 0, 100, BLUE, -1, "This rebellion is the result of a genestrealer cult preparing the");
	textprintf_ex (dest, infoFont, 0, 125, BLUE, -1, "world for the invasion of the Tynaid's Hive Fleet Kraken.");
	textprintf_ex (dest, infoFont, 0, 150, BLUE, -1, "Fight off the hord of Tyranids scrum while heading towards");
	textprintf_ex (dest, infoFont, 0, 175, BLUE, -1, "the Hive ship in order end the threat.");
	textprintf_ex (dest, infoFont, 50, 200, BLUE, -1, "Press left or right arrow key to move left or right.");
	textprintf_ex (dest, infoFont, 50, 225, BLUE, -1, "Press the up arrow key to jump.");
	textprintf_ex (dest, infoFont, 50, 250, BLUE, -1, "Press space bar to shoot.");

	textprintf_ex (dest, optionFont, 0, screenHeight-35, RED, -1, "PRESS ANY KEY TO CONTINUE");

	destroy_font (titleFont);
	destroy_font (infoFont);
	destroy_font (optionFont);
	destroy_font (copyRight);
	destroy_bitmap (background);
}

void displayLevelStart (BITMAP * dest, FONT * statusFont, int screenWidth, int screenHeight, int curLevel) {
	rectfill(screen, 0, 0, screenWidth, screenHeight, BLACK);
	rect (screen, 1, 1, screenWidth-1, screenHeight - 1, BLUE);
	rect (screen, 2, 2, screenWidth-2, screenHeight - 2, BLUE);
	rect (screen, 3, 3, screenWidth-3, screenHeight - 3, BLUE);

	FONT *& holdStatus = statusFont;
	if (!statusFont)
		holdStatus = font;

	textprintf_ex (dest, holdStatus, screenWidth/3, screenHeight/3, BLUE, -1, "LEVEL: %d", curLevel);

	rest (1000);
}

void displayStatus (BITMAP * dest, FONT * statusFont, FONT * optionFont, int screenWidth, int life, int score, bool music) {
	FONT *& hold = statusFont;
	if (statusFont != NULL)
		hold = statusFont;
	else
		hold = font;

	if (life >= 0)
		textprintf_ex (dest, hold, 0, 0, 15, -1, "Life: %d", life);
	textprintf_ex (dest, hold, 225, 0, 15, -1, "Score: %d", score);

	if (optionFont != NULL)
		hold = optionFont;
	else
		hold = font;

	textprintf_ex (dest, hold, screenWidth - 100, 0, 15, -1, "Help: crtl-h");

	if (music)
		textprintf_ex (dest, hold, screenWidth - 100, 10, 15, -1, "Music: ON");
	else
		textprintf_ex (dest, hold, screenWidth - 100, 10, 15, -1, "Music: OFF");
}

void displayHelp (BITMAP * dest, FONT * statusFont, FONT * optionFont, int screenWidth, int screenHeight) {
	rectfill(screen, 0, screenHeight/5, screenWidth, screenHeight - 200, BLACK);
	rect (screen, 1, screenHeight/5+1, screenWidth-1, screenHeight - 199, BLUE);

	int xStart = 5;
	int yStart = screenHeight/5+5;
	
	FONT *& holdOption = optionFont;
	if (!optionFont)
		holdOption = font;
	FONT *& holdStatus = statusFont;
	if (!statusFont)
		holdStatus = font;

	textprintf_ex (screen, holdStatus, screenWidth/2, yStart+10, WHITE, -1, "HELP");
	textprintf_ex (screen, holdOption, xStart, yStart+40, WHITE, -1, "Press left/right arrow key to move left or right.");
	textprintf_ex (screen, holdOption, xStart, yStart+60, WHITE, -1, "Press up arrow key to jump.");
	textprintf_ex (screen, holdOption, xStart, yStart+80, WHITE, -1, "Press space bar to shoot.");
	textprintf_ex (screen, holdStatus, xStart, yStart+120, BLUE, -1, "LIFE: 20");
	textprintf_ex (screen, holdOption, xStart+200, yStart+140, WHITE, -1, " Represents how many soldiers you have left.");
	textprintf_ex (screen, holdOption, xStart, yStart +160, WHITE, -1, "Press crtl-m to turn music on or off");
	textprintf_ex (screen, holdOption, xStart, yStart + 180, WHITE, -1, "OBJECTIVE: reach the other end of the level.");
	textprintf_ex (screen, holdStatus, xStart, yStart+240, WHITE, -1, "PRESS ANY KEY TO CONTINUE");
}

void displayLevelEnd (BITMAP * dest, FONT * statusFont, int screenWidth, int screenHeight, int curLevel, int & score) {
	rectfill(screen, 0, 0, screenWidth, screenHeight, BLACK);
	rect (screen, 1, 1, screenWidth-1, screenHeight - 1, BLUE);
	rect (screen, 2, 2, screenWidth-2, screenHeight - 2, BLUE);
	rect (screen, 3, 3, screenWidth-3, screenHeight - 3, BLUE);

	FONT *& holdStatus = statusFont;
	if (!statusFont)
		holdStatus = font;

	textprintf_ex (dest, holdStatus, screenWidth/3 - 50, screenHeight/3, BLUE, -1, "END LEVEL: %d", curLevel);
	textprintf_ex (dest, holdStatus, screenWidth/3 - 100, screenHeight/3 + 50, BLUE, -1, "Points: +1000");
	textprintf_ex (dest, holdStatus, screenWidth/3 - 100, screenHeight/3 + 150, BLUE, -1, "Score: %d", score);
	textprintf_ex (dest, holdStatus, screenWidth/3 - 200, screenHeight/3 + 300, BLUE, -1, "Press Enter to continue");

	readkey (); // clear input buffer
	while ((!key[KEY_ENTER]) && (!key[KEY_ESC])); // Wait for player to press any key
	readkey (); // clears input buffer
}

void displayEnd (BITMAP * dest, int score, int & highScore, int life, int screenWidth, int screenHeight) {
	PALETTE palette;	// Color palette for fonts.
	BITMAP * background;
	FONT * title;
	FONT * info = load_font (PATHFONT"GiantRobotArmy Med (24).pcx", palette, NULL);
	FONT * option = load_font (PATHFONT"GiantRobotArmy Med (18).pcx", palette, NULL);
	
	if (life >= 0) {
		background = load_bitmap (PATHBACK"won.bmp", NULL);
		blit (background, dest, 0,0,0,0, screenWidth, screenHeight);
		
		title = load_font (PATHFONT"Space Marine (72).pcx", palette, NULL);
		textprintf_ex (dest, title, 50, 0, BLUE, -1, "VICTORY!");
		textprintf_ex (dest, info, 100, 270, BLUE, -1, "Tyranids scum has been eliminated !");
	}
	else {
		background = load_bitmap (PATHBACK"lost.bmp", NULL);
		blit (background, dest, 0,0,0,0, screenWidth, screenHeight);
		
		title = load_font (PATHFONT"a dripping marker(72).pcx", palette, NULL);
		textprintf_ex (dest, title, 200, 0, RED, -1, "GAME OVER!");
		textprintf_ex (dest, info, 100, 270, RED, -1, "Tyranids have taken over the planet !");
	}

	if (highScore < score)
		highScore = score;

	textprintf_ex (dest, info, screenWidth/3, 300, BLUE, -1, "Score: %d", score);
	textprintf_ex (dest, info, screenWidth/3, 340, BLUE, -1, "High Score: %d", score);
	textprintf_ex (dest, info, screenWidth/3, 380, BLUE, -1, "Life: %d", life);

	textprintf_ex (dest, option, screenWidth/5, screenHeight-50, BLUE, -1, "Press Y to RESET. Press ESC to EXIT.");

	if (background)
		destroy_bitmap (background);
	if (title)
		destroy_font (title);
	if (info)
		destroy_font (info);
}