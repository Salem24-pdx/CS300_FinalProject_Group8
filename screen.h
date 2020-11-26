#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>

using namespace std;
 
// items
const char FOOD = 'F';
const char TOOL = 'T';
const char OBSTACLE = '!';
const char CHEST = '$';
const char SHIP = 'S';
const char BINOCULARS = 'B';
const char NONE = ' ';
const char HEROCHAR = '@';

// terrains
// todo: set these to color pair reverence values and check datatype
const int MEADOW = 1;   // black on green
const int SWAMP = 2;    // black on magenta
const int WATER = 3;    // black on blue
const int WALL = 4;     // black on white
const int HERO = 5;     // yellow on red
const int DIAMOND = 6;  // white on cyan

// directions
const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 3;
const int WEST = 4;

class screen
{
	public:

		screen();   //set up windows, pads, color pairs
		~screen();  //tear down widows, pads, color pairs

		// unless otherwise specified, functions return OK on success, other

		// item constants: FOOD, TOOL, OBSTACLE, CHEST, SHIP, BINOCULARS, HEROCHAR, NONE
		// terrain constants: MEADOW, SWAMP, WATER, WALL, HERO, DIAMOND
		// place an item and/or a terrain on the screen at x,y
		int put(int x, int y, char item, int terrain);

		// if you use something besides the declared constants above,
		// be sure to type cast with (char) or (int)
		int put(int x, int y, char item);
		int put(int x, int y, int terrain);

		// direction constants: NORTH, SOUTH, EAST, WEST
		// change the cursor location
		int moveCursor(int direction);
		int putCursor(int x, int y);

		// returns cursor x and y
		int getCursorX();
		int getCursorY();

		// clear map and menu windows
		int init();

		// get key from viewPort window (non-blocking)
		int getKey();

		// refresh map and viewPort windows
		int refresh();

		// center viewPort on coordinate
		int center(int x, int y);

	private:

		int resize();

		WINDOW* viewPort;    //displayed viewport
		WINDOW* divider;     //displayed divider
		WINDOW* menu;        //displayed menu
		WINDOW* arrows;      //map edge indicators

		int x = 0;           //cursor position
		int y = 0;           //cursor position
		int heroX = 0;       //hero position
		int heroY = 0;       //hero position

		int viewPortWidth;
		int viewPortHeight;
		int pminrow;         // upper left corner of viewPort rect
		int pmincol;         // upper left corner of viewPort rect

		int minMenuWidth = 20;
		int menuWidth;
};

#endif /* SCREEN_H */
