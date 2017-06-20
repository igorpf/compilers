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
    printf("Antes do loop\n");
    while(tac->prev) {
        tac=tac->prev;
        printf("TAC: %d\n", tac->type);
    }
    printf("Depois do loop\n");
    tac->prev = l1;
    l1->next = l2;
    return l2;
}
void tacPrintBack(TAC* last) {
    fprintf(stderr, "Imprimindo código gerado\n");
    TAC* tac;
    for(tac = last; tac; tac=tac->prev) {        
        if(tac->type==TAC_SYMBOL)
            continue;
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
    for (t = tac; t->prev; t = tac->prev ) {
        t->prev->next = t;
    }
    return t;
}
void tacPrintForward(TAC* first) {
    fprintf(stderr, "Imprimindo código gerado\n");
    TAC* tac;
    for(tac = first; tac; tac=tac->next) {
        if(tac->type==TAC_SYMBOL)
            continue;
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
            result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); 
            break;
        case AST_ADD:
            result = tacJoin(code[0],tacJoin(code[1],
                tacCreate(TAC_ADD, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)
                )); 
            break;
        case AST_WHEN:
            makeWhenThen(code[0],code[1]);

        default:
            result = tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
            break;
    }
    //return code for this node
    return result;
}

TAC* makeWhenThen(TAC* code0, TAC* code1) {
    TAC* iftac, *labeltac;
    HASH_NODE* newlabel;
    newlabel = makeLabel();
    iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
    labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
    return tacJoin(tacJoin(tacJoin(code0,iftac),code1),labeltac);
}