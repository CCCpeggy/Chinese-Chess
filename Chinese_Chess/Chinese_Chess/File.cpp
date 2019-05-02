#include "File.h"
#include<fstream>
Board File::loadFile(string filename)
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
	//player = temp;
	boardinfo.close();
	return board;
}

void File::writeFile(Board, string)
{
	//§âboard¼g¥X¥h
}
