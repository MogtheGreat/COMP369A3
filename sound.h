#ifndef SOUND_H
#define SOUND_H
#include <allegro.h>

#define PATHMUSIC "Resources/Music/"
#define PATHSOUND "Resources/Sound/"

class sound {
	int volume;
    int pan;
    int pitch;
public:
	sound ();
	~sound ();

	void musicOn ();
	void musicOff ();

	int getVolume ();
	int getPan ();
	int getPitch ();
	void setVolume (int setTo);
	void setPan (int setTo);
	void setPitch (int setTo);
};

#endif