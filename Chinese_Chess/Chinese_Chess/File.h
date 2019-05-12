#ifndef  _FILE_
#define _FILE_

#include <string>
#include "Board.h"
#include "Log.h"
using namespace std;
class File
{
public:
	pair<Board,int> loadFile(string);
	void writeFile(Board x,int player);
	void writeAll(vector < pair<Board, int> >rec,int move);
	vector<pair<Board, int>> loadAll(string filename);
};

#endif