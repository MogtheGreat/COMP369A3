/*
Title: main.cpp
Description: Plays the game Battle Of Ichar IV which is a platform/shooter game that can be played on the 
			 keyboard.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
/*
 DOCUMENTATION
 Program Purpose:
 	To play a platform/shooter game called Battle Of Ichar IV. The player  must fight/avoid hord of aliens
 	as they try to reach the end of the level. They have a set number of lives in order to complete all levels.

  Compile (assuming running on Linux):
 	gcc -Wall main.cpp sprites.cpp load.cpp mappyal.c level.cpp movement.cpp weapons.cpp enemy.cpp display.cpp sound.cpp `pkg-config --cflags --libs allegro` -lstdc++ -o BattleOfIcharIV
 	or
	make
 Execution (assuming running on Linux):
 	./BattleOfIcharIV
 */
#include "sprites.h"
#include "load.h"
#include "level.h"
#include "movement.h"
#include "weapons.h"
#include "enemy.h"
#include "display.h"
#include "sound.h"

using namespace std;

//Timer variables.
volatile int counter;
volatile int ticks;
volatile int framerate;

//calculate framerate every second
void timer1 (void) {
	counter++;
	framerate = ticks;
	ticks = 0;
	rest(2);
}
END_OF_FUNCTION (timer1)

/*
	Using command line input, determines whatever to
	activate debug mode or normal play.
*/
int checkDebug (int argc, char * argv[]) {
	if (argc == 1) return 0; // Only one argument
	else if (strcmp(argv[1],"-d") == 0) return 1; // if second argument is -d
	return 0;
}


int main (int argc, char * argv[])  {
	int debug = checkDebug (argc, argv);

	//Initialize allegro library, window, timer, and sound system
	if (initialize()) {
		return 1;
	}

	// Create the sprites for the game
	sprites * player;
	sprites * bullets[MAX_BULLETS];
	sprites * enemies[MAX_ENEMIES];
	sprites * explosions [MAX_EXPLOSIONS];
	sprites * blood;
	if (!(initSprite (player, bullets, enemies, explosions, blood))) // If one the sprites images does not load, exit the game
		return 1;

	//Main Gameplay Variables
	bool gameOver = false;
	bool levelOver = false;
	int life = 30;
	int score = 0;
	int highscore = 0;
	bool pause = false;
	bool music = true;
	bool once = false;
	Levels lvl;		//Deals with level environment and scrolling

	//Initialize Fonts for Game
	PALETTE palette;	// Color palette for fonts.
	FONT * statusFont = load_font (PATHFONT"Space Marine (24).pcx", palette, NULL);
	FONT * optionFont = load_font (PATHFONT"COMPUTER Robot (14).pcx", palette, NULL);

	//Loads the sound effects and music
	SAMPLE * introMusic = load_sample (PATHMUSIC"Two Steps From Hell - Protectors of the Earth.wav");
	SAMPLE * mainMusic = load_sample(PATHMUSIC"Strength of a Thousand Men - Two Steps from Hell .wav");
	SAMPLE * badEnd = load_sample (PATHMUSIC"Warhammer 40,000 Eternal Crusade Soundtrack Tyranids - Theme.wav");
	SAMPLE * goodEnd = load_sample (PATHMUSIC"Audiomachine - Dauntless (Epic Powerful Heroic Music).wav");
	SAMPLE * alienDeath = load_sample (PATHSOUND"Bomb_Exploding.wav");
	SAMPLE * shoot = load_sample (PATHSOUND"AK47 Assault Rifle.wav");
	SAMPLE * jump = load_sample (PATHSOUND"Jump.wav");
	SAMPLE * playerDeath = load_sample (PATHSOUND"Cracking Chest Open.wav");

	vector <string> mapList = getLvls (); //Loads names of all available map levels from folder
	lvl.initGlobals (0, HEIGHT/8 + 10, mapList.size()); //Initializes the levels global variables
	sound soundCtrl; // Controls volume, pitch and pan for music and sound effects
	BITMAP * buffer = create_bitmap (WIDTH, HEIGHT); // Set up secondary buffer
	clear (buffer);

	//identify variables used by interupt function
	LOCK_VARIABLE (counter);
	LOCK_VARIABLE (framerate);
	LOCK_VARIABLE (ticks);
	LOCK_FUNCTION (timer1);

	//create new interrupt handler
	install_int (timer1, 1000);

	displayDisclaimer (); // display Copyright and statire notice.
	while (!keypressed()); // Wait for player to press any key
	readkey(); // clears buffer

	displayStart (screen, WIDTH-1, HEIGHT-1); // Displays the opening screen
	// Plays intro music
	play_sample(introMusic, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE); // Plays intro Music
	while (!keypressed()); // Wait for player to press any key
	readkey(); // clears buffer
	stop_sample(introMusic); // Stops sample from playing

	//Main game loop
	while (!key[KEY_ESC]){
		if (debug)
			cout << "Starting main game loop." << endl;
	
		 if (!gameOver)
			play_sample(mainMusic, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), TRUE); // Plays main game Music
	
		//Main Game Play Branch
		if (!gameOver && (!key[KEY_ESC])) {
			lvl.resetCameraPos (0, 75); // Resets camera to the beginning of the game
			player -> setX(80); // Resets players position
			if (!lvl.loadLevel (mapList))	// Loads next level if there is one.
				return 1;

			displayLevelStart (screen, statusFont, WIDTH-1, HEIGHT-1, lvl. getCurLvl()+1);

			//Gameplay loop
			while (!gameOver && !levelOver && (!key[KEY_ESC])) {
				if (!pause) {
					lvl.drawLevel (buffer, WIDTH, HEIGHT); // Draws environment to buffer
					player -> drawframe(buffer);	// Draws player's sprite
					
					// Gets player's inpute and move sprite accordingly
					playerInput (player, bullets, lvl, music, pause, soundCtrl, shoot, jump);
					onScreen (player, WIDTH - player -> getWidth()); // Keeps player on screen
				
					// Moves bullets and draws to buffer
					updatebullets (buffer, bullets, enemies, explosions, WIDTH-1, score, soundCtrl, alienDeath, lvl);
					updateEnemies (buffer, enemies, WIDTH-1, HEIGHT-1); // Moves enemies and draws to buffer
					updateExplosion (buffer, explosions, blood); //Moces the explosion sprites
				
					enemyPhysic (enemies, lvl);	// Allows enemies to interact with the environment
					enemyCollision (player, enemies, blood, life, soundCtrl, playerDeath); //Check to see if enemy has killed player

					displayStatus (buffer, statusFont, optionFont, WIDTH-1, life, score, music); // Display life and score

					//blit the double buffer 
					vsync();
					acquire_screen();
					blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
       				release_screen();

       				ticks++;
       				player -> incrementFireCount (); // Allows player to fire.
       				onScreen (player, WIDTH - player -> getWidth()); // Keeps player on screen
       				
       				//Scrolls the screen and ajust the player and enemy sprites
	       			if (lvl. shiftScreen ()) {
	       				player -> moveSprite (-2, 0);
	       				for (int n = 0; n < MAX_ENEMIES; n++) {
	       					enemies[n] -> moveSprite (-4,0);
	       				}
	       			}

	       			//Check for level End
	       			if (lvl.levelEnd (player -> getX(), WIDTH - player -> getWidth()))
	       				levelOver = true;
	       			if (life < 0) // Check for game over
	       				gameOver = true;
	       			
	       			//Determines if music should be on or off
	       			if (music)
	       				soundCtrl. musicOn ();
	       			else
	       				soundCtrl. musicOff ();
	       			// Adjust the main game music
	       			adjust_sample (introMusic, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE);
				}
				// Pauses the game and display help module
				else {
					displayHelp (screen, statusFont, optionFont, WIDTH-1, HEIGHT-1); // Displays the help module to the player
					while (!keypressed()); // Wait for player to press any key
					readkey (); // clears input buffer
					pause = false; // restart game
				}
			} // end of game loop
			
			if (debug)
				cout << "END OF LEVEL OR GAME" << endl;
			
			MapFreeMem (); // Frees the map
			
			// If game is not over and players have not exit game
			if ((!gameOver) && (!key[KEY_ESC])) {
				if (debug)
					cout << "END OF LEVEL" << endl;
				
				score += 1000; // Bonus points for player
				// Display the level end status
				displayLevelEnd (screen, statusFont, WIDTH-1, HEIGHT-1, lvl. getCurLvl()+1, score);
				lvl.incrementCurLvl(); // Get next Level

				if (debug) {
					cout << "curLvl: " << lvl. getCurLvl () << endl;
					cout << "lvl. anotherLevel (): " << lvl. anotherLevel () << endl;
				}

				//Checks to make sure there is another level
				if (!lvl. anotherLevel ()) {
					levelOver = false;

					if (debug)
						cout << "levelOver: " << levelOver << endl;
				}

				//If there is no more lvels, then game is over
				if (lvl. doneGame ()) {
					gameOver = true;

					if (debug)
						cout << "LAST LEVEL DONE! GAME OVER!" << endl;
				}
			}
		} // End of Main Gameplay Branch

		// Player's lost or have completed game.
		if ((gameOver) && (!key[KEY_ESC])) {
				if (debug)
					cout << "GAME OVER SCREEN!" << endl;

				stop_sample(mainMusic); // Stops sample from playing

				if (!once) {
					displayEnd (screen, score, highscore, life, WIDTH-1, HEIGHT-1); // Displays the end game screen
					
					//Plays the right music for the ending
					if (life >= 0)
						play_sample(goodEnd, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE); // Plays good End
					else
						play_sample(badEnd, soundCtrl. getVolume (), soundCtrl. getPan(), soundCtrl. getPitch(), FALSE); // Plays good End
					once = true;
				}

				// Players decides to restart the game
				if (key[KEY_Y]) {
					life = 30;
					score = 0;
					levelOver = false;
					gameOver = false;
					once = false;
					lvl. setCurLvl (0);

					if (life >= 0)
						stop_sample(goodEnd); // Stops sample from playing
					else
						stop_sample(badEnd); // Stops sample from playing
				}
			}

       	ticks++;
	} // End of main loop

	if (debug)
		cout << "FREEING STUFF!" << endl;

	//Frees sprites
	delete player;
	for (int n = 0; n < MAX_BULLETS; n++)
		delete bullets[n];
	for (int n = 0; n < MAX_ENEMIES; n++)
		delete enemies[n];
	for (int n = 0; n < MAX_EXPLOSIONS; n++)
		delete explosions[n];
	delete blood;
	
	//Frees font
	destroy_font (statusFont);
	destroy_font (optionFont);

	// Frees samples
	destroy_sample (introMusic);
	destroy_sample (mainMusic);
	destroy_sample (badEnd);
	destroy_sample (goodEnd);
	destroy_sample (alienDeath);
	destroy_sample (shoot);
	destroy_sample (jump);
	destroy_sample (playerDeath);

	allegro_exit ();
	return 0;
}
END_OF_MAIN()