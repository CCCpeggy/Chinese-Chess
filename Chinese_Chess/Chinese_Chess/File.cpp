#include "File.h"
#include<fstream>
pair<Board,int> File::loadFile(string filename)
{
	ifstream boardinfo;
	boardinfo.open(filename);
	Board board;
	short temp;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			boardinfo >> temp;
			if (temp == 0) { temp = 15; }
			board[Point(i,j)] = temp;
		}
	}
	boardinfo >> temp;
	int player;
	player = temp;
	boardinfo.close();
	return pair<Board,int>(board,player);
}

void File::writeFile(Board, string)
{
	//§âboard¼g¥X¥h
}
