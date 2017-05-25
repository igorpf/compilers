#include "ast.h"



void semanticSetDeclarations(AST* node) {
	int i;
	if(!node)
		return;
	switch(node->type) {
		case AST_VAR_DEF:
			if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
				fprintf(stderr, "Semantic error, variable %s already defined\n",node->symbol->text);	
				exit(4);
			}
			node->symbol->type = SYMBOL_VAR;
			if(node->sons[0]->type == AST_T_BYT)
				 node->symbol->dataType = DATATYPE_BYTE;
		default:
			break;
	}
	for(i=0; i < MAX_SONS; i++) {
		semanticSetDeclarations(node->sons[i]);
	}
}