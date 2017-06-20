#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL   1
#define TAC_ADD      2
#define TAC_SUB      3
#define TAC_IFZ      4
#define TAC_LABEL    5
#define TAC_UNKNOWN  6
#define TAC_ARG      7
#define TAC_VEC_READ 8
#define TAC_VEC_WRITE 9
#define TAC_CALL     10
#define TAC_MOV      11
#define TAC_RETURN   12
#define TAC_BEGIN_FUN 13
#define TAC_END_FUN  14


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
TAC* tacCreateOp(int type, TAC* op1, TAC* op2);
#endif