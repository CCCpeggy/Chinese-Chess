#define UNICODE
#include<windows.h>
#include<iostream>
#include <string>
#include "Board.h"
using namespace std;
class Piece
{
public:
	Piece(string s = "", bool p = false);
	string symbol; //the symbol to print out
	bool player; //0:black 1:red
	void pos(string s, bool p); //set the status

	//grid
	static string gridLabel[2];
	static string gridLine[19];
	static string menu[12];
	static string dialog[5];
};

