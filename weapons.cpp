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

void updatebullets (BITMAP * buffer, sprites * bullets[MAX_BULLETS], sprites * enemies[MAX_ENEMIES], 
					sprites * explosions [MAX_EXPLOSIONS], int mapWidth) {
	for (int n = 0; n < MAX_BULLETS; n++) {
		if (bullets[n] -> getAlive()) {
			updatebullet (bullets[n], enemies, explosions, mapWidth);
			bullets[n] -> drawframe (buffer);
		}
	}
}

void updatebullet (sprites * bullet, sprites * enemies[MAX_ENEMIES], 
				   sprites * explosions [MAX_EXPLOSIONS], int mapWidth) {

	//move the bullet
	bullet -> moveSprite (bullet -> getXSpeed (), bullet -> getYSpeed ());

	if ((bullet -> getX () < 0) || (bullet-> getX() > mapWidth)) {
		bullet -> setAlive (0);
		return;
	}

	for (int n = 0; n < MAX_ENEMIES; n++) {
		if (enemies[n] -> getAlive ()) {
			int x = bullet -> getX ();
			int y = bullet -> getY ();

			//Get enemy alien bounding rectangle
			int x1 = enemies [n] -> getX ();
			int y1 = enemies [n] -> getY ();
			int x2 = x1 + enemies[n] -> getWidth ();
			int y2 = y1 + enemies[n] -> getHeight ();

			//check for collision
			if (enemies[n] -> inside (x, y, x1, y1, x2, y2)) {
				enemies[n] -> setAlive (0);
				bullet -> setAlive (0);
				startExplosion (explosions, enemies[n]-> getX (),enemies[n]-> getY());
				//SCORE
				break;
			}
		}
	}
}

void startExplosion (sprites * explosions [MAX_EXPLOSIONS], int x, int y) {
	for (int n = 0; n < MAX_EXPLOSIONS; n++) {
		if (!(explosions[n] -> getAlive())) {
			explosions[n] -> setAlive (1);
			explosions[n] -> setX (x);
			explosions[n] -> setY (y);
			break;
		}
	}
}

void updateExplosion (BITMAP * buffer, sprites * explosions [MAX_EXPLOSIONS]) {
	for (int n = 0; n < MAX_EXPLOSIONS; n++) {
		if (explosions[n] -> getAlive()) {
			explosions[n] -> updateSprite ();
			explosions[n] -> drawframe (buffer);

			if (explosions[n] -> getCurFrame () >= explosions[n] -> getMaxFrame ()) {
				explosions[n] -> setCurFrame (0);
				explosions[n] -> setAlive (0);
			}
		}
	}
}
