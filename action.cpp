#include "action.h"

using namespace std;

void playerInput (SPRITE * player, Levels lvl) {
	int oldX = player -> getX ();

	if (key[KEY_RIGHT]) {
		player -> setFacing (1);
		player -> updateAnimation();
		player -> moveSprite (4, 0);
	}
	else if (key[KEY_LEFT]) {
		player -> setFacing (0);
		player -> updateAnimation();
		player -> moveSprite (-4, 0);
	}
	else
		player -> setCurFrame (0);

	//handle jumping
	if (player -> getJump () == JUMPIT) {
		if (!lvl.collided (player-> getX() + (player -> getWidth ()), player-> getY() + (player-> getHeight())))
			player -> setJump (0);
		if (key[KEY_SPACE])
			player -> setJump (30);
	}
	else {
		player -> moveSprite (0, -(player-> getJump()/3));
		player -> addToJump (-1);
	}


	if (player -> getJump () < 0) {
		if (lvl.collided (player-> getX() + (player -> getWidth ()), player-> getY() + (player-> getHeight())))
		{
			player -> setJump(JUMPIT);
			while (lvl.collided (player-> getX() + (player -> getWidth ()), player-> getY() + (player-> getHeight())))
				player -> moveSprite (0, -2);
		}
	}

	if (!player -> getFacing ()) {
		if (lvl.collided (player-> getX(), player-> getY() + (player-> getHeight()))) {
			player -> setX (oldX);
		}
	}
	else {
		if (lvl.collided (player-> getX() + (player -> getWidth ()), player-> getY() + (player-> getHeight()))) {
			player -> setX (oldX);
		}
	}
}