#include "mini_stack.h"
void init_mini_stack(MINI_STACK *pstack){
	if(pstack!=NULL) {
		pstack->parray = NULL;
		pstack->top = -1;
		pstack->capacity = 0;
	}
}
void resize_mini_stack(MINI_STACK *pstack){
	if(pstack == NULL) return;
	if(pstack->capacity == 0) pstack->capacity = 1;
	pstack->parray = realloc(pstack->parray, (pstack->capacity*=2)*sizeof(unsigned char));
	
	if(pstack->parray == NULL){
		//puts("ERROR: Out of memory!");
		exit(EXIT_FAILURE);
	}
}

void destroy_mini_stack(MINI_STACK *pstack){
	if(pstack != NULL) {
		if(pstack->parray != NULL) free(pstack->parray);
		init_mini_stack(pstack);
	}
}

void mini_push(MINI_STACK *pstack, unsigned char number){
	if(pstack != NULL) {
		if(++(pstack->top) == pstack->capacity) resize_mini_stack(pstack);
		pstack->parray[pstack->top] = number;
	}
}

char mini_pop(MINI_STACK *pstack){
	if(pstack == NULL) return -1;
	if(pstack->top >= 0) {
		return pstack->parray[pstack->top--];
	}
	else return -1;
}
