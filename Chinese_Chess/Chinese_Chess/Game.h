#ifndef  _GAME_
#define _GAME_

#include "Board.h"
#include "Piece.h"
#include "Log.h"
#include <string>
#include <iomanip>
#include<windows.h>
#include <io.h>
#include <direct.h>
#include <iostream>
#include <cmath>
using namespace std;
class Game
{
private:
	int player = 0;  // 0 1

public:
	Game(Board, int);
	Game(vector<pair<Board, int>>);
	Board board;
	Log log;
	static Piece pieces[15];
	Piece piecegrid;
	HANDLE handleSTDOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD originalColor = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	bool Checkmate = false;

	//draw console
	void drawInterface(); //將Game的資料顯示
	void drawCheckerboard(int, int);
	void drawBanner();
	void drawFooter();
	void drawStatus();
	void drawBattleSituation(int); //戰況顯示 取log
	void drawMenu(int); //0 1 2 3
	void drawDialog(string, int);  //Button是否, 1是 0否
	void drawUpperDialog(int);
	void drawdownerDialog(int);
	void drawStringFormat(int, string, int);
	void drawOpenTxt(int, vector<string>);

	//player
	void setPlayer(int);
	void changePlayer();
	int getPlayer();
};

#endif