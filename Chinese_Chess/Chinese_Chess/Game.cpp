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
	drawBanner();
	for (int i = 0; i < 10; i++) {
		drawCheckerboard(i, 0);
	}
	drawFooter();

}

void Game::drawCheckerboard(int i, int mode) {//mode:0->一般, 1->目錄, 2->對話確認框
	int range;
	if (mode == 0) {
		range = 8;
	}
	else if (mode == 1) {
		range = 4;
	}
	else if (mode == 2) {
		range = 3;
	}


	drawBattleSituation(i);
	for (int j = 0; j <= range; j++) {
		if (board[i][j] > 0) {
			if (board[i][j] == 15) {
				cout << piecegrid.gridLine[i * 2][j * 2 * 2] << piecegrid.gridLine[i * 2][j * 2 * 2 + 1];
			}
			else {
				cout << pieces[board[i][j]];
			}
		}
		else if (board[i][j] < 0) {
			SetConsoleTextAttribute(handleSTDOutput,  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			if (board[i][j] == -15) {
				cout << piecegrid.gridLine[i * 2][j * 2 * 2] << piecegrid.gridLine[i * 2][j * 2 * 2 + 1];
			}
			else {
				cout << pieces[-board[i][j]].symbol;
			}
		}

		SetConsoleTextAttribute(handleSTDOutput, originalColor);
		if (j != 8) {
			cout << piecegrid.gridLine[i * 2][(j * 2 + 1) * 2 ] << piecegrid.gridLine[i * 2][(j * 2 + 1) * 2 + 1];
		}
		else if (j == 8) {
			cout << "　";
		}

	}

	if (i == 1 && mode == 0) {
		drawStatus();
	}


	if (mode == 0 && i != 9) {
		cout << endl << setw(50) << piecegrid.gridLine[2 * i + 1] << endl;
	}

}


void Game::drawBattleSituation(int i)
{
	vector<string> logs = log.getMove();
	if (i < logs.size())
		cout << logs[i] << "　";
	else
		cout << "第 " << i << "筆戰績記錄" << "　";
}

void Game::drawBanner()
{
	SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED | FOREGROUND_BLUE);
	cout << endl << setw(11) <<"戰況顯示" << setw(39) << piecegrid.gridLabel[0] << endl;
	SetConsoleTextAttribute(handleSTDOutput, originalColor);
}

void Game::drawFooter()
{
	SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED | FOREGROUND_BLUE);
	cout << endl << setw(50) << piecegrid.gridLabel[1] << endl;
	SetConsoleTextAttribute(handleSTDOutput, originalColor);
}

void Game::drawStatus()
{
	if (player == 0) {
		cout << setw(10) << "現在輪到";
		SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
		cout << "紅方";
		SetConsoleTextAttribute(handleSTDOutput, originalColor);
		cout << "下棋";
	}
	else if (player == 1) {
		cout << setw(10) << "現在輪到";
		SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_INTENSITY);
		cout << "黑方";
		SetConsoleTextAttribute(handleSTDOutput, originalColor);
		cout << "下棋";
	}
}

void Game::drawMenu(int index)
{
	drawBanner();
	for (int i = 0; i < 10; i++) {

		if (i == 2) {
			drawCheckerboard(i, 1);
			cout << endl << setw(16) << "　";
			for (int j = 0; j < 20; j++) {
				cout << piecegrid.gridLine[2 * i + 1][j];
			}

			SetConsoleTextAttribute(handleSTDOutput, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
			cout << piecegrid.menu[0];
			SetConsoleTextAttribute(handleSTDOutput, originalColor);
			cout << endl;
		}
		else if (i >= 3 && i <= 6) {
			drawCheckerboard(i, 1);

			SetConsoleTextAttribute(handleSTDOutput, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
			for (int j = 0; j < 4; j++) {
				cout << piecegrid.menu[(i - 3) * 2 + 1][j];
			}
			if (i == index + 3) {
				SetConsoleTextAttribute(handleSTDOutput, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				for (int j = 4; j < 12; j++) {
					cout << piecegrid.menu[(i - 3) * 2 + 1][j];
				}
				SetConsoleTextAttribute(handleSTDOutput, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
			}
			else {
				
				for (int j = 4; j < 12; j++) {
					cout << piecegrid.menu[(i - 3) * 2 + 1][j];
				}
			}
			for (int j = 12; j < 16; j++) {
				cout << piecegrid.menu[(i - 3) * 2 + 1][j];
			}
			SetConsoleTextAttribute(handleSTDOutput, originalColor);
			cout << endl << setw(16) << "　";
			for (int j = 0; j < 20; j++) {
				cout <<  piecegrid.gridLine[2 * i + 1][j];
			}
			SetConsoleTextAttribute(handleSTDOutput, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
			cout << piecegrid.menu[(i - 3) * 2 + 2] << endl;
			SetConsoleTextAttribute(handleSTDOutput, originalColor);

		}
		else {
			drawCheckerboard(i, 0);
		}
	}
	drawFooter();
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
