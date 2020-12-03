//#include "common.h"
#include "player.h"
//#include "array.h"
#include "screen.h"
#include "loader.h"

//void add_energy(int & energy, int to_add);
//void remove_energy(int & energy, int to_remove);
//void add_whiffles(int & whiffles, int to_add);
//void remove_whiffles(int & whiffles, int to_remove);


class game_logic
{

	public:
		game_logic();
		~game_logic();
		int check_next(int ch);
		void move(int ch);
		void buy_food();
		void buy_tool();
		void remove_obstacle();
		void open_chest();
		void buy_ship();
		void buy_binoculars();
		void display_clue();

		screen s;



	private:
		player hero;
		Array map;
		loader l;
		int cur_x;
		int cur_y;
};


