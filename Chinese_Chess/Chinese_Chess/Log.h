#ifndef  _LOG_
#define _LOG_

#include "Board.h"
#include <utility>
class Log
{
private:
	vector<pair<Board, int> > record;//�s�C�@�⪺�ѽL
	int move;//�ĴX��
public:
	void WriteLog(Board, int player);
	bool isFirst();//�P�_���S���e�@��
	bool isFinal();
	pair<Board, int> LastBoard();
	pair<Board, int> NextBoard();
};

#endif