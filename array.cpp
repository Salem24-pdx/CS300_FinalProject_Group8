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
			array[i][j].clue = NULL;
			array[i][j].food -> name = NULL;
			array[i][j].obstacle -> name = NULL;
			array[i][j].tool -> name = NULL;
			array[i][j].tile -> name = NULL;
		}
}
Array::~Array()
{
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
		}	
	delete [] array;
	delete array;
}

//getters

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

char * Array::get_clue(int row, int col)
{
	return array[row][col].clue;
}

Cell & Array::get_terrain(int row, int col)
{
	return array[row][col];
}



















