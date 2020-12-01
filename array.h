/*
 * CS300 Frupal project: array.cpp
 * Jiawei Liu 2020
 * This is the header file for the map data structure for the world
 * storing the data of each grovnick
 */

#include<iostream>
using namespace std;

//the structure that store all the data in a cell
struct Food
{
	int number;
	char * name;
};

struct Obstacle
{
	int number;
	char * name;
};

struct Tool
{
	int number;
	char * name;
};

struct Tile
{
	int number;
	char * name;
};

struct Cell
{
	Food * food;
	Obstacle * obstacle;
	Tool * tool;
	Tile * tile;
	
	char * clue;			// a point to character array.
	bool diamond;
	bool ship;
	bool binocular;
};

//an 2d array that contain cells
class Array
{
	public:
	Array();
	~Array();

	Food *& get_food(int row, int col);
	Obstacle *& get_obstacle(int row, int col);
	Tool *& get_tool(int row, int col);
	Tile *& get_tile(int row, int col);

	char * get_clue(int row, int col);
	//get the data in a cell
	Cell & get_terrain(int row, int col);

	void set_food(int row, int col, Food *&);
	void set_obstacle(int row, int col, Obstacle *&);
	void set_tool(int row, int col, Tool *&);
	void set_tile(int row, int col, Tile *&);
	
	void set_terrain(int row, int col, Cell *&);
	
	private:
	Cell ** array;	
};








