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
int ai_move(BOARD (*)[WIDTH], int *);
int ai_movpawn(BOARD (*)[WIDTH], int , int);
void mov_figure(BOARD (*)[WIDTH], int , int , int, int);
int ai_movbishop(BOARD (*)[WIDTH], int , int );
void suicide_rook(BOARD (*)[WIDTH], int);