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
	void drawInterface(); //將Game的資料顯示
	void drawMenu(int); //0 1 2 3
	void drawDialog(string, int);  //Button是否, 1是 0否
	void changePlayer();
};

#endif