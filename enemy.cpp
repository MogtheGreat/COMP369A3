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
			enemies[n] -> setX (rand() % 250 + 350);
			enemies[n] -> setY (100);
		}
	}
}
