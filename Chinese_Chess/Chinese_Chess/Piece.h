#define UNICODE
#include<windows.h>
#include<iostream>
#include <string>
#include "Board.h"
using namespace std;
class Piece
{
public:
	Piece();
	string symbol; //the symbol to print out
	bool player; //0:black 1:red
	int locx; 
	int locy; 
	void pos(string s, bool p, int x, int y); //set the status

	//grid
	string gridline[10][9];
};

