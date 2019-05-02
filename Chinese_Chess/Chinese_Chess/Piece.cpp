#include "Piece.h"

Piece::Piece() {
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 8; j++) {
			if (i == 0) {
				if (j == 8) {
					gridline[i][j] = "�� ";
				}
				else if (j == 0) {
					gridline[i][j] = "�� ";
				}
				else {
					gridline[i][j] = "�� ";
				}
			}
			else if (i == 9) {
				if (j == 8) {
					gridline[i][j] = "�� ";
				}
				else if (j == 0) {
					gridline[i][j] = "�� ";
				}
				else {
					gridline[i][j] = "�� ";
				}
			}
			else if (i == 4) {
				if (j == 0 || j == 8) {
					gridline[i][j] = "��";
				}
				else {
					gridline[i][j] = "�X";
				}
			}
			else if (i == 5) {
				if (j == 0 || j == 8) {
					gridline[i][j] = "��";
				}
				else {
					gridline[i][j] = "�X";
				}
			}
			else {
				if (j == 0 || j == 8) {
					gridline[i][j] = "��";
				}
				else {
					gridline[i][j] = "��";
				}

			}
		}
	}

	
}


void Piece::pos(string s, bool p, int x, int y) {
	symbol = s;
	player = p;
	locx = x;
	locy = y;
}
