#include "tacs.h"
#include <stdio.h>
#include <stdlib.h>

TAC* makeWhenThen(TAC* code0, TAC* code1);
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
    TAC* tac = l2;
    while(tac->prev) {
        tac=tac->prev;
        // printf("TAC: %d\n", tac->type);
    }
    tac->prev = l1;
    l1->next = l2;
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
            case TAC_IFZ:
                fprintf(stderr, "TAC_IFZ");
                break;
            case TAC_LABEL:
                fprintf(stderr, "TAC_LABEL");
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
TAC* tacReverse(TAC* tac) {
    TAC* t = 0;
    for (t = tac; t->prev; t = t->prev ) {
        printf("t %d\n", t->type);
        t->prev->next = t;
    }
    return t;
}
void tacPrintForward(TAC* first) {
    fprintf(stderr, "Imprimindo código gerado\n");
    TAC* tac;
    for(tac = first; tac; tac=tac->next) {
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
            case TAC_IFZ:
                fprintf(stderr, "TAC_IFZ");
                break;
            case TAC_LABEL:
                fprintf(stderr, "TAC_LABEL");
                break;
            case TAC_UNKNOWN:
                fprintf(stderr, "TAC_UNKNOWN");
                break;
            case TAC_ARG:
                fprintf(stderr, "TAC_ARG");
                break;
            case TAC_VEC_READ:
                fprintf(stderr, "TAC_VEC_READ");
                break;
            case TAC_VEC_WRITE:
                fprintf(stderr, "TAC_VEC_WRITE");
                break;
            case TAC_CALL:
                fprintf(stderr, "TAC_CALL");
                break;
            case TAC_MOV:
                fprintf(stderr, "TAC_MOV");
                break;
            case TAC_RETURN:
                fprintf(stderr, "TAC_RETURN");
                break;
            case TAC_BEGIN_FUN:
                fprintf(stderr, "TAC_BEGIN_FUN");
                break;
            case TAC_END_FUN:
                fprintf(stderr, "TAC_END_FUN");
                break;
        }
        if(tac->res)
            fprintf(stderr, ", %s", tac->res->text);
        else 
            fprintf(stderr, ",0");
        if(tac->op1)
            fprintf(stderr, ", %s", tac->op1->text);
        else 
            fprintf(stderr, ",0");
        if(tac->op2)
            fprintf(stderr, ", %s", tac->op2->text);
        else 
            fprintf(stderr, ",0");
        printf(")\n");
    }
}
TAC* tacGenerate(AST* node) {
    if(!node)
        return 0;
    int i;
    TAC * code[MAX_SONS], *result;
    //process children node
    for(i=0; i<MAX_SONS; i++) {
        code[i] = tacGenerate(node->sons[i]);
    }
    //process this node
    switch(node->type) {
        case AST_SYMBOL:
            printf("simbolo\n");
            result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); 
            break;
        case AST_ADD:
        printf("add\n");
            result = tacCreateOp(TAC_ADD,code[0],code[1]);                 
            break;
        case AST_WHEN:
            makeWhenThen(code[0],code[1]);
        default:
        printf("defout\n");
            result = tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
            break;
    }
    //return code for this node
    return result;
}

TAC* tacCreateOp(int type, TAC* op1, TAC* op2) {
    return tacJoin(op1,
                tacJoin(op2, tacCreate(type, makeTemp(), op1?op1->res:0, op2?op2->res:0)));
}

TAC* makeWhenThen(TAC* code0, TAC* code1) {
    TAC* iftac, *labeltac;
    HASH_NODE* newlabel;
    newlabel = makeLabel();
    iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
    labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
    return tacJoin(tacJoin(tacJoin(code0,iftac),code1),labeltac);
}