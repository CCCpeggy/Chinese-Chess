#ifndef  _BOARD_
#define _BOARD_

#include <vector>
#include "Point.h"
using namespace std;
class Board
{

public:
	Board();
	void changeBoard(Board);
	void select(Point);
	int move(Point, Point);
	void repent(Board);
	void randMove(int player);
	vector<short>& operator [](int);
	short& operator [](Point&);
private:
	void deselect();
	vector<vector<short>> board;
	void ifPointValidChangeBoard(Point, Point,Point leftUp= Point (0,0),Point rightDown = Point(9, 8));
	Point findChess(int);//only for ±N«Ó,§ä¤£¨ìret(-1,-1)
};

#endif
