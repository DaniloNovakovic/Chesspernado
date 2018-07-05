/*
	chesspernado
    Copyright (C) 2017  Danilo Novakoviæ

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
void start_tutorial(void);
void print_tutorial(BOARD (*)[WIDTH]);
void update_pawn(BOARD (*)[WIDTH], int, int, int);
void update_knight(BOARD (*)[WIDTH], int, int);
void update_bishop(BOARD (*)[WIDTH], int, int);
FILE * tutorial_lines(FILE *);
int get_input_tuto(BOARD (*)[WIDTH], int *);
void remove_states(BOARD (*)[WIDTH]); 
unsigned char start_ai_animation(FILE *);
void find_bishop_ai(BOARD (*)[WIDTH], int *, int *);
void hint_print(BOARD (*)[WIDTH]);

//game simulation
unsigned char start_game_simulation(void);
unsigned char continue_msg(void); // returns 1 if user wants to continue, and 0 if he doesnt
unsigned char is_happy_king_alive(BOARD (*)[WIDTH]);