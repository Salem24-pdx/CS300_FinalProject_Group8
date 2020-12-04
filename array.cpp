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
	/*
	for(int i = 0; i < 128; ++i)
		for(int j = 0; j < 128; ++j)
		{
			array[i][j].clue = NULL;
			array[i][j].food -> name = NULL;
			array[i][j].obstacle -> name = NULL;
			array[i][j].tool -> name = NULL;
			array[i][j].tile -> name = NULL;
		}
	*/
}
Array::~Array()
{
	/*
	for(int i = 0; i < 128; ++i)
		for(int j = 0; j < 128; ++j)
		{
			if(array[i][j].clue != NULL)
				delete array[i][j].clue;
			if(array[i][j].food -> name != NULL)
				delete array[i][j].food -> name;
			if(array[i][j].tool -> name != NULL)
				delete array[i][j].tool -> name;
			if(array[i][j].obstacle -> name != NULL)
				delete array[i][j].obstacle -> name;
			if(array[i][j].tile -> name != NULL)
				delete array[i][j].tile -> name;
		}*/	
	//delete [] array;
	//delete array;
}

//getters

bool Array::is_seen(int row, int col)
{
	return array[row][col].seen;
}

//return food obj in cell
Food *& Array::get_food(int row, int col)
{
	return array[row][col].food;
}

//return obstacle obj
Obstacle *& Array::get_obstacle(int row, int col)
{
	return array[row][col].obstacle;
}

//return tool obj
Tool *& Array::get_tool(int row, int col)
{
	return array[row][col].tool;
}

//return tile obj
Tile *& Array::get_tile(int row, int col)
{
	return array[row][col].tile;
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
	return array[row][col].tile -> type;
}
//setters

void Array::set_seen(int row, int col, bool revealed)
{
	array[row][col].seen = revealed;
}

void Array::set_food(int row, int col, Food * obj)
{
	array[row][col].food = obj;
	/*
	if(array[row][col].food == NULL)			
	{
		array[row][col].food = new Food;
		array[row][col].food -> name = obj -> name;
		array[row][col].food -> cost = obj -> cost;
		array[row][col].food -> energy = obj -> energy;
	}
	else 
	{
		array[row][col].food -> name = obj -> name;
		array[row][col].food -> cost = obj -> cost;
		array[row][col].food -> energy = obj -> energy;
	}	
	*/
}

void Array::set_obstacle(int row, int col, Obstacle * obj)
{
	array[row][col].obstacle = obj;
	/*
	if(array[row][col].obstacle == NULL)			
	{
		array[row][col].obstacle = new Obstacle;
		array[row][col].obstacle -> name = obj -> name;
		array[row][col].obstacle -> cost = obj -> cost;
		array[row][col].obstacle -> type = obj -> type;
	}
	else 
	{
		array[row][col].obstacle -> name = obj -> name;
		array[row][col].obstacle -> cost = obj -> cost;
		array[row][col].obstacle -> type = obj -> type;
	}
	*/
}
void Array::set_tool(int row, int col, Tool * obj)
{
	array[row][col].tool = obj;

	/*
	if(array[row][col].tool == NULL)			
	{
		array[row][col].tool = new Tool;
	}
	array[row][col].tool -> name = obj -> name;
	array[row][col].tool -> cost = obj -> cost;
	array[row][col].tool -> type = obj -> type;
	array[row][col].tool -> energyDiv = obj -> energyDiv;
//	array[row][col].tool -> purchased = obj -> purchased;  ** set ->cost = 0 instead when bought
	*/	
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
	if(array[row][col].tile == NULL)
		array[row][col].tile = new Tile;
	array[row][col].tile -> type = type;

}

void Array::set_terrain(int row, int col, Cell * obj)
{
	set_food(row, col, obj -> food);
	set_obstacle(row, col, obj -> obstacle);
	set_tool(row, col, obj -> tool);
	place_terrain(row, col, obj -> tile -> type);
	set_clue(row, col, obj -> clue);
	set_chest(row, col, obj -> chest);
}


//remove tools, obstacle, food, chest, return true if success
bool Array::remove_stuff(int row, int col)
{

	array[row][col].food = NULL;
	array[row][col].obstacle = NULL;
	array[row][col].tool = NULL;
	array[row][col].chest = 0;


	if(array[row][col].food != NULL)
	{
		delete array[row][col].food;
		return true;
	}
	else if(array[row][col].obstacle != NULL)
	{
		delete array[row][col].obstacle;
		return true;
	}
	else if(array[row][col].tool != NULL)
	{
		delete array[row][col].tool;
		return true;
	}
	else if(array[row][col].chest != 0)
	{
		array[row][col].chest = 0;
		return true;
	}
	//Does tile need to be removed?

	/*
	else if(array[row][col].binocular == true)
	{
		array[row][col].binocular = false;
		return true;
	}
	*/
	else
		return false;
}





















