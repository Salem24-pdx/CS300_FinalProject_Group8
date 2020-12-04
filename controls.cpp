#include <ncurses.h>
#include "controls.h"
#include "common.h"
using namespace std;



game_logic::game_logic()
{
	cur_x = 63;
	cur_y = 63;
	string filename = "savefile.dat";
	Array * ptrMap = &map;
	l.loadIn(filename.c_str(),ptrMap);
}

game_logic::~game_logic()
{
}

//checks to see the next tile before the playere moves there
int game_logic::check_next(int ch)
{

	int next_x = cur_x;
	int next_y = cur_y;
	Tile * temp_tile = NULL;
	

	if(ch == '1' && next_y > 0)//check north
	{
		--next_y;
	}
	else if(ch == '3' && next_y < 127)//check south
	{
		++next_y;
	}
	else if(ch == '4' && next_x > 0)//check west
	{
		--next_x;
	}
	else if(ch == '2' && next_x < 127)//check east
	{
		++next_x;
	}

	temp_tile = map.get_tile(next_y, next_x);
	return temp_tile->type;
}

//moves the player and performs various actions based on the cell
void game_logic::move(int ch)
{
	int tile_check;
	//char item_check = 'a';
	//Displays map around in 1 cycle
/*	s.put(cur_x,cur_y,map.get_terrain(cur_x,cur_y));
	s.put(cur_x+1,cur_y,map.get_terrain(cur_x+1,cur_y));
	s.put(cur_x-1,cur_y,map.get_terrain(cur_x-1,cur_y));
	s.put(cur_x,cur_y+1,map.get_terrain(cur_x,cur_y+1));
	s.put(cur_x+1,cur_y+1,map.get_terrain(cur_x+1,cur_y+1));
	s.put(cur_x-1,cur_y+1,map.get_terrain(cur_x-1,cur_y+1));
	s.put(cur_x,cur_y-1,map.get_terrain(cur_x,cur_y-1));
	s.put(cur_x+1,cur_y-1,map.get_terrain(cur_x+1,cur_y-1));
	s.put(cur_x-1,cur_y-1,map.get_terrain(cur_x-1,cur_y-1));*/
	//s.put(cur_x,cur_y,HEROCHAR,HERO);
	for (int i = -1;i<2;++i)
		for (int z = -1; z<2;++z)
		{
		s.put(cur_x+i,cur_y+z,map.get_terrain(cur_y+i,cur_x+z));
		if(map.get_food(cur_x+i, cur_y+z))
			s.put(cur_x+i,cur_y+z,'F');
		}


	//Displays bottom menu
	string ENE = "Energy: " + to_string(hero.getEnergy()) + " ";
	const char *echar = ENE.c_str();

	string WH = "Whiffles: " + to_string(hero.getWhiffles()) + " ";
	const char *wchar = WH.c_str();

	s.printtobot(1, wchar);
	s.printtobot(2, echar);


	//checks to see what the next tile is
	tile_check = check_next(ch);

	if(tile_check == WALL)
	{
		hero.loseEnergy(1);
		return;
	}
	else if(tile_check == SWAMP)
	{
		hero.loseEnergy(2);
	}
	else
	{
		hero.loseEnergy(1);
	}

	//moves the player to the next tile
	if(ch == '1' && cur_y > 1)//move north
	{
		--cur_y;
	}
	else if(ch == '3' && cur_y < 126)//move south
	{
		++cur_y;
	}
	else if(ch == '4' && cur_x > 1)//move west
	{
		--cur_x;
	}
	else if(ch == '2' && cur_x < 126)//move east
	{
		++cur_x;
	}

	//checks to see what item is in a tile
	//item_check = map.check_cell(y, x);

	
	

	if(map.get_food(cur_y, cur_x))
	{
		buy_food();
	}
	if(map.get_tool(cur_y, cur_x))
	{
		buy_tool();
	}
	if(map.get_obstacle(cur_y, cur_x))
	{
		remove_obstacle();
	}
	if(map.get_chest(cur_y, cur_x))
	{
		open_chest();
	}
	/*if(map.get_ship(cur_y, cur_x))
	{
		buy_ship();
	}
	if(map.get_binoculars(cur_y, cur_x))
	{
		buy_binoculars();
	}*/				//No map get ship or get binoculars yet
	if(map.get_clue(cur_y, cur_x))
	{
		display_clue();
	}
	

}

//buys food, adding energy and removing whiffles from the player
void game_logic::buy_food()
{
	Food * tile_food = map.get_food(cur_y, cur_x);
	if(hero.getWhiffles() < tile_food->cost)
	{
		return;
	}

	
	hero.addEnergy(tile_food->energy);
	hero.loseWhiffles(tile_food->cost);
	map.remove_stuff(cur_y, cur_x);

	return;
}

//buys a tool, removing whiffles and adding a tool to the player
void game_logic::buy_tool()
{
	Tool * tile_tool = map.get_tool(cur_y, cur_x);
	if(hero.getWhiffles() < tile_tool->cost)
	{
		return;
	}

	hero.addTool(tile_tool);
	hero.loseWhiffles(tile_tool->cost);
	map.remove_stuff(cur_y, cur_x);

	return;
}

//removes an obstacle from the map. checks to see if the player has a matching
//tool type and if so, uses up the tool
void game_logic::remove_obstacle()
{
	//double check function
	Obstacle * tile_obstacle = map.get_obstacle(cur_y, cur_x);
	int cost_divider = hero.retrieve(tile_obstacle->type);
	
	if(cost_divider == 0)
	{
		hero.loseEnergy(tile_obstacle->cost);
	}
	else
	{
		hero.loseEnergy(tile_obstacle->cost/cost_divider);
		if(tile_obstacle->type == 1)
		{
			hero.remove("PICK");
		}
		if(tile_obstacle->type == 2)
		{
			hero.remove("AXE");
		}
	}

	map.remove_stuff(cur_y, cur_x);

	return;
}

//opens a chest, removing a chest from the map and adding whiffles to the player
void game_logic::open_chest()
{
	//chest * tile_chest = map.get_chest(cur_y,cur_x);
	hero.addWhiffles(map.get_chest(cur_y, cur_x));

	map.remove_stuff(cur_y, cur_x);

	return;
}

void game_logic::buy_ship()
{
	if(hero.getWhiffles() < 50)
	{
		return;
	}

	hero.inShip();
	hero.loseWhiffles(50);

	map.remove_stuff(cur_y, cur_x);

	return;
}

void game_logic::buy_binoculars()
{
	if(hero.getWhiffles() < 25)
	{
		return;
	}

	hero.addBino();
	hero.loseWhiffles(25);
	map.remove_stuff(cur_y, cur_x);

	return;
}

void game_logic::display_clue()
{
}
