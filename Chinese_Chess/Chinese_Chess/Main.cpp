#include "Game.h"
#include "File.h"
#include <utility>
using namespace std;


int main() {
	while (true) {
		//��l
		Game game;
		File file;

		//�]�w����
		Board loadBoard = file.loadFile("game.txt");
		game.board.changeBoard(loadBoard);
		game.drawInterface();
		system("pause");

		//��ܬY�ӴѤl
		game.board.select(Point(0,0));
		game.drawInterface();
		system("pause");

		//���ʴѤl
		if (game.board.move(Point(0, 0), Point(0, 0)) == -1) {
			game.log.WriteLog(game.board, game.getPlayer());
			game.drawInterface();
		}
		system("pause");

		//�^�_
		if (!game.log.isFirst()) {
			pair<Board,int> lastLog = game.log.LastBoard();
			game.setPlayer(lastLog.second);
			game.board.repent(lastLog.first);
			game.drawInterface();
		}
		system("pause");
		
		//�_��
		if (!game.log.isFinal()) {
			pair<Board, int> nextLog = game.log.NextBoard();
			game.setPlayer(nextLog.second);
			game.board.repent(nextLog.first);
			game.drawInterface();
		}
		system("pause");
		
		//���
		game.drawMenu(0);
		system("pause");

		//Dialog
		game.drawDialog("Exit", 0);
		system("pause");

		//�g��
		file.writeFile(game.board, "result.txt");
	}
}