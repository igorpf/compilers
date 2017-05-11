#include "astree.h"
#include <stdio.h>
#include <stdlib.h>
AST* astCreate(int type, HASH_NODE* symbol, AST* son0, AST* son1, AST* son2, AST* son3) {
	AST *newNode = calloc(sizeof(AST));

	newNode->type = type;
	newNode->symbol = symbol;
	newNode->sons[0] = son0;
	newNode->sons[1] = son1;
	newNode->sons[2] = son2;
	newNode->sons[3] = son3;
	return newNode;
}

void astPrint(int level, AST* node){
	if(!node)
		return;
	int i;
	for(i=0;i<level;i++)
		printf("  ");
	fprintf(stderr, "AST(");
	switch(node->type) {
		case AST_SYMBOL:
			break;
			fprintf(stderr, "AST_SYMBOL" );
		case AST_ADD: 
			fprintf(stderr, "AST_ADD" );
			break;
	}
	if(node->symbol)
		fprintf(stderr, ",%s)", node->symbol->text);
	else
		fprintf(stderr, ",)");
	int i;
	for(i=0; i < MAX_SONS; i++)
		astPrint(level+1,node->sons[i]);
}