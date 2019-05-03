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
	void drawInterface(); //�NGame��������
	void drawMenu(int); //0 1 2 3
	void drawDialog(string, int);  //Button�O�_, 1�O 0�_

	//player
	void setPlayer(int);
	void changePlayer();
	int getPlayer();
};

#endif