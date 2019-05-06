#ifndef  _LOG_
#define _LOG_

#include "Board.h"
#include <utility>
#include<string>
class Log
{
private:
	vector<pair<Board, int> > record;//�s�C�@�⪺�ѽL
	int move;//�ĴX��
	vector<string>displayText;
	string pieceName[15] = { "","�N ","�h ","�H ","�� ","�� ","�] ","�� ","�� ","�K ","�H ","�� ","�X ","�� ","�L " };
	string roadBlack[9] = { "�� ","�� ","�� ","�� ","�� ","�� ","�� ","�� ","�� " };
	string roadRed[9] = { "�E ","�K ","�C ","�� ","�� ","�| ","�T ","�G ","�@ " };
	string action[3] = { "�� ","�i ","�h " };
public:
	void WriteLog(Board, int player);
	bool isFirst();//�P�_���S���e�@��
	bool isFinal();
	void moveDisplay(int piece, Point original, Point change);//�Ԫp���
	vector<string> getMove();
	pair<Board, int> LastBoard();
	pair<Board, int> NextBoard();
};

#endif