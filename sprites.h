#ifndef SPRITES_H
#define SPRITES_H
#include <allegro.h>

#define JUMPIT 1600
#define MAX_BULLETS 20
#define MAX_ENEMIES 3

class sprites {
	int dir, alive;
	int x, y;
	int width, height;
	int facing;
	int jump;
	int firecount, firedelay;
	int xspeed, yspeed;
	int xdelay, ydelay;
	int xcount, ycount;
	int curframe, maxframe, animdir;
	int framecount, framedelay;
	int animcolumns;
	int animstartx, animstarty;
	BITMAP * image;
public:
	sprites ();
	~sprites ();
	int load (char * fileName);
	void drawframe (BITMAP * dest);
	void updateAnimation();
	void updateSprite ();
	int inside (int xx, int yy, int left, int top, int right, int bottom);

	//GET functions
	int getDir ();
	int getAlive ();
	int getX ();
	int getY();
	int getWidth ();
	int getHeight ();
	int getFacing ();
	int getJump ();
	int getFireCount ();
	int getFireDelay ();
	int getXSpeed ();
	int getYSpeed ();
	int getXDelay ();
	int getYDelay ();
	int getXCount ();
	int getYCount ();
	int getCurFrame ();
	int getMaxFrame ();
	int getAnimDir ();
	int getFrameCount ();
	int getFrameDelay ();
	int getAnimColumns ();
	int getAnimStartX ();
	int getAnimeStartY ();
	BITMAP * getImage ();

	//SET functions
	void setDir (int setTo);
	void setAlive (int setTo);
	void setX (int setTo);
	void setY(int setTo);
	void setWidth (int setTo);
	void setHeight (int setTo);
	void setFacing (int setTo);
	void setJump (int setTo);
	void setFireCount (int setTo);
	void setFireDelay (int setTo);
	void setXSpeed (int setTo);
	void setYSpeed (int setTo);
	void setXDelay (int setTo);
	void setYDelay (int setTo);
	void setXCount (int setTo);
	void setYCount (int setTo);
	void setCurFrame (int setTo);
	void setMaxFrame (int setTo);
	void setAnimDir (int setTo);
	void setFrameCount (int setTo);
	void setFrameDelay (int setTo);
	void setAnimColumns (int setTo);
	void setAnimStartX (int setTo);
	void setAnimStartY (int setTo);

	//ADD TO functions
	void moveSprite (int xx, int yy);
	void addToJump (int num);
	void incrementFireCount ();
};

#endif