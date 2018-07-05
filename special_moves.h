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
#include "list.h"
#define REVIVE_POINTS 60
#define BUY_POINTS 90
#define BUY_SUICIDE_ROOK 18
#define MIN_POINTS 6
#define BUY_HAPPY_KING 6
int undo(BOARD (*)[WIDTH], NODE **, int *);
int revive(BOARD (*)[WIDTH], int *);
void count_player(BOARD (*)[WIDTH], int *, int *);
int buy(BOARD (*)[WIDTH], int *);