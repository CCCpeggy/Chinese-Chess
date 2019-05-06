#include "Piece.h"


Piece::Piece() {

	gridLabel[0] = "���@���@���@���@���@���@���@���@��";
	gridLabel[1] = "�E�@�K�@�C�@���@���@�|�@�T�@�G�@�@";
	gridLine[0] = "�D�סססססססססססססססD";
	gridLine[1] = "���@�U�@�U�@�U�@�U���U�@�U�@�U�@��";
	gridLine[2] = "���X�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX��";
	gridLine[3] = "���@�U�@�U�@�U���U�@�U�@�U�@�U�@��";
	gridLine[4] = "���X�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX��";
	gridLine[5] = "���@�U�@�U�@�U�@�U�@�U�@�U�@�U�@��";
	gridLine[6] = "���X�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX��";
	gridLine[7] = "���@�U�@�U�@�U�@�U�@�U�@�U�@�U�@��";
	gridLine[8] = "���X�X�X�X�X�X�X�X�X�X�X�X�X�X�X��";
	gridLine[9] = "���@�@�@���e�@�@�@�@�@�~�ɡ@�@�@��";
	gridLine[10] = "���X�X�X�X�X�X�X�X�X�X�X�X�X�X�X��";
	gridLine[11] = "���@�U�@�U�@�U�@�U�@�U�@�U�@�U�@��";
	gridLine[12] = "���X�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX��";
	gridLine[13] = "���@�U�@�U�@�U�@�U�@�U�@�U�@�U�@��";
	gridLine[14] = "���X�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX��";
	gridLine[15] = "���@�U�@�U�@�U�@�U���U�@�U�@�U�@��";
	gridLine[16] = "���X�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX�ϡX��";
	gridLine[17] = "���@�U�@�U�@�U���U�@�U�@�U�@�U�@��";
	gridLine[18] = "�D�סססססססססססססססD";
	menu[0] = "���� �� �� �� �� ���� ";
	menu[1] = "��  �~��C�� �� ";
	menu[2] = "���� �� �� �� �� ���� ";
	menu[3] = "��  ���s�}�l �� ";
	menu[4] = "���� �� �� �� �� ���� ";
	menu[5] = "��  �H�K���� �� ";
	menu[6] = "���� �� �� �� �� ���� ";
	menu[7] = "��  ���}�C�� �� ";
	menu[8] = "���� �� �� �� �� ���� ";
}


void Piece::pos(string s, bool p) {
	symbol = s;
	player = p;
}
