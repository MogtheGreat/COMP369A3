#include "movement.h"

using namespace std;

void playerInput (sprites * player, sprites * bullets[MAX_BULLETS], Levels lvl) {

	int oldX = player -> getX ();
	int oldY = player -> getY ();

	if (DEBUG2){
		cout << "Player x and y before function..." << endl;
		cout << "player -> x: " << oldX << endl;
		cout << "player -> y: " << oldY << endl;
	}

	if (key[KEY_RIGHT]) {
		player -> setFacing (1);
		player -> updateAnimation ();
		player -> moveSprite (6,0);
	}
	else if (key[KEY_LEFT]) {
		player -> setFacing (0);
		player -> updateAnimation ();
		player -> moveSprite (-6,0);
	}
	else
		player -> setCurFrame (0);

	//Controls shooting
	if (key[KEY_V]) {
		if ((player -> getFireCount ()) > (player -> getFireDelay())) {
			player -> setFireCount (0);
			fireatenemy (bullets, player -> getX (), player -> getY ());
		}
	}

	//Start jumping
	if (player -> getJump () == JUMPIT) {
		if (!lvl.collided (player-> getX() + (player -> getWidth ()), player-> getY() + (player-> getHeight())))
			player -> setJump (0);
		if (key[KEY_SPACE])
			player -> setJump (30);
	}

	handleJump (player, lvl);
	handleWall (player, lvl, oldX, oldY);

	if (DEBUG2){
		cout << "Player x and y after function..." << endl;
		cout << "player -> x: " << player -> getX () << endl;
		cout << "player -> y: " << player -> getY () << endl;
	}
}

void enemyPhysic (sprites * enemies[MAX_ENEMIES], Levels lvl) {
	for (int n = 0; n < MAX_ENEMIES; n++) {
		if (enemies[n] -> getJump () == JUMPIT) {
			if (!lvl.collided (enemies[n]-> getX() + (enemies[n] -> getWidth ()), enemies[n]-> getY() + (enemies[n]-> getHeight())))
			enemies[n] -> setJump (0);
		}

		handleJump (enemies[n], lvl);
		handleWall (enemies[n], lvl, enemies[n] -> getX(), enemies[n] -> getY ());
	}
}

void handleJump (sprites * spr, Levels lvl) {
	
	if (spr -> getJump () != JUMPIT) {
		spr -> moveSprite (0, -(spr-> getJump()/3));
		spr -> addToJump (-1);
	}

	if (spr -> getJump () < 0) {
		if (lvl.collided (spr-> getX() + (spr -> getWidth ()), spr-> getY() + (spr-> getHeight())))
		{
			spr -> setJump(JUMPIT);
			while (lvl.collided (spr-> getX() + (spr -> getWidth ()), spr-> getY() + (spr-> getHeight())))
				spr -> moveSprite (0, -2);
		}
	}
}

void handleWall (sprites * spr, Levels lvl, int oldX, int oldY) {
	if (!spr -> getFacing ()) {
		if (lvl.collided (spr-> getX(), spr-> getY() + (spr-> getHeight()))) {
			spr -> setX (oldX);
			spr -> setY (oldY);
		}
	}
	else {
		if (lvl.collided (spr-> getX() + (spr -> getWidth ()), spr-> getY() + (spr-> getHeight()))) {
			spr -> setX (oldX);
			spr -> setY (oldY);
		}
	}
}
