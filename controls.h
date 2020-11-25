void add_energy(int & energy, int to_add);
void remove_energy(int & energy, int to_remove);
void add_whiffles(int & whiffles, int to_add);
void remove_whiffles(int & whiffles, int to_remove);
int check_next(int ch, cell map[128][128], int y, int x, int ymax, int xmax);
void move(int ch, cell map[128][128], int & y, int & x, int ymax, int xmax, int & energy);
void buy_food(int & whiffles, int & energy, int whiffles_remove, int energy_add);
void buy_tool(int & whiffles);
void remove_obstacle(int & energy, int energy_cost);


