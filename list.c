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

NODE *make_node(TYPE inf) {
	NODE *pnew = malloc(sizeof(NODE));
	if(pnew == NULL){
		puts("ERROR: Out of RAM!");
		exit(EXIT_FAILURE);
	}
	pnew->pnext = pnew->pprev = NULL;
	/*boardcpy(pnew->inf.board, inf.board);
	pnew->inf.points = inf.points;*/ 
	pnew->inf = inf; //i'm unsure if this is shallow copy or not.
	return pnew;
}
/*This is some kind of mixture of list and stack which should work
	good for my /undo command*/
void list_push(NODE **pcurr, TYPE inf) {
	NODE *pnew = make_node(inf);
	if(*pcurr == NULL) {
		*pcurr = pnew;
		return;
	}
	else if((*pcurr)->pnext == NULL) {
		(*pcurr)->pnext = pnew;
		pnew->pprev = *pcurr;
	}
	else {
		(*pcurr)->pnext->inf = inf; //warning: could be shallow copy care!
		free(pnew);
	}
	*pcurr = (*pcurr)->pnext;
	delete_fnodes(pcurr);
}
//deletes all nodes after pcurr node (hence the name delete forward nodes)
void delete_fnodes(NODE **pcurr) {
	if(*pcurr == NULL) return;
	if((*pcurr)->pnext != NULL) {
		NODE *ptemp = (*pcurr)->pnext;
		NODE *pnext;
		(*pcurr)->pnext = NULL;
		while(ptemp != NULL) {
			pnext = ptemp->pnext;
			ptemp->pnext = ptemp->pprev = NULL;
	
			free(ptemp);
			ptemp = pnext;
		}
	}
}
NODE *find_start(NODE *pcurr) {
	if(pcurr!=NULL) {
		while(pcurr->pprev != NULL)
			pcurr = pcurr->pprev;
	}
	return pcurr;
}
void delete_full_list(NODE **pcurr) {
	if(*pcurr != NULL) {
		NODE *pstart = find_start(*pcurr);
		*pcurr = NULL;
		if(pstart != NULL) {
			delete_fnodes(&pstart);
			free(pstart);
		}
	}
}
