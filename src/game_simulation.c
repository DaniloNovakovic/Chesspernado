#include "tutorial.h"
#include "ai_movement.h"
#include "waves.h"
#include "special_moves.h"
#include "list.h"
#include "menu.h"

unsigned char start_game_simulation(void) {
	BOARD board[HEIGHT][WIDTH];
	char c;
	int points;
	unsigned char attempt;
	unsigned char temp = 0;
	char buffer[MAX_BUFFER];
	//TODO: Buy Happy king
	do{
		init_board(board);
		points = BUY_HAPPY_KING;
		system("tput reset");
		print_matrix(board);
		printf("\x1b[35;1mScore\x1b[0m: %d\n\n", points);
		printf("\x1b[37;1;4mTASK\x1b[0m: Buy happy king (\x1b[1mK\x1b[0m) from shop.\n");
		printf("hint: /buy command\n");
		if(get_input_tuto(board, &points))
			return 0;
	}while(!is_happy_king_alive(board));
	print_matrix(board);
	printf("\x1b[33;1mGOOD JOB! Happy King will now generate 1 point each turn.\x1b[0m\n");
	puts("Let's change scenario now...");
	if(!continue_msg()) return 0;
	
	//TODO: Save Happy King in 1 move.
	attempt = 0;
	do{
		if(attempt++) {
			printf("\x1b[31;1mFAILURE!\x1b[0m Happy king has met the maker. :( \nTry again...\n");
			wait(3);
		}
		init_board(board);
		board[HEIGHT/2-1][WIDTH/2+1].type = board[HEIGHT/2-1][WIDTH/2-1].type = 'p';
		board[HEIGHT/2-1][WIDTH/2+1].player = board[HEIGHT/2-1][WIDTH/2-1].player = 1;
		board[HEIGHT/2][WIDTH/2].type = 'K';
		board[HEIGHT/2][WIDTH/2].player = 0;
		points = BUY_SUICIDE_ROOK<<1;
		c = 3;
		do{
			system("tput reset");
			print_matrix(board);
			printf("\x1b[35;1mScore\x1b[0m: %d\n\n", points);		
			printf("\x1b[37;1;4mTASK\x1b[0m: SAVE KING!\n");
			if(points != 0) {
				printf("hint1: use suicide rooks (you can't move happy king)\n");
				printf("hint2: use /buy & /skip commands (/buy won't end move)\n");
			}else printf("hint: use /skip command to finish move\n");
			if((temp = get_input_tuto(board, &points)) == 1)
				return 0;
			if(temp == 2)
				break;
			if(board[HEIGHT/2][WIDTH/2].type != 'K')
				break;
		}while(--c > 0);
		
		suicide_rook(board, 0);
		ai_move(board, &points);
		print_matrix(board);
	}while(board[HEIGHT/2][WIDTH/2].type != 'K');
	
	printf("\x1b[33;1mCONGRATULATIONS!\x1b[0m\n"
	"The word has spread across the kingdom of a noble warrior who saved the king!\n");
	if(!continue_msg()) return 0;
	
	//TODO: Show that new pawns will be generated if enemy AI has no legal move
	init_board(board);
	board[HEIGHT/2][WIDTH/2].type = 'p';
	board[HEIGHT/2][WIDTH/2].player = 1;
	board[HEIGHT/2+1][WIDTH/2].type = 'N';
	board[HEIGHT/2+1][WIDTH/2].player = 0;
	points ^= points;
	print_matrix(board);
	printf("\x1b[35;1mScore\x1b[0m: %d\n\n", points);	
	printf("AI has no legal move right now, meaning that\x1b[31;1m new pawns will be generated\x1b[0m\n"
	 "next move, unless you do something about it...\n");
	 printf("\x1b[37;1;4mTASK\x1b[0m: Do whatever you want.\n");
	if(get_input_tuto(board, &points) == 1) return 0;
	
	suicide_rook(board, 0);	
	
	if(!ai_move(board, &points)) 
		generate_wave1(board, 3);
	
	print_matrix(board);
	
	if(!continue_msg()) return 0;
	
	//TODO: /revive command demonstration
	init_board(board);
	board[2][4].type = board[4][1].type = board[3][7].type = board[7][3].type = 'p';
	board[2][4].player = board[4][1].player = board[3][7].player = board[7][3].player = 1;
	board[1][3].type = 'b';
	board[1][3].player = 1;
	board[5][2].type = board[4][7].type = board[9][4].type = 'N';
	board[6][6].type = board[10][1].type = 'B';
	board[5][2].player = board[4][7].player = board[9][4].player = board[6][6].player = board[10][1].player = 0;
	print_matrix(board);
	puts("AIs turn...");
	wait(2);
	ai_move(board, &points);
	
	points = REVIVE_POINTS;
	print_matrix(board);
	printf("\x1b[35;1mScore\x1b[0m: %d\n\n", points);
	puts("Oops looks like one of your pieces died. ");
	puts("Good thing you have enough points to revive it.");
	printf("\x1b[37;1;4mTASK\x1b[0m: Use \"/revive\" to revive fallen piece.\n");
	do {
		printf("Command: ");
		fgets(buffer, MAX_BUFFER, stdin);
		if(!strncmp(buffer, "/back", 5)) return 0;
		else if(!strncmp(buffer, "/revive", 7)) {
			revive(board, &points);
			print_matrix(board);
			printf("\x1b[35;1mScore\x1b[0m: %d\n\n", points);
		} 
	}while(strncmp(buffer, "/revive", 7));
	if(!continue_msg()) return 0;
	
	return 1;
}
unsigned char is_happy_king_alive(BOARD (*board)[WIDTH]) {
	unsigned char i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			if(board[i][j].type == 'K') 
				return 1;
		}
	}
	return 0;
}
unsigned char continue_msg(void) {
	char c;
	do{
		printf("\nContinue (Y/n) ? ");
		scanf("%c", &c);
		if(c != '\n') getchar();
	}while(c!='y' && c!='Y' && c!='n' && c!='N' && c!='\n'); 
	if(c == 'n' || c == 'N') return 0;
	return 1;
}
//returns 1 if user wants to go back to main menu
int get_input_tuto(BOARD (*board)[WIDTH], int *points) {
	char buffer[MAX_BUFFER];
	int nb_fails = 0;
	int i, i1, j1, i2, j2;
	
	printf("note: type \x1b[37;1m/back\x1b[0m to go back to main menu at any time.\n");
	do {
				i = 0;
				printf(BLUE "Command: " CL_RESET);
				fgets(buffer, MAX_BUFFER, stdin);
				if(buffer[0] == '/') {
					if(!strncmp(buffer, "/end", 4) || !strncmp(buffer, "/exit",5))  {
						exit(EXIT_SUCCESS);
					}
					else if(!strncmp(buffer, "/back", 5))
						return 1;
					else if(!strncmp(buffer, "/help", 5)) {
						chesspernado_rules();
						system("tput reset");
						print_tutorial(board);
						printf("\x1b[35;1mScore\x1b[0m: %d\n\n", *points);
						continue;
					}
					if(points != NULL) {	
						/*if(!strncmp(buffer, "/revive", 7)) {
							if(!revive(board, points)) {
								puts("error: revive unavailable");
							}
							else {
								return 0;
							}
						}*/
						 if(!strncmp(buffer, "/buy", 4)) {
							buy(board, points);
							return 0;
						}
						else if(!strncmp(buffer, "/skip", 5)) {
							return 2;
						}
					}
				}
				i = syntax_check(buffer);
				if(!i) {
					if(buffer[0] == 'K') puts("error: \x1b[31;1mYOU CAN'T MOVE HAPPY KING!\x1b[0m");
					else {
						printf("Notation: Piece \x1b[31;1mtype\x1b[0m / \x1b[35;1mfrom\x1b[0m / \x1b[32;1mto\x1b[0m" 
						" - where both '\x1b[35;1mfrom\x1b[0m' and '\x1b[32;1mto\x1b[0m' are defined \nas column/row. ");
						printf("example: \x1b[31;1mN\x1b[35;1me6\x1b[32;1mc5\x1b[0m \x1b[33;1m*CASE SENSITIVE!*\x1b[0m\n");
					}
					if(++nb_fails > 1) {
						wait(3);
						system("tput reset");
						print_tutorial(board);
					}
					continue;
				}
				i = command_check(board, buffer);
			}while(!i);
			
			char *s = &buffer[1];
			j1 = *s++ - 'a';
			i1 = *s++ - '0';
			if(*s >= '0' && *s <='2') i1 = HEIGHT - (i1*10 + (*s++ - '0'));
			else i1 = HEIGHT - i1;
			
			j2 = *s++ - 'a';
			i2 = *s++ - '0';
			
			if(*s >= '0' && *s <='2') 	i2 = HEIGHT - (i2*10 + (*s++ - '0'));
			else i2 = HEIGHT - i2;
	
			mov_figure(board, i1, j1, i2, j2);
			
			return 0;
}
