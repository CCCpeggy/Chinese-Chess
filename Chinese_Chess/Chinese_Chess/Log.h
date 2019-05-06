#ifndef  _LOG_
#define _LOG_

#include "Board.h"
#include <utility>
#include<string>
class Log
{
private:
	vector<pair<Board, int> > record;//存每一手的棋盤
	int move;//第幾手
	vector<string>displayText;
	string pieceName[15] = { "","將 ","士 ","象 ","車 ","馬 ","包 ","卒 ","帥 ","仕 ","象 ","車 ","傌 ","炮 ","兵 " };
	string roadBlack[9] = { "１ ","２ ","３ ","４ ","５ ","６ ","７ ","８ ","９ " };
	string roadRed[9] = { "九 ","八 ","七 ","六 ","五 ","四 ","三 ","二 ","一 " };
	string action[3] = { "平 ","進 ","退 " };
public:
	void WriteLog(Board, int player);
	bool isFirst();//判斷有沒有前一筆
	bool isFinal();
	void moveDisplay(int piece, Point original, Point change);//戰況顯示
	vector<string> getMove();
	pair<Board, int> LastBoard();
	pair<Board, int> NextBoard();
};

#endif