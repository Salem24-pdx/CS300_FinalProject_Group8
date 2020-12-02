#ifndef LOADER_H
#define LOADER_H

#include "common.h"

#include <string>
#include <vector>

using namespace std;

class loader
{
	public:
		loader();
		~loader();
		int loadIn(const char* filename);


	private:

	        vector<Food *> foods;
        	vector<Tool *> tools;
        	vector<Obstacle *> obstacles;

};


#endif /* LOADER_H */
