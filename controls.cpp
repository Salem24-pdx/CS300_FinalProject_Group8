#include <ncurses.h>
#include "controls.h"

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

void move(int ch, array & map, int & y, int & x, int ymax, int xmax, player & hero)
{
	int tile_check;

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
}

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

void remove_obstacle(player & hero, array & map, int y, int x)
{
	//not finished
	obstacle * tile_obstacle = map.get_obstacle(y, x);
	int cost_divider = hero.retrieve(tile_obstacle.type);

	if(cost_divider == 0)
	{
		hero.loseEngery(tile_obstacle.cost);

	}
	return;
}

void open_chest(player & hero, array & map, int y, int x)
{
	chest * tile_chest = map.get_chest(y, x);
	hero.addWhiffles(tile_chest.value);

	return;
}
