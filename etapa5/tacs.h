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
#define TAC_MUL      15
#define TAC_DIV      16
#define TAC_GT       17
#define TAC_LT       18
#define TAC_GE       19
#define TAC_LE       20
#define TAC_EQ       21
#define TAC_NE       22
#define TAC_AND      23
#define TAC_OR       24
#define TAC_T_BYT    25
#define TAC_T_SHO    26
#define TAC_T_LON    27
#define TAC_T_FLO    28
#define TAC_T_DOU    29 
#define TAC_FUNC_DEF_PARAM 30 
#define TAC_JUMP     31



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
