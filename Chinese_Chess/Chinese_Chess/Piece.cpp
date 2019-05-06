#include "Piece.h"


Piece::Piece() {

	gridLabel[0] = "１　２　３　４　５　６　７　８　９";
	gridLabel[1] = "九　八　七　六　五　四　三　二　一";
	gridLine[0] = "．＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝．";
	gridLine[1] = "∥　｜　｜　｜＼｜／｜　｜　｜　∥";
	gridLine[2] = "∥—＋—＋—＋—＋—＋—＋—＋—∥";
	gridLine[3] = "∥　｜　｜　｜／｜＼｜　｜　｜　∥";
	gridLine[4] = "∥—＋—＋—＋—＋—＋—＋—＋—∥";
	gridLine[5] = "∥　｜　｜　｜　｜　｜　｜　｜　∥";
	gridLine[6] = "∥—＋—＋—＋—＋—＋—＋—＋—∥";
	gridLine[7] = "∥　｜　｜　｜　｜　｜　｜　｜　∥";
	gridLine[8] = "∥———————————————∥";
	gridLine[9] = "∥　　　楚河　　　　　漢界　　　∥";
	gridLine[10] = "∥———————————————∥";
	gridLine[11] = "∥　｜　｜　｜　｜　｜　｜　｜　∥";
	gridLine[12] = "∥—＋—＋—＋—＋—＋—＋—＋—∥";
	gridLine[13] = "∥　｜　｜　｜　｜　｜　｜　｜　∥";
	gridLine[14] = "∥—＋—＋—＋—＋—＋—＋—＋—∥";
	gridLine[15] = "∥　｜　｜　｜＼｜／｜　｜　｜　∥";
	gridLine[16] = "∥—＋—＋—＋—＋—＋—＋—＋—∥";
	gridLine[17] = "∥　｜　｜　｜／｜＼｜　｜　｜　∥";
	gridLine[18] = "．＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝．";
}


void Piece::pos(string s, bool p) {
	symbol = s;
	player = p;
}
