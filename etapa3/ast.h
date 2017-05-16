#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>

#include "hash.h"

#define AST_SYMBOL 0
#define AST_ADD 1
#define AST_SUB 2
#define AST_DIV 3
#define AST_MULT 4
#define AST_CMD 5
#define AST_CMDL 6
#define AST_VAR_DEF 7
#define AST_PROGRAM 8
#define AST_PRINT_LIST 9
#define AST_VECTOR_DEF 10
#define AST_INIT_VECTOR_DEF 11
#define AST_VECTOR_PARAM_LIST 12
#define AST_FUNC_DEF 13
#define AST_FUNC_DEF_PARAM_LIST 14
#define AST_FUNC_DEF_PARAM_LIST_REST 15
#define AST_FUNC_CALL 16
#define AST_FUNC_CALL_PARAM_LIST 17
#define AST_FUNC_CALL_PARAM_LIST_REST 18
#define AST_VAR_ASSIGNMENT 19
#define AST_VECTOR_ASSIGNMENT 20
#define AST_READ 21
#define AST_PRINT 22
#define AST_RETURN 23
#define AST_WHEN 24
#define AST_WHEN_ELSE 25
#define AST_WHILE 26
#define AST_FOR 27
#define AST_OP_GREATER 28
#define AST_OP_LESS 29
#define AST_OP_LE 30
#define AST_OP_GE 31
#define AST_OP_EQ 32
#define AST_OP_NE 33
#define AST_OP_AND 34
#define AST_OP_OR 35
#define AST_VECTOR_ACCESS 36
#define AST_T_BYT 37
#define AST_T_SHO 38
#define AST_T_LON 39
#define AST_T_FLO 40
#define AST_T_DOU 41
#define AST_CMD_BLOCK 42
#define AST_FUNC_DEF_PARAM 43

#define MAX_SONS 4

typedef struct ast {
    int type;
    HASH_NODE* symbol;
    struct ast *son0;
    struct ast *son1;
    struct ast *son2;
    struct ast *son3;
} AST;

AST* astCreate(int type, HASH_NODE* symbol, AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint(int level, AST* node);
void astPrintSrc(AST* node);
#endif
