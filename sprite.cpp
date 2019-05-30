#include "sprite.h"

using namespace std;

SPRITE :: SPRITE () {
	dir = 0;
	alive = 0;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	xspeed = 0;
	yspeed = 0;
	xdelay = 0;
	ydelay = 0;
	xcount = 0;
	ycount = 0;
	curframe = 0;
	maxframe = 0;
	animdir = 0;
	framecount = 0;
	framedelay = 0;
	animcolumns = 0;
	animstartx = 0;
	animstarty = 0;
	facing = 1;
	jump = JUMPIT;
}

SPRITE :: SPRITE (int xx, int yy, int wid, int ht, int curF, int frameC, int frameD, int maxF, int animC) {
	x = xx;
	y = yy;
	width = wid;
	height = ht;
	curframe = curF;
	framecount = frameC;
	framedelay = frameD;
	maxframe = maxF;
	animdir = 1;
	animcolumns = animC;
	animstartx = 0;
	animstarty = 0;
	facing = 1;
	jump = JUMPIT;
}

SPRITE :: SPRITE (int dr, int alv, int xx, int yy, int xs, int ys, int xd, int yd, int xc, int yc,
				  int curf, int maxf, int animd, int framec, int framed, int animC, int animSX, int animSY) {
	dir = dr;
	alive = alv;
	x = xx;
	y = yy;
	xspeed = xs;
	yspeed = ys;
	xdelay = xd;
	ydelay = yd;
	xcount = xc;
	ycount = yc;
	curframe = curf;
	maxframe = maxf;
	animdir = animd;
	framecount = framec;
	framedelay = framed;
	animcolumns = animC;
	animstartx = animSX;
	animstarty = animSY;
	facing = 1;
	jump = JUMPIT;
}

SPRITE::~SPRITE () {
	//remove bitmap from memory
    if (image != NULL)
        destroy_bitmap(image);
}

int SPRITE::load (char *filename) {
	image = load_bitmap (filename, NULL);
	if (image == NULL) return 0;
	return 1;
}

void SPRITE :: drawframe (BITMAP * dest, int debug) {
	
	if (debug)
		cout << "Starting drawing frame..." << endl;
	
	int fx = animstartx + (curframe % animcolumns) * width;
    int fy = animstarty + (curframe / animcolumns) * height;

    if (debug){
    	cout << "fx: " << fx << endl;
    	cout << "fy: " << fy << endl;
    	cout << "Starting blit" << endl;
    }

    if (facing == 1)
	    masked_blit(image,dest,fx,fy,x,y,width,height);
	else {
		BITMAP * temp = create_bitmap (width, height);
		blit (image, temp, fx, fy, 0, 0, width, height);
		draw_sprite_h_flip (dest, temp, x, y);
		destroy_bitmap (temp);
	}
}

void SPRITE::updateAnimation() 
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

void SPRITE :: setFacing (int face) {
	facing = face;
}

int SPRITE :: getFacing () {
	return facing;
}

void SPRITE :: setCurFrame (int curF) {
	curframe = curF;
}

void SPRITE :: moveSprite (int xx, int yy) {
	x += xx;
	y += yy;
}

int SPRITE :: getJump () {
	return jump;
}

void SPRITE :: setJump (int jmp) {
	jump = jmp;
}

void SPRITE :: addToJump (int num) {
	jump += num;
}

int SPRITE :: getX () {
	return x;
}

void SPRITE :: setX (int xx) {
	x = xx;
}

int SPRITE :: getY () {
	return y;
}

int SPRITE :: getWidth () {
	return width;
}

int SPRITE :: getHeight () {
	return height;
}
