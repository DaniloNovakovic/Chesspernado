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

void init_board(BOARD (*board)[WIDTH]) {
	int i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			board[i][j].type = 0;
			board[i][j].player = -1;
			board[i][j].state = 0;
		}
	}
}
void print_matrix(BOARD (*board)[WIDTH]) {
	//printf("\33[2J");  				// cls (version 1)
	system("tput reset");			// cls ((better) version 2) - resets terminal also
	int i, j, k = 0;
	printf("\n\t     ");
	for(i ^= i; i < WIDTH; printf("%c ", 'a' + i++));
		
	printf("\n\t     ");
	for(i ^= i; i < WIDTH; i++) 
		printf("--");
	
	putchar('\n');
	for(i ^= i; i < HEIGHT; i++) {
		printf(CL_RESET "\t%2d | ", HEIGHT - i);
		for(j ^= j; j < WIDTH; j++) {
			switch(board[i][j].type) {
				case 0 : printf((k&1) == 1 ? BG_YELLOW  "  " : BG_WHITE  "  "); break;
				case 'K' : case 'B' : case 'N' : case 'R' : case 'P': case 'k' : case 'n' : case 'r' : case 'p' :
					printf((k&1) == 1 ? BG_YELLOW : BG_WHITE);
					printf(board[i][j].player == 1 ? RED "%c " CL_RESET : BLUE  "%c " CL_RESET , board[i][j].type); break;
				case 'b' :
					printf((k&1) == 1 ? BG_YELLOW : BG_WHITE);
					printf("\x1b[36;1m%c \x1b[0m", board[i][j].type);
					break;
			}
			k ^= 1;
		}
		k ^= 1;
		printf(CL_RESET "| %2d\n", HEIGHT - i);
	}
	printf("\t     ");
	for(i ^= i; i < WIDTH; i++) 
		printf("--");
	printf("\n\t     ");
	for(i ^= i; i < WIDTH; printf("%c ", 'a' + i++));
	puts("\n");
}

void usage_tip(void) {
	printf("Usage ex.:  \x1b[31;1mN\x1b[35;1me6\x1b[32;1mc5\x1b[0m" 
	" (\x1b[31;1mtype\x1b[0m, \x1b[35;1mfrom\x1b[0m (column/row) - \x1b[32;1mto\x1b[0m(column/row))\n\x1b[33;1m*CASE SENSITIVE*\x1b[0m\n");
}
void boardcpy(BOARD (*b1)[WIDTH], BOARD (*b2)[WIDTH]) {
	int i, j;
	for(i ^= i; i < HEIGHT; i++) {
		for(j ^= j; j < WIDTH; j++) {
			b1[i][j].type = b2[i][j].type;
			b1[i][j].player = b2[i][j].player;
			b1[i][j].state = b2[i][j].state;
		}
	}
}

void rm_piece(BOARD *piece) {
	piece->type = 0;
	piece->player = -1;
	piece->state = 0;
}
void rm_wave(BOARD (*board)[WIDTH]) {
	int i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			if(board[i][j].player == 1) {
				rm_piece(&board[i][j]);
			}
		}
	}
}
int is_empty(BOARD (*board)[WIDTH], int p) {
	int i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			if(board[i][j].player == p) 
				return 0;
		}
	}
	return 1;
}
int is_full(BOARD (*board)[WIDTH]) {
	int i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			if(board[i][j].type == 0) 
				return 0;
		}
	}
	return 1;
}