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
#include "waves.h"
int board_setup(BOARD (*board)[WIDTH]){
	unsigned short bishops;
	unsigned short knights;
	char buffer[MAX_BUFFER];
	char *p;
	char option = 'n';
	int i, j;
	do{
		bishops = MAX_BISHOPS;
		knights = MAX_KNIGHTS;
		do {
			print_matrix(board);
			printf("\nYou have \x1b[35;1m%hu\x1b[0m bishops and \x1b[35;1m%hu\x1b[0m knights left.\n", bishops, knights);
			printf("Place them anywhere from 1st to 5th row. \x1b[31;1mMAX 5TH ROW!\x1b[0m" 
			"\n(ex. \x1b[33;1mN\x1b[32;1mc\x1b[31;1m3\x1b[0m (\x1b[33;1mtype/\x1b[32;1mcolumn/\x1b[31;1mrow\x1b[0m)) ");
			printf("(or type \x1b[1m/random\x1b[0m)\n");
			printf("\x1b[32;1mType in where to place them\x1b[0m: ");
			fgets(buffer, MAX_BUFFER, stdin);
			if(!strncmp(buffer, "/end", 4) || !strncmp(buffer, "/exit",5))  {
				exit(EXIT_SUCCESS);
			}
			if(!strncmp(buffer, "/back", 5)) {
				return 1;
			}
			if(!strncmp(buffer, "/random", 7)) {
				srand(time(NULL));
				while(bishops > 0 || knights > 0) {
					i = random_number(7, 11);
					j = random_number(0, 7);
					if(board[i][j].type == 0) {
						if(knights>0) {
							knights--;
							board[i][j].type = 'N';
							board[i][j].player = 0;
						}
						else {
							bishops--;
							board[i][j].type = 'B';
							board[i][j].player = 0;
						}
					}
				}
				continue;
			}
			if(!strncmp(buffer, "/re", 3)) {
				init_board(board);
				bishops = 2;
				knights = 3;
				continue;
			}
			p = &buffer[0];
			if(*p != 'N' && *p != 'B') {
				printf("\x1b[31;1merror:\x1b[0m unrecognized char %c\nusage ex. " 
				"\x1b[33;1mN\x1b[32;1mc\x1b[31;1m3\x1b[0m (\x1b[33;1mtype/\x1b[32;1mcolumn/\x1b[31;1mrow\x1b[0m)\n", *p);
				wait(3);
				continue;
			}
			if(*++p < 'a' || *p > 'h') {
				printf("\x1b[31;1merror:\x1b[0m unrecognized char %c\nusage ex. " 
				"\x1b[33;1mN\x1b[32;1mc\x1b[31;1m3\x1b[0m (\x1b[33;1mtype/\x1b[32;1mcolumn/\x1b[31;1mrow\x1b[0m)\n", *p);
				wait(3);
				continue;
			}
			if(*++p < '1' || *p > '5') {
				if(*p <= '9') printf("\x1b[31;1merror\x1b[0m: MAX 5th ROW!\n");
				else 
				printf("\x1b[31;1merror:\x1b[0m unrecognized char %c\nusage ex. " 
				"\x1b[33;1mN\x1b[32;1mc\x1b[31;1m3\x1b[0m (\x1b[33;1mtype/\x1b[32;1mcolumn/\x1b[31;1mrow\x1b[0m)\n", *p);
				wait(3);
				continue;
			}
			i = HEIGHT - (*p - '0');
			j = *--p - 'a';
			if(board[i][j].player == 0) {
				puts("error: that position is already taken. Please try again.");
				wait(3);
				continue;
			}
			switch(*--p) {
				case 'N' : if(knights == 0) {
									puts("\x1b[31;1merror:\x1b[0m you have no more knights left.");
									wait(3);
									continue;
								}
								board[i][j].type = 'N'; 
								board[i][j].player = 0;
								knights--;
				break;
				case 'B' :	if(bishops == 0) {
									puts("\x1b[31;1merror:\x1b[0m you have no more bishops left.");
									wait(3);
									continue;
								}
								board[i][j].type = 'B'; 
								board[i][j].player = 0;
								bishops--;
				break;
			}
		}while(bishops != 0 || knights != 0);
		print_matrix(board);
		do{
			printf("Type \x1b[32;1my\x1b[0m to confirm the setup, "
					"or \x1b[31;1mn\x1b[0m to set it up again: ");
			scanf(" %c", &option);
			getchar();
		}while(option != 'y' && option != 'Y' && option != 'N' && option != 'n');
		if(option == 'n' || option == 'N') {
				init_board(board);
		}
	}while(option == 'n' || option == 'N');
	return 0;
}
//waits n seconds
void wait(int n) {
	time_t start, end;
	double elapsed = 0;
	time(&start);
	do{
		time(&end);	
		elapsed = difftime(end, start);
	}while(elapsed < n);
}
