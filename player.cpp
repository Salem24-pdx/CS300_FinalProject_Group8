#include "player.h"


player::player()
{
	whiffles = 1000;
	energy = 100;
	head = NULL;
	ship = 0;
	bino = 0;
}

int player::getBino()
{
	return bino;
}
int player::addBino()
{
	bino = 1;
	return bino;
}
int player::loseBino()
{
	bino = 0;
	return bino;
}

int player::getShip()
{
	return ship;
}
int player::inShip()
{
	ship = 1;
	return ship;
}
int player::outShip()
{
	ship = 0;
	return ship;
}

int player::getWhiffles()	//Function handling players whiffles
{
	return whiffles;
}
int player::loseWhiffles(int x)
{
	whiffles = whiffles - x;
	return whiffles;
}
int player::addWhiffles(int x)
{
	whiffles = whiffles + x;
	return whiffles;
}

int player::getEnergy()	//Function handling players energy
{
	return energy;
}

int player::loseEnergy(int x)
{
	energy = energy - x;
	return energy;
}
int player::addEnergy(int x)
{
	energy = energy + x;
	return energy;
}

int player::displayTools()
{
	return displayTools(head);
}
int player::displayTools(node * head)	//Function to display all items in players inventory
{
	if (head == NULL)
		return 0;
	cout<<head->data.name<<endl;
	return	displayTools(head->next);
}
int player::addTool(Tool * to_add)
{
	return	addTool(head,to_add);
}
int player::addTool(node * & head,Tool * to_add)	//Function to add a tool that meets all critera 
{
	if(!head)
	{
		node * temp = new node;
		temp->data.name = to_add->name;
		temp->data.type = to_add->type;
		temp->data.energyDiv = to_add->energyDiv;
		temp->next=NULL;
		head = temp;
		return 1;
	}
	return	addTool(head->next,to_add);
}

int player::retrieve(int check)
{
	return retrieve(head,check);
}
int player::retrieve(node * head,int check)  //Function to retrieve an item based on item type and what it can be used for
{
	if(!head)
		return 0;
	if(head->data.type == check)
	{
		cout<<head->data.name<<endl;
		return head->data.energyDiv + retrieve(head->next,check);
	}
	return	retrieve(head->next,check);
}

int player::remove(string check)
{
	return remove(head,check);
}
int player::remove(node * &head,string check)	//Function to remove a single tool based on name
{
	if (!head)
		return 0;
	if (head->data.name.compare(check)==0)
	{
		node * temp = head -> next;
		delete (head);
		head = temp;
	}
		//delete
	return remove(head->next,check);
}

int player::removeAll(node *&head) //Function to dealloacte the list of tools
{
	if (head == NULL)
		return 0;
	removeAll(head->next);
	delete (head);
	return 0;
}
player::~player()
{

}



