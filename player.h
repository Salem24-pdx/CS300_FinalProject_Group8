#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;
struct tool{	//Tool data type
	string name;
	int type;
	int energyDiv;
};

struct node{	//Linked list of tools
	tool data;
	node * next;
};

class player
{
	public:
		player ();
		~player ();
		 
		int getWhiffles();	//Player whiffle functions
		int loseWhiffles(int x);
		int addWhiffles(int x);

		int getEnergy();	//Player energy functions
		int loseEnergy(int x);
		int addEnergy(int x);

		int displayTools(); //Wrappers for the linked list

		int addTool(tool & to_add);

		int retrieve(int check);
		
		int remove(string item);
	private:
		int energy;	//Private data types and functions
		int whiffles;
		node * head;
		int addTool(node * & head, tool & to_add);	//Linked list recursive functions
		int displayTools(node * head);
		int retrieve(node * head,  int check);
		int remove (node *  & head, string item);
		int removeAll(node * &head);
};
