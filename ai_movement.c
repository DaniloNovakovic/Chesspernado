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
#include "ai_movement.h"
void suicide_rook(BOARD (*board)[WIDTH], int p) {
	int i = 0, j = 0, k = 0;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			if(board[i][j].type == 'R' && board[i][j].player == p) {
				if(p == 0) {
					for(k = 0; (i - k) >=0 ; k++) {
						if(((i-k-1)<0) && board[i-k][j].type == 0) {
							rm_piece(&board[i][j]);
							break;
						}
						if(k != 0 && board[i-k][j].type != 0){
							rm_piece(&board[i-k][j]);
							rm_piece(&board[i][j]);
							break;
						}
					}
				}
				else {
					for(k = 0; i + k < HEIGHT; k++) {
						if((i+k+1) >= HEIGHT && board[i+k][j].type == 0) {
							rm_piece(&board[i][j]);
							break;
						}
						if(board[i+k][j].type != 0) {
							rm_piece(&board[i+k][j]);
							rm_piece(&board[i][j]);
							break;
						}
					}
				}
			}
		}
	}
}
int ai_move(BOARD (*board)[WIDTH], int *points) {
	int i, j, figures_moved = 0;
	for(i = HEIGHT - 1; i >= 0; i--) {
		for(j = WIDTH - 1; j >= 0; j--) {
			if(board[i][j].player == 1) {
				switch(board[i][j].type) {
					case 'p': figures_moved += ai_movpawn(board, i, j); break;
					case 'b': figures_moved += ai_movbishop(board, i, j); break;
				}
			} 
			else if(points != NULL && board[i][j].player == 0 && board[i][j].type == 'K') {
				(*points)++;
			}
		}
	}
	return figures_moved;
}
//returns 1 if pawn had legal move, 0 if it didn't
int ai_movpawn(BOARD (*board)[WIDTH], int i, int j) {
	if((i+1 == HEIGHT-1) && board[i+1][j].type == 0) {
		mov_figure(board, i, j, i+1, j);
		end++;
		return 1;
	}
	if(i+1 < HEIGHT) {
		if(j-1 >= 0) {
			if(board[i+1][j-1].player == 0) {
				mov_figure(board, i, j, i+1, j-1);
				return 1;
			}
		}
		if(j+1 < WIDTH) {
			if(board[i+1][j+1].player == 0) {
				mov_figure(board, i, j, i+1, j+1);
				return 1;
			}
		}
		if(board[i+1][j].type == 0) {
			mov_figure(board, i, j, i+1, j);
			return 1;
		}
	}
	
	return 0;
}
int ai_movbishop(BOARD (*board)[WIDTH], int i, int j) {
	int k;
	if(j-1 >= 0 && i+1 < HEIGHT) {
		for(k = 1; i+k < HEIGHT && j - k >= 0; k++) {
			if(board[i+k][j-k].player == 0) {
				mov_figure(board, i, j, i+k, j-k);
				return 1;
			}
			if((((i+k+1) >= HEIGHT) || ((j-k-1)<0)) && board[i+k][j-k].player != 1) {
				mov_figure(board, i, j, i+k, j-k);
				if(i+k == HEIGHT - 1) end++;
				return 1;
			}
			if(board[i+k][j-k].player == 1 && ((i+k-1)!= i && (j-k+1) != j)) {
				mov_figure(board, i, j, i+k-1, j-k+1);
				return 1;
			}
		}
	}
	if(j+1 < WIDTH && i+1 < HEIGHT) {
		for(k = 1; i+k < HEIGHT && j+k < WIDTH; k++) {
			if(board[i+k][j+k].player == 0) {
				mov_figure(board, i, j, i+k, j+k);
				return 1;
			}
			if((((i+k+1) >= HEIGHT) || ((j+k+1)>=WIDTH)) && board[i+k][j+k].player != 1) {
				mov_figure(board, i, j, i+k, j+k);
				if(i+k == HEIGHT - 1) end++;
				return 1;
			}
			if(board[i+k][j+k].player == 1 &&  ((i+k-1)!= i && (j+k-1) != j)) {
				mov_figure(board, i, j, i+k-1, j+k-1);
				return 1;
			}
		}
	}
	return 0;
}
void mov_figure(BOARD (*board)[WIDTH], int i1, int j1, int i2, int j2) {
			board[i2][j2].type = board[i1][j1].type;
			board[i2][j2].player = board[i1][j1].player;
			board[i2][j2].state = 1;	
			rm_piece(&board[i1][j1]);
}