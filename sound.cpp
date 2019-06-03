#include "sound.h"

sound :: sound () {
	volume = 255;
	pan = 128;
	pitch = 1000;
}

sound :: ~sound () {}

void sound :: musicOn () {
	volume = 255;
}

void  sound :: musicOff () {
	volume = 0;
}

int sound :: getVolume (){
	return volume;
}

int sound :: getPan () {
	return pan;
}

int sound :: getPitch () {
	return pitch;
}

void sound :: setVolume (int setTo) {
	volume = setTo;
}

void sound :: setPan (int setTo) {
	pan = setTo;
}

void sound :: setPitch (int setTo) {
	pitch = setTo;
}
