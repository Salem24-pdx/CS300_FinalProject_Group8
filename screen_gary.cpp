// screen.cpp
#include "screen.h"
#include <ncurses.h>

// for abort program:
#include <cstdio>
#include <cstdlib>


using namespace std;

screen::screen()
{
	initscr();

	if (has_colors() == FALSE) {
		endwin();
		printf("ERROR: Your terminal does not support color!\n");
        	exit(1);
	}

	gamePad = newpad(128, 128);
	seenPad = newpad(128, 128);

	viewPortWidth = COLS - menuWidth - 1;
	if (viewPortWidth > 128)
	{
		viewPortWidth = 128;
		menuWidth = COLS - viewPortWidth - 1;
	}

	viewPort = newwin(LINES, viewPortWidth, 0, 0);
	divider  = newwin(LINES, 1, 0, viewPortWidth);
	menu     = newwin(LINES, menuWidth, 0, viewPortWidth + 1);

	mvwvline(divider, 0, 0, '#', LINES - 1);

	start_color();
	// INDEX, FOREGROUND, BACKGROUND
	init_pair(MEADOW,  COLOR_BLACK,  COLOR_GREEN);
	init_pair(SWAMP,   COLOR_BLACK,  COLOR_MAGENTA);
	init_pair(WATER,   COLOR_BLACK,  COLOR_BLUE);
	init_pair(WALL,    COLOR_BLACK,  COLOR_WHITE);
	init_pair(HERO,    COLOR_YELLOW, COLOR_RED);
	init_pair(DIAMOND, COLOR_WHITE,  COLOR_CYAN);

	nodelay(stdscr, TRUE);
	nodelay(viewPort, TRUE);
	nodelay(divider, TRUE);
	nodelay(menu, TRUE);
}

screen::~screen()
{
	delwin(gamePad);
	delwin(seenPad);

	delwin(viewPort);
	delwin(divider);
	delwin(menu);
}

bool screen::put(int x, int y, char item, int terrain)
{
return true;
}

bool screen::put(int x, int y, char item)
{
return true;
}

bool screen::put(int x, int y, int terrain)
{
return true;
}

bool screen::putHero(int x, int y)
{
return true;
}

bool screen::moveCursor(int direction)
{
return true;
}

bool screen::putCursor(int x, int y)
{
return true;
}

int screen::getCursorX()
{
return x;
}

int screen::getCursorY()
{
return y;
}

bool screen::see(int x, int y)
{
return true;
}

bool screen::init()
{
	wclear(viewPort);
	wclear(menu);

	wclear(gamePad);
	wclear(seenPad);

	clear();

return true;
}

// check all our windows for a keypress, just in case someone didnt focus the cursor on viewPort
int screen::getKey()
{
	int key;

	key = getch();
	if (key != ERR)
		return key;

	key = wgetch(viewPort);
	if (key != ERR)
		return key;

	key = wgetch(divider);
	if (key != ERR)
		return key;

	key = wgetch(menu);
	if (key != ERR)
		return key;

	return ERR;
}

// refresh all windows and screen
int screen::refreshWin()
{
	int v = wrefresh(viewPort);
	int d = wrefresh(divider);
	int m = wrefresh(menu);

	int s = refresh();

	if (ERR == v || ERR == d || ERR == m || ERR == s)
	{
		return ERR;
	}

	return OK;
}
