#include "Piece.h"


Piece::Piece() {

	gridLabel[0] = "１　２　３　４　５　６　７　８　９";
	gridLabel[1] = "九　八　七　六　五　四　三　二　一";
	gridLine[0] = "．＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝．　　　　　　　　　　　　";
	gridLine[1] = "∥　｜　｜　｜＼｜／｜　｜　｜　∥　　　　　　　　　　　　";
	gridLine[2] = "∥—＋—＋—＋—＋—＋—＋—＋—∥　　　　　　　　　　　　";
	gridLine[3] = "∥　｜　｜　｜／｜＼｜　｜　｜　∥　　　　　　　　　　　　";
	gridLine[4] = "∥—＋—＋—＋—＋—＋—＋—＋—∥　　　　　　　　　　　　";
	gridLine[5] = "∥　｜　｜　｜　｜　｜　｜　｜　∥　　　　　　　　　　　　";
	gridLine[6] = "∥—＋—＋—＋—＋—＋—＋—＋—∥　　　　　　　　　　　　";
	gridLine[7] = "∥　｜　｜　｜　｜　｜　｜　｜　∥　　　Esc　選單　S　存檔";
	gridLine[8] = "∥———————————————∥　　　　　　　　　　　　";
	gridLine[9] = "∥　　　楚河　　　　　漢界　　　∥　　　　<　悔棋　>　還原";
	gridLine[10] = "∥———————————————∥　　　　　　　　　　　　";
	gridLine[11] = "∥　｜　｜　｜　｜　｜　｜　｜　∥　　　　 Enter　選取棋子";
	gridLine[12] = "∥—＋—＋—＋—＋—＋—＋—＋—∥　　　　　　　　　　　　";
	gridLine[13] = "∥　｜　｜　｜　｜　｜　｜　｜　∥　　↑　　　　　　　　　";
	gridLine[14] = "∥—＋—＋—＋—＋—＋—＋—＋—∥　　　　　　　　　　　　";
	gridLine[15] = "∥　｜　｜　｜＼｜／｜　｜　｜　∥　　↓　　　　　　　　　";
	gridLine[16] = "∥—＋—＋—＋—＋—＋—＋—＋—∥　　　　　　　　　　　　";
	gridLine[17] = "∥　｜　｜　｜／｜＼｜　｜　｜　∥　　　　　　　　　　　　";
	gridLine[18] = "．＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝．　　　　　　　　　　　　";
	menu[0] = "╔═ ═ ═ ═ ═ ═╗ ";
	menu[1] = "║  繼續遊戲 ║ ";
	menu[2] = "╠═ ═ ═ ═ ═ ═╣ ";
	menu[3] = "║  重新開始 ║ ";
	menu[4] = "╠═ ═ ═ ═ ═ ═╣ ";
	menu[5] = "║  隨便打打 ║ ";
	menu[6] = "╠═ ═ ═ ═ ═ ═╣ ";
	menu[7] = "║  離開遊戲 ║ ";
	menu[8] = "╚═ ═ ═ ═ ═ ═╝ ";

	dialog[0] = "╔ ═　═　═　═　═　═　═　═　═　═ ╗ ";
	dialog[1] = "║　　　　　　　　　　　　　　　║ ";
	dialog[2] = "║　　　　　是　　　　否　　　　║ ";
	dialog[3] = "╚ ═　═　═　═　═　═　═　═　═　═ ╝ ";

}


void Piece::pos(string s, bool p) {
	symbol = s;
	player = p;
}
