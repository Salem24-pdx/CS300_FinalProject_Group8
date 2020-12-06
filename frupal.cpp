#include <ncurses.h>
//#include "player.h"
#include "controls.h"
using namespace std;

int main()
{
	/*player test;
	Tool axe;
	axe.name = "AXE";
	axe.type = 1;
	axe.energyDiv = 3;

	Tool hammer;
	hammer.name = "HAMMER";
	hammer.type = 0;
	hammer.energyDiv = 2;
	test.addTool(1,axe);
	test.addTool(1,axe);
	test.addTool(1,axe);
	test.remove(axe);
	test.addTool(0,hammer);
	test.displayTools();
	cout<<test.retrieve(0);
	//test.displayTools(); //Some testing i did to make sure functions worked as intended for player class */
	game_logic game;
	game.start();


	return 0;
}
