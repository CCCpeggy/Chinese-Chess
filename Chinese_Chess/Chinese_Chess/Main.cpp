#include "Game.h"
#include "File.h"
#include <conio.h>
#include <utility>
#include <Windows.h>
#pragma region define
#define READ_FILE_NAME "game.txt"
#define WRITE_FILE_NAME "result.txt"
#define 棋盤基準點X 16
#define 棋盤基準點Y 2
#define 棋盤X軸加權 4
#define 棋盤Y軸加權 2
#define 遊戲模式 1110
#define 選單模式 1111
#define 對話框模式 1112
#define SHOW_DIALOG(CONTENT,FUNC){ gameMode = 對話框模式;dialogIndex = 0;dialogFunc = (FUNC);dialogContent = (CONTENT);showDialog(dialogContent, 0);}
#define 紅方 0
#define 黑方 1
#define 紅棋起始位置 Point(9,0)
#define 黑棋起始位置 Point(0,0)

#pragma endregion
using namespace std;

#pragma region  declare

//關於畫面
HANDLE handleInput;
HANDLE handleOutput;

//關於遊戲
const wchar_t* projectName = L"象棋";
Game* game = nullptr;
File file;
Point gamePoint; //目前輸入點所在位置
Point selectedPoint; //選取的象棋所在位置
int gameMode;

//控制的function
void updateCursor(); //更新輸入點所在位置
void setCursor(int, int); //設定輸入點所在位置
void movePoint(int); // 0 左; 1 上; 2 右; 3 下;

//遊戲的function
void initBoard(); //初始化遊戲
void selectChess(); //選擇棋子
int moveChess(); //移動選擇的棋子 //回傳不為-1:遊戲結束
void undo(); //悔棋
void redo(); //回復
void showMenu(int); //顯示選單
void showDialog(string, int); //顯示對話框
void endGame(); //結束遊戲
void showInterface(); //重新顯示遊戲畫面
bool hasChess();
bool validMove();

#pragma endregion

int main() {

	char key;
	int menuIndex = 0; //選單選取項目
	int dialogIndex = 0; //對話框選取項目
	bool selectedChess = false; //是否選取了棋子
	void (*dialogFunc)() = nullptr; //對話框所要做的動作
	string dialogContent = ""; //對話框顯示的文字

#pragma region init

	handleInput = GetStdHandle(STD_INPUT_HANDLE);
	handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTitle(projectName);

	DWORD consoleCnt;
	DWORD consoleMode;
	INPUT_RECORD input;

	GetConsoleMode(handleInput, &consoleMode);
	SetConsoleMode(handleInput, consoleMode & ~ENABLE_LINE_INPUT);

#pragma endregion

	initBoard();

#pragma region gameLoop
	while (ReadConsoleInput(handleInput, &input, 1, &consoleCnt))
	{
		if (input.EventType == KEY_EVENT)
		{
			if (input.Event.KeyEvent.bKeyDown == TRUE)
			{
				switch (input.Event.KeyEvent.wVirtualKeyCode) {
				case VK_UP: //26
				case VK_DOWN: //28
				case VK_LEFT: //25
				case VK_RIGHT: //27
					//上下左右移動時
					//遊戲模式
					if (gameMode == 遊戲模式) {
						//變更游標
						movePoint(input.Event.KeyEvent.wVirtualKeyCode - VK_LEFT);
						updateCursor();
					}
					//選單模式
					else if (gameMode == 選單模式) {
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_UP) menuIndex--;
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) menuIndex++;
						//計算選單選取項目
						menuIndex = menuIndex % 4;
						//重新顯示選單
						showMenu(menuIndex);
					}
					//對話框模式
					else if (gameMode == 對話框模式) {
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) dialogIndex--;
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) dialogIndex++;
						//計算對話框選取項目
						dialogIndex = dialogIndex % 2;
						//重新顯示對話框
						showDialog(dialogContent, dialogIndex);
					}
					break;
				case VK_RETURN:
					//按Enter動作
					//遊戲模式
					if (gameMode == 遊戲模式) {
						int piecePart = game->board[gamePoint] <= 7 ? 黑方 : 紅方;
						if (game->board[gamePoint] <= 0 ) {
							//移動位置
							int gameStatus = moveChess();
							if (gameStatus == 1) SHOW_DIALOG("紅色勝利，要重新開始遊戲嗎", initBoard);
							if (gameStatus == 2) SHOW_DIALOG("黑色勝利，要重新開始遊戲嗎", initBoard);
						}
						else if(piecePart == game->getPlayer()){
							selectChess();
						}
					}
					//選單模式
					else if (gameMode == 選單模式) {
						//選單選擇項目
						switch (menuIndex) {
						case 0:
							//繼續遊戲
							//顯示光標
							CONSOLE_CURSOR_INFO lpCursor;
							lpCursor.dwSize = 1;
							lpCursor.bVisible = TRUE;
							SetConsoleCursorInfo(handleOutput, &lpCursor);
							showInterface();
							break;
						case 1:
							//重新開始
							SHOW_DIALOG("確定要重新開始遊戲嗎", initBoard);
							break;
						case 2:
							//回主選單
							break;
						case 3:
							//結束遊戲
							SHOW_DIALOG("確定要結束遊戲嗎", endGame);
							break;
						}
						gameMode = 遊戲模式;
					}
					//對話框模式
					else if (gameMode == 對話框模式) {
						//選擇"是"
						if (dialogIndex == 1) dialogFunc();
						//重新顯示畫面
						showInterface();
					}
					break;
				case VK_ESCAPE:
					//esc 顯示選單
					gameMode = 選單模式;
					menuIndex = 0;
					showMenu(0);
					break;
				default:
					//悔棋
					if (input.Event.KeyEvent.uChar.AsciiChar == '<') {
						SHOW_DIALOG("確定要悔棋嗎", undo);
					}
					//還原
					else if (input.Event.KeyEvent.uChar.AsciiChar == '>') {
						SHOW_DIALOG("確定要還原嗎", redo);
					}
				}
			}
		}
	}
#pragma endregion

}

void updateCursor()
{
	COORD setPoint;
	setPoint.X = (gamePoint.y) * 棋盤X軸加權 + 棋盤基準點X;
	setPoint.Y = (gamePoint.x) * 棋盤Y軸加權 + 棋盤基準點Y;
	SetConsoleCursorPosition(handleOutput, setPoint);
}

void setCursor(Point point)
{
	setCursor(point.x, point.y);
}

void setCursor(int x, int y)
{
	gamePoint.x = x;
	gamePoint.y = y;

	updateCursor();
}

void movePoint(int direction)
{
	switch (direction) {
		//left
	case 0:
		gamePoint.y += gamePoint.y ? -1 : 0;
		break;
		//up
	case 1:
		gamePoint.x += gamePoint.x ? -1 : 0;
		break;
		//right
	case 2:
		gamePoint.y += gamePoint.y < 8 ? 1 : 0;
		break;
		//down
	case 3:
		gamePoint.x += gamePoint.x < 9 ? 1 : 0;
		break;

	}
}

void initBoard() {
	gameMode = 遊戲模式;
	if (game != nullptr) delete game;
	game = new Game();
	Board loadBoard = file.loadFile(READ_FILE_NAME).first;
	game->board.changeBoard(loadBoard);
	showInterface();
	setCursor(game->getPlayer() ? 黑棋起始位置 : 紅棋起始位置);
}

void selectChess()
{
	selectedPoint = gamePoint;
	game->board.select(gamePoint);
	showInterface();
}

int moveChess()
{
	int status = game->board.move(selectedPoint, gamePoint);
	if (status == -1) game->log.WriteLog(game->board, game->getPlayer());
	game->changePlayer();
	showInterface();
	return status;
}

void undo()
{
	if (!game->log.isFirst()) {
		pair<Board, int> lastLog = game->log.LastBoard();
		game->setPlayer(lastLog.second);
		game->board.repent(lastLog.first);
		showInterface();
	}
}

void redo()
{
	if (!game->log.isFinal()) {
		pair<Board, int> nextLog = game->log.NextBoard();
		game->setPlayer(nextLog.second);
		game->board.repent(nextLog.first);
		showInterface();
	}
}

void showMenu(int index)
{
	Point tmpPoint = gamePoint;
	setCursor(-1, -4);
	game->drawMenu(index);	
	setCursor(tmpPoint);
	//隱藏光標
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 1;
	lpCursor.bVisible = FALSE;
	SetConsoleCursorInfo(handleOutput, &lpCursor);
}

void showDialog(string content, int number)
{
	game->drawDialog(content, number);
}

void endGame()
{
	file.writeFile(game->board, WRITE_FILE_NAME);
	ExitProcess(0);
}

void showInterface() {
	Point tmpPoint = gamePoint;
	setCursor(-1, -4);
	game->drawInterface();
	setCursor(tmpPoint);
}

bool hasChess()
{
	return game->board[gamePoint] != 0;
}

bool validMove()
{
	return game->board[gamePoint] <= 0;
}

