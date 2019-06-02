#include "enemy.h"

using namespace std;

void updateEnemies (BITMAP * buffer, sprites * enemies[MAX_ENEMIES], int mapWidth, int mapHeight) {
	// update/draw alien enemies
	for (int n = 0; n < MAX_ENEMIES; n++) {
		if (enemies[n] -> getAlive ()) {
			enemies[n] -> moveSprite (enemies[n] -> getXSpeed (), enemies[n] -> getYSpeed ());
			enemies[n] -> updateAnimation();

			int x = enemies[n] -> getX ();
			int y = enemies[n] -> getY();

			if (!((x < -(enemies[n]-> getWidth())) || (x > mapWidth) || (y < 0) || (y > mapHeight))) {
				 enemies[n] -> drawframe (buffer);
			}
			else
				enemies[n] -> setAlive (0);
		}
		else {
			enemies[n] -> setAlive (1);
			enemies[n] -> setX (rand() % 450 + 350);
			enemies[n] -> setY (150);
		}
	}
}

void enemyCollision (sprites * player, sprites * enemies[MAX_ENEMIES], sprites * blood, int & life) {
	int x = player -> getX () + player-> getWidth ()/2;
	int y = player -> getY () + player-> getHeight ()/2;

	for (int n = 0; n < MAX_ENEMIES; n++) {
		if (enemies[n] -> getAlive ()) {
			
			int x1 = enemies[n] -> getX();
			int y1 = enemies[n] -> getY ();
			int x2 = x1 + enemies[n] -> getWidth ();
			int y2 = y1 + enemies[n] -> getHeight ();

			if (enemies[n] -> inside (x, y, x1, y1, x2, y2)) {
				enemies[n] -> setAlive (0);
				blood -> setAlive (1);
				blood -> setX (player -> getX());
				blood -> setY (player -> getY());
				life--;
			}
		}
	}
}
