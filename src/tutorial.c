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
#include "tutorial.h"
#include "ai_movement.h"
#include "waves.h"
#define BG_GREEN "\x1b[42m" 
#define BG_CYAN "\x1b[44m"
void start_tutorial(void) {
	BOARD board[HEIGHT][WIDTH];
	//char c;
	FILE *pin = fopen("tutorial.txt", "r");
	if(pin == NULL) {
		puts("error: failed to open tutorial.txt");
		exit(EXIT_FAILURE);
	}
	
	system("tput reset");
	printf("\t\t\x1b[32;4;1mTUTORIAL\x1b[0m\n");
	
	init_board(board);
	
	int i = (int)HEIGHT/2, j = (int)WIDTH/2;
	
	board[i][j].type = 'N';
	board[i][j].player = 0;
	update_knight(board, i, j);
	
	print_tutorial(board);
	pin = tutorial_lines(pin);
	printf("Notation: Piece \x1b[31;1mtype\x1b[0m / \x1b[35;1mfrom\x1b[0m / \x1b[32;1mto\x1b[0m" 
	" - where both '\x1b[35;1mfrom\x1b[0m' and '\x1b[32;1mto\x1b[0m' are defined \nas column/row. ");
	printf("example: \x1b[31;1mN\x1b[35;1me6\x1b[32;1mc5\x1b[0m \x1b[33;1m*CASE SENSITIVE*\x1b[0m\n");
	printf("\x1b[37;1;4mTASK\x1b[0m: Move knight (\x1b[1mN\x1b[0m) to any "
		"\x1b[32;1mAVAILABLE\x1b[0m field\n");

	if(get_input_tuto(board, NULL))
		return;
	print_matrix(board);
	printf("\x1b[36;1mSPLENDID WORK!\x1b[0m\n");
	if(!continue_msg()) return;
	
	system("tput reset");
	
	init_board(board);

	board[i][j].type = 'B';
	board[i][j].player = 0;
	update_bishop(board, i, j);
	
	print_tutorial(board);
	pin = tutorial_lines(pin);
	printf("\x1b[37;1;4mTASK\x1b[0m: Move bishop (\x1b[1mB\x1b[0m) to any "
		"\x1b[32;1mAVAILABLE\x1b[0m field\n");
	
	if(get_input_tuto(board, NULL))
		return;
	print_matrix(board);
	printf("\x1b[33;1mMARVELOUS! You are on your way to becoming a pro!\x1b[0m\n");
	if(!continue_msg()) return;
	
	if(!start_ai_animation(pin)) return;
	
	if(!start_game_simulation()) return;
	
	system("tput reset");
	printf("\t\t\x1b[32;1mCONGRATULATIONS!\x1b[0m\n");
	puts("\nYou have finished the tutorial! \nYou are now ready to defend the homeland!");
	wait(3);
	
	fclose(pin);
}

//prints out chars from file to stdout until ~ or EOF char  
FILE *tutorial_lines(FILE *pin) {
	if(pin != NULL) {
		char c, prev = 0; 
		unsigned char alpha= 0;
		while((c = fgetc(pin))!=EOF && c != '~') {
			if(prev == '@' && (alpha&1)) {
				switch(c) {
					case '1': printf("\x1b[31;1m"); continue; break;
					case '2': printf("\x1b[32;1m"); continue; break;
					case '3': printf("\x1b[33;1m"); continue; break;
					case '4': printf("\x1b[34;1m"); continue; break;
					case '5': printf("\x1b[35;1m"); continue; break;
					case '6': printf("\x1b[36;1m"); continue; break;
					case '7': printf("\x1b[37;1m"); continue; break;
				}
			}
			if(c=='@') {
				printf((alpha&1) == 0 ? "\x1b[35;1m" : "\x1b[0m");
				alpha^=1;
				prev = c;
				continue;
			}
			putchar(c);
			prev = c;
		}
	}
	return pin;
}
void print_tutorial(BOARD (*board)[WIDTH]) {
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
				case 0 : if(board[i][j].state == 2) printf(BG_GREEN  "  ");
							else if(board[i][j].state == 3) printf(BG_CYAN  "  ");
							else printf((k&1) == 1 ? BG_YELLOW  "  " : BG_WHITE  "  "); 
							break;
				case 'K' : case 'B' : case 'N' :  case 'R' : case 'P': case 'k' :  case 'n' : case 'r' : case 'p' :
					if(board[i][j].state == 2)	printf(BG_GREEN);
					else if(board[i][j].state == 3) printf(BG_CYAN);
					else printf((k&1) == 1 ? BG_YELLOW : BG_WHITE);
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

unsigned char start_ai_animation(FILE *pin) {
	int p = 1;
	//char c;
	system("tput reset");
	pin = tutorial_lines(pin);
	if(!continue_msg()) return 0;
	
	BOARD board[HEIGHT][WIDTH];
	int i = (int)HEIGHT/2, j = (int)WIDTH/2;
	int loops = 5;
	do{
		init_board(board);
		
		board[i][j].type = 'p';
		board[i][j].player = 1;
		if(loops == 4) {
			board[i+1][j-1].type = 'N';
			board[i+1][j-1].player = 0;
		}
		if(loops == 3) {
			board[i+1][j+1].type = 'N';
			board[i+1][j+1].player = 0;
		}
		if(loops == 2) {
			board[i+1][j+1].type = board[i+1][j-1].type = 'N';
			board[i+1][j+1].player = board[i+1][j-1].player = 0;
		}
		if(loops == 1) {
			board[i+1][j].type = 'N';
			board[i+1][j].player = 0;
		}
		system("tput reset");
		update_pawn(board, i, j, p);
		print_tutorial(board);
		printf("\n\t\x1b[34;1mDANGER\x1b[0m\t\x1b[32;1mAVAILABLE\x1b[0m\n");
		wait(2);
		if(!ai_move(board, NULL)) {
			generate_wave1(board, 1);
		}
		print_matrix(board);
		wait(2);
	}while(--loops > 0);
	
	system("tput reset");
	pin = tutorial_lines(pin);
	if(!continue_msg()) return 0;
	
	loops = 4;
	int moves = 2;
	
	do {
		i = 0;
		j = WIDTH/2;
		init_board(board);
		board[i][j].type = 'b';
		board[i][j].player = 1;
		if(loops == 3) {
			board[i+1][j-1].type = 'N';
			board[i+1][j-1].player = 0;
		}
		if(loops == 2) {
			board[i+1][j+1].type = 'N';
			board[i+1][j+1].player = 0;
		}
		if(loops == 1) {
			board[i+1][j+1].type = board[i+1][j-1].type = 'N';
			board[i+1][j+1].player = board[i+1][j-1].player = 0;
		}
		moves = 2;
		do{
			find_bishop_ai(board, &i, &j);
			update_bishop(board, i, j);
			system("tput reset");
			print_tutorial(board);
			printf("\n\t\x1b[32;1mAVAILABLE\x1b[0m\n");
			wait(2);
			if(!ai_move(board, NULL)) {
				generate_wave1(board, 1);
			}
			print_matrix(board);
			wait(2);
			remove_states(board);
		}while(--moves > 0);
		print_matrix(board);
	} while(--loops > 0);
	
	system("tput reset");
	printf("Supported in-game commands:\n");
	pin = tutorial_lines(pin);
	if(!continue_msg()) return 0;
	
	system("tput reset");
	printf("Supported in-game commands:\n");
	pin = tutorial_lines(pin);
	if(!continue_msg()) return 0;
	
	return 1;
}
void update_pawn(BOARD (*board)[WIDTH], int i, int j, int p) {
	if(p) {
		if(i+1 < HEIGHT) {
			if(j+1 < WIDTH) board[i+1][j+1].state = 3;
			if(j-1 >= 0) board[i+1][j-1].state = 3;
			if(board[i+1][j].type == 0) board[i+1][j].state = 2;
		}
	}
	else {
		if(i-1 >= 0) {
			if(j+1 < WIDTH) board[i-1][j+1].state = 3;
			if(j-1 >= 0) board[i-1][j-1].state = 3;
			if(board[i-1][j].type == 0) board[i-1][j].state = 2;
		}
	}
}
void update_knight(BOARD (*board)[WIDTH], int i, int j) {
	if(i+1 < HEIGHT) {
		if(j+2<WIDTH) 
			if(board[i+1][j+2].player != board[i][j].player) 
				board[i+1][j+2].state = 2;
		if(j-2>=0) 
			if(board[i+1][j-2].player != board[i][j].player)
				board[i+1][j-2].state = 2;
	}
	if(i-1 >= 0) {
		if(j+2<WIDTH)
			if(board[i-1][j+2].player != board[i][j].player)
				board[i-1][j+2].state = 2;
		if(j-2>=0)
			if(board[i-1][j-2].player != board[i][j].player)
				board[i-1][j-2].state = 2;
	}
	if(i+2 < HEIGHT) {
		if(j+1<WIDTH)
			if(board[i+2][j+1].player != board[i][j].player)
				board[i+2][j+1].state = 2;
		if(j-1>=0) 
			if(board[i+2][j-1].player != board[i][j].player)
				board[i+2][j-1].state = 2;
	}
	if(i-2 >= 0) {
		if(j+1<WIDTH)
			if(board[i-2][j+1].player != board[i][j].player)
				board[i-2][j+1].state = 2;
		if(j-1>=0)
			if(board[i-2][j-1].player != board[i][j].player)
				board[i-2][j-1].state = 2;
	}		
}
void update_bishop(BOARD (*board)[WIDTH], int i, int j) {
	int k;
	if(!board[i][j].player) {
		for(k = 1; i - k >= 0; k++) {	
			if(j - k >= 0) {
				if(board[i-k][j-k].player == board[i][j].player) break;
				board[i-k][j-k].state = 2;
				if(board[i-k][j-k].type != 0) break;
			}
			else break;
		}
		for(k = 1; i - k >= 0; k++) {	
			if(j + k < WIDTH) {
				if(board[i-k][j+k].player == board[i][j].player) break;
				board[i-k][j+k].state = 2;
				if(board[i-k][j+k].type != 0) break;
			}
			else break;
		}
	}
	for(k = 1; i + k < HEIGHT; k++) {	
		if(j - k >= 0) {
			if(board[i+k][j-k].player == board[i][j].player) break;
			board[i+k][j-k].state = 2;
			if(board[i+k][j-k].type != 0) break;
		}
		else break;
	}
	for(k = 1; i + k < HEIGHT; k++) {	
		if(j + k < WIDTH) {
			if(board[i+k][j+k].player == board[i][j].player) break;
			board[i+k][j+k].state = 2;
			if(board[i+k][j+k].type != 0) break;
		}
		else break;
	}
}
void remove_states(BOARD (*board)[WIDTH]) {
	int i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j =0; j < WIDTH; j++) {
			board[i][j].state = 0;
		}
	}
}
void find_bishop_ai(BOARD (*board)[WIDTH], int *pi, int *pj) {
	int i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			if(board[i][j].type == 'b' && board[i][j].player == 1) {
				*pi = i;
				*pj = j;
				return;
			}
		}
	}
}
void hint_print(BOARD (*board)[WIDTH]) {
	char buffer[MAX_BUFFER];
	char *s;
	unsigned char i, j, x = 1;
	do{
		print_matrix(board);
		printf("note: type \x1b[31;1mx\x1b[0m to back out.\n");
		printf("Type in place (\x1b[33;1mcolumn\x1b[0m/\x1b[32;1mrow\x1b[0m) of interest: ");
		fgets(buffer, MAX_BUFFER, stdin);
		if(buffer[0] == 'x') return;
		
		s = &buffer[0];
		if(*s < 'a' || *s > 'h') continue;
		if(*++s < '1' || *s > '9') continue;
	
		s = &buffer[0];
		j = *s++ - 'a';
		i = *s++ - '0';
		if(*s >= '0' && *s <='2') i = HEIGHT - (i*10 + (*s - '0'));
		else i = HEIGHT - i;
		switch(board[i][j].type) {
			case 'N': update_knight(board, i, j); x ^= x; break;
			case 'b': case 'B': update_bishop(board, i, j); x^=x; break;
			case 'p': update_pawn(board, i, j, 1); x^=x; break;
			case 'K': puts("\x1b[35;1mYou can't move happy king. He generates 1 point each turn.\x1b[0m"); 
						 wait(2); print_matrix(board); return; break;
			case 'R': puts("\x1b[35;1mSuicide rook sprints forward and explodes upon contact" 
							" \nkilling both himself and target hit.\x1b[0m");
						wait(3); print_matrix(board); return; break;	
			case 0: puts("The field is empty."); wait(2); print_matrix(board); return; break;
			return; break;
		}
	}while(x);
	system("tput reset");
	print_tutorial(board);
	remove_states(board);
}