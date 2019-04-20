#ifndef  _FILE_
#define _FILE_

#include <string>
#include "Board.h"
using namespace std;
class File
{
public:
	Board loadFile(string);
	void writeFile(Board, string);
};

#endif