#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD    2
#define TAC_SUB    3

typedef struct tac_struch {
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_struct* prev;
    struct tac_struct* next;
} TAC;
TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
TAC* tacJoin(TAC* l1,TAC* l2);
void tacPrintBack(TAC* last);
TAC* tacGenerate(AST* node);
#endif