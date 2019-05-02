#ifndef  _FILE_
#define _FILE_

#include <string>
#include "Board.h"
using namespace std;
class File
{
public:
	pair<Board,int> loadFile(string);
	void writeFile(Board, string);
};

#endif