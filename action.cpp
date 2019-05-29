#include "action.h"

void playerInput (SPRITE * player) {
	if (key[KEY_RIGHT]) {
		player -> setFacing (1);
		player -> updateAnimation();
	}
	else if (key[KEY_LEFT]) {
		player -> setFacing (0);
		player -> updateAnimation();
	}
	else
		player -> setCurFrame (0);
}