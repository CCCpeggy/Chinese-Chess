#include "Board.h"
#include <time.h>
#pragma region define
#define 空格 15
#define 將 1
#define 士 2
#define 象 3
#define 車 4
#define 馬 5
#define 包 6
#define 卒 7
#define 帥 8
#define 仕 9
#define 相 10
#define 俥 11
#define 傌 12
#define 炮 13
#define 兵 14
#define size_t int
#pragma endregion

Board::Board()
{
	//15白格 -15灰格 可以吃的為負號 -1~-14 不能吃的為1~14
	board.resize(10);
	for (size_t i = 0; i < 10; i++)
	{
		board[i].resize(9);
		for (size_t j = 0; j < 9; j++)
		{
			board[i][j] = 空格;
		}
	}
	//將 帥
	board[0][4] = 將;
	board[9][4] = 帥;
	//士 仕
	board[0][3] = 士;
	board[0][5] = 士;
	board[9][3] = 仕;
	board[9][5] = 仕;
	//象 相
	board[0][2] = 象;
	board[0][6] = 象;
	board[9][2] = 相;
	board[9][6] = 相;
	//車 俥
	board[0][0] = 車;
	board[0][8] = 車;
	board[9][0] = 俥;
	board[9][8] = 俥;
	//馬 傌
	board[0][1] = 馬;
	board[0][7] = 馬;
	board[9][1] = 傌;
	board[9][7] = 傌;
	//包 炮
	board[2][1] = 包;
	board[2][7] = 包;
	board[7][1] = 炮;
	board[7][7] = 炮;
	//卒 
	board[3][0] = 卒;
	board[3][2] = 卒;
	board[3][4] = 卒;
	board[3][6] = 卒;
	board[3][8] = 卒;
	//兵
	board[6][0] = 兵;
	board[6][2] = 兵;
	board[6][4] = 兵;
	board[6][6] = 兵;
	board[6][8] = 兵;
}

void Board::changeBoard(Board board)
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			this->board[i][j] = board[i][j];
		}
	}
}

void Board::select(Point p)
{
	vector<Point> oneStep = { Point(0,1),Point(0,-1) ,Point(1,0) ,Point(-1,0) };
	vector<Point> diagonalStep = { Point(1,1),Point(1,-1) ,Point(-1,1) ,Point(-1,-1) };
	vector<Point> horseStep = { Point(1,2),Point(-1,2) ,Point(1,-2),Point(-1,-2) , Point(2,1),Point(2,-1) , Point(-2,1),Point(-2,-1) ,};
	short chessType = board[p.x][p.y];
	deselect();//回到沒選棋的狀態

	switch (chessType)
	{
	#pragma region 將
		case 將:
			for (size_t i = 0; i < 4; i++)
			{
				ifPointValidChangeBoard(p, p + oneStep[i], Point(0, 3), Point(2, 5));
				if (findChess(帥).y == p.y)
				{
					bool obstacle = false;
					for (size_t i = (size_t)p.x + 1; i < findChess(帥).x; i++)
					{
						if (board[i][p.y] != 空格)
						{
							obstacle = true;
							break;
						}
					}
					if (!obstacle)
					{
						ifPointValidChangeBoard(p, findChess(帥));
					}
				}
			}
		break;
		#pragma endregion
	#pragma region 帥
		case 8:
			for (size_t i = 0; i < 4; i++)
			{
				ifPointValidChangeBoard(p, p + oneStep[i], Point(7, 3), Point(9, 5));
				if (findChess(將).y == p.y)
				{
					bool obstacle = false;
					for (size_t i = findChess(將).x + 1; i < p.x; i++)
					{
						if (board[i][p.y] != 空格)
						{
							obstacle = true;
							break;
						}
					}
					if (!obstacle)
					{
						ifPointValidChangeBoard(p, findChess(將));
					}
				}
			}
			break;
	#pragma endregion
	#pragma region 士 仕
		case 士:
			for (size_t i = 0; i < 4; i++)
			{
				ifPointValidChangeBoard(p, p + diagonalStep[i], Point(0, 3), Point(2, 5));
			}
			break;
		case 仕:
			for (size_t i = 0; i < 4; i++)
			{
				ifPointValidChangeBoard(p, p + diagonalStep[i], Point(7, 3), Point(9, 5));
			}
			break;
	#pragma endregion
	#pragma region 象 相
		case 象:
		case 相:
			for (size_t i = 0; i < 4; i++)
			{
				Point pt = p + diagonalStep[i];
				if (!checkPointInBoard(pt))
				{
					continue;
				}
				if ((*this)[pt] == 空格)
				{
					ifPointValidChangeBoard(p, p + diagonalStep[i] * 2);
				}
			}
			break;
	#pragma endregion
	#pragma region 車 俥
		case 車:
		case 俥:
			for (size_t i = 0; i < 4; i++)
			{
				for (size_t n = 1; n <= 9; n++)
				{
					ifPointValidChangeBoard(p, p + 	oneStep[i] * n);
					Point pt = p + oneStep[i]*n;
					if (!checkPointInBoard(pt))
					{
						continue;
					}
					if ((*this)[pt] != -空格)
					{
						break;
					}
				}
			}
			break;
	#pragma endregion
	#pragma region 馬 傌
		case 馬:
		case 傌:
			for (size_t i = 0; i < 4; i++)
			{
				Point pt = p + oneStep[i];
				if (!checkPointInBoard(pt))
				{
					continue;
				}
				if ((*this)[pt] == 空格)
				{
					ifPointValidChangeBoard(p, p + horseStep[2*i]);
					ifPointValidChangeBoard(p, p + horseStep[2 * i + 1]);
				}
			}
			break;
	#pragma endregion
	#pragma region 包 炮
		case 包:
		case 炮:
			for (size_t i = 0; i < 4; i++)
			{
				bool meetFirst = false;
				for (size_t n = 1; n <= 9; n++)
				{
					Point pt = p + oneStep[i] * n;
					if (!checkPointInBoard(pt))
					{
						continue;
					}
					if (!meetFirst)
					{
						
						if ((*this)[pt] == 空格)
						{
							ifPointValidChangeBoard(p, p + oneStep[i] * n);							
						}
						else
						{
							meetFirst = true;
						}
					}
					else
					{
						if ((*this)[pt] != 空格)
						{
							ifPointValidChangeBoard(p, p + oneStep[i] * n);
							break;
						}
					}
				}
			}
			break;
#pragma endregion
	#pragma region 卒 兵
		case 卒:
			if (p.x<=4)
			{
				ifPointValidChangeBoard(p, p + oneStep[2]);
			}
			else
			{
				for (size_t i = 0; i < 4; i++)
				{
					if (i!=3)
					{
						ifPointValidChangeBoard(p, p + oneStep[i]);
					}
				}
			}
		break;
		case 兵:
			if (p.x <= 4)
			{
				for (size_t i = 0; i < 4; i++)
				{
					if (i != 2)
					{
						ifPointValidChangeBoard(p, p + oneStep[i]);
					}
				}
			}
			else
			{
				ifPointValidChangeBoard(p, p + oneStep[3]);
			}
	#pragma endregion
	default:
		break;
	}
}

void Board::deselect()
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			if (board[i][j] < 0)
				board[i][j] *= -1;
		}
	}
}



int Board::move(Point location, Point destination)
{
	board[destination.x][destination.y] = board[location.x][location.y];
	board[location.x][location.y] = 空格;
	deselect();
	if (findChess(將)==Point(-1,-1))
	{
		return 1;//red win
	}
	else if(findChess(帥) == Point(-1, -1))
	{
		return 0;//black win
	}
	else
	{
		return -1;//nothing happened
	}
	
}

void Board::repent(Board board)
{
	changeBoard(board);
}

pair<Point,Point> Board::randMove(int player)
{
	
	vector<Point> chessLocations;
	chessLocations.clear();
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			if (player==0)
			{
				if (1<= board[i][j]&&board[i][j] <= 7)
				{
					chessLocations.push_back(Point(i, j));
				}
			}
			else if (player==1)
			{
				if (8<= board[i][j]&& board[i][j] <= 14)
				{
					chessLocations.push_back(Point(i, j));
				}
			}
		}
	}
	srand(time(NULL));
	int r1; 
	vector<Point> chessDestinations;
	do
	{
		r1= rand() % chessLocations.size();
		chessDestinations.clear();
		select(chessLocations[r1]);	
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				if (board[i][j] < 0)
				{
					chessDestinations.push_back(Point(i, j));
				}
			}
		}
	} while (chessDestinations.empty());
	int r2 = rand() % chessDestinations.size();
	return make_pair(chessLocations[r1], chessDestinations[r2]);
}

vector<short>& Board::operator[](int index)
{
	return board[index];
}

short& Board::operator[](Point& p)
{
	short zero = 0;
	if (p.x<0||p.x>9||p.y<0||p.y>8)
	{
		return zero;
	}
	return board[p.x][p.y];
}

bool Board::checkPointInBoard(Point p)
{
	if ((0<=p.x&&p.x<=10)&&(0<=p.y&&p.y<=9))
	{
		return true;
	}
	return false;
}

void Board::ifPointValidChangeBoard(Point p,Point dest, Point leftUp, Point rightDown)
{
	if (leftUp.x<= dest.x&& leftUp.y <= dest.y&&
		dest.x <= rightDown.x && dest.y <= rightDown.y&&
		(player(*this,p)!= player(*this, dest))
		)
	{
		board[dest.x][dest.y] *= -1;
	}
}

Point Board::findChess(int chessType)
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			if (chessType==board[i][j])
			{
				return Point(i,j);
			}
		}
	}
	return Point(-1,-1);
}

int player(Board& b, Point p)
{
	if (0<=abs(b[p])&&abs(b[p])<=7)
	{
		return 0;
	}
	else if(8 <= abs(b[p]) && abs(b[p]) <=14)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
