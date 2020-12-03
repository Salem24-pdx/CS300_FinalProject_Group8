/*
 * CS300 Frupal project: array.cpp
 * Jiawei Liu 2020
 * This is the header file for the map data structure for the world
 * storing the data of each grovnick
 */
#include"common.h"

struct Cell
{
	Food * food;
	Obstacle * obstacle;
	Tool * tool;
	Tile * tile;
	
	bool clue;			// the clue to the diamond
	int chest;	
	//bool diamond;
	//bool ship;
	//bool binocular;
};

//an 2d array that contain cells
class Array
{
	public:
	Array();
	~Array();
		
	//getters
	Food *& get_food(int row, int col);
	Obstacle *& get_obstacle(int row, int col);
	Tool *& get_tool(int row, int col);
	Tile *& get_tile(int row, int col);
	int get_chest(int row, int col);	
	bool get_clue(int row, int col);

	//get the data in a cell
	Cell & get_terrain(int row, int col);

	//setters
	void set_food(int row, int col, Food *);
	void set_obstacle(int row, int col, Obstacle *);
	void set_tool(int row, int col, Tool *);
	void place_terrain(int row, int col, int type);	
	void set_chest(int row, int col, int money);
	void set_clue(int row, int col, bool clue);
	void set_terrain(int row, int col, Cell *);	
	
	//return a single character to check what in the cell
	//char check_cell(int row, int col);
	//remove tools, obstacle, food, chest, return true if success
	bool remove_stuff(int row, int col);
	private:
	Cell ** array;	
};








