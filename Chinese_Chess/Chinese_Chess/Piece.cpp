#include "Piece.h"

Piece::Piece() {
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 8; j++) {
			if (i == 0) {
				if (j == 8) {
					gridline[i][j] = "שß ";
				}
				else if (j == 0) {
					gridline[i][j] = "שÝ ";
				}
				else {
					gridline[i][j] = "שש ";
				}
			}
			else if (i == 9) {
				if (j == 8) {
					gridline[i][j] = "שו ";
				}
				else if (j == 0) {
					gridline[i][j] = "שד ";
				}
				else {
					gridline[i][j] = "שש ";
				}
			}
			else if (i == 4) {
				if (j == 0 || j == 8) {
					gridline[i][j] = "שר ";
				}
				else {
					gridline[i][j] = "¢r ";
				}
			}
			else if (i == 5) {
				if (j == 0 || j == 8) {
					gridline[i][j] = "שר ";
				}
				else {
					gridline[i][j] = "¢s ";
				}
			}
			else {
				if (j == 0 || j == 8) {
					gridline[i][j] = "שר ";
				}
				else {
					gridline[i][j] = "¢q ";
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
