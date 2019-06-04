/*
Title: sprites.cpp
Description: A sprite object that contains all the variables and functions that a sprite might need.
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#include "sprites.h"

//Constructor
sprites :: sprites () { }

//Deconstructor
sprites :: ~sprites () {
	if (image != NULL)
		destroy_bitmap (image);
}

/*
	Loads a bitmap into the sprite.

	Param:
		fileName 	- The name of the file that represents the bitmap being loaded
	Return:
		0 if failed to laod
		1 if successful
*/
int sprites :: load (char * fileName) {
	image = load_bitmap (fileName, NULL);
	if (image == NULL) return 0;
	return 1;
}

/*
	Draws a frame from a loaded bitmap onto a destinated bitmap.

	Param:
		dest 		 - A bitmap that is to be drawn on.
	Return:
		N/A
*/
void sprites :: drawframe (BITMAP * dest) {
	// Finds the desired frame in the bitmap
	int fx = animstartx + (curframe % animcolumns) * width;
    int fy = animstarty + (curframe / animcolumns) * height;

    if (facing == 1) // Sprite facing to the right.
	    masked_blit(image,dest,fx,fy,x,y,width,height); // Draws the sprite as is on the bitmap
	else { // Sprite facing to the left
		BITMAP * temp = create_bitmap (width, height); // Create a new temp bitmap
		blit (image, temp, fx, fy, 0, 0, width, height); // Add the sprite to the bitmap
		draw_sprite_h_flip (dest, temp, x, y); // Draw the sprite flipped in the opposite direction
		destroy_bitmap (temp); // Destroy the temp bitmap.
	}
}

/*
	Cycles through the sprites animation sequence.
	Param:
		N/A
	Return:
		N/A
*/
void sprites :: updateAnimation() 
{
    //update frame based on animdir
    if (++framecount > framedelay)
    {
        framecount = 0;
		curframe += animdir;

		if (curframe < 0) {
            curframe = maxframe-1;
		}
		if (curframe > maxframe-1) {
            curframe = 1;
        }
    }
}

/*
	Updates the sprites animation and position.

	Param:
		N/A
	Return:
		N/A
*/
void sprites :: updateSprite () {
	// update x position
	if (++xcount > xdelay) {
		xcount = 0;
		x += xspeed;
	}

	//update y postion
	if (++ycount > ydelay) {
		ycount = 0;
		y += yspeed;
	}

	// Updates the sprites animation sequence
	if (++framecount > framedelay) {
		framecount = 0;
		if (animdir == -1) {
			if (--curframe < 0)
				curframe = maxframe;
		}
		else if (animdir == 1) {
			if (++curframe > maxframe)
				curframe = 0;
		}
	}
}

/*
	Checks to see if the sprite is inside another sprite bounding box.

	Param:
		xx		- x position
		yy 		- y position
		left	- Left side bounding box
		top 	- Top of bounding box
		right 	- Right side of bounding box
		bottom  - The bottom of the bounding box
*/
int sprites :: inside (int xx, int yy, int left, int top, int right, int bottom) {
	if (xx > left && xx < right && yy > top && yy < bottom) {
		return 1;
	}
	else
		return 0;
}

/***************GET fuctutions***************/
// Get functions return one of the variables from the object

int sprites :: getDir () {
	return dir;
}

int sprites :: getAlive () {
	return alive;
}

int sprites :: getX () {
	return x;
}

int sprites :: getY() {
	return y;
}

int sprites :: getWidth () {
	return width;
}

int sprites :: getHeight (){
	return height;
}

int sprites :: getFacing () {
	return facing;
}

int sprites :: getJump () {
	return jump;
}
int sprites :: getFireCount () {
	return firecount;
}

int sprites :: getFireDelay () {
	return firedelay;
}

int sprites :: getXSpeed () {
	return xspeed;
}

int sprites :: getYSpeed () {
	return yspeed;
}

int sprites :: getXDelay () {
	return xdelay;
}

int sprites :: getYDelay () {
	return ydelay;
}

int sprites :: getXCount () {
	return xcount;
}

int sprites :: getYCount () {
	return ycount;
}

int sprites :: getCurFrame () {
	return curframe;
}

int sprites :: getMaxFrame () {
	return maxframe;
}

int sprites :: getAnimDir () {
	return animdir;
}

int sprites :: getFrameCount () {
	return framecount;
}

int sprites :: getFrameDelay () {
	return framedelay;
}

int sprites :: getAnimColumns () {
	return animcolumns;
}

int sprites :: getAnimStartX () {
	return animstartx;
}

int sprites :: getAnimeStartY () {
	return animstarty;
}

BITMAP * sprites :: getImage () {
	return image;
}

/******************SET Functions******************/
// Set functions changes the value of one of the variables in the object


void sprites :: setDir (int setTo) {
	dir = setTo;
}

void sprites :: setAlive (int setTo) {
	alive = setTo;
}

void sprites :: setX (int setTo) {
	x = setTo;
}

void sprites :: setY(int setTo) {
	y = setTo;
}

void sprites :: setWidth (int setTo) {
	width = setTo;
}

void sprites :: setHeight (int setTo) {
	height = setTo;
}

void sprites :: setFacing (int setTo) {
	facing = setTo;
}

void sprites :: setJump (int setTo) {
	jump = setTo;
}

void sprites :: setFireCount (int setTo) {
	firecount = setTo;
}

void sprites :: setFireDelay (int setTo) {
	firedelay = setTo;
}

void sprites :: setXSpeed (int setTo) {
	xspeed = setTo;
}

void sprites :: setYSpeed (int setTo) {
	yspeed = setTo;
}

void sprites :: setXDelay (int setTo) {
	xdelay = setTo;
}

void sprites :: setYDelay (int setTo) {
	ydelay = setTo;
}

void sprites :: setXCount (int setTo) {
	xcount = setTo;
}

void sprites :: setYCount (int setTo) {
	ycount = setTo;
}

void sprites :: setCurFrame (int setTo) {
	curframe = setTo;
}

void sprites :: setMaxFrame (int setTo) {
	maxframe = setTo;
}

void sprites :: setAnimDir (int setTo) {
	animdir = setTo;
}

void sprites :: setFrameCount (int setTo) {
	framecount = setTo;
}

void sprites :: setFrameDelay (int setTo) {
	framedelay = setTo;
}

void sprites :: setAnimColumns (int setTo) {
	animcolumns = setTo;
}

void sprites :: setAnimStartX (int setTo) {
	animstartx = setTo;
}

void sprites :: setAnimStartY (int setTo) {
	animstarty = setTo;
}

/******************ADD To functions******************/

/*
	Adjust the sprites positions.

	Param:
		xx 	- A value to be added to the sprites x position
		yy 	- A value to be added to the sprites y position
	Return:
		N/A
*/
void sprites :: moveSprite (int xx, int yy) {
	x += xx;
	y += yy;
}

/*
	Adjust the sprites jump variable which controls jumping height

	Param:
		num 		- A positvie/negative value to be added to jump.
	Return:
		N/A
*/
void sprites :: addToJump (int num) {
	jump += num;
}

/*
	Increaments the firecount variable.

	Param:
		N/A
	Return;
		N/A
*/
void sprites :: incrementFireCount () {
	firecount++;
}
