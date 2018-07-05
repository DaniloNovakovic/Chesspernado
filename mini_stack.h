#include <stdlib.h>
#ifndef __MINI_STACK__
#define __MINI_STACK__
typedef struct mini_stack_st {
	unsigned char *parray;
	int top;
	unsigned capacity;
} MINI_STACK;
void init_mini_stack(MINI_STACK *);
void resize_mini_stack(MINI_STACK *pstack);
void destroy_mini_stack(MINI_STACK *pstack);
void mini_push(MINI_STACK *pstack, unsigned char number);
char mini_pop(MINI_STACK *pstack);
#endif
