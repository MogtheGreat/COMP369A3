#include "auxi.h"

using namespace std;

int checkDebug (int argc, char * argv[]) {
	if (argc == 1) return 0;
	else if (strcmp(argv[1],"-d") == 0) return 1;
	return 0;
}

int initialize () {
	int check = allegro_init ();
	if (check != 0) {
		std::cerr << "Allegro library failed to initialize!" << std::endl;
		return 1;
	}

	check = install_timer ();
	if (check != 0) {
		std:: cerr << "Timer failed to install!" << std:: endl;
		return 1;
	}
	
	check = install_keyboard ();
	if (check != 0) {
		std:: cerr << "Keyboard failed to install!" << std::endl;
		return 1;
	}

	set_color_depth (16);
	check = set_gfx_mode (MODE, WIDTH, HEIGHT, 0,0);
	if (check != 0) {
		allegro_message ("%s\n", allegro_error);
		return 1;
	}

	return 0;
}

vector <string> getLvls () {
	vector<string> list;	// Holds the file list from the directory
	DIR * dir;				// Used to 
	struct dirent * ent;
	
	//Opens the directory
	if ((dir = opendir (PATH)) != NULL) {
		// gets all files and directories in the folder
		while ((ent = readdir (dir)) != NULL) {
			string temp (ent -> d_name);
			string completePath = PATH;
			completePath += temp;
			
			// Checks to see if there is a file in the directory.
			if ((temp != ".") && (temp != "..")) {
				list.push_back (completePath); // Stores the file name in the list.
			}
		}
		closedir (dir); // closes directories
	}

	return list;
}

BITMAP * grabframe (BITMAP * source, int width, int height, int startx, int starty, int columns, int frame) {
	BITMAP * temp = create_bitmap (width, height);
	int x = startx + (frame % columns) * width;
	int y = starty + (frame / columns) * height;
	blit (source, temp, x, y, 0, 0, width, height);
	return temp;
}
