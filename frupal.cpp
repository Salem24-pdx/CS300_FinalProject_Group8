#include <ncurses.h>
//#include "player.h"
#include "controls.h"
using namespace std;

int main()
{
	/*player test;
	test.loseWhiffles(69);
	tool axe;
	axe.name = "AXE";
	axe.type = 2;
	axe.energyDiv = 3;

	tool hammer;
	hammer.name = "HAMMER";
	hammer.type = 1;
	hammer.energyDiv = 2;
	cout<<(test.getWhiffles())<<"\n";
	cout<<(test.getEnergy())<<"\n";
	test.addTool(axe);
	test.addTool(hammer);
	cout<<(test.retrieve(2));
	//test.displayTools(); //Some testing i did to make sure functions worked as intended for player class */
	game_logic game;
	game.s.init();
	game.s.putCursor(63,63);
	game.s.center(63,63);
	game.s.refreshWin();
	int key = 0;
	while (key != 'q'){
		game.s.refreshWin();
		key = game.s.getKey();
		//game.check_next(key);
		if (key == KEY_UP)
			game.s.moveCursor(NORTH);
		if (key == KEY_DOWN)
			game.s.moveCursor(SOUTH);
	       	if (key == KEY_LEFT)
			game.s.moveCursor(WEST);
		if (key == KEY_RIGHT)
			game.s.moveCursor(EAST);

		game.move(key);
	}
	


	return 0;
}
