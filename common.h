/*
 * 
 */


#include<iostream>
#include<cctype>
#include<cstring>
using namespace std;

// common use data structures and constant

// items
const char FOOD = 'F';
const char TOOL = 'T';
const char OBSTACLE = '!';
const char CHEST = '$';
const char SHIP = 'S';
const char BINOCULARS = 'B';
const char NONE = ' ';
const char HEROCHAR = '@';

// terrains
// todo: set these to color pair reverence values and check datatype
const int MEADOW = 1;   // black on green
const int SWAMP = 2;    // black on magenta
const int WATER = 3;    // black on blue
const int WALL = 4;     // black on white
const int HERO = 5;     // yellow on red
const int DIAMOND = 6;  // white on cyan
const int HIDDEN = 7;   // normal on black

// directions
const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 3;
const int WEST = 4;


struct Food {
	string name;
	int cost;
	int energy;
};

struct Tool {
    string name;
	int cost;
	int type;
        int energyDiv;
	bool purchased;
};

struct Obstacle {
	string name;
	int type;
	int cost;
};

struct Clue {
	bool accuracy;
};

struct Chest {
	int value;
};

