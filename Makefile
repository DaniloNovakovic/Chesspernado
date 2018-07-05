all:
	gcc -Wall chesspernado.c ch_board.c ch_cmd.c init_setup.c waves.c ai_movement.c list.c special_moves.c menu.c tutorial.c game_simulation.c mini_stack.c -o chesspernado -std=c99

