#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>

using namespace std;

class screen
{
	public:

		screen();   //set up windows, pads, color pairs
		~screen();  //tear down widows, pads, color pairs

		// items
		const char FOOD = 'F';
		const char TOOL = 'T';
		const char OBSTACLE = '!';
	        const char CHEST = '$';
		const char SHIP = 'S';
		const char BINOCULARS = 'B';
		const char NOITEM = ' ';

		// terrains
		// todo: set these to color pair reverence values and check datatype
		const int MEADOW = 1;   // black on green
		const int SWAMP = 2;    // black on magenta
		const int WATER = 3;    // black on blue
		const int WALL = 4;     // black on white
		const int HERO = 5;     // yellow on red
		const int DIAMOND = 6;  // white on cyan

		// these return true on success
		bool put(int x, int y, char item, int terrain);
		bool put(int x, int y, char item);
		bool put(int x, int y, int terrain);
		bool putHero(int x, int y);
		bool putDiamond(int x, int y);

		// directions
		const int NORTH = 1;
		const int EAST = 2;
		const int SOUTH = 3;
		const int WEST = 4;

		bool moveCursor(int direction);
		bool putCursor(int x, int y);

		int getCursorX();
		int getCursorY();

		bool see(int x, int y);

		bool init();

	private:

		WINDOW* gamePad;   //hidden pad contains the full current map
		WINDOW* seenPad;   //hidden pad contains the cells revealed
		WINDOW* viewPort;  //displayed viewport
		WINDOW* divider;   //displayed divider
		WINDOW* menu;      //displayed menu

		int x, y;          //cursor position
		int heroX, heroY;  //hero position
};

#endif /* SCREEN_H */
