#include "astree.h"
#include <stdio.h>
#include <stdlib.h>
AST* astCreate(int type, HASH_NODE* symbol, AST* *sons) {
	AST *newNode = calloc(sizeof(AST));

	newNode->type = type;
	newNode->symbol = symbol;
	newNode->sons = sons;
	return newNode;
}

void astPrint(AST* node){
	if(!node)
		return;
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
		astPrint(node->sons[i]);
}