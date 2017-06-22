#include "tacs.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

TAC* makeWhenThen(TAC* code0, TAC* code1);
TAC* makeWhenThenElse(TAC* code0, TAC* code1, TAC* code2);
TAC* makeWhile(TAC* code0, TAC* code1);
TAC* makeFor(TAC* code0, TAC* code1, TAC* code2, HASH_NODE *symbol);
TAC* makeFuncDef(TAC* type, TAC* params, TAC* cmdBlock, HASH_NODE *symbol);

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
    // printf("join %d\n", tac->prev?1:0);
    while(tac->prev) {
        printf("TAC: %d\n", tac->type);
        tac=tac->prev;
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
            case TAC_MUL:
                fprintf(stderr, "TAC_MUL");
                break;
            case TAC_DIV:
                fprintf(stderr, "TAC_DIV");
                break;
            case TAC_GT:
                fprintf(stderr, "TAC_GT");
                break;
            case TAC_LT:
                fprintf(stderr, "TAC_LT");
                break;
            case TAC_GE:
                fprintf(stderr, "TAC_GE");
                break;
            case TAC_LE:
                fprintf(stderr, "TAC_LE");
                break;
            case TAC_EQ:
                fprintf(stderr, "TAC_EQ");
                break;
            case TAC_NE:
                fprintf(stderr, "TAC_NE");
                break;
            case TAC_AND:
                fprintf(stderr, "TAC_AND");
                break;
            case TAC_OR:
                fprintf(stderr, "TAC_OR");
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
            case TAC_T_BYT:
                fprintf(stderr, "TAC_T_BYT");
                break;
            case TAC_T_SHO:
                fprintf(stderr, "TAC_T_SHO");
                break;
            case TAC_T_LON:
                fprintf(stderr, "TAC_T_LON");
                break;
            case TAC_T_FLO:
                fprintf(stderr, "TAC_T_FLO");
                break;
            case TAC_T_DOU:
                fprintf(stderr, "TAC_T_DOU");
                break;
			case TAC_JUMP:
                fprintf(stderr, "TAC_JUMP");
                break;
            case TAC_MOV_IND:
                fprintf(stderr, "TAC_MOV_IND");
                break;
            case TAC_PRINT:
                fprintf(stderr, "TAC_PRINT");
                break;
            case TAC_READ:
                fprintf(stderr, "TAC_READ");
                break;
            case TAC_PARAM:
                fprintf(stderr, "TAC_PARAM");
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
            result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); 
            break;
        case AST_ADD:
            result = tacCreateOp(TAC_ADD,code[0],code[1]);
            break;
        case AST_SUB:
            result = tacCreateOp(TAC_SUB,code[0],code[1]);
            break;
        case AST_MULT:
            result = tacCreateOp(TAC_MUL,code[0],code[1]);
            break;
        case AST_DIV:
            result = tacCreateOp(TAC_DIV,code[0],code[1]);
            break;
        case AST_OP_GREATER:
            result = tacCreateOp(TAC_GT,code[0],code[1]);
            break;
        case AST_OP_LESS:
            result = tacCreateOp(TAC_LT,code[0],code[1]);
            break;
        case AST_OP_LE:
            result = tacCreateOp(TAC_LE,code[0],code[1]);
            break;
        case AST_OP_GE:
            result = tacCreateOp(TAC_GE,code[0],code[1]);
            break;
        case AST_OP_EQ:
            result = tacCreateOp(TAC_EQ,code[0],code[1]);
            break;
        case AST_OP_NE:
            result = tacCreateOp(TAC_NE,code[0],code[1]);
            break;
        case AST_OP_AND:
            result = tacCreateOp(TAC_AND,code[0],code[1]);
            break;
        case AST_OP_OR:
            result = tacCreateOp(TAC_OR,code[0],code[1]);
            break;
        case AST_T_BYT:
            result = tacCreate(TAC_T_BYT,0,0,0);
            break;
        case AST_T_SHO:
            result = tacCreate(TAC_T_SHO,0,0,0);
            break;
        case AST_T_LON:
            result = tacCreate(TAC_T_LON,0,0,0);
            break;
        case AST_T_FLO:
            result = tacCreate(TAC_T_FLO,0,0,0);
            break;
        case AST_T_DOU:
            result = tacCreate(TAC_T_DOU,0,0,0);
            break;
        case AST_RETURN:
            result = tacJoin(code[0], tacCreate(TAC_RETURN,code[0]?code[0]->res:0,0,0));
            break;
        case AST_CMDL:
        case AST_PROGRAM:        
        case AST_VECTOR_PARAM_LIST:
         case AST_FUNC_DEF_PARAM_LIST: //esses aqui tem os tipos junto. 
        //                                 tem que fazer outro case?
         case AST_FUNC_DEF_PARAM_LIST_REST:        
            result = tacJoin(code[0], code[1]);
            break;
        case AST_VAR_ASSIGNMENT:
            result = tacJoin(code[0], tacCreate(TAC_MOV,node->symbol,code[0]?code[0]->res:0,0));
            break;
        case AST_VECTOR_ASSIGNMENT:
            result =
            tacJoin( 
                tacJoin(code[0],code[1]),
                    tacCreate(TAC_MOV_IND,node->symbol,code[0]?code[0]->res:0,code[1]?code[1]->res:0));
            break;
        case AST_CMD:
        case AST_CMD_BLOCK:
            result = code[0];
            break;
        case AST_FUNC_DEF_PARAM:
			result = tacJoin(code[0],tacCreate(TAC_PARAM, node->symbol, 0, 0));
            break;
        case AST_FUNC_CALL:
            result = tacJoin(code[0], tacCreate(TAC_CALL, makeTemp(), node->symbol, 0));
            break;
        case AST_WHEN:
            result = makeWhenThen(code[0],code[1]);
            break;
		case AST_WHEN_ELSE:
            result = makeWhenThenElse(code[0],code[1],code[2]);
            break;
		case AST_WHILE:
            result = makeWhile(code[0],code[1]);
            break;
		case AST_FOR:
            result = makeFor(code[0],code[1],code[2],node->symbol);
            break;
        case AST_READ:
            result = tacCreate(TAC_READ, node->symbol,0,0);
            break;
        case AST_PRINT:
            result = tacJoin(code[0], tacCreate(TAC_PRINT, 0,0,0));
            break;
        case AST_FUNC_CALL_PARAM_LIST:
        case AST_FUNC_CALL_PARAM_LIST_REST:
        case AST_PRINT_LIST:
            result = tacJoin(tacJoin(code[0], tacCreate(TAC_ARG, code[0]? code[0]->res : 0, 0, 0)), code[1]);
            break;
        case AST_FUNC_DEF:
            result = makeFuncDef(code[0],code[1],code[2],node->symbol);
            break;
        default:
            printf("caiu no default %d\n", node->type);
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
    TAC *iftac, *labeltac;
    HASH_NODE* newlabel = makeLabel();
    iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
    labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
    return tacJoin(tacJoin(tacJoin(code0,iftac),code1),labeltac);
}

TAC* makeWhenThenElse(TAC* code0, TAC* code1, TAC* code2) {
    TAC *iftac, *jumptac, *labeltac, *labeltac2;
    HASH_NODE *newlabel, *newlabel2;
    newlabel = makeLabel();
	newlabel2 = makeLabel();
    iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
	labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
	jumptac = tacCreate(TAC_JUMP, newlabel2, 0, 0);
	labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code0,iftac),code1),jumptac),labeltac),code2),labeltac2);
}

TAC* makeWhile(TAC* code0, TAC* code1) {
    TAC *iftac, *jumptac, *labeltac, *labeltac2, *movetac;
    HASH_NODE *newlabel, *newlabel2;
    newlabel = makeLabel();
	newlabel2 = makeLabel();
    iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
	labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
	jumptac = tacCreate(TAC_JUMP, newlabel2, 0, 0);
	labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labeltac2,code0),iftac),code1),jumptac),labeltac);
}

TAC* makeFor(TAC* code0, TAC* code1, TAC* code2, HASH_NODE *symbol) {
    TAC *iftac, *jumptac, *comptac, *labeltac, *labeltac2, *movetac, *symboltac, *addtac;
    HASH_NODE *newlabel, *newlabel2;
    newlabel = makeLabel();
	newlabel2 = makeLabel();
	symboltac = tacCreate(TAC_SYMBOL, symbol,0,0);
	comptac = tacCreate(TAC_LE, makeTemp(), symboltac->res, code1?code1->res:0);
    iftac = tacCreate(TAC_IFZ, newlabel, comptac->res, 0);
	jumptac = tacCreate(TAC_JUMP, newlabel2, 0, 0);
    labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
	labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
	movetac = tacCreate(TAC_MOV, symboltac->res, code0?code0->res:0, 0);
	addtac = tacCreate(TAC_ADD, symboltac->res, symboltac->res, hashInsert(SYMBOL_LIT_INTEGER,"1"));
    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin
			(symboltac,code0),code1),movetac),labeltac2),comptac),iftac),code2),addtac),jumptac),labeltac);
}
TAC* makeFuncDef(TAC* type, TAC* params, TAC* cmdBlock, HASH_NODE *symbol) {
    TAC* beginf = tacCreate(TAC_BEGIN_FUN, symbol, 0, 0);
    TAC* endf = tacCreate(TAC_END_FUN, symbol, 0, 0);

    return tacJoin(tacJoin(tacJoin(params, beginf), cmdBlock), endf);
}