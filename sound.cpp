/*
Title: sound.h
Description: An object that controls the volume, pitch and pan for the music and sound
			 in the game
Author: Michael G. Oranski
ID: 2743708
Date: June 3, 2019
*/
#include "sound.h"

/*
	Consturctor
*/
sound :: sound () {
	volume = 255;
	pan = 128;
	pitch = 1000;
}

/*
	Deconstructor
*/
sound :: ~sound () {}

/*
	Turns the music on.
*/
void sound :: musicOn () {
	volume = 255;
}

/*
	Turns the music off.
*/
void  sound :: musicOff () {
	volume = 0;
}

/***************GET fuctutions***************/
// Get functions return one of the variables from the object

int sound :: getVolume (){
	return volume;
}

int sound :: getPan () {
	return pan;
}

int sound :: getPitch () {
	return pitch;
}

/******************SET Functions******************/
// Set functions changes the value of one of the variables in the object

void sound :: setVolume (int setTo) {
	volume = setTo;
}

void sound :: setPan (int setTo) {
	pan = setTo;
}

void sound :: setPitch (int setTo) {
	pitch = setTo;
}
