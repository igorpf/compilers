#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

FILE *yyout;


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

void astPrintSrc(AST* node) {
    if(!node)
        return;
    int i;

    switch(node->type) {
        case AST_SYMBOL:            
            fprintf(yyout, "%s", node->symbol->text);
            break;
        case AST_ADD: 
            fprintf(yyout, "(" );
            astPrintSrc(node->son0);
            fprintf(yyout, " + " );
            astPrintSrc(node->son1);
            fprintf(yyout, ")" );
            break;
        case AST_SUB: 
            fprintf(yyout, "(" );
            astPrintSrc(node->son0);
            fprintf(yyout, " - " );
            astPrintSrc(node->son1);
            fprintf(yyout, ")" );
            break;
        case AST_DIV: 
            fprintf(yyout, "(" );
            astPrintSrc(node->son0);
            fprintf(yyout, " / " );
            astPrintSrc(node->son1);
            fprintf(yyout, ")" );
            break;
        case AST_MULT: 
            fprintf(yyout, "(" );
            astPrintSrc(node->son0);
            fprintf(yyout, " * " );
            astPrintSrc(node->son1);
            fprintf(yyout, ")" );
            break;
        case AST_CMD: 
            astPrintSrc(node->son0);
            break;
        case AST_CMDL: 
            printf("\n");
            astPrintSrc(node->son0);
            if(node->son1)
                astPrintSrc(node->son1);
            break;
        case AST_VAR_DEF: 
            astPrintSrc(node->son0);
            printf(":");
            astPrintSrc(node->son1);
            astPrintSrc(node->son2);
            break;  
        case AST_VECTOR_DEF: 
            fprintf(yyout, "AST_VECTOR_DEF" );
            break;  
        case AST_INIT_VECTOR_DEF: 
            fprintf(yyout, "AST_INIT_VECTOR_DEF" );
            break;  
        case AST_VECTOR_PARAM_LIST: 
            fprintf(yyout, "AST_VECTOR_PARAM_LIST" );
            break;  
        case AST_PRINT_LIST: 
            fprintf(yyout, "AST_PRINT_LIST" );
            break;  
        case AST_PROGRAM: 
            printf("\n");
            astPrintSrc(node->son0);
            astPrintSrc(node->son1);
            // astPrintSrc(node->son2);
            // astPrintSrc(node->son3);
            break;  
        case AST_FUNC_DEF: 
            fprintf(yyout, "AST_FUNC_DEF" );
            break;  
        case AST_FUNC_DEF_PARAM_LIST: 
            fprintf(yyout, "AST_FUNC_DEF_PARAM_LIST" );
            break;  
        case AST_FUNC_DEF_PARAM_LIST_REST: 
            fprintf(yyout, "AST_FUNC_DEF_PARAM_LIST_REST" );
            break;  
        case AST_FUNC_CALL: 
            fprintf(yyout, "AST_FUNC_CALL" );
            break;  
        case AST_FUNC_CALL_PARAM_LIST: 
            fprintf(yyout, "AST_FUNC_CALL_PARAM_LIST" );
            break;  
        case AST_FUNC_CALL_PARAM_LIST_REST: 
            fprintf(yyout, "AST_FUNC_CALL_PARAM_LIST_REST" );
            break;  
        case AST_VAR_ASSIGNMENT: 
            fprintf(yyout, "AST_VAR_ASSIGNMENT" );
            break;  
        case AST_VECTOR_ASSIGNMENT: 
            fprintf(yyout, "AST_VECTOR_ASSIGNMENT" );
            break;  
        case AST_READ: 
            fprintf(yyout, "AST_READ" );
            break;  
        case AST_PRINT: 
            fprintf(yyout, "AST_PRINT" );
            break;  
        case AST_RETURN: 
            fprintf(yyout, "AST_RETURN" );
            break;  
        case AST_WHEN: 
            fprintf(yyout, "AST_WHEN" );
            break;  
        case AST_WHEN_ELSE: 
            fprintf(yyout, "AST_WHEN_ELSE" );
            break;  
        case AST_WHILE: 
            fprintf(yyout, "AST_WHILE" );
            break;  
        case AST_FOR: 
            fprintf(yyout, "AST_FOR" );
            break;  
        case AST_OP_GREATER: 
            fprintf(yyout, "AST_OP_GREATER" );
            break;  
        case AST_OP_LESS: 
            fprintf(yyout, "AST_OP_LESS" );
            break;  
        case AST_OP_LE: 
            fprintf(yyout, "AST_OP_LE" );
            break;  
        case AST_OP_GE: 
            fprintf(yyout, "AST_OP_GE" );
            break;  
        case AST_OP_EQ: 
            fprintf(yyout, "AST_OP_EQ" );
            break;  
        case AST_OP_NE: 
            fprintf(yyout, "AST_OP_NE" );
            break;  
        case AST_OP_AND: 
            fprintf(yyout, "AST_OP_AND" );
            break;  
        case AST_OP_OR: 
            fprintf(yyout, "AST_OP_OR" );
            break;      
        case AST_VECTOR_ACCESS: 
            fprintf(yyout, "AST_VECTOR_ACCESS" );
            break;      
        case AST_T_BYT: 
            fprintf(yyout, "byte" );
            break;  
        case AST_T_SHO: 
            fprintf(yyout, "short" );
            break;
        case AST_T_LON: 
            fprintf(yyout, "long" );
            break;  
        case AST_T_FLO: 
            fprintf(yyout, "float" );
            break;
        case AST_T_DOU: 
            fprintf(yyout, "double" );
            break;   
    }

    fprintf(yyout, " ");

    // astPrintSrc(node->son0);
    // astPrintSrc(node->son1);
    // astPrintSrc(node->son2);
    // astPrintSrc(node->son3);
}