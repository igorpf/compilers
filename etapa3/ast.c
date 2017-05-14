#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

AST* astCreate(int type, HASH_NODE* symbol, AST* son0, AST* son1, AST* son2, AST* son3) {
	AST *newNode = calloc(1, sizeof(AST));

	newNode->type = type;
	newNode->symbol = symbol;
	newNode->son0 = son0;
	newNode->son1 = son1;
	newNode->son2 = son2;
	newNode->son3 = son3;
	return newNode;
}

void astPrint(int level, AST* node){
	if(!node)
		return;
	int i;

	for(i=0;i<level;i++)
		fprintf(stderr, "  ");
	fprintf(stderr, "AST(");
	switch(node->type) {
		case AST_SYMBOL:			
			fprintf(stderr, "AST_SYMBOL" );
			break;
		case AST_ADD: 
			fprintf(stderr, "AST_ADD" );
			break;
		case AST_SUB: 
			fprintf(stderr, "AST_SUB" );
			break;
		case AST_DIV: 
			fprintf(stderr, "AST_DIV" );
			break;
		case AST_MULT: 
			fprintf(stderr, "AST_MULT" );
			break;
		case AST_CMD: 
			fprintf(stderr, "AST_CMD" );
			break;
		case AST_CMDL: 
			fprintf(stderr, "AST_CMDL" );
			break;
		case AST_VAR_DEF: 
			fprintf(stderr, "AST_VAR_DEF" );
			break;	
		case AST_VECTOR_DEF: 
			fprintf(stderr, "AST_VECTOR_DEF" );
			break;	
		case AST_INIT_VECTOR_DEF: 
			fprintf(stderr, "AST_INIT_VECTOR_DEF" );
			break;	
		case AST_VECTOR_PARAM_LIST: 
			fprintf(stderr, "AST_VECTOR_PARAM_LIST" );
			break;	
		case AST_PRINT_LIST: 
			fprintf(stderr, "AST_PRINT_LIST" );
			break;	
		case AST_PROGRAM: 
			fprintf(stderr, "AST_PROGRAM" );
			break;	
		case AST_FUNC_DEF: 
			fprintf(stderr, "AST_FUNC_DEF" );
			break;	
		case AST_FUNC_DEF_PARAM_LIST: 
			fprintf(stderr, "AST_FUNC_DEF_PARAM_LIST" );
			break;	
		case AST_FUNC_DEF_PARAM_LIST_REST: 
			fprintf(stderr, "AST_FUNC_DEF_PARAM_LIST_REST" );
			break;	
		case AST_FUNC_CALL: 
			fprintf(stderr, "AST_FUNC_CALL" );
			break;	
		case AST_FUNC_CALL_PARAM_LIST: 
			fprintf(stderr, "AST_FUNC_CALL_PARAM_LIST" );
			break;	
		case AST_FUNC_CALL_PARAM_LIST_REST: 
			fprintf(stderr, "AST_FUNC_CALL_PARAM_LIST_REST" );
			break;	
		case AST_VAR_ASSIGNMENT: 
			fprintf(stderr, "AST_VAR_ASSIGNMENT" );
			break;	
		case AST_VECTOR_ASSIGNMENT: 
			fprintf(stderr, "AST_VECTOR_ASSIGNMENT" );
			break;	
		case AST_READ: 
			fprintf(stderr, "AST_READ" );
			break;	
		case AST_PRINT: 
			fprintf(stderr, "AST_PRINT" );
			break;	
		case AST_RETURN: 
			fprintf(stderr, "AST_RETURN" );
			break;	
		case AST_WHEN: 
			fprintf(stderr, "AST_WHEN" );
			break;	
		case AST_WHEN_ELSE: 
			fprintf(stderr, "AST_WHEN_ELSE" );
			break;	
		case AST_WHILE: 
			fprintf(stderr, "AST_WHILE" );
			break;	
		case AST_FOR: 
			fprintf(stderr, "AST_FOR" );
			break;	
		case AST_OP_GREATER: 
			fprintf(stderr, "AST_OP_GREATER" );
			break;	
		case AST_OP_LESS: 
			fprintf(stderr, "AST_OP_LESS" );
			break;	
		case AST_OP_LE: 
			fprintf(stderr, "AST_OP_LE" );
			break;	
		case AST_OP_GE: 
			fprintf(stderr, "AST_OP_GE" );
			break;	
		case AST_OP_EQ: 
			fprintf(stderr, "AST_OP_EQ" );
			break;	
		case AST_OP_NE: 
			fprintf(stderr, "AST_OP_NE" );
			break;	
		case AST_OP_AND: 
			fprintf(stderr, "AST_OP_AND" );
			break;	
		case AST_OP_OR: 
			fprintf(stderr, "AST_OP_OR" );
			break;		
		case AST_VECTOR_ACCESS: 
			fprintf(stderr, "AST_VECTOR_ACCESS" );
			break;		
	}
	if(node->symbol)
		fprintf(stderr, ",%s)", node->symbol->text);
	else
		fprintf(stderr, ")");

	fprintf(stderr, "\n");

	astPrint(level+1,node->son0);
	astPrint(level+1,node->son1);
	astPrint(level+1,node->son2);
	astPrint(level+1,node->son3);
}
