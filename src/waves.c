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
#include "waves.h"
#define MAX_ROW 5
/* i and j are gonna be randomly generated, randomized loop can last
	for max_loops, if it still hasn't placed figures by then, then they will be placed in the 
	first available position in board, if they can't be placed anywhere in the board, player
	will lose the game*/
void generate_wave1(BOARD (*board)[WIDTH], int pawns) {
	srand(time(NULL));
	int max_loops = 50, i, j, k;
	for(k = 0; k < max_loops && pawns > 0; k++) {
		generate_index(&i, &j);
		if(board[i][j].type == 0) {
			pawns--;
			board[i][j].type = 'p';
			board[i][j].player = 1;
		}
	}
	if(pawns > 0) {
		int j;
		for(i = 0; i < HEIGHT && pawns > 0; i++) {
			for(j = 0; j < WIDTH && pawns > 0; j++) {
				if(board[i][j].type == 0) {
					pawns--;
					board[i][j].type = 'p';
					board[i][j].player = 1;
				}
			}
		}
		if(pawns > 0) end++;
	}
	
}
void generate_wave2(BOARD (*board)[WIDTH], int pawns, int bishops) {
	srand(time(NULL));
	int max_loops = 50, i, j, k;
	for(k = 0; k < max_loops && (pawns > 0 || bishops > 0); k++) {
		generate_index(&i, &j);
		if(board[i][j].type == 0 && i < 3 && bishops > 0) {
			bishops--;
			board[i][j].type = 'b';
			board[i][j].player = 1;
			generate_index(&i, &j);
		}
		if(board[i][j].type == 0 && pawns > 0) {
			pawns--;
			board[i][j].type = 'p';
			board[i][j].player = 1;
		}
	}
	if(pawns > 0 || bishops > 0) {
		int j;
		for(i = 0; i < HEIGHT && (pawns > 0 || bishops > 0); i++) {
			for(j = 0; j < WIDTH && (pawns > 0 || bishops > 0); j++) {
				if(board[i][j].type == 0 && bishops > 0) {
					bishops--;
					board[i][j].type = 'b';
					board[i][j].player = 1;
				}
				if(board[i][j].type == 0 && pawns > 0) {
					pawns--;
					board[i][j].type = 'p';
					board[i][j].player = 1;
				}
			}
		}
		if(pawns > 0 || bishops > 0) end++;
	}
	
}
void generate_pawn(BOARD (*board)[WIDTH]) {
	generate_wave1(board, 1);
}
void generate_index(int *pi, int *pj) {
	*pi = random_number(0, 4);
	*pj = random_number(0, 7);
}
//closed interval [min, max]
int random_number(int min, int max) {
	int result = 0, low = 0, high = 0;
	//swaps min and max withouth any additional variable
	if(min > max) {
		min^=max;
		max^=min;
		min^=max;
	}
	low = min;
	high = max + 1; 

	result = (rand() % (high - low)) + low;
	return result;
}