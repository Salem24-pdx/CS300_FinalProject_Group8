#include <ncurses.h>
#include "controls.h"
#include "common.h"
using namespace std;

/*void add_energy(int & energy, int to_add)
{
	energy += to_add;
	return;
}

void remove_energy(int & energy, int to_remove)
{
	energy -= to_remove;
	return;
}

void add_whiffles(int & whiffles, int to_add)
{
	whiffles += to_add;
	return;
}

void remove_whiffles(int & whiffles, int to_remove)
{
	whiffles -= to_remove;
	return;
}*/

//Checks to see the next tile before the player moves there
int game_logic::check_next(int ch)
{

	int next_x = cur_x;
	int next_y = cur_y;
	Tile * temp_tile = NULL;
	

	if(ch == KEY_UP && next_y > 0)
	{
		--next_y;
	}
	else if(ch == KEY_DOWN && next_y < 127)
	{
		++next_y;
	}
	else if(ch == KEY_LEFT && next_x > 0)
	{
		--next_x;
	}
	else if(ch == KEY_RIGHT && next_x < 127)
	{
		++next_x;
	}

	temp_tile = map.get_tile(next_y, next_x);
	return temp_tile.type;
}

//moves the player and performs various actions based on the cell
void game_logic::move(int ch)
{
	int tile_check;
	//char item_check = 'a';

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
	if(ch == KEY_UP && cur_y > 0)
	{
		--cur_y;
	}
	else if(ch == KEY_DOWN && cur_y < ymax)
	{
		++cur_y;
	}
	else if(ch == KEY_LEFT && cur_x > 0)
	{
		--cur_x;
	}
	else if(ch == KEY_RIGHT && cur_x < xmax)
	{
		++cur_x;
	}

	//checks to see what item is in a tile
	//item_check = map.check_cell(y, x);

	
	if(map.get_food(cur_y, cur_x))
	{
		buy_food();
	}
	if(get_tool(cur_y, cur_x))
	{
		buy_tool();
	}
	if(get_obstacle(cur_y, cur_x))
	{
		remove_obstacle();
	}
	if(get_chest(cur_y, cur_x))
	{
		open_chest();
	}
	if(get_ship(cur_y, cur_x))
	{
		buy_ship();
	}
	if(get_binoculars(cur_y, cur_x))
	{
		buy_binoculars();
	if(get_clue(cur_y, cur_x))
	{
		display_clue();
	}
	

}

//buys food, adding energy and removing whiffles from the player
void game_logic::buy_food()
{
	Food * tile_food = map.get_food(cur_y, cur_x);
	if(hero.getWhiffles() < tile_food.cost)
	{
		return;
	}

	
	hero.addEnergy(tile_food.energy);
	hero.loseWiffles(tile_food.cost);
	map.remove_stuff(cur_y, cur_x);

	return;
}

//buys a tool, removing whiffles and adding a tool to the player
void game_logic::buy_tool()
{
	Tool * tile_tool = map.get_tool(cur_y, curx);
	if(hero.getWhiffles() < tile_tool.cost)
	{
		return;
	}

	hero.addTool(tile_tool);
	hero.loseWhiffles(tile_tool.cost);
	map.remove_stuff(cur_y, cur_x);

	return;
}

//removes an obstacle from the map. checks to see if the player has a matching
//tool type and if so, uses up the tool
void game_logic::remove_obstacle()
{
	//double check function
	Obstacle * tile_obstacle = map.get_obstacle(cur_y, cur_x);
	int cost_divider = hero.retrieve(tile_obstacle.type);
	
	if(cost_divider == 0)
	{
		hero.loseEnergy(tile_obstacle.cost);
	}
	else
	{
		hero.loseEnergy(tile_obstacle.cost/cost_divider);
		if(tile_obstacle.type == 1)
		{
			hero.remove("PICK");
		}
		if(tile_obstacle.type == 2)
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
