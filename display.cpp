/*
Title: display.cpp
Description: Deals with displaying info to player, display help module, start screen and game over screen.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#include "display.h"

/*
	Display legal notice that I do not own anything from the Warhammer 40K intellicual property. Also
	display a note about satire. This is the result of the rise of alt-rights supporting/endorsing some of the ideals
	expressed in the franchise. In other words it made me slightly uncomfortable. So I wrote this warning
	just to cover myself.
	Param:
		N/A
	Return:
		N/A
*/
void displayDisclaimer () {
	textprintf_ex (screen, font, 300, 0, WHITE, -1, "Disclaimer");
	textprintf_ex (screen, font, 0, 10, WHITE, -1, "The Ultramarines and Tyranids are part of the Warhammer 40K brand. The author of this game");
	textprintf_ex (screen, font, 0, 20, WHITE, -1,"does not claim any right to these intellicual property. As such this game can not be use");
	textprintf_ex (screen, font, 0, 30, WHITE, -1, "to gain montarty profit. This game is designed strictly for entertainment and nothing else.");

	textprintf_ex (screen, font, 0, 70, WHITE, -1, "It should also be notice that the views expressed in the Warhammer 40K universe are to be");
	textprintf_ex (screen, font, 0, 80, WHITE, -1, "considered satire and does not express the opinion of the author of this game.");
	textprintf_ex (screen, font, 0, 110, WHITE, -1, "If you agree, press any key to continue. Otherwise press ESC twice to exit.");
}

/*
	Displays the start page. Contains the story and the instructions for the game.
	Param:
		dest 		 - A bitmap that is to be drawn on.
		screenWidth  - An integer that represens how wide the screen is
		screenHeight - An integer that represents how tall the screen is
	Return:
		N/A
*/
void displayStart (BITMAP * dest, int screenWidth, int screenHeight) {
	PALETTE palette;	// Color palette for fonts.
	//Load the resources for the start page. 
	FONT * titleFont = load_font (PATHFONT"Space Marine (36).pcx", palette, NULL);
	FONT * infoFont = load_font (PATHFONT"GiantRobotArmy Med (18).pcx", palette, NULL);
	FONT * optionFont = load_font (PATHFONT"Space Marine (24).pcx", palette, NULL);
	FONT * copyRight = load_font (PATHFONT"TimesNewRoman.pcx", palette, NULL);
	BITMAP * background = load_bitmap (PATHBACK"start.bmp", NULL);

	// Display background if it is found.
	if (background)
		blit (background, dest, 0,0,0,0, screenWidth, screenHeight);

	textprintf_ex (dest, titleFont, 0, 0, BLUE, -1, "Battle Of Ichar IV"); //Display the Title
	textprintf_ex (dest, copyRight, screenWidth/3, 30, BLUE, -1, "copy righted 2019"); // Copy right for the game

	// Display the story for the game
	textprintf_ex (dest, infoFont, 0, 50, BLUE, -1, "The Ultramarines have been called on to put down a rebellion");
	textprintf_ex (dest, infoFont, 0, 75, BLUE, -1, "on the planet Ichar IV.");
	textprintf_ex (dest, infoFont, 0, 100, BLUE, -1, "This rebellion is the result of a genestrealer cult preparing the");
	textprintf_ex (dest, infoFont, 0, 125, BLUE, -1, "world for the invasion of the Tynaid's Hive Fleet Kraken.");
	textprintf_ex (dest, infoFont, 0, 150, BLUE, -1, "Fight off the hord of Tyranids scrum while heading towards");
	textprintf_ex (dest, infoFont, 0, 175, BLUE, -1, "the Hive ship in order end the threat.");

	//Display the instructions for the game
	textprintf_ex (dest, infoFont, 50, 200, BLUE, -1, "Press left or right arrow key to move left or right.");
	textprintf_ex (dest, infoFont, 50, 225, BLUE, -1, "Press the up arrow key to jump.");
	textprintf_ex (dest, infoFont, 50, 250, BLUE, -1, "Press space bar to shoot.");
	textprintf_ex (dest, optionFont, 0, screenHeight-35, RED, -1, "PRESS ANY KEY TO CONTINUE");

	//Release the resoucres for the start page
	destroy_font (titleFont);
	destroy_font (infoFont);
	destroy_font (optionFont);
	destroy_font (copyRight);
	destroy_bitmap (background);
}

/*
	Display the start page for the level.
	Param:
		dest 		 - A bitmap that is to be drawn on.
		statusFont 	 - A font object that represents the font used for displaying status
		screenWidth  - An integer that represens how wide the screen is
		screenHeight - An integer that represents how tall the screen is
*/
void displayLevelStart (BITMAP * dest, FONT * statusFont, int screenWidth, int screenHeight, int curLevel) {
	//Creates the background for the level start page.
	rectfill(screen, 0, 0, screenWidth, screenHeight, BLACK);
	//Creates the border
	for (int i = 0; i <= 4; i++)
		rect (screen, i, i, screenWidth-i, screenHeight - i, BLUE);

	//Check to make sure there is a font to use. 
	FONT *& holdStatus = statusFont;
	if (!statusFont)
		holdStatus = font;

	//Display level introduction
	textprintf_ex (dest, holdStatus, screenWidth/3, screenHeight/3, BLUE, -1, "LEVEL: %d", curLevel);
	//Wait a second
	rest (1000);
}

/*
	Displays the player's status during main gameplay. Display life, score and menu option.
	Param:
		dest 		 - A bitmap that is to be drawn on.
		statusFont 	 - A font object that represents the font used for displaying status
		optionFont 	 - A font object that represents a font to be used for displaying gameplay option.
		screenWidth  - An integer that represens how wide the screen is
		life 		 - An integer that represents how many lives/soldiers the player has left
		score 		 - An integer that represents the player's current score.
		music 		 - A boolean that represent whatever the music is on or off
	Return:
		N/A
*/
void displayStatus (BITMAP * dest, FONT * statusFont, FONT * optionFont, int screenWidth, int life, int score, bool music) {
	// Check to make sure there is a font to use.
	FONT *& hold = statusFont;
	if (statusFont != NULL)
		hold = statusFont;
	else
		hold = font;

	// Display the amount of life on the screen.
	if (life >= 0)
		textprintf_ex (dest, hold, 0, 0, 15, -1, "Life: %d", life);
	textprintf_ex (dest, hold, 225, 0, 15, -1, "Score: %d", score); // Display the current score

	// Check to make sure there is a font to use.
	if (optionFont != NULL)
		hold = optionFont;
	else
		hold = font;

	textprintf_ex (dest, hold, screenWidth - 100, 0, 15, -1, "Help: crtl-h"); // Display help menu option

	// Display the music status
	if (music)
		textprintf_ex (dest, hold, screenWidth - 100, 10, 15, -1, "Music: ON");
	else
		textprintf_ex (dest, hold, screenWidth - 100, 10, 15, -1, "Music: OFF");
}

/*
	Displays the help module to the player. Contains instructions and objective.

	Param:
		dest 		 - A bitmap that is to be drawn on.
		statusFont 	 - A font object that represents the font used for displaying status
		optionFont 	 - A font object that represents a font to be used for displaying gameplay option.
		screenWidth  - An integer that represens how wide the screen is
		screenHeight - An integer that represents how tall the screen is
	Return:
		N/A		
*/
void displayHelp (BITMAP * dest, FONT * statusFont, FONT * optionFont, int screenWidth, int screenHeight) {
	// Creates a help "window" to be drawn over the game
	rectfill(dest, 0, screenHeight/5, screenWidth, screenHeight - 200, BLACK);
	rect (dest, 1, screenHeight/5+1, screenWidth-1, screenHeight - 199, BLUE);

	// get the starting position to begin writing
	int xStart = 5;
	int yStart = screenHeight/5+5;
	
	// Check to make sure there is a font to use.
	FONT *& holdOption = optionFont;
	if (!optionFont)
		holdOption = font;
	FONT *& holdStatus = statusFont;
	if (!statusFont)
		holdStatus = font;

	// Dispaly the info to the screen within the help "window"
	textprintf_ex (dest, holdStatus, screenWidth/2, yStart+10, WHITE, -1, "HELP");
	textprintf_ex (dest, holdOption, xStart, yStart+40, WHITE, -1, "Press left/right arrow key to move left or right.");
	textprintf_ex (dest, holdOption, xStart, yStart+60, WHITE, -1, "Press up arrow key to jump.");
	textprintf_ex (dest, holdOption, xStart, yStart+80, WHITE, -1, "Press space bar to shoot.");
	textprintf_ex (dest, holdStatus, xStart, yStart+120, BLUE, -1, "LIFE: 20");
	textprintf_ex (dest, holdOption, xStart+200, yStart+140, WHITE, -1, " Represents how many soldiers you have left.");
	textprintf_ex (dest, holdOption, xStart, yStart +160, WHITE, -1, "Press crtl-m to turn music on or off");
	textprintf_ex (dest, holdOption, xStart, yStart + 180, WHITE, -1, "OBJECTIVE: reach the other end of the level.");
	textprintf_ex (dest, holdStatus, xStart, yStart+240, WHITE, -1, "PRESS ANY KEY TO CONTINUE");
}

/*
	Display the end of the level status, player's score, bonus point. Waits for players to press enter or ESC.

	Param:
		dest 		 - A bitmap that is to be drawn on.
		statusFont 	 - A font object that represents the font used for displaying status
		screenWidth  - An integer that represens how wide the screen is
		screenHeight - An integer that represents how tall the screen is
		curLevel 	 - An integer that represents the current level of the game
		score 		 - A reference to an integer that represents the player's current score
	Return:
		N/A
*/
void displayLevelEnd (BITMAP * dest, FONT * statusFont, int screenWidth, int screenHeight, int curLevel, int & score) {
	// Create the background and border
	rectfill(dest, 0, 0, screenWidth, screenHeight, BLACK);
	for (int i = 0; i <= 4; i++)
		rect (screen, i, i, screenWidth-i, screenHeight - i, BLUE);

	// Check to make sure there is a font to use.
	FONT *& holdStatus = statusFont;
	if (!statusFont)
		holdStatus = font;

	// Display info
	textprintf_ex (dest, holdStatus, screenWidth/3 - 50, screenHeight/3, BLUE, -1, "END LEVEL: %d", curLevel);
	textprintf_ex (dest, holdStatus, screenWidth/3 - 100, screenHeight/3 + 50, BLUE, -1, "Points: +1000");
	textprintf_ex (dest, holdStatus, screenWidth/3 - 100, screenHeight/3 + 150, BLUE, -1, "Score: %d", score);
	textprintf_ex (dest, holdStatus, screenWidth/3 - 200, screenHeight/3 + 300, BLUE, -1, "Press Enter to continue");

	readkey (); // clear input buffer
	while ((!key[KEY_ENTER]) && (!key[KEY_ESC])); // Wait for player to press any key
	readkey (); // clears input buffer
}

/*
	Display the end game screen. End game screen varies depending on the amound of life the players has.

	Param:
		dest 		 - A bitmap that is to be drawn on.
		score 		 - An integer that represents the player's current score.
		highScore 	 - A reference to an integer that represents the player's highest score
		life 		 - An integer that represents how many lives/soldiers the player has left
		screenWidth  - An integer that represens how wide the screen is
		screenHeight - An integer that represents how tall the screen is
	Return:
		N/A
*/
void displayEnd (BITMAP * dest, int score, int & highScore, int life, int screenWidth, int screenHeight) {
	PALETTE palette;	// Color palette for fonts.
	
	// These resources varies depending on the amount of life the players has
	BITMAP * background;
	FONT * title;

	// Loads font resources
	FONT * info = load_font (PATHFONT"GiantRobotArmy Med (24).pcx", palette, NULL);
	FONT * option = load_font (PATHFONT"GiantRobotArmy Med (18).pcx", palette, NULL);
	
	// Player has beaten the game
	if (life >= 0) {
		//Load the background image
		background = load_bitmap (PATHBACK"won.bmp", NULL);
		blit (background, dest, 0,0,0,0, screenWidth, screenHeight);
		
		//Loads the winning message
		title = load_font (PATHFONT"Space Marine (72).pcx", palette, NULL);
		textprintf_ex (dest, title, 50, 0, BLUE, -1, "VICTORY!");
		textprintf_ex (dest, info, 100, 270, BLUE, -1, "Tyranids scum has been eliminated !");
	}
	//Player has died
	else {
		//Load the background image
		background = load_bitmap (PATHBACK"lost.bmp", NULL);
		blit (background, dest, 0,0,0,0, screenWidth, screenHeight);
		
		//Loads the game over message
		title = load_font (PATHFONT"a dripping marker(72).pcx", palette, NULL);
		textprintf_ex (dest, title, 200, 0, RED, -1, "GAME OVER!");
		textprintf_ex (dest, info, 100, 270, RED, -1, "Tyranids have taken over the planet !");
	}

	// Save highscore if higher
	if (highScore < score)
		highScore = score;

	// display the player's status
	textprintf_ex (dest, info, screenWidth/3, 300, BLUE, -1, "Score: %d", score);
	textprintf_ex (dest, info, screenWidth/3, 340, BLUE, -1, "High Score: %d", score);
	textprintf_ex (dest, info, screenWidth/3, 380, BLUE, -1, "Life: %d", life);

	//Gives the player the option to exit the game or restart
	textprintf_ex (dest, option, screenWidth/5, screenHeight-50, BLUE, -1, "Press Y to RESET. Press ESC to EXIT.");

	// Release the resources
	if (background)
		destroy_bitmap (background);
	if (title)
		destroy_font (title);
	if (info)
		destroy_font (info);
}
