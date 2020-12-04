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
		if (key == '1')
		{
			game.s.moveCursor(NORTH);
			game.move(key);
		}
		if (key == '3')
		{
			game.s.moveCursor(SOUTH);
			game.move(key);
		}
	       	if (key == '4')
		{
			game.s.moveCursor(WEST);
			game.move(key);
		}

		if (key == '2')
		{
			game.s.moveCursor(EAST);
			game.move(key);
		}

	}
	


	return 0;
}
