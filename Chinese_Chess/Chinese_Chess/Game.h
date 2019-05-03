#ifndef  _GAME_
#define _GAME_

#include "Board.h"
#include "Piece.h"
#include "Log.h"
#include <string>
#include<windows.h>
#include <iostream>
#include <cmath>
using namespace std;
class Game
{
private:
	int player = 0;  // 0 1

public:
	Game();
	Board board;
	Log log;
	Piece pieces[16];
	Piece piecegrid;

	//draw console
	void drawInterface(); //將Game的資料顯示
	void drawMenu(int); //0 1 2 3
	void drawDialog(string, int);  //Button是否, 1是 0否

	//player
	void setPlayer(int);
	void changePlayer();
	int getPlayer();
};

#endif