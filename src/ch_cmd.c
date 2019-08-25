/*
	chesspernado
    Copyright (C) 2017  Danilo Novaković

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "chesspernado.h"

int command_check(BOARD (*board)[WIDTH], char *s) {
	int i1, j1, i2, j2, piece;
	piece = *s++;
	j1 = *s++ - 'a';
	i1 = *s++ - '0';
	if(*s >= '0' && *s <='2') i1 = HEIGHT - (i1*10 + (*s++ - '0'));
	else i1 = HEIGHT - i1;
	
	j2 = *s++ - 'a';
	i2 = *s++ - '0';
	
	if(*s >= '0' && *s <='2') 	i2 = HEIGHT - (i2*10 + (*s++ - '0'));
	else i2 = HEIGHT - i2;
	
	//printf("j1 = %d, i1 = %d, j2 = %d, i2 = %d\n", j1, i1, j2, i2);
	
	if(board[i1][j1].player != player) {
	    puts("error: you are trying to move an empty/enemy piece.");
		return 0;
	}
	if(board[i1][j1].type != piece) {
		printf("error: you tried to move '%c', but '%c' is on that position.\n", piece, board[i1][j1].type);
		return 0;
	}
	per ^= per;
	per++;
	switch(piece) {
		case 'P': 	if(!pawn_check(board, i1, j1, i2, j2)) return 0; break;
		case 'N':	if(!knight_check(board, i1, j1, i2, j2)) return 0; break;	
		case 'B':	if(!bishop_check(board, i1, j1, i2, j2)) return 0; break;
	}
	
	return 1;
}

int pawn_check(BOARD (*board)[WIDTH], int i1, int j1, int i2, int j2) {
	int absi, absj;
	if(board[i2][j2].player == board[i1][j1].player) {
		if(per) puts("error: friendly piece is blocking the path.");
		return 0;
	}
	absi = abs(i1 - i2);
	absj = abs(j1 - j2);
	if(j1!=j2) {	
		if(absj > 1) {
			if(per) printf("error: pawn can only move vertical. (diagonally is exeption for eating enemy piece).\n");
			return 0;
		}
		else if(!board[i2][j2].type) {
			if(per) puts("error: pawn can move diagonally only to eat enemys piece.");
			return 0;			
		}
	}
	if((player == 0) ? i1 < i2 : i1 > i2) {
		if(per) puts("error: pawn can't go backwards!");
		return 0;
	}
	if(absi>1) {
		if(per) puts("error: pawn can move only 1 step in chesspernados.");
		return 0;
	}
	if(!board[i1][j1].state && absi == 2) {
		if(i1 > i2 ? board[i1-1][j1].type  : board[i1+1][j1].type ) {
			if(per) puts("error: another piece is blocking the path.");
			return 0;
		}
	}
	if(j1 == j2 && board[i2][j2].type) {
		if(per) puts("error: another piece is blocking the path.");
		return 0;
	}
	
	return 1;
}

int knight_check(BOARD (*board)[WIDTH], int i1, int j1, int i2, int j2) {
	int absi, absj;
	if(board[i2][j2].player == board[i1][j1].player) {
		if(per) puts("error: friendly piece is blocking the path.");
		return 0;
	}
	absi = abs(i1 - i2);
	absj = abs(j1 - j2);
	if(absi < 1 || absi > 2 || absj < 1 || absj > 2) {
		if(per) puts("error: knight can only move in 'L'-shape.");
		return 0;
	}
	if(!((absi == 1 && absj ==2) || (absi == 2 && absj == 1))) {
		if(per) puts("error: knight can only move in 'L'-shape. ");
		return 0;
	} 
	return 1;
}


int bishop_check(BOARD (*board)[WIDTH], int i1, int j1, int i2, int j2) {
	int absi, absj, p, k;
	if(board[i2][j2].player == board[i1][j1].player) {
		if(per) puts("error: friendly piece is blocking the path.");
		return 0;
	}
	absi = abs(i1 - i2);
	absj = abs(j1 - j2);
	if(absi != absj) {
		if(per) puts("error: bishop can only move diagonally.");
		return 0;
	}
	//checks if there is an obsticle in diagonal path
	for(k = 1, p = absi; k < p; k++) {
			if(i1 > i2) {
				if(j1 < j2 ? board[i1 - k][j1+k].type : board[i1 - k][j1-k].type) {
					if(per) puts("error: another piece is blocking the path.");
					return 0;
				}
			}
			else if(j1 < j2 ? board[i1 + k][j1+k].type : board[i1 + k][j1-k].type) {
					if(per) puts("error: another piece is blocking the path.");
					return 0;
			}
	}
	
	return 1;
}

/*Checks if syntax of given command is correct, returns 1 if it is, and 0 if it's not*/
int syntax_check(char *p) {
	if(*p != 'N' && *p != 'P' &&  *p != 'B') return 0;
	if(*++p < 'a' || *p > 'h') return 0;
	if(*++p < '1' || *p > '9') return 0;
	char temp = *p++;
	if((*p >= '0' && *p <= '2') && temp == '1') p++;
	if(*p < 'a' || *p > 'h') return 0;
	if(*++p < '1' || *p > '9') return 0;
	temp = *p++;
	if((*p >= '0' && *p<='9') && temp != '1') return 0;
	if((temp == '1') && (*p > '2') ) return 0;
	return 1;
}