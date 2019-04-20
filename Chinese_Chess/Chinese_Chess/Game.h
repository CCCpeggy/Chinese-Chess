#ifndef  _GAME_
#define _GAME_

#include "Board.h"
#include "Log.h"
#include <string>
using namespace std;
class Game
{
private:
	int player;
	
public:
	Game();
	Board board;
	Log log;
	void drawInterface(); //�NGame��������
	void drawMenu(int); //0 1 2 3
	void drawDialog(string, int);  //Button�O�_, 1�O 0�_
	void changePlayer();
};

#endif