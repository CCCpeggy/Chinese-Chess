#include "Game.h"

Piece Game::pieces[15];

Game::Game()
{	
	pieces[1].pos("將", 0);
	pieces[2].pos("士", 0);
	pieces[3].pos("象", 0);
	pieces[4].pos("車", 0);
	pieces[5].pos("馬", 0);
	pieces[6].pos("包", 0);
	pieces[7].pos("卒", 0);

	pieces[8].pos("帥", 1);
	pieces[9].pos("仕", 1);
	pieces[10].pos("相", 1);
	pieces[11].pos("車", 1);
	pieces[12].pos("傌", 1);
	pieces[13].pos("炮", 1);
	pieces[14].pos("兵", 1);
	pieces[15].pos("　", 1);
}


ostream& operator<<(ostream& cout, const Piece& p) {
	if (p.player) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_RED);
		cout << p.symbol;
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
		cout << p.symbol;
	}
	return cout;
}


void Game::drawInterface()
{
	for (int i = 0; i < 10; i++) {
		
		drawCheckerboard(i);
		if (i == 4) {
			cout << setw(47) << "∥        楚河       漢界       ∥ " << endl;
		}

	}

}

void Game::drawCheckerboard(int i)
{
	
	if(i<=4) {
		
		if (i != 0) {
			cout << setw(12) << " ";
			for (int k = 0; k <= 8; k++) {
				if (k == 0 || k == 8) {
					cout << "∥";
				}
				else {
					cout << "│ ";
				}

				if ((i == 1 && k == 4) || (i == 2 && k == 3)) {
					cout << "╱ ";
				}
				else if ((i == 1 && k == 3) || (i == 2 && k == 4)) {
					cout << "╲ ";
				}
				else {
					cout << "  ";
				}
			}
			cout << endl;
		}

		drawBattleSituation(i);
		for (int j = 0; j <= 8; j++) {
			if (board[i][j] == 15) {
				cout << piecegrid.gridline[i][j];
			}
			else if (board[i][j] == -15) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
				cout << piecegrid.gridline[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			}
			else if (board[i][j] > 0) {
				cout << pieces[board[i][j]];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				if (j == 8) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << "　";
				}

			}
			else if (board[i][j] < 0) {
				cout << pieces[-board[i][j]];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				if (j == 8) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << "　";
				}
			}


			if (i == 0 && j != 8) {
				cout << "＝";
			}
			else if (i != 0 && j != 8) {
				cout << "—";
			}
		}
	}

	

	if(i>=5) {
		drawBattleSituation(i);
		for (int j = 0; j <= 8; j++) {
			
			if (board[i][j] == 15) {
				cout << piecegrid.gridline[i][j];
			}
			else if (board[i][j] == -15) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
				cout << piecegrid.gridline[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			}
			else if (board[i][j] > 0) {
				cout << pieces[board[i][j]];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				if (j == 8) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << "　";
				}

			}
			else if (board[i][j] < 0) {
				cout << pieces[-board[i][j]];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				if (j == 8) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << "　";
				}
			}

			if (i == 9 && j != 8) {
				cout << "＝";
			}
			else if (i != 9 && j != 8) {
				cout << "—";
			}
		}
		

		if (i != 9) {

			cout << endl;
			cout << setw(12) << " ";

			for (int k = 0; k <= 8; k++) {
				if (k == 0 || k == 8) {
					cout << "∥";
				}
				else {
					cout << "│ ";
				}
				if ((k == 4 && i == 7) || (k == 3 && i == 8)) {
					cout << "╱ ";
				}
				else if ((k == 3 && i == 7) || (k == 4 && i == 8)) {
					cout << "╲ ";
				}
				else {
					cout << "  ";
				}
			}
		}
	}
	cout << endl;
}

void Game::drawBattleSituation(int i)
{
	cout << "戰績記錄" << i << "   " ;
}

void Game::drawMenu(int)
{
}

void Game::drawDialog(string, int)
{
}

void Game::setPlayer(int newPlayer)
{
	player = newPlayer;
}

void Game::changePlayer()
{
	player = player ? 0 : 1;
}

int Game::getPlayer()
{
	return player;
}
