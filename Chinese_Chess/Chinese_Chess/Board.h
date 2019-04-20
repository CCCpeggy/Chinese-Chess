#ifndef  _BOARD_
#define _BOARD_

#include <vector>
#include "Point.h"
using namespace std;
class Board
{
private:
public:
	vector<vector<char>> board;
	void changeBoard(Board);
	void choose(Point);
	int move(Point, Point);
	void repent(Board);
};

#endif
