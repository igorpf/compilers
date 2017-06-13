#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD    2
#define TAC_SUB    3
#define TAC_IFZ    4
#define TAC_LABEL  5
/*
TAC_ARG
TAC_VEC_READ
TAC_VEC_WRITE
TAC_CALL
TAC_MOV
TAC_RETURN
TAC_BEGIN_FUN
TAC_END_FUN
*/

typedef struct tac_struct {
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
TAC* tacReverse(TAC* tac);
void tacPrintForward(TAC* first);
#endif