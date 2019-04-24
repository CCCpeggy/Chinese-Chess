#include "Board.h"

Board::Board()
{
	//15白格 -15灰格 可以吃的為負號 -1~-14 不能吃的為1~14
	board.resize(10);
	for (size_t i = 0; i < 10; i++)
	{
		board[i].resize(9);
		for (size_t j = 0; j < 9; j++)
		{
			board[i][j] = 15;
		}
	}
	//將 帥
	board[0][4] = 1;
	board[9][4] = 8;
	//士 仕
	board[0][3] = 2;
	board[0][5] = 2;
	board[9][3] = 9;
	board[9][5] = 9;
	//象 相
	board[0][2] = 3;
	board[0][6] = 3;
	board[9][2] = 10;
	board[9][6] = 10;
	//車 俥
	board[0][0] = 4;
	board[0][8] = 4;
	board[9][0] = 11;
	board[9][8] = 11;
	//馬 傌
	board[0][1] = 5;
	board[0][7] = 5;
	board[9][1] = 12;
	board[9][7] = 12;
	//包 炮
	board[2][1] = 6;
	board[2][7] = 6;
	board[7][1] = 13;
	board[7][7] = 13;
	//卒 
	board[3][0] = 7;
	board[3][2] = 7;
	board[3][4] = 7;
	board[3][6] = 7;
	board[3][8] = 7;
	//兵
	board[6][0] = 14;
	board[6][2] = 14;
	board[6][4] = 14;
	board[6][6] = 14;
	board[6][8] = 14;
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
	vector<Point> moveOneStep = { Point(0,1),Point(0,-1) ,Point(1,0) ,Point(-1,0) };
	vector<Point> moveDiagonalStep = { Point(1,1),Point(1,-1) ,Point(-1,1) ,Point(-1,-1) };
	short chessType = board[p.x][p.y];
	deselect();//回到沒選棋的狀態

	switch (chessType)
	{
	//將 帥
	case 1:
		for (size_t i = 0; i < 4; i++)
		{
			ifPointValidChangeBoard(p,p+ moveOneStep[i], Point(0, 3), Point(2, 5));
			if (findChess(8).y==p.y)
			{
				bool obstacle=false;
				for (size_t i = (size_t)p.x+1; i < findChess(8).x; i++)
				{
					if (board[i][p.y]!=15)	
					{
						obstacle=true;
						break;
					}
				}
				if (!obstacle)
				{
					ifPointValidChangeBoard(p, findChess(8));
				}
			}
		}
		break;
	//帥
	case 8:
		for (size_t i = 0; i < 4; i++)
		{
			ifPointValidChangeBoard(p, p + moveOneStep[i], Point(7, 3), Point(9, 5));
			if (findChess(1).y == p.y)
			{
				bool obstacle = false;
				for (size_t i = (size_t)p.x + 1; i < findChess(1).x; i++)
				{
					if (board[i][p.y] != 15)
					{
						obstacle = true;
						break;
					}
				}
				if (!obstacle)
				{
					ifPointValidChangeBoard(p, findChess(1));
				}
			}
		}
		break;

	//士 仕
	case 2:
		for (size_t i = 0; i < 4; i++)
		{
			ifPointValidChangeBoard(p, p + moveDiagonalStep[i], Point(0, 3), Point(2, 5));
		}
		break; 
	case 9:
		for (size_t i = 0; i < 4; i++)
		{
			ifPointValidChangeBoard(p, p + moveDiagonalStep[i], Point(7, 3), Point(9, 5));
		}
		break;
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
	board[location.x][location.y] = 15;
	deselect();
	if (findChess(1)==Point(-1,-1))
	{
		return 1;//red win
	}
	else if(findChess(8) == Point(-1, -1))
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

vector<short>& Board::operator[](int index)
{
	return board[index];
}

void Board::ifPointValidChangeBoard(Point p,Point dest, Point leftUp=Point(0,0), Point rightDown = Point(9, 8))
{
	if (leftUp.x<= dest.x&& leftUp.y <= dest.y&&
		dest.x <= rightDown.x && dest.y <= rightDown.y&&
		(board[p.x][p.y]<=7!= board[dest.x][dest.y] <= 7|| board[dest.x][dest.y] ==15)
		)
	{
		board[p.x][p.y] *= -1;
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

