#include "player.h"


player::player()
{
	whiffles = 1000;
	energy = 100;
	head = NULL;
	ship = 0;
	bino = 0;
	array_size = 2;
	array_head = new node *[2];
	for (int i = 0; i<2; i++)
	{
		array_head[i]=NULL;
	}
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
	for (int i=0;i<array_size;i++)
	{
		node * curr = array_head[i];
		if (curr)
			cout<<"Chain #"<<i<<endl;
		while (curr)
		{
			cout<<curr->data.name;
			curr = curr ->next;
		}

	}
	return 0;
}
int player::addTool(Tool * to_add)
{
	return	addTool((array_head[to_add->type]),to_add);
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

node * player::retrieve(int check)
{
	return (array_head[check]);
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
	return 1;
}

int player::remove(Tool & item)
{
	return remove(array_head[item.type],item);
}
int player::remove(node * &head,Tool & item)	//Function to remove a single tool based on name
{
	if (!head)
		return 0;
	if (head->data.name.compare(item.name)==0 && head->data.energyDiv == item.energyDiv)
	{
		node * temp = head -> next;
		delete (head);
		head = temp;
		return 1;
	}
		//delete
	return remove(head->next,item);
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



