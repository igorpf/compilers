#include "tacs.h"
#include <stdio.h>
#include <stdlib.h>

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2) {
    TAC* newTac;
    newTac = (TAC*) calloc(1, sizeof(TAC));
    newTac->type = type;
    newTac->res = res;
    newTac->op1 = op1;
    newTac->op2 = op2;

    return newTac;
}
TAC* tacJoin(TAC* l1,TAC* l2) {
    if(!l1) return l2;
    if(!l2) return l1;
    TAC* tac;
    for(tac=l2;tac;tac = tac->prev) {

    }
    tac->prev = l1;
    return l2;
}
void tacPrintBack(TAC* last) {
    fprintf(stderr, "Imprimindo código gerado\n");
    TAC* tac;
    for(tac = last; tac; tac=tac->prev) {
        fprintf(stderr, "TAC(");
        switch(tac->type) {
            case TAC_SYMBOL:
                fprintf(stderr, "TAC_SYMBOL");
                break;
            case TAC_ADD:
                fprintf(stderr, "TAC_ADD");
                break;
            case TAC_SUB:
                fprintf(stderr, "TAC_SUB");
                break;
            case TAC_UNKNOWN:
                fprintf(stderr, "TAC_UNKNOWN");
                break;
        }
        if(tac->res)
            fprintf(stderr, "%s", tac->res->text);
        else 
            fprintf(stderr, ",0");
        if(tac->op1)
            fprintf(stderr, "%s", tac->op1->text);
        else 
            fprintf(stderr, ",0");
        if(tac->op2)
            fprintf(stderr, "%s", tac->op2->text);
        else 
            fprintf(stderr, ",0");
    }
}
TAC* tacGenerate(AST* node) {
    if(!node)
        return 0;
    int i;
    TAC* code[MAX_SONS], result = 0;
    //process children node
    for(i=0; i<MAX_SONS; i++) {
        code[i] = tacGenerate(node->sons[i]);
    }
    //process this node
    switch(node->type) {
        case AST_SYMBOL:
            result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); 
            break;
        case AST_ADD:
            result = tacJoin(code[0],tacJoin(code[1],
                tacCreate(TAC_ADD, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)
                )); 
            break;
        default:
            result = tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
            break;
    }
    //return code for this node
    return result;
}