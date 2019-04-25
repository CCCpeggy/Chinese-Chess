#include "Game.h"
#include "File.h"
#include <utility>
using namespace std;


int main() {
	while (true) {
		//初始
		Game game;
		File file;

		//設定版面
		Board loadBoard = file.loadFile("game.txt");
		game.board.changeBoard(loadBoard);
		game.drawInterface();
		system("pause");

		//選擇某個棋子
		game.board.select(Point(0,0));
		game.drawInterface();
		system("pause");

		//移動棋子
		if (game.board.move(Point(0, 0), Point(0, 0)) == -1) {
			game.log.WriteLog(game.board, game.getPlayer());
			game.drawInterface();
		}
		system("pause");

		//回復
		if (!game.log.isFirst()) {
			pair<Board,int> lastLog = game.log.LastBoard();
			game.setPlayer(lastLog.second);
			game.board.repent(lastLog.first);
			game.drawInterface();
		}
		system("pause");
		
		//復原
		if (!game.log.isFinal()) {
			pair<Board, int> nextLog = game.log.NextBoard();
			game.setPlayer(nextLog.second);
			game.board.repent(nextLog.first);
			game.drawInterface();
		}
		system("pause");
		
		//選單
		game.drawMenu(0);
		system("pause");

		//Dialog
		game.drawDialog("Exit", 0);
		system("pause");

		//寫檔
		file.writeFile(game.board, "result.txt");
	}
}