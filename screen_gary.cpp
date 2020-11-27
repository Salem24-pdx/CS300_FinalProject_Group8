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

	// create viewPort pad
	viewPort = newpad(128, 128);

	// split screen into menu and viewPort
	// menu gets menuWidth
	// viewPort gets the rest up to 128
	// if there is unused space, menu gets it
	menuWidth = minMenuWidth;
	viewPortWidth = COLS - menuWidth - 1;
	if (viewPortWidth > 128) {
		viewPortWidth = 128;
		menuWidth = COLS - viewPortWidth - 1;
	}

	int lines = LINES;
	if (lines > 128) {
		lines = 128;
	}

	viewPortHeight = lines;
	if (viewPortHeight > 128) {
	viewPortHeight = 128;
	}

	// create divider and fill it with #
	divider  = newwin(lines, 1, 0, viewPortWidth);
	mvwvline(divider, 0, 0, '#', lines);
	wrefresh(divider);

	// create menu window
	menu = newwin(lines, menuWidth, 0, viewPortWidth + 1);
	wrefresh(menu);

	// define colors
	start_color();
	// INDEX, FOREGROUND, BACKGROUND
	init_pair(MEADOW,  COLOR_BLACK,  COLOR_GREEN);
	init_pair(SWAMP,   COLOR_BLACK,  COLOR_MAGENTA);
	init_pair(WATER,   COLOR_BLACK,  COLOR_BLUE);
	init_pair(WALL,    COLOR_BLACK,  COLOR_WHITE);
	init_pair(HERO,    COLOR_YELLOW, COLOR_RED);
	init_pair(DIAMOND, COLOR_WHITE,  COLOR_CYAN);

	// turn off key input blocking
	nodelay(viewPort, TRUE);
	keypad(viewPort, TRUE);
}

screen::~screen()
{
	// delete windows/pads
	delwin(viewPort);
	delwin(divider);
	delwin(menu);

	// reset terminal and end ncurses mode
	endwin();
}

int screen::resize() {
	// split screen into menu and viewPort
	// menu gets menuWidth
	// viewPort gets the rest up to 128
	// if there is unused space, menu gets it
	menuWidth = minMenuWidth;
	viewPortWidth = COLS - menuWidth - 1;
	if (viewPortWidth > 128) {
		viewPortWidth = 128;
		menuWidth = COLS - viewPortWidth - 1;
	}

	int lines = LINES;
	if (lines > 128) {
		lines = 128;
	}

	viewPortHeight = lines;
	if (viewPortHeight > 128) {
	viewPortHeight = 128;
	}

	int d = wresize(divider, lines, 1);
        mvwvline(divider, 0, 0, '#', lines);
	int m = wresize(menu, lines, menuWidth);

        int md = mvwin(divider, 0, viewPortWidth);
        int mm = mvwin(menu, 0, viewPortWidth + 1);

        wrefresh(divider);
        wrefresh(menu);

	int r = screen::refreshWin();

        if (d == ERR || m == ERR || r == ERR || md == ERR || mm == ERR) {
                return ERR;
        }
        return OK;
}

int screen::put(int x, int y, char item, int terrain)
{
	if (x < 0 || y < 0 || x > 127 || y > 127) {
		return ERR;
	}

	int itemResult = put(x, y, (char) item);
	int terrainResult = put(x, y, (int) terrain);

	if (itemResult == ERR || terrainResult == ERR) {
		return ERR;
	}
	return OK;
}

int screen::put(int x, int y, char item)
{
	if (x < 0 || y < 0 || x > 127 || y > 127) {
		return ERR;
	}

	// extract terrain
	chtype terrain = mvwinch(viewPort, y, x) & A_COLOR;

	// put terrain back with item
	return mvwaddch(viewPort, y, x, (chtype) (item | terrain));
}

int screen::put(int x, int y, int terrain)
{
	if (x < 0 || y < 0 || x > 127 || y > 127) {
		return FALSE;
	}

	// extract item
	chtype item = mvwinch(viewPort, y, x) & A_CHARTEXT;

	// put item back with terrain
	return mvwaddch(viewPort, y, x, (chtype) (item | COLOR_PAIR(terrain)));
}

int screen::moveCursor(int direction)
{
	// check for edge of map
	if ((NORTH == direction && y == 0) || (WEST == direction && x == 0) || (SOUTH == direction && y == 127) || (EAST == direction && x == 127)) {
		return ERR;
	}

	if (NORTH == direction) {
		--y;
	}
	if (WEST == direction) {
		--x;
	}
	if (SOUTH == direction) {
		++y;
	}
	if (EAST == direction) {
		++x;
	}

	return OK;
}

int screen::putCursor(int inx, int iny)
{
	// check for edge of map
	if (inx < 0 || inx > 127 || iny < 0 || inx > 127) {
		return ERR;
	}

	x = inx;
	y = iny;
	return OK;
}

int screen::getCursorX()
{
	return x;
}

int screen::getCursorY()
{
	return y;
}

int screen::init()
{
	int v = wclear(viewPort);
	int w = wclear(menu);

	if (v == ERR || w == ERR) {
		return ERR;
	}

	return OK;
}

int screen::getKey()
{
	int key = wgetch(viewPort);
	if (key == KEY_RESIZE) {
		resize();
	}
	return key;
}

int screen::refreshWin()
{

	int m = wnoutrefresh(menu);

	//// maintain margin between hero and edge
	int margin = 3;

	// adjust left edge
	if (x - pmincol < margin) {
		pmincol -= margin - (x - pmincol);
	}
	// adjust top edge
	if (y - pminrow < margin) {
		pminrow -= margin - (y - pminrow);
	}

	int pmaxcol = pmincol + viewPortWidth - 1;
	int pmaxrow = pminrow + viewPortHeight - 1;

	// adjust right edge
	if (pmaxcol - x < margin) {
		pmincol += margin - (pmaxcol - x);
		pmaxcol += margin - (pmaxcol - x);
	}
	// adjust bottom edge
	if (pmaxrow - y < margin) {
		pminrow += margin - (pmaxrow - y);
		pmaxrow += margin - (pmaxrow - y);
	}

	//// unless the window is at edge of map
	if (pmincol < 0) {
		pmincol = 0;
	}
	if (pminrow < 0) {
		pminrow = 0;
	}
	if (pmaxcol > 127) {
		pmincol = 127 - viewPortWidth + 1;
	}
	if (pmaxrow > 127) {
		pminrow = 127 - viewPortHeight + 1;
	}

	// place cursor in viewPort
	wmove(viewPort, y, x);
	int v = pnoutrefresh(viewPort, pminrow, pmincol, 0, 0, viewPortHeight - 1, viewPortWidth - 1);

	doupdate();

	if (ERR == v || ERR == m)
	{
		return ERR;
	}

	return OK;
}

int screen::center(int x, int y) {
	if (x < 0 || y < 0 || x > 127 || y > 127) {
		return FALSE;
	}

	pmincol = x - (viewPortWidth / 2);
	pminrow = y - (viewPortHeight / 2);
	return OK;
}
