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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define MAX_BISHOPS 2
#define MAX_KNIGHTS 3
#define WIDTH 8
#define HEIGHT 12
#define MAX_BUFFER 10
#define RED "\x1b[33;1m"
#define BLUE  "\x1b[37;1m"
#define BG_WHITE "\x1b[40m"
#define BG_YELLOW "\x1b[41m"
#define CL_RESET  "\x1b[0m"
/*NOTE: macro names above do not match the actuall color because i'm still experimenting 
	with what colors match the best, and i don't want to change macro name everytime i try 
	out new color
*/
#ifndef __BOARD__
#define __BOARD__
typedef struct board_st{
	int type : 8;	// type = {K,P,N,B,0} 
	int player : 2;	// player = {-1, 0, 1}
	unsigned char state : 3;
} BOARD;

extern unsigned char player;
extern unsigned char per;
extern unsigned char end;
extern unsigned char difficulty;

//basic board functions (print, init, copy)
void print_matrix(BOARD (*)[WIDTH]);
void init_board(BOARD (*)[WIDTH]);
int is_empty(BOARD (*)[WIDTH], int); 
int is_full(BOARD (*)[WIDTH]);
void usage_tip(void); 
void boardcpy(BOARD (*)[WIDTH], BOARD (*)[WIDTH]);
void rm_piece(BOARD *);
void rm_wave(BOARD (*)[WIDTH]);

//init setup
int board_setup(BOARD (*)[WIDTH]);
void wait(int);

//syntax and command check functions
int syntax_check(char *);
int command_check(BOARD (*)[WIDTH], char *);
int pawn_check(BOARD (*)[WIDTH], int, int, int, int);
int knight_check(BOARD (*)[WIDTH], int, int, int, int);
int bishop_check(BOARD (*)[WIDTH], int, int, int, int);

#endif
