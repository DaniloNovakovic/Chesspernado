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
#ifndef __LIST__
#define __LIST__
typedef struct move_st {
	BOARD board[HEIGHT][WIDTH];
	int points;
} TYPE;
typedef struct node_st {
	TYPE inf;
	struct node_st *pnext;
	struct node_st *pprev;
} NODE;

NODE *make_node(TYPE);
void list_push(NODE **, TYPE);
void delete_fnodes(NODE **);
NODE *find_start(NODE *);
void delete_full_list(NODE **);
#endif