#include "File.h"
#include<fstream>
#include "Log.h"
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

void File::writeFile(Board x,int player)
{
	ofstream boardOutput("outputBoard.txt");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (x[Point(i, j)]<0&& x[Point(i, j)]!=-15)
			{
				boardOutput << (-1)*x[Point(i, j)] << " ";
			}
			else if (x[Point(i, j)] == 15|| x[Point(i, j)]==-15)
			{
				boardOutput << 0 << " ";
			}
			else
			{
				boardOutput <<x[Point(i, j)] << " ";
			}
		}
		boardOutput << endl;
	}
	boardOutput << player << endl;
	boardOutput.close();
}

void File::writeAll(vector < pair<Board, int> >rec)
{
	ofstream recOutput("allRec.txt");
	for (int c = 1; c< rec.size(); c++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (rec[c].first[Point(i, j)] < 0 && rec[c].first[Point(i, j)] != -15)
				{
					recOutput << (-1)*rec[c].first[Point(i, j)] << " ";
				}
				else if (rec[c].first[Point(i, j)] == 15 || rec[c].first[Point(i, j)] == -15)
				{
					recOutput << 0 << " ";
				}
				else
				{
					recOutput << rec[c].first[Point(i, j)] << " ";
				}
				recOutput << endl;
			}
		}
		recOutput << rec[c].second << endl;
	}
	recOutput.close();
}
