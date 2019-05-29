#ifndef SPRITE_H
#define SPRITE_H
#include <allegro.h>
#include <iostream>

class SPRITE {
	int dir, alive;
	int x, y;
	int width, height;
	int xspeed, yspeed;
	int xdelay, ydelay;
	int xcount, ycount;
	int curframe, maxframe, animdir;
	int framecount, framedelay;
	int animcolumns;
	int animstartx, animstarty;
	BITMAP * image;
public:
	SPRITE ();
	SPRITE (int xx, int yy, int wid, int ht, int curF, int frameC, int frameD, int maxF, int animC);
	SPRITE (int dr, int alv, int xx, int yy, int xs, int ys, int xd, int yd, int xc, int yc,
			int curf, int maxf, int animd, int framec, int framed, int animC, int animSX, int animSY);
	~SPRITE ();
	int load (char *filename);
	void drawframe (BITMAP * dest, int debug);
	void updateAnimation();
};

#endif