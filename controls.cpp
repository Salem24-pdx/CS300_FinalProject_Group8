#include <ncurses.h>
#include "controls.h"

void add_energy(int & energy, int to_add)
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
}

int check_next(int ch, cell map[128][128], int y, int x, int ymax, int xmax)
{
	int temp_y;
	int temp_x;

	if(ch == KEY_DOWN && y < ymax)
	{
		--temp_y;
	}
	else if(ch == KEY_DOWN && y < ymax)
	{
		++temp_y;
	}
	else if(ch == KEY_LEFT && x > 0)
	{
		--temp_x;
	}
	else if(ch == KEY_RIGHT && x < xmax)
	{
		++temp_x;
	}

	return map[temp_y][temp_x].tile;
}

void move(int ch, cell map[128][128], int & y, int & x, int ymax, int xmax, int & energy)
{
	int tile_check;

	tile_check = check_next(ch, map, y, x, ymax, xmax);
	if(tile_check == 3)
	{
		remove_energy(energy, 1);
		return;
	}
	else if(tile_check == 2)
	{
		remove_energy(energy, 2);
	}
	else
	{
		remove_energy(energy, 1);
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

void buy_food(int & whiffles, int & energy, int whiffles_remove, int energy_add)
{
	if(whiffles < whiffles_remove)
	{
		return;
	}

	remove_whiffles(whiffles, whiffles_remove);
	add_energy(energy, energy_add);

	return;
}

void buy_tool(int & whiffles, int cost)
{
	if(whiffles < cost)
	{
		return;
	}

	remove_whiffles(whiffles, cost);

	return;
}

void remove_obstacle(int & energy, int energy_cost)
{
	int cost_divider = 1;

	remove_energy(energy, energy_cost);

	return;
}
