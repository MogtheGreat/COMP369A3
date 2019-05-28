#include <allegro.h>
#include <string>
#include <iostream>
#include "mappyal.h"

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 448

using namespace std;

int main (void) {
	int mapxoff;
	int mapyoff;
	
	allegro_init ();
	install_timer ();
	install_keyboard ();
	set_color_depth (16);
	set_gfx_mode (MODE, WIDTH, HEIGHT, 0,0);

	char path [] = "Resources/Map/Battle World 1.FMP";
	char * hold = path;
	MapLoad (hold);
	BITMAP * buffer = create_bitmap (WIDTH, HEIGHT);
	clear (buffer);

	while (!key[KEY_ESC]){
		mapxoff = 0;
		mapyoff = HEIGHT/2 + 10;

		//draw the background tiles
		MapDrawBG(buffer, mapxoff, mapyoff, 0, 0, WIDTH-1, HEIGHT-1);

        //draw foreground tiles
		MapDrawFG(buffer, mapxoff, mapyoff, 0, 0, WIDTH-1, HEIGHT-1, 0);

		//blit the double buffer 
		vsync();
		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
        release_screen();
	}

	MapFreeMem ();
	destroy_bitmap (buffer);
	allegro_exit ();
	return 0;
}
END_OF_MAIN()