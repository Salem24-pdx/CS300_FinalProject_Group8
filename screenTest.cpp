#include <ncurses.h>
#include "screen.h"

int main() {

	int items[] = {FOOD, TOOL, OBSTACLE, CHEST, SHIP, BINOCULARS, NONE};
	int terrain[] = {MEADOW, SWAMP, WATER, WALL, HERO, DIAMOND};

	screen h;
	h.refreshWin();
	while (h.getKey() == ERR);
	return 0;
}
