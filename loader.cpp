#include "loader.h"
#include "common.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>	// transform
#include <cctype>	// tolower

using namespace std;

loader::loader() {
/*	obstacles.clear();
	foods.clear();
	tools.clear();
*/
}

loader::~loader() {
	for (auto ptr : obstacles) {
		delete ptr;
	}
	for (auto ptr : foods) {
		delete ptr;
	}
	for (auto ptr : tools) {
		delete ptr;
	}
}

int loader::loadIn(const char* filename) {

	ifstream infile(filename);
	string line;

	const int LMAP = 1;
	const int LHERO = 2;
	const int LFOOD = 3;
	const int LTOOL = 4;
	const int LOBSTICAL = 5;
	const int LCLUE = 6;
	const int LCHEST = 7;


	int section = 0;

	while (getline(infile, line)) {

		line = line.substr(0, line.find("#")); // truncate comments at #
//printf("%s\n", line.c_str());

		istringstream s(line);
		string word;

		if (!(s >> word)) {  // blank line
			continue;
		}
//printf("%s\n", word.c_str());
		// select section
		if (word.rfind("[", 0) == 0) {
		transform(word.begin(), word.end(), word.begin(), ::tolower); // lowercase the section header
		}
		if (word.rfind("[map]", 0) == 0) {
			section = LMAP;
			continue;
		}
		if (word.rfind("[hero]", 0) == 0) {
			section = LHERO;
			continue;
		}
		if (word.rfind("[food]", 0) == 0) {
			section = LFOOD;
			continue;
		}
		if (word.rfind("[tool]", 0) == 0) {
			section = LTOOL;
			continue;
		}
		if (word.rfind("[obstical]", 0) == 0) {
			section = LOBSTICAL;
			continue;
		}
		if (word.rfind("[clue]", 0) == 0) {
			section = LCLUE;
			continue;
		}
		if (word.rfind("[chest]", 0) == 0) {
			section = LCHEST;
			continue;
		}

		if (section == 0) {
			continue;	// we havent declared a section yet
		}

		switch(section) {
			case LMAP :
				break;
			case LHERO :
				break;
			case LFOOD :
				{
					Food* thisfood = new Food;

					string name = word;
					if (name.rfind("\"", 0) == 0) {		// name is quoted, so add to it until we find a terminating quote
						while (name.back() != '\"') {
							string nextpart;
							s >> nextpart;
							name = name + " " + nextpart;
						}
					}
					if (name.front() == '\"') {
						name.erase(0,1);
					}
					if (name.back() == '\"') {
						name.pop_back();
					}
					thisfood->name = name;

					s >> thisfood->cost >> thisfood->energy;

					int x, y;
					s >> x >> y;

					foods.push_back(thisfood);

// TODO					Array::set_food(y, x, thisfood);
printf("%s\n%i\n%i\n%i\n%i\n\n",thisfood->name.c_str(), thisfood->cost, thisfood->energy, x, y);
//delete thisfood;
				}
				break;
			case LTOOL :
				break;
			case LOBSTICAL :
				break;
			case LCLUE :
				break;
			case LCHEST :
				break;
			default :
				continue;
		}

	}

	infile.close();
	return 0;

}

