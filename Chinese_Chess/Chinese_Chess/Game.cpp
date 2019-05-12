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

void Game::drawCheckerboard(int i, int mode) {//mode:0->一般, 1->目錄, 2, 3->對話確認框
	int range;
	if (mode == 0) {
		range = 8;
	}
	else if (mode == 1) {
		range = 4;
	}
	else if (mode == 2) {
		range = 2;
	}
	else if (mode == 3) {
		range = 8;
	}

	cout << "｜　";
	drawBattleSituation(i);
	cout << "｜　";
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

	if (i == 1) {
		drawStatus();
	}
	else if (i == 7) {
		cout << setw(22) << "←　→　方向鍵控制光標";
	}
	if (mode == 0 && i != 9) {
		if (i == 4 || i == 5) {
			cout << "　　　　　　　　　　　　";
		}
		cout << endl << setw(82) << piecegrid.gridLine[2 * i + 1] << endl;
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
	cout << "．——　戰況表　——．";
	SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED | FOREGROUND_BLUE);
	cout << setw(36) << piecegrid.gridLabel[0] << endl << endl;
	SetConsoleTextAttribute(handleSTDOutput, originalColor);
}

void Game::drawFooter()
{
	cout << endl << endl << "．—————————．";
	SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED | FOREGROUND_BLUE);
	cout << setw(36) << piecegrid.gridLabel[1] << endl;
	SetConsoleTextAttribute(handleSTDOutput, originalColor);
}

void Game::drawStatus()
{
	if (player == 0) {
		cout << setw(14) << "現在輪到";
		SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
		cout << "紅方";
		SetConsoleTextAttribute(handleSTDOutput, originalColor);
		cout << "下棋";
	}
	else if (player == 1) {
		cout << setw(14) << "現在輪到";
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
			cout << endl << setw(24) << "　";
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
			cout << endl << setw(24) << "　";
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

void Game::drawDialog(string output, int index)
{
	drawBanner();
	for (int i = 0; i < 10; i++) {
		if (i == 3) {
			drawGridFormat(i, output);
		}
		else if (i == 4) {
			drawCheckerboard(i, 2);
			drawStringFormat(i, output, -1);

			cout << endl << setw(24) << "　";
			for (int j = 0; j < 12; j++) {
				cout << piecegrid.gridLine[2 * i + 1][j];
			}
			SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
			cout << piecegrid.dialog[(i - 4) + 1] << endl;
			SetConsoleTextAttribute(handleSTDOutput, originalColor);
		}
		else if(i == 5){
			drawCheckerboard(i, 2);
			SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
			int pos;
			index == 0 ? pos = 12 : pos = 22;
			int j = 0;
			for (; j < pos; j++) {
				cout << piecegrid.dialog[(i - 4) + 1][j];
			}
			SetConsoleTextAttribute(handleSTDOutput, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			cout << piecegrid.dialog[(i - 4) + 1][pos] << piecegrid.dialog[(i - 4) + 1][pos + 1];
			SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
			for (j = pos + 2; j < 36; j++) {
				cout << piecegrid.dialog[(i - 4) + 1][j];
			}
			cout << endl << setw(24) << "　";
			SetConsoleTextAttribute(handleSTDOutput, originalColor);
			for (int j = 0; j < 12; j++) {
				cout << piecegrid.gridLine[2 * i + 1][j];
			}
			SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
			cout << piecegrid.dialog[i-2];
			SetConsoleTextAttribute(handleSTDOutput, originalColor);
			cout << endl;

		}
		else {
			drawCheckerboard(i, 0);
		}
	}
	drawFooter();
}

void Game::drawOpenTxt(int index) {


	//讀取資料夾所有txt
	char buffer[_MAX_PATH];
	_getcwd(buffer, _MAX_PATH);
	char* extenName = "*.txt";
	unsigned long long hFile;
	struct _finddata_t fileName;
	hFile = _findfirst(extenName, &fileName);
	do {
		filename.push_back(fileName.name);
	} while (hFile != -1 && _findnext(hFile, &fileName) == 0);

	//計算資料夾有txt的數量
	int txtcount = filename.size();
	if (txtcount < 3) {
		for (int i = 3 - txtcount; i > 0; i--) {
			filename.push_back("　　　　");
		}
	}


	drawBanner();
	for (int i = 0; i < 10; i++) {

		if (i == 3) {
			drawGridFormat(i, "");
		}
		else if (i == 4) {
			drawCheckerboard(i, 2);
			drawStringFormat(i, filename[(i - 4) * 2], index);
			cout << endl << setw(24) << "　";

			for (int j = 0; j < 12; j++) {
				cout << piecegrid.gridLine[2 * i + 1][j];
			}
			drawStringFormat(i, filename[(i - 4) * 2 + 1], index);

		}
		else if (i == 5) {
			cout << endl;
			drawCheckerboard(i, 2);
			drawStringFormat(i, filename[(i - 4) * 2], index);
			cout << endl << setw(24) << "　";
			for (int j = 0; j < 12; j++) {
				cout << piecegrid.gridLine[2 * i + 1][j];
			}
			SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
			cout << piecegrid.dialog[3];
			SetConsoleTextAttribute(handleSTDOutput, originalColor);
			cout << endl;
		}
		else {
			drawCheckerboard(i, 0);
		}

	}
	drawFooter();
}

void Game::drawGridFormat(int row, string output) {

	drawCheckerboard(row, 3);
	cout << endl << setw(24) << "　";
	for (int j = 0; j < 12; j++) {
		cout << piecegrid.gridLine[2 * row + 1][j];
	}
	SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
	cout << piecegrid.dialog[0];
	SetConsoleTextAttribute(handleSTDOutput, originalColor);
	cout << endl;

}

void Game::drawStringFormat(int row, string output, int index) {
	SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
	cout << "║ ";
	int front = (30 - output.length()) / 2 + 1;
	SetConsoleTextAttribute(handleSTDOutput, originalColor);
	if (index != -1) {
		//若為開舊檔框模式則執行
		
	}
	cout << setw(front + output.length() - 1) << output;
	SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED);
	output.length() % 2 == 0 ? cout << setw(front + 1) << "║ " : cout << setw(front + 2) << "║ ";
	SetConsoleTextAttribute(handleSTDOutput, originalColor);

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
