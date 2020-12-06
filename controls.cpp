#include <ncurses.h>
#include "controls.h"
#include "common.h"
using namespace std;



game_logic::game_logic()
{
	string filename = "leveltemp.dat";
//	Array * ptrMap = &map;
	l.loadIn(filename.c_str(), &map);
	cur_x = l.getHeroCol();
	cur_y = l.getHeroLine();
}

game_logic::~game_logic()
{
}

void game_logic::start()
{
	s.init();

	// set up for first turn
	s.putCursor(cur_x, cur_y);
	s.center(cur_x, cur_y);
	look(cur_y, cur_x);
	discover(cur_y, cur_x);
	moveMenu();
        if ((s.getCursorY() == cur_y) && (s.getCursorX() == cur_x)) {
        	actionMenu();
        }
	updateStats();

	int key = 0;
	while (key != 'q' && hero.getEnergy()>=0){

		key = s.getKey();

		if (key == '+') {
			hero.addEnergy(1000000);
			updateStats();
		}

		//move hero
		if (key == '1' || key == '2' || key == '3' || key == '4')
		{
			move(key);
			look(cur_y, cur_x);
			discover(cur_y, cur_x);
			moveMenu();
			actionMenu();
			updateStats();
		}

		// move cursor
                if (key == KEY_UP) {
                        s.moveCursor(NORTH);
			discover(s.getCursorY(), s.getCursorX());
			moveMenu();
                }
                if (key == KEY_DOWN) {
                        s.moveCursor(SOUTH);
                        discover(s.getCursorY(), s.getCursorX());
			moveMenu();
                }
                if (key == KEY_LEFT) {
                        s.moveCursor(WEST);
                        discover(s.getCursorY(), s.getCursorX());
			moveMenu();
                }
                if (key == KEY_RIGHT) {
                        s.moveCursor(EAST);
                        discover(s.getCursorY(), s.getCursorX());
			moveMenu();
                }

		// actions
		if ((s.getCursorY() == cur_y) && (s.getCursorX() == cur_x)) {
			char item = whats_at(cur_y, cur_x);

			// action by keypress
			if (key == '5' && item != NONE) {
				switch (item) {
					case FOOD:
						s.clearmenu();
						moveMenu();
						buy_food();
						updateStats();
						break;
					case SHIP:
						s.clearmenu();
						moveMenu();
						buy_ship();
						updateStats();
						break;
					case BINOCULARS:
						s.clearmenu();
						moveMenu();
						buy_binoculars();
						updateStats();
						break;
					case TOOL:
						s.clearmenu();
						moveMenu();
						buy_tool();
						updateStats();
						break;
				}
			}

			//automatic action
			if (item != NONE) {
				switch (item) {
					case CHEST:
						s.clearmenu();
						moveMenu();
						open_chest();
						updateStats();
						break;
					case OBSTACLE:
						s.clearmenu();
						moveMenu();
						remove_obstacle();
						updateStats();
						break;
					case CLUE:
						s.clearmenu();
						moveMenu();
						display_clue();
						updateStats();
						break;
				}
			}
		}
	}
}
//checks to see the next tile before the playere moves there
int game_logic::check_next(int ch)
{

	int next_x = cur_x;
	int next_y = cur_y;
//	Tile * temp_tile = NULL;
	

	if(ch == '1' && next_y > 0)//check north
	{
		--next_y;
	}
	else if(ch == '3' && next_y < 127)//check south
	{
		++next_y;
	}
	else if(ch == '4' && next_x > 0)//check west
	{
		--next_x;
	}
	else if(ch == '2' && next_x < 127)//check east
	{
		++next_x;
	}

//	temp_tile = map.get_tile(next_y, next_x);
//	return temp_tile->type;

	return map.get_terrain(next_y, next_x);
}

//moves the player and performs various actions based on the cell
void game_logic::move(int ch)
{

	int tile_check;


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
	if(ch == '1' && cur_y > 0)//move north
	{
		--cur_y;
	}
	else if(ch == '3' && cur_y < 127)//move south
	{
		++cur_y;
	}
	else if(ch == '4' && cur_x > 0)//move west
	{
		--cur_x;
	}
	else if(ch == '2' && cur_x < 127)//move east
	{
		++cur_x;
	}


}

//buys food, adding energy and removing whiffles from the player
void game_logic::buy_food()
{
	Food * tile_food = map.get_food(cur_y, cur_x);
	//s.printtomenu("Food: " + tile_food->name + "\nCost: " + to_string(tile_food->cost) + "\nEnergy Gained: " + to_string(tile_food->energy));

	if(hero.getWhiffles() < tile_food->cost)
	{
		return;
	}


	hero.addEnergy(tile_food->energy);
	hero.loseWhiffles(tile_food->cost);
	map.remove_stuff(cur_y, cur_x);

	s.printtomenu("\nDelicious and nutritious!\n");
	return;
}

//buys a tool, removing whiffles and adding a tool to the player
void game_logic::buy_tool()
{
	Tool * tile_tool = map.get_tool(cur_y, cur_x);
	//s.printtomenu("Tool: " + tile_tool->name + "\nCost: " + to_string(tile_tool->cost));

	if(hero.getWhiffles() < tile_tool->cost)
	{
		return;
	}

	hero.addTool(tile_tool);
	hero.loseWhiffles(tile_tool->cost);
	map.remove_stuff(cur_y, cur_x);

	return;
}

//removes an obstacle from the map. checks to see if the player has a matching
//tool type and if so, uses up the tool
void game_logic::remove_obstacle()
{
	//double check function
	Obstacle * tile_obstacle = map.get_obstacle(cur_y, cur_x);
	
	node * inventory = hero.retrieve(tile_obstacle->type);
	if (hero.getEnergy() < tile_obstacle->cost)
		return;
	s.printtomenu("\n> Which tool?\n");
	int x = '6';
	int z = 'z';
	node * curr = inventory;
	s.printtomenu("\n 0) to break it without a tool\n");
	while (curr != NULL)
	{
		string tempTool;
		tempTool += "\n";
		tempTool+= x;
	       	tempTool += ") Tool: " + curr->data.name + " Reduce energy cost by " + to_string(curr->data.energyDiv) + "\n"; 
		s.printtomenu(tempTool);
		curr = curr->next;
		++x;
	}
	while((z >= 58 || z <= 53) && z != '0')
	{
		z = s.getKey();
	}
	curr = inventory;
	if(z<x &&z >=54)
	{
		int counter = z-54;
		while (curr != NULL && (counter>0))
		{
			curr = curr->next;
			--counter;
		}
		hero.loseEnergy(tile_obstacle->cost/curr->data.energyDiv);
		hero.remove(curr->data);

	}
	else if (z =='0')
		hero.loseEnergy(tile_obstacle->cost);
	else 
		return;
	s.clearmenu();
	moveMenu();
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

	hero.inShip(map.get_tool(cur_y,cur_x));
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

	hero.addBino(map.get_tool(cur_y,cur_x));
	hero.loseWhiffles(25);
	map.remove_stuff(cur_y, cur_x);

	return;
}

void game_logic::display_clue()
{
}

void game_logic::look(int heroLine, int heroCol) {
	int range;
	if(hero.getBino())
		range = 2;
	else 
		range = 1;

        for (int c = -1 * range; c <= range; ++c) {
                for (int l = -1 * range; l <= range; ++l)
                {
			int row = l + heroLine;
			int col = c + heroCol;

			if (row >= 0 && row <= 127 && col >= 0 && col <= 127) {
				s.put(col, row, whats_at(row, col), map.get_terrain(row, col));
				map.set_seen(row, col, true);
			}
                }
	}

	s.put(heroCol, heroLine, HEROCHAR, HERO);
	s.putCursor(heroCol, heroLine);
}

char game_logic::whats_at(int row, int col) {

        if (row < 0 || row > 127 || col < 0 || col > 127) {
		return '\0';  // return null character if out of range
	}

	if (map.get_food(row, col)) {
		return FOOD;
	}

	if (map.get_tool(row, col)) {
		if (map.get_tool(row, col)->type == 1) {
			return SHIP;
		}
		if (map.get_tool(row,col)->type == 0) {
			return BINOCULARS;
		}
		return TOOL;
	}

	if (map.get_obstacle(row, col)) {
		return OBSTACLE;
	}

	if (map.get_chest(row, col)) {
		return CHEST;
	}

	if (map.is_clue(row, col)) {
		return CLUE;
	}

	return NONE;
}

void game_logic::discover(int row, int col) {

	if (! map.is_seen(row, col)) {
		s.clearmenu();
		return;
	}

	char item = whats_at(row, col);

	string out;

	switch (item) {
		case FOOD:
			{
				Food * food = map.get_food(row, col);
				out = "> Food: " + food->name + "\n> Cost: " + to_string(food->cost) + "\n> Energy: " +to_string(food->energy) + "\n";
			}
			break;
		case SHIP:
			{
				Tool * ship = map.get_tool(row, col);
				out = "> Ship: " + ship->name + "\n> Cost: " + to_string(ship->cost) + "\n";
			}
			break;
		case BINOCULARS:
			{
				Tool * binoculars = map.get_tool(row, col);
				out = "> Binoculars: " + binoculars->name + "\n> Cost: " + to_string(binoculars->cost) + "\n";
			}
			break;
		case TOOL:
			{
				Tool * tool = map.get_tool(row, col);
				out = "> Tool: " + tool->name + "(" + to_string(tool->energyDiv) + "X)\n> Cost: " + to_string(tool->cost) + "\n";
			}
			break;
		case OBSTACLE:
			{
				Obstacle * obstacle = map.get_obstacle(row, col);
				out = "> Obstacle: " + obstacle->name + "\nEnergy required: " + to_string(obstacle->cost) + "\n";
			}
			break;
		case CHEST:
			out = "> Chest: ? whiffles\n";
	}

	if (map.get_terrain(row, col) == DIAMOND) {
		out = "> The Royal Diamond\n";
	}

	s.clearmenu();
	s.printtomenu(out);

	return;
}

void game_logic::moveMenu() {
	s.printtomenu("Options:\n1) North\n2) East\n3) South\n4) West\n");
	return;
}

void game_logic::actionMenu() {
	char item = whats_at(cur_y, cur_x);

	string out = "\n";

	switch (item) {
		case FOOD:
			out = "\n5) Purchase and eat food\n";
			break;
		case SHIP:
			out = "\n5) Purchase passage for a voyage\n";
			break;
		case BINOCULARS:
			out = "\n5) Purchase these binoculars\n";
			break;
		case TOOL:
			out = "\n5) Purchase this tool\n";
			break;
		case OBSTACLE:
			out = "\n5) Break this obstacle\n";
			break;
	}

	s.printtomenu(out);
	return;
}

void game_logic::updateStats() {

        string ENE = "Energy: " + to_string(hero.getEnergy()) + " ";
        const char *echar = ENE.c_str();

        string WH = "Whiffles: " + to_string(hero.getWhiffles()) + " ";
        const char *wchar = WH.c_str();

        s.printtobot(1, wchar);
        s.printtobot(2, echar);

	return;
}
