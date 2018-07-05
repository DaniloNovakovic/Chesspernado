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
#include "list.h"
#include "special_moves.h"
#include "waves.h"
int undo(BOARD (*board)[WIDTH], NODE **pcurr, int *points) {
	if(*pcurr != NULL) {
		boardcpy(board, (*pcurr)->inf.board);
		*points = (*pcurr)->inf.points;
		*pcurr = (*pcurr)->pprev;
		return 1;
	}
	return 0; // returns 0 upon failure 
}
int revive(BOARD (*board)[WIDTH], int *points) {
	int bishops, knights;
	char c;
	if(*points < REVIVE_POINTS) {
		printf("error: you need \x1b[36;1m%d\x1b[0m points for revive!\n", REVIVE_POINTS);
		wait(2);
		return 0;
	}
	if(is_full(board)) {
		printf("error: you can't revive because the board is full");
		wait(2);
		return 0;
	}
	count_player(board, &bishops, &knights);
	knights = MAX_KNIGHTS - knights;
	bishops = MAX_BISHOPS - bishops;
	printf("\x1b[31;1mDead\x1b[0m: knights (\x1b[35;1mN\x1b[0m) = \x1b[36;1m %d \x1b[0m, "
	"bishops (\x1b[35;1mB\x1b[0m) =\x1b[36;1m %d\x1b[0m\n", knights, bishops);
	if(bishops > 0 || knights > 0) {
		unsigned char loop = 0;
		do{
			printf("\x1b[33;1mNote\x1b[0m: type \x1b[31;1m'x'\x1b[0m to back out in any moment.\n");
			printf("Which \x1b[35;1mpiece\x1b[0m do you want to revive? : ");
			scanf(" %c", &c);
			getchar();	// eats newline char
			switch(c) {
				case 'N': if(knights > 0) loop++;
							else {
								puts("error: you have no dead knights.");
								continue;
							}
				break;
				case 'B': if(bishops > 0) loop++;
							else {
								puts("error: you have no dead bishops.");
								continue;
							}
				break;	
				case 'x': case 'X': return 1; break;
			} 
			
		}while(!loop);
		
		char buffer[MAX_BUFFER];
		char *p;
		loop = 0;
		int i, j;
		
		print_matrix(board);
		
		do{
			printf("Type in where to place \x1b[35;1m%c\x1b[0m (column/row) (\x1b[31;1m MAX 5th ROW!\x1b[0m): ", c);
			fgets(buffer, MAX_BUFFER, stdin);
			if(!strncmp(buffer, "/end", 4) || !strncmp(buffer, "/exit",5))  {
				exit(EXIT_SUCCESS);
			}
			if(buffer[0] == 'x' || buffer[0] == 'X') return 1;
			p= &buffer[0];
			if(*p < 'a' || *p > 'h') {
				printf("\x1b[31;1merror:\x1b[0m unrecognized char %c\nusage ex. \x1b[32;1mc\x1b[33;1m3\x1b[0m"
				"(\x1b[32;1mcolumn/\x1b[33;1mrow\x1b[0m)\n", *p);
				continue;
			}
			if(*++p < '1' || *p > '5') {
				if(*p <= '9') printf("\x1b[31;1merror\x1b[0m: MAX 5th ROW!\n");
				else 
				printf("\x1b[31;1merror:\x1b[0m unrecognized char %c\nusage ex. " 
				"\x1b[32;1mc\x1b[31;1m3\x1b[0m (\x1b[32;1mcolumn/\x1b[31;1mrow\x1b[0m)\n", *p);
				continue;
			}
			i = HEIGHT - (*p - '0');
			j = *--p - 'a';
			if(board[i][j].type != 0) {
				puts("error: that position is already taken. Please try again.");
				continue;
			}
			switch(c) {
				case 'N' : 	board[i][j].type = 'N'; 
								board[i][j].player = 0;
								*points-=REVIVE_POINTS;
								loop++;
				break;
				case 'B' :	board[i][j].type = 'B'; 
								board[i][j].player = 0;
								*points-=REVIVE_POINTS;
								loop++;
				break;
			}
		}while(!loop);
		return 1;
	}
	printf("error: there is no piece to revive (everybody is alive)\n");
	return 0;
}

//returns 0 if player didn't buy anything and 1 if he did
int buy(BOARD (*board)[WIDTH], int *points) {
	char c;
	if(*points < MIN_POINTS) {
		printf("error: you need \x1b[36;1m%d\x1b[0m points to buy!\n", MIN_POINTS);
		wait(2);
		return 0;
	}
	if(is_full(board)) {
		printf("error: you can't buy anything because the board is full");
		wait(2);
		return 0;
	}
	int i, j;
	unsigned char loop = 0, placed = 0;
	do{
		system("tput reset");
		puts("\x1b[35;1mSTORE\x1b[0m\n");
		printf("Items for sale:\n");
		printf("\t1. Knight (\x1b[35;1mN\x1b[0m) --- price: %d\n", BUY_POINTS);
		printf("\t2. Bishop (\x1b[35;1mB\x1b[0m) --- price: %d\n", BUY_POINTS);
		printf("\t3. Suicide Rook (\x1b[35;1mR\x1b[0m) --- price: %d\n", BUY_SUICIDE_ROOK);
		printf("\t4. Happy king (\x1b[35;1mK\x1b[0m) --- price: %d\n", BUY_HAPPY_KING);
		puts("\tx - Nothing");
		do{
			printf("\nWhich item from the list would you like to buy? : ");
			scanf(" %c", &c);
			getchar();	// eats newline char
			
			switch(c) {
				case '1': if(*points < BUY_POINTS) {
								printf("Not enough points.\n");
								continue;
							}
							c = 'N'; 
							loop++; 
				break; 
				case '2': if(*points < BUY_POINTS) {
								printf("Not enough points.\n");
								continue;
							} 
							c = 'B'; 	
							loop++;	
				break;
				case '3':  if(*points < BUY_SUICIDE_ROOK) {
									printf("Not enough points.\n");
									continue;
								} 
							c = 'R'; loop++; break;
				case '4': placed = 30;
							   do{
								   i = random_number((HEIGHT/2), HEIGHT-2);
								   j = random_number(0, WIDTH-1);
								   if(board[i][j].type == 0) {
									   board[i][j].type = 'K';
									   board[i][j].player = 0;
									   *points-=BUY_HAPPY_KING;
									   return 1;
								   }
							   }while(--placed > 0);
							   printf("error: Happy king couldn't be placed anyhwere.");
							   return 0;
				break;
				case 'x': case 'X': return 0; break;
			} 
		}while(!loop);
	}while(!loop);
	
	char buffer[MAX_BUFFER];
	char *p;
	loop = 0;
	
	print_matrix(board);
	
	do{
		printf("Type in where to place \x1b[35;1m%c\x1b[0m (column/row): ", c);
		fgets(buffer, MAX_BUFFER, stdin);
		if(!strncmp(buffer, "/end", 4) || !strncmp(buffer, "/exit",5))  {
			exit(EXIT_SUCCESS);
		}
		p= &buffer[0];
		if(*p < 'a' || *p > 'h') {
			printf("\x1b[31;1merror:\x1b[0m unrecognized char %c\nusage ex. \x1b[32;1mc\x1b[33;1m3\x1b[0m"
				"(\x1b[32;1mcolumn/\x1b[33;1mrow\x1b[0m)\n", *p);
			continue;
		}
		if(*++p < '1' || *p > '5') {
			if(*p <= '9') printf("\x1b[31;1merror\x1b[0m: MAX 5th ROW!\n");
				else 
				printf("\x1b[31;1merror:\x1b[0m unrecognized char %c\nusage ex. " 
				"\x1b[32;1mc\x1b[31;1m3\x1b[0m (\x1b[32;1mcolumn/\x1b[31;1mrow\x1b[0m)\n", *p);
			continue;
		}
		i = HEIGHT - (*p - '0');
		j = *--p - 'a';
		if(board[i][j].type != 0) {
			puts("error: that position is already taken. Please try again.");
			continue;
		}
		switch(c) {
			case 'N' : case 'B':	board[i][j].type = c; 
										board[i][j].player = 0;
										*points-=BUY_POINTS;
										loop++;
			break;
			case 'R': board[i][j].type = c;
						 board[i][j].player = 0;
						*points-=BUY_SUICIDE_ROOK;
						loop++;
			break;
		}
	}while(!loop);
	return 1;
	
}
void count_player(BOARD (*board)[WIDTH], int *bishops, int *knights) {
	int L = 0, S = 0;
	int i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			if(!board[i][j].player) {
				switch(board[i][j].type) {
					case 'B': L++; break;
					case 'N': S++; break;
				}
			}
		}
	}
	*bishops = L;
	*knights = S;
}