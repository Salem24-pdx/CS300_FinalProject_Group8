#include <ncurses.h>
#include "controls.h"
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
int check_next(int ch, array & map, int y, int x, int ymax, int xmax)
{

	Tile * temp_tile = NULL;
	

	if(ch == KEY_DOWN && y < ymax)
	{
		--y;
	}
	else if(ch == KEY_DOWN && y < ymax)
	{
		++y;
	}
	else if(ch == KEY_LEFT && x > 0)
	{
		--x;
	}
	else if(ch == KEY_RIGHT && x < xmax)
	{
		++x;
	}

	temp_tile = map.get_tile(y, x);
	return temp_tile.number;
}

//moves the player and performs various actions based on the cell
void move(int ch, player & hero, array & map, int & y, int & x, int ymax, int xmax)
{
	int tile_check;
	char item_check = 'a';

	//checks to see what the next tile is
	tile_check = check_next(ch, map, y, x, ymax, xmax);
	if(tile_check == 4)
	{
		hero.loseEnergy(1);
		return;
	}
	else if(tile_check == 2)
	{
		hero.loseEnergy(2);
	}
	else
	{
		hero.loseEnergy(1);
	}

	//moves the player to the next tile
	if(ch == KEY_UP && y > 0)
	{
		--y;
	}
	else if(ch == KEY_DOWN && y < ymax)
	{
		++y;
	}
	else if(ch == KEY_LEFT && x > 0)
	{
		--x;
	}
	else if(ch == KEY_RIGHT && x < xmax)
	{
		++x;
	}

	//checks to see what item is in a tile
	item_check = map.check_cell(y, x);

	if(item_check == FOOD)
	{
		buy_food(hero, map, y, x);
	}
	if(item_check == TOOL)
	{
		buy_tool(hero, map, y, x);
	}
	if(item_check == OBSTACLE)
	{
		remove_obstacle(hero, map, y, x);
	}
	if(item_check == CHEST)
	{
		open_chest(hero, map, y, x);
	}


}

//buys food, adding energy and removing whiffles from the player
void buy_food(player & hero, array & map, int y, int x)
{
	food * tile_food = map.get_food(y, x);
	if(hero.getWhiffles() < tile_food.cost)
	{
		return;
	}

	
	hero.addEnergy(tile_food.energy);
	hero.loseWiffles(tile_food.cost);

	return;
}

//buys a tool, removing whiffles and adding a tool to the player
void buy_tool(player & hero, array & map, int y, int x)
{
	tool * tile_tool = map.get_tool(y, x);
	if(hero.getWhiffles() < tile_tool.cost)
	{
		return;
	}

	hero.addTool(tile_tool);
	hero.loseWhiffles(tile_tool.cost);

	return;
}

//removes an obstacle from the map. checks to see if the player has a matching
//tool type and if so, uses up the tool
void remove_obstacle(player & hero, array & map, int y, int x)
{
	//not finished
	obstacle * tile_obstacle = map.get_obstacle(y, x);
	int cost_divider = hero.retrieve(tile_obstacle.type);
	
	hero.loseEnergy(tile_obstacle.cost/cost_divider);

	hero.remove(tile_obstacle.name);


	return;
}

//opens a chest, removing a chest from the map and adding whiffles to the player
void open_chest(player & hero, array & map, int y, int x)
{
	chest * tile_chest = map.get_chest(y, x);
	hero.addWhiffles(tile_chest.value);

	return;
}
