#include "Log.h"
#include "Point.h"
void Log::WriteLog(Board board, int player)
{
	move++;
	vector<pair<Board, int> >::iterator itt;
	for (itt = record.begin() + static_cast<unsigned short>(move - 1); itt != record.end(); itt++)
	{
		record.erase(itt);
	}
	record.push_back(pair<Board,int>(board,player));
}
//writelog ©M moveDisplay ¦X¨Ö
bool Log::isFirst()
{
	return move == 1;
}

bool Log::isFinal()
{
	return move == record.size();
}

void Log::moveDisplay(int piece, Point original, Point change)
{
	vector<string>::iterator it;
	for (it = displayText.begin() + static_cast<unsigned short>(move - 1); it != displayText.end(); it++)
	{
		displayText.erase(it);
	}
	string status;
	string temp = to_string(move);
	for (int i = temp.length(); i <= 4; i++)
	{
		status += " ";
	}
	status += temp;
	status += " ";
	if (piece<8) { status += "¶Â : "; }
	else { status += "¬õ : "; }
	status += pieceName[piece];
	if (piece == 1 || piece == 4 || piece == 6 || piece == 7)
	{
		if (original.y == change.y)
		{
			status += roadBlack[original.x];
			status += action[0];
			status += roadBlack[change.x];
		}
		else if (original.y < change.y)
		{
			status += roadBlack[original.x];
			status += action[1];
			status += roadBlack[change.y - original.y - 1];
		}
		else if (original.y > change.y)
		{
			status += roadBlack[original.x];
			status += action[2];
			status += roadBlack[original.y - change.y - 1];
		}
	}
	if (piece == 2 || piece == 3 || piece == 5)
	{
		if (original.y < change.y)
		{
			status += roadBlack[original.x];
			status += action[1];
			status += roadBlack[change.x];
		}
		else if (original.y > change.y)
		{
			status += roadBlack[original.x];
			status += action[2];
			status += roadBlack[change.x];
		}
	}
	if (piece == 8 || piece == 11 || piece == 13 || piece == 14)
	{
		if (original.y == change.y)
		{
			status += roadRed[original.x];
			status += action[0];
			status += roadRed[change.x];
		}
		else if (original.y > change.y)
		{
			status += roadRed[original.x];
			status += action[1];
			status += roadRed[(-1)*(change.y - original.y) + 1];
		}
		else if (original.y < change.y)
		{
			status += roadRed[original.x];
			status += action[2];
			status += roadRed[(-1)*(original.y - change.y) + 1];
		}
	}
	if (piece == 9 || piece == 10 || piece == 12)
	{
		if (original.y < change.y)
		{
			status += roadRed[original.x];
			status += action[2];
			status += roadRed[change.x];
		}
		else if (original.y > change.y)
		{
			status += roadRed[original.x];
			status += action[1];
			status += roadRed[change.x];
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
