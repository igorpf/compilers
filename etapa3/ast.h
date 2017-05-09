#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>

#include "hash.h"

#define AST_SYMBOL 0
#define AST_ADD 1

#define MAX_SONS 4

typedef struct ast {
	int type;
	HASH_NODE* symbol;
	struct ast *sons[MAX_SONS];
} AST;

AST* astCreate(int type, AST* *sons);
void astPrint(void);

#endif