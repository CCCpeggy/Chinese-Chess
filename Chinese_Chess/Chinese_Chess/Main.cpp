#include "Game.h"
#include "File.h"
#include <conio.h>
#include <utility>
#include <Windows.h>
#pragma region define
#define READ_FILE_NAME "game.txt"
#define WRITE_FILE_NAME "result.txt"
#define BOARD_X 0
#define BOARD_Y 0
#define SHOW_DIALOG(CONTENT,FUNC){ gameMode = 2;dialogIndex = 0;dialogFunc = (FUNC);dialogContent = (CONTENT);showDialog(dialogContent, 0);}
#define GAME_MODE 1110
#define MENU_MODE 1111
#define DIALOG_MODE 1112

#pragma endregion
using namespace std;

#pragma region  declare

//����e��
HANDLE handleInput;
HANDLE handleOutput;

//����C��
const wchar_t* projectName = L"�H��";
Game* game = nullptr;
File file;
Point gamePoint; //�ثe��J�I�Ҧb��m
Point selectedPoint; //������H�ѩҦb��m

//���function
void updateCursor(); //��s��J�I�Ҧb��m
void setCursor(int, int); //�]�w��J�I�Ҧb��m
void movePoint(int); // 0 ��; 1 �W; 2 �k; 3 �U;

//�C����function
void initBoard(); //��l�ƹC��
void selectChess(); //��ܴѤl
int moveChess(); //���ʿ�ܪ��Ѥl //�^�Ǥ���-1:�C������
void undo(); //����
void redo(); //�^�_
void showMenu(int); //��ܿ��
void showDialog(string, int); //��ܹ�ܮ�
void endGame(); //�����C��
void showInterface(); //���s��ܹC���e��
bool hasChess();
bool validMove();

#pragma endregion

int main() {

	char key;
	int gameMode = GAME_MODE;
	int menuIndex = 0; //���������
	int dialogIndex = 0; //��ܮؿ������
	bool selectedChess = false; //�O�_����F�Ѥl
	void (*dialogFunc)() = nullptr; //��ܮةҭn�����ʧ@
	string dialogContent = ""; //��ܮ���ܪ���r

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
					//�W�U���k���ʮ�
					//�C���Ҧ�
					if (gameMode == GAME_MODE) {
						//�ܧ���
						movePoint(input.Event.KeyEvent.wVirtualKeyCode - VK_LEFT);
						updateCursor();
					}
					//���Ҧ�
					else if (gameMode == MENU_MODE) {
						//�p����������
						menuIndex = (++menuIndex) % 4;
						//���s��ܿ��
						showMenu(menuIndex);
					}
					//��ܮؼҦ�
					else if (gameMode == DIALOG_MODE) {
						//�p���ܮؿ������
						dialogIndex = (++dialogIndex) % 2;
						//���s��ܹ�ܮ�
						showDialog(dialogContent, dialogIndex);
					}
					break;
				case VK_RETURN:
					//��Enter�ʧ@
					//�C���Ҧ�
					if (gameMode == GAME_MODE) {
						if (game->board[gamePoint] <= 0) {
							//���ʦ�m
							int gameStatus = moveChess();
							if (gameStatus == 1) SHOW_DIALOG("����ӧQ�A�n���s�}�l�C����", initBoard);
							if (gameStatus == 2) SHOW_DIALOG("�¦�ӧQ�A�n���s�}�l�C����", initBoard);
						}
						else {
							selectChess();
						}
					}
					//���Ҧ�
					else if (gameMode == MENU_MODE) {
						//����ܶ���
						switch (menuIndex) {
						case 0:
							//�~��C��
							showInterface();
							break;
						case 1:
							//���s�}�l
							SHOW_DIALOG("�T�w�n���s�}�l�C����", initBoard);
							break;
						case 2:
							//�^�D���
							break;
						case 3:
							//�����C��
							SHOW_DIALOG("�T�w�n�����C����", endGame);
							break;
						}
						gameMode = GAME_MODE;
					}
					//��ܮؼҦ�
					else if (gameMode == DIALOG_MODE) {
						//���"�O"
						if (dialogIndex == 1) dialogFunc();
						//���s��ܵe��
						showInterface();
					}
					break;
				case VK_ESCAPE:
					//esc ��ܿ��
					gameMode = MENU_MODE;
					menuIndex = 0;
					showMenu(0);
					break;
				default:
					//����
					if (input.Event.KeyEvent.uChar.AsciiChar == '<') {
						SHOW_DIALOG("�T�w�n���Ѷ�", undo);
					}
					//�٭�
					else if (input.Event.KeyEvent.uChar.AsciiChar == '>') {
						SHOW_DIALOG("�T�w�n�٭��", redo);
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
	setPoint.X = (gamePoint.x) * 4 + BOARD_X;
	setPoint.Y = (gamePoint.y) * 2 + BOARD_Y;
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
		gamePoint.x += gamePoint.x ? -1 : 0;
		break;
		//up
	case 1:
		gamePoint.y += gamePoint.y ? -1 : 0;
		break;
		//right
	case 2:
		gamePoint.x += gamePoint.x < 8 ? 1 : 0;
		break;
		//down
	case 3:
		gamePoint.y += gamePoint.y < 9 ? 1 : 0;
		break;

	}
}

void initBoard() {
	setCursor(0, 0);
	if (game != nullptr) delete game;
	game = new Game();
	Board loadBoard = file.loadFile(READ_FILE_NAME).first;
	game->board.changeBoard(loadBoard);
	showInterface();
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
	if (status == -1) {
		game->log.WriteLog(game->board, game->getPlayer());
		showInterface();
	}
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
	game->drawMenu(index);
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
	setCursor(0, 0);
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

