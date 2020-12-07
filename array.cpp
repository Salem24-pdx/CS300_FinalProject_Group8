/*
 * CS300 Fruple 2d array date structure implement file
 * Jiawei Liu 2020
 * This is the .cpp file for array
 */

#include"array.h"


Array::Array()
{
	array = new Cell * [128];
	for(int i = 0; i < 128; ++i)
		array[i] = new Cell[128];
	//initialize

	for(int i = 0; i < 128; ++i)
		for(int j = 0; j < 128; ++j)
		{
			array[i][j].clue = false;
			array[i][j].has_clue = false;
			array[i][j].seen = false;
			array[i][j].chest = 0;
			array[i][j].terrain = HIDDEN;


			array[i][j].food = NULL;
			array[i][j].obstacle = NULL;
			array[i][j].tool = NULL;
		}

}
Array::~Array()
{
}

//getters

bool Array::is_seen(int row, int col)
{
	return array[row][col].seen;
}

//return food obj in cell
Food * Array::get_food(int row, int col)
{
	return array[row][col].food;
}

//return obstacle obj
Obstacle * Array::get_obstacle(int row, int col)
{
	return array[row][col].obstacle;
}

//return tool obj
Tool * Array::get_tool(int row, int col)
{
	return array[row][col].tool;
}

//return the truthfulness
bool Array::get_clue(int row, int col)
{
	return array[row][col].clue;
}
bool Array::is_clue(int row, int col)
{
	return array[row][col].has_clue;
}

int Array::get_chest(int row, int col)
{
	return array[row][col].chest;
}

int Array::get_terrain(int row, int col)
{
	return array[row][col].terrain;
}
//setters
void Array::set_seen(int row, int col, bool revealed)
{
	array[row][col].seen = revealed;
}

void Array::set_food(int row, int col, Food * obj)
{
	array[row][col].food = obj;
}

void Array::set_obstacle(int row, int col, Obstacle * obj)
{
	array[row][col].obstacle = obj;
}
void Array::set_tool(int row, int col, Tool * obj)
{
	array[row][col].tool = obj;
}

void Array::set_clue(int row, int col, bool clue)
{
	array[row][col].clue = clue;
	array[row][col].has_clue = true;
}
void Array::set_chest(int row, int col, int money)
{
	array[row][col].chest = money;
}

void Array::place_terrain(int row, int col, int type)
{
	array[row][col].terrain = type;
}

/*void Array::set_terrain(int row, int col, Cell * obj)
{
	set_food(row, col, obj -> food);
	set_obstacle(row, col, obj -> obstacle);
	set_tool(row, col, obj -> tool);
	place_terrain(row, col, obj -> tile -> type);
	set_clue(row, col, obj -> clue);
	set_chest(row, col, obj -> chest);

}
*/

//remove tools, obstacle, food, chest, return true if success
bool Array::remove_stuff(int row, int col)
{

	array[row][col].food = NULL;
	array[row][col].obstacle = NULL;
	array[row][col].tool = NULL;
	array[row][col].chest = 0;
	array[row][col].has_clue = false;

	return true;
}





















