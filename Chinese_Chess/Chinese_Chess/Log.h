#ifndef  _LOG_
#define _LOG_

#include "Board.h"
#include <utility>
class Log
{
private:
	vector<pair<Board, int> > record;//存每一手的棋盤
	int move;//第幾手
public:
	void WriteLog(Board, int player);
	bool isFirst();//判斷有沒有前一筆
	bool isFinal();
	pair<Board, int> LastBoard();
	pair<Board, int> NextBoard();
};

#endif