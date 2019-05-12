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
	pair<Point, Point> randMove(int player);//return ��m �ت��a
	vector<short>& operator [](int);
	short& operator [](Point&);
private:
	void deselect();
	friend int player(Board&,Point);
	vector<vector<short>> board;
	bool checkPointInBoard(Point);
	void ifPointValidChangeBoard(Point, Point,Point leftUp= Point (0,0),Point rightDown = Point(9, 8));
	Point findChess(int);//only for �N��,�䤣��ret(-1,-1)
};

#endif
