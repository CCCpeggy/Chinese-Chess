#include "Game.h"
#include "File.h"
#include <conio.h>
#include <utility>
#include <Windows.h>
#include <cmath>
#pragma region define
#define READ_FILE_NAME "game.txt"
#define WRITE_FILE_NAME "result.txt"
#define 棋盤基準點X 28
#define 棋盤基準點Y 2
#define 棋盤X軸加權 4
#define 棋盤Y軸加權 2
#define 遊戲模式 1110
#define 選單模式 1111
#define 對話框模式 1112
#define 選檔模式 1113
#define 結束模式 1114
#define SHOW_DIALOG(CONTENT,FUNC){gameMode = 對話框模式;dialogIndex = 1;dialogFunc = (FUNC);dialogContent = (CONTENT);showDialog(dialogContent, 1);}
#define 紅方 1
#define 黑方 0
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
Point tmpPoint; //暫存位置
Point selectedPoint; //選取的象棋所在位置
vector<string> fileNames;
int gameMode;
bool gameOver = false;
int menuIndex = 0; //選單選取項目
int dialogIndex = 0; //對話框選取項目
int fileIndex = 0; //檔案選取項目
bool selectedChess = false; //是否選取了棋子
void(*dialogFunc)() = nullptr; //對話框所要做的動作
string dialogContent = ""; //對話框顯示的文字

//控制的function
void updateCursor(); //更新輸入點所在位置
void setCursor(int, int); //設定輸入點所在位置
void movePoint(int); // 0 左; 1 上; 2 右; 3 下;
void visibleCursor(bool);
void setInputCursor();

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
void showFile(int); //顯示檔案
void loadFIle(int); //載入檔案
void backGameMode();

#pragma endregion

int main() {

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
					if (gameMode == 結束模式 ||gameMode == 遊戲模式) {
						//變更游標
						movePoint(input.Event.KeyEvent.wVirtualKeyCode - VK_LEFT);
						updateCursor();
					}
					else if (gameMode == 選單模式) {
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_UP) menuIndex--;
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) menuIndex++;
						//計算選單選取項目
						menuIndex += 4;
						menuIndex = menuIndex % 4;
						//重新顯示選單
						showMenu(menuIndex);
					}
					else if (gameMode == 對話框模式) {
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) dialogIndex--;
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) dialogIndex++;
						//計算對話框選取項目
						dialogIndex += 2;
						dialogIndex = dialogIndex % 2;
						//重新顯示對話框
						showDialog(dialogContent, dialogIndex);
					}
					else if (gameMode == 選檔模式) {
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_UP) fileIndex--;
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) fileIndex++;
						//計算對話框選取項目
						fileIndex += fileNames.size();
						if(fileNames.size() > 0) fileIndex = fileIndex % fileNames.size();
						//重新顯示選檔列表					
						showFile(fileIndex);
					}
					break;
				case VK_RETURN:
					//按Enter動作
					if (gameMode == 遊戲模式) {
						int piecePart = game->board[gamePoint] <= 7 ? 黑方 : 紅方;
						if (game->board[gamePoint] <= 0) {
							//移動位置
							int gameStatus = moveChess();
							if (gameStatus == 紅方)
								SHOW_DIALOG("紅色勝利，要重新開始遊戲嗎", initBoard);
							if (gameStatus == 黑方)
								SHOW_DIALOG("黑色勝利，要重新開始遊戲嗎", initBoard);
						}
						else if (piecePart == game->getPlayer()) {
							selectChess();
						}
					}
					else if (gameMode == 選單模式) {
						//選單選擇項目
						switch (menuIndex) {
						case 0:
							//繼續遊戲
							backGameMode();
							break;
						case 1:
							//重新開始
							SHOW_DIALOG("確定要重新開始遊戲嗎", initBoard);
							break;
						case 2:
							//載入檔案
							gameMode = 選檔模式;
							fileNames = file.listFile();
							showFile(0);
							fileIndex = 0;
							break;
						case 3:
							//結束遊戲
							SHOW_DIALOG("確定要結束遊戲嗎", endGame);
							break;
						}
					}
					else if (gameMode == 對話框模式) {
						//選擇"是"
						if (dialogIndex == 0) {
							dialogFunc();
						}
						else {
							backGameMode();
						}
					}
					else if (gameMode == 選檔模式) {
						loadFIle(fileIndex);
					}
					break;
				case VK_ESCAPE:
					//esc 顯示選單
					if (gameMode == 結束模式 || gameMode == 遊戲模式) {
						gameMode = 選單模式;
						menuIndex = 0;
						showMenu(0);
					}
					else {
						backGameMode();
					}
					break;
				default:
					if (gameMode == 遊戲模式 || gameMode == 結束模式) {
						//悔棋
						if (input.Event.KeyEvent.uChar.AsciiChar == '<') {
							if (!game->log.isFirst()) {
								SHOW_DIALOG("確定要悔棋嗎", undo);
							}
						}
						//還原
						else if (input.Event.KeyEvent.uChar.AsciiChar == '>') {
							if (!game->log.isFinal()) {
								SHOW_DIALOG("確定要還原嗎", redo);
							}
						}
						//亂數移動位置
						else if (gameMode == 遊戲模式 && (!gameOver) && input.Event.KeyEvent.uChar.AsciiChar == 'R') {
							pair<Point, Point> randomMovePoint = game->board.randMove(game->getPlayer());
							selectedPoint = randomMovePoint.first;
							gamePoint = randomMovePoint.second;
							int gameStatus = moveChess();
							if (gameStatus == 紅方)
								SHOW_DIALOG("紅色勝利，要重新開始遊戲嗎", initBoard);
							if (gameStatus == 黑方)
								SHOW_DIALOG("黑色勝利，要重新開始遊戲嗎", initBoard);
						}
						//存檔
						else if (input.Event.KeyEvent.uChar.AsciiChar == 'S') {
							file.writeFile(game->board, game->getPlayer());
						}
						//存檔
						else if (input.Event.KeyEvent.uChar.AsciiChar == 'A') {
							file.writeAll(game->log.getRecord(), game->log.getMoveNum());
						}
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

void setInputCursor()
{
	COORD setPoint;
	setPoint.X = 0;
	setPoint.Y = 0;
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

void visibleCursor(bool visible)
{
	setCursor(gamePoint);

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 1;
	lpCursor.bVisible = visible;
	SetConsoleCursorInfo(handleOutput, &lpCursor);
}

void initBoard() {
	gameMode = 遊戲模式;
	gameOver = false;
	if (game != nullptr) delete game;
	pair<Board, int> loadFile = file.loadFile(READ_FILE_NAME);
	game = new Game(loadFile.first, loadFile.second);
	backGameMode();
	visibleCursor(true);
	setCursor(game->getPlayer() == 紅方 ? 紅棋起始位置 : 黑棋起始位置);
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
	game->changePlayer();
	game->log.WriteLog(game->board, game->getPlayer());
	game->log.moveDisplay(std::abs(game->board[gamePoint]), selectedPoint, gamePoint);
	showInterface();
	return status;
}

void undo()
{
	pair<Board, int> lastLog = game->log.LastBoard();
	game->setPlayer(lastLog.second);
	game->board.repent(lastLog.first);
	int gameStatus = game->board.situation(game->board);
	backGameMode();
}

void redo()
{
	pair<Board, int> nextLog = game->log.NextBoard();
	game->setPlayer(nextLog.second);
	game->board.repent(nextLog.first);
	backGameMode();
}

void showMenu(int index)
{
	visibleCursor(false);
	setInputCursor();
	game->drawMenu(index);
}

void showDialog(string content, int number)
{
	visibleCursor(false);
	setInputCursor();
	game->drawDialog(content, number);
}

void endGame()
{
	file.writeFile(game->board, game->getPlayer());
	ExitProcess(0);
}

void showInterface() {
	setInputCursor();
	game->drawInterface();
	setCursor(gamePoint);
}

void showFile(int index)
{
	visibleCursor(false);
	setInputCursor();
	game->drawOpenTxt(index,fileNames);
}

void loadFIle(int index) {
	vector<pair<Board, int>> fileBoards = file.loadAll(fileNames[index]);
	gameMode = 遊戲模式;
	if (game != nullptr) delete game;
	game = new Game(fileBoards);
	backGameMode();
	visibleCursor(true);
	setCursor(game->getPlayer() == 紅方 ? 紅棋起始位置 : 黑棋起始位置);
}

void backGameMode()
{
	showInterface();
	visibleCursor(true);
	int gameStatus = game->board.situation(game->board);
	if (gameStatus == 紅方 || gameStatus == 黑方) gameMode = 結束模式;
	else gameMode = 遊戲模式;
}
