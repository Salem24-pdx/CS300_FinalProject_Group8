#include <string>
#include "loader.h"

using namespace std;

int main() {
	string filename = "savefile.dat";
	loader l;

	l.loadIn(filename.c_str());

	return 0;
}
