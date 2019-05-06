#include "Game.h"
#include "File.h"
#include <conio.h>
#include <utility>
#include <Windows.h>
#pragma region define
#define READ_FILE_NAME "game.txt"
#define WRITE_FILE_NAME "result.txt"
#define �ѽL����IX 16
#define �ѽL����IY 2
#define �ѽLX�b�[�v 4
#define �ѽLY�b�[�v 2
#define �C���Ҧ� 1110
#define ���Ҧ� 1111
#define ��ܮؼҦ� 1112
#define SHOW_DIALOG(CONTENT,FUNC){ gameMode = ��ܮؼҦ�;dialogIndex = 0;dialogFunc = (FUNC);dialogContent = (CONTENT);showDialog(dialogContent, 0);}
#define ���� 0
#define �¤� 1
#define ���Ѱ_�l��m Point(9,0)
#define �´Ѱ_�l��m Point(0,0)

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
int gameMode;

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
					if (gameMode == �C���Ҧ�) {
						//�ܧ���
						movePoint(input.Event.KeyEvent.wVirtualKeyCode - VK_LEFT);
						updateCursor();
					}
					//���Ҧ�
					else if (gameMode == ���Ҧ�) {
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_UP) menuIndex--;
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) menuIndex++;
						//�p����������
						menuIndex = menuIndex % 4;
						//���s��ܿ��
						showMenu(menuIndex);
					}
					//��ܮؼҦ�
					else if (gameMode == ��ܮؼҦ�) {
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) dialogIndex--;
						if (input.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) dialogIndex++;
						//�p���ܮؿ������
						dialogIndex = dialogIndex % 2;
						//���s��ܹ�ܮ�
						showDialog(dialogContent, dialogIndex);
					}
					break;
				case VK_RETURN:
					//��Enter�ʧ@
					//�C���Ҧ�
					if (gameMode == �C���Ҧ�) {
						int piecePart = game->board[gamePoint] <= 7 ? �¤� : ����;
						if (game->board[gamePoint] <= 0 ) {
							//���ʦ�m
							int gameStatus = moveChess();
							if (gameStatus == 1) SHOW_DIALOG("����ӧQ�A�n���s�}�l�C����", initBoard);
							if (gameStatus == 2) SHOW_DIALOG("�¦�ӧQ�A�n���s�}�l�C����", initBoard);
						}
						else if(piecePart == game->getPlayer()){
							selectChess();
						}
					}
					//���Ҧ�
					else if (gameMode == ���Ҧ�) {
						//����ܶ���
						switch (menuIndex) {
						case 0:
							//�~��C��
							//��ܥ���
							CONSOLE_CURSOR_INFO lpCursor;
							lpCursor.dwSize = 1;
							lpCursor.bVisible = TRUE;
							SetConsoleCursorInfo(handleOutput, &lpCursor);
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
						gameMode = �C���Ҧ�;
					}
					//��ܮؼҦ�
					else if (gameMode == ��ܮؼҦ�) {
						//���"�O"
						if (dialogIndex == 1) dialogFunc();
						//���s��ܵe��
						showInterface();
					}
					break;
				case VK_ESCAPE:
					//esc ��ܿ��
					gameMode = ���Ҧ�;
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
	setPoint.X = (gamePoint.y) * �ѽLX�b�[�v + �ѽL����IX;
	setPoint.Y = (gamePoint.x) * �ѽLY�b�[�v + �ѽL����IY;
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
	gameMode = �C���Ҧ�;
	if (game != nullptr) delete game;
	game = new Game();
	Board loadBoard = file.loadFile(READ_FILE_NAME).first;
	game->board.changeBoard(loadBoard);
	showInterface();
	setCursor(game->getPlayer() ? �´Ѱ_�l��m : ���Ѱ_�l��m);
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
	//���å���
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

