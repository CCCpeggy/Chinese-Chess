#include "Log.h"
#include "Point.h"
void Log::WriteLog(Board board, int player)
{
	move++;
	vector<pair<Board, int> >::iterator itt;
	for (itt = record.begin() + move; itt != record.end(); )
	{
		itt = record.erase(itt);
	}
	record.push_back(pair<Board,int>(board,player));
}
bool Log::isFirst()
{
	return move == 0;
}

bool Log::isFinal()
{
	return move == record.size() - 1;
}

void Log::moveDisplay(int piece, Point original, Point change)
{
	vector<string>::iterator it;
	for (it = displayText.begin() + static_cast<unsigned short>(move - 1); it != displayText.end(); )
	{
		it = displayText.erase(it);
	}
	string status;
	int tmpMove = move;

	for (int i = 0; i < 1; i++, tmpMove /= 10)
	{
		status = roadBlack[tmpMove % 10] + status;
	}

	if (piece < 8) { status += "¶Â¡G"; }
	else { status += "¬õ¡G"; }
	status += pieceName[piece];
	if (piece == 1 || piece == 4 || piece == 6 || piece == 7)
	{
		if (original.x == change.x)
		{
			status += roadBlack[original.y + 1];
			status += action[0];
			status += roadBlack[change.y + 1];
		}
		else if (original.x < change.x)
		{
			status += roadBlack[original.y + 1];
			status += action[1];
			status += roadBlack[change.x - original.x];
		}
		else if (original.x > change.x)
		{
			status += roadBlack[original.y + 1];
			status += action[2];
			status += roadBlack[original.x - change.x];
		}
	}
	if (piece == 2 || piece == 3 || piece == 5)
	{
		if (original.x < change.x)
		{
			status += roadBlack[original.y + 1];
			status += action[1];
			status += roadBlack[change.y + 1];
		}
		else if (original.x > change.x)
		{
			status += roadBlack[original.y + 1];
			status += action[2];
			status += roadBlack[change.y + 1];
		}
	}
	if (piece == 8 || piece == 11 || piece == 13 || piece == 14)
	{
		if (original.x == change.x)
		{
			status += roadRed[original.y];
			status += action[0];
			status += roadRed[change.y];
		}
		else if (original.x > change.x)
		{
			status += roadRed[original.y];
			status += action[1];
			status += roadRed[8-((-1)*(change.x - original.x) )+1];
		}
		else if (original.x < change.x)
		{
			status += roadRed[original.y];
			status += action[2];
			status += roadRed[8-((-1)*(original.x - change.x))+1 ];
		}
	}
	if (piece == 9 || piece == 10 || piece == 12)
	{
		if (original.x < change.x)
		{
			status += roadRed[original.y];
			status += action[2];
			status += roadRed[change.y];
		}
		else if (original.x > change.x)
		{
			status += roadRed[original.y];
			status += action[1];
			status += roadRed[change.y];
		}
	}
	displayText.push_back(status);
}


pair<Board, int> Log::LastBoard()
{
	move--;
	return record[move];
}

pair<Board, int> Log::NextBoard()
{
	move++;
	return record[move];
}

vector<string> Log::getMove()
{
	return displayText;
}

vector<pair<Board, int> > Log::getRecord()
{
	return record;
}

Log::Log(Board initial, int player)
{
	record.push_back(pair<Board,int>(initial,player));
	move = 0;

}
int Log::getMoveNum()
{
	return move;
}

void Log::displayFile(vector<pair<Board, int>>allRec)
{
	Point original;
	Point change;
	int piece;
	//¤ñ¸û2­Óboard
	for (int c = 0; c < allRec.size()-1; c++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (allRec[c].first[i][j] != allRec[c + 1].first[i][j])
				{
					if (allRec[c + 1].first[i][j] != 0 && allRec[c].first[i][j] == 0)
					{
						change = Point(i, j);
						piece = allRec[c + 1].first[i][j];
					}
					else if (allRec[c + 1].first[i][j] == 0 && allRec[c].first[i][j] != 0)
					{
						original = Point(i, j);
					}
				}
			}
		}
		moveDisplay(piece, original, change);
	}
}

