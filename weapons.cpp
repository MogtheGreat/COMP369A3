#include "weapons.h"

using namespace std;

void fireatenemy (sprites * bullets[MAX_BULLETS], int x, int y) {
	for (int n = 0; n < MAX_BULLETS; n++) {
		if (!(bullets[n] -> getAlive())) {
			bullets[n] -> setAlive (1);
			bullets[n] -> setX (x + WEAPONLOC);
			bullets[n] -> setY (y + WEAPONLOC);
			return;
		}
	}
}

void updatebullets (BITMAP * buffer, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES], int mapWidth) {
	for (int n = 0; n < MAX_BULLETS; n++) {
		if (bullets[n] -> getAlive()) {
			updatebullet (bullets[n], enemies, mapWidth);
			bullets[n] -> drawframe (buffer);
		}
	}
}

void updatebullet (sprites * bullet, sprites * enemies[MAX_ENEMIES], int mapWidth) {

	//move the bullet
	bullet -> moveSprite (bullet -> getXSpeed (), bullet -> getYSpeed ());

	if ((bullet -> getX () < 0) || (bullet-> getX() > mapWidth)) {
		bullet -> setAlive (0);
		return;
	}

	for (int n = 0; n < MAX_ENEMIES; n++) {
		if (enemies[n] -> getAlive ()) {
			int x = bullet -> getX () / 2;
			int y = bullet -> getY () / 2;

			//Get enemy alien bounding rectangle
			int x1 = enemies [n] -> getX ();
			int y1 = enemies [n] -> getY ();
			int x2 = x1 + enemies[n] -> getWidth ();
			int y2 = y1 + enemies[n] -> getHeight ();

			//check for collision
			if (enemies[n] -> inside (x, y, x1, y1, x2, y2)) {
				enemies[n] -> setAlive (0);
				bullet -> setAlive (0);
				//EXPLOSION
				//SCORE
				break;
			}
		}
	}
}