#include "tacs.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            /*case TAC_MOV_IND:
                fprintf(stderr, "TAC_MOV_IND");
                break;*/
            case TAC_PRINT:
                fprintf(stderr, "TAC_PRINT");
                break;
            case TAC_READ:
                fprintf(stderr, "TAC_READ");
                break;
            case TAC_PARAM:
                fprintf(stderr, "TAC_PARAM");
                break;
            case TAC_VAR_DEC:
                fprintf(stderr, "TAC_VAR_DEC");
                break;
            case TAC_VEC_DEC:
                fprintf(stderr, "TAC_VEC_DEC");
                break;
            case TAC_VEC_DEC_INIT:
                fprintf(stderr, "TAC_VEC_DEC_INIT");
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
        fprintf(stderr,")\n");
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
        /*case AST_T_BYT:
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
            break;*/
        case AST_RETURN:
            result = tacJoin(code[0], tacCreate(TAC_RETURN,code[0]?code[0]->res:0,0,0));
            break;
        case AST_CMDL:
        case AST_PROGRAM:        
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
                    tacCreate(TAC_VEC_WRITE,node->symbol,code[0]?code[0]->res:0,code[1]?code[1]->res:0));
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
            result = code[0];
            break;
        case AST_FUNC_CALL_PARAM_LIST:
        case AST_FUNC_CALL_PARAM_LIST_REST:
        case AST_PRINT_LIST:
            result = tacJoin(tacJoin(code[0], tacCreate(TAC_PRINT, code[0]? code[0]->res : 0,0,0)), code[1]);//tacJoin(code[0], tacCreate(TAC_ARG, code[0]? code[0]->res : 0, 0, 0)), code[1]);
            break;
        case AST_FUNC_DEF:
            result = makeFuncDef(code[0],code[1],code[2],node->symbol);
            break;
        case AST_VAR_DEF:
            result = tacJoin(code[0],tacCreate(TAC_VAR_DEC, node->symbol,code[1]?code[1]->res:0,0));
            break;
        case AST_VECTOR_DEF:
            result = tacJoin(code[0],tacCreate(TAC_VEC_DEC, node->symbol,code[1]?code[1]->res:0,0));
            break;
        case AST_INIT_VECTOR_DEF:
            result = tacJoin(code[0], tacJoin(code[2],tacCreate(TAC_VEC_DEC_INIT, node->symbol,code[1]?code[1]->res:0,0)));
            break;
        case AST_VECTOR_ACCESS:
            result = tacJoin(code[0], tacCreate(TAC_VEC_READ, makeTemp(),node->symbol,code[0]?code[0]->res:0));
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

    return tacJoin(tacJoin(tacJoin(tacJoin(type,params),beginf), cmdBlock), endf);
}
void asmGen(TAC* first) {
    FILE* fout = fopen("asm.s", "w");
    TAC *tac, *tacAux;
	char *strings[MAX_STRINGS];
	int i;

	for(i = 0; i < MAX_STRINGS; i++)
		strings[i] = 0;

	i = 0;

    for(tac = first; tac; tac=tac->next) {
        // fprintf(fout, "TAC(");
        switch(tac->type) {
            case TAC_SYMBOL:
                fprintf(fout, "## TAC_SYMBOL\n");
				if(tac->res->type > 3 && tac->res->type < 7){ // se for literal (se for identificador, acho q nao precisa)
                    fprintf(fout, "\t.comm _%s,4,4\n", tac->res->text);
					fprintf(fout, "\tmovl $%s, _%s(%%rip)\n", tac->res->text, tac->res->text);
				}
                break;
            case TAC_ADD:
                fprintf(fout, 
                    "## TAC_ADD\n"
					"\t.comm _%s,4,4\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\taddl _%s(%%rip), %%eax\n"
                    "\tmovl %%eax, _%s(%%rip)\n"
                    , tac->res->text, tac->op1->text, tac->op2->text, tac->res->text);
                break;
            case TAC_SUB:
                fprintf(fout, 
                    "## TAC_SUB\n"
					"\t.comm _%s,4,4\n"
                    "\tmovl _%s(%%rip), %%edx\n"
					"\tmovl _%s(%%rip), %%eax\n"
                    "\tsubl %%eax, %%edx\n"
                    "\tmovl %%edx, %%eax\n"
					"\tmovl %%eax, _%s(%%rip)\n"
                    , tac->res->text, tac->op1->text, tac->op2->text, tac->res->text);
                break;
            case TAC_MUL:
                fprintf(fout, 
                    "## TAC_MUL\n"
					"\t.comm _%s,4,4\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\timull _%s(%%rip), %%eax\n"
                    "\tmovl %%eax, _%s(%%rip)\n"
                    , tac->res->text, tac->op1->text, tac->op2->text, tac->res->text);
                break;
            case TAC_DIV:
                fprintf(fout, 
                    "## TAC_DIV\n"
					"\t.comm _%s,4,4\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tcltd\n"
                    "\tidivl _%s(%%rip)\n"
					"\tmovl %%eax, _%s(%%rip)\n"
                    , tac->res->text, tac->op1->text, tac->op2->text, tac->res->text);
                break;
            case TAC_GT:
                fprintf(fout, "TAC_GT");
                break;
            case TAC_LT:
                fprintf(fout, "TAC_LT");
                break;
            case TAC_GE:
                fprintf(fout, "TAC_GE");
                break;
            case TAC_LE:
                fprintf(fout, "TAC_LE");
                break;
            case TAC_EQ:
                fprintf(fout, "TAC_EQ");
                break;
            case TAC_NE:
                fprintf(fout, "TAC_NE");
                break;
            case TAC_AND:
                fprintf(fout, "TAC_AND");
                break;
            case TAC_OR:
                fprintf(fout, "TAC_OR");
                break;
            case TAC_IFZ:
                fprintf(fout, "##TAC_IFZ\n");
                break;
            case TAC_LABEL:
                fprintf(fout, 
                    "## TAC_LABEL\n"
                    "%s:\n"
                    , tac->res->text);
                break;
            /*case TAC_UNKNOWN:
                fprintf(fout, "##TAC_UNKNOWN\n");
                break;
            case TAC_ARG:
                fprintf(fout, "##TAC_ARG\n");
                break;*/
            case TAC_VEC_READ:
                /*
                return f[a] -> 
                movl    a(%rip), %eax
                movl    f(,%eax,4), %eax
                */

                fprintf(fout,
                    "## TAC_VEC_READ\n"
					"\t.comm _%s,4,4\n"
                    "\tmovl _%s(%%rip), %%eax \n"
                    "\tmovl _%s(,%%eax,4), %%eax \n" //tem que ver esse 4 ali. teria que pegar o tipo da variável temporária
                    "\tmovl %%eax, _%s(%%rip) \n"	
                    ,tac->res->text,tac->op2->text,tac->op1->text,tac->res->text);
                break;
            case TAC_VEC_WRITE:
                /* Formato  para
                    f[1] = a;
                    movl    a(%rip), %eax   
                    movl    %eax, f+4(%rip)  -> se fosse f[0] ficaria f(%rip)
                */
                fprintf(fout, 
					"##TAC_VEC_WRITE\n"
					"\tmovl _%s(%%rip), %%eax \n"
					"\tmovl %%eax, _%s+%d(%%rip)\n"
					,tac->op2->text,tac->res->text,atoi(tac->op1->text)*4);
                break;
            case TAC_CALL:
                fprintf(fout, "##TAC_CALL\n");
                break;
            case TAC_MOV:
                fprintf(fout,
                    "## TAC_MOV\n"
                    "\tmovl _%s(%%rip), %%eax \n"
                    "\tmovl %%eax, _%s(%%rip) \n" 
                    ,tac->op1->text,tac->res->text);
                break;
            case TAC_RETURN:
            //o retorno da função sempre é guardado no %eax
				for(tacAux = tac; tacAux->type != TAC_END_FUN; tacAux = tacAux->next)
					;
                fprintf(fout, 
                    "## TAC_RETURN\n"
                    "\tmovl _%s(%%rip), %%eax\n" , tac->res->text);
				if(strcmp(tacAux->res->text, "main"))
					fprintf(fout, "\tpopq	 %%rbp\n");
		
				fprintf(fout,
					"\tleave\n"
                   	"\tret \n"); 
                break;
            case TAC_BEGIN_FUN:
                fprintf(fout, 
					"##TAC_BEGIN_FUN\n"
					"\t.globl %s\n"
					"%s:\n"
					"\t.cfi_startproc\n"
					"\tpushq	%%rbp\n"
					"\tmovq	%%rsp, %%rbp\n", tac->res->text, tac->res->text);
                break;
            case TAC_END_FUN:
				fprintf(fout, "##TAC_END_FUN\n");
				if(strcmp(tac->res->text, "main"))
					fprintf(fout, "\tpopq	 %%rbp\n");
				fprintf(fout,
					"\tleave\n"
                    "\tret \n"
					"\t.cfi_endproc\n");
                break;
            /*case TAC_T_BYT:
                fprintf(fout, "TAC_T_BYT");
                break;
            case TAC_T_SHO:
                fprintf(fout, "TAC_T_SHO");
                break;
            case TAC_T_LON:
                fprintf(fout, "TAC_T_LON");
                break;
            case TAC_T_FLO:
                fprintf(fout, "TAC_T_FLO");
                break;
            case TAC_T_DOU:
                fprintf(fout, "TAC_T_DOU");
                break;
			case TAC_MOV_IND:
                fprintf(fout, "##TAC_MOV_IND\n");
                break;*/
            case TAC_JUMP:
                fprintf(fout, "##TAC_JUMP\n");
                break;  
            case TAC_PRINT:
				if(tac->res->type != 7){
					fprintf(fout, 
							"##TAC_PRINT\n"
							"\t.comm _%s,4,4\n", tac->res->text);
					if(tac->res->type > 3 && tac->res->type < 7)
						fprintf(fout, "\tmovl $%s, _%s(%%rip)\n", tac->res->text, tac->res->text);
					fprintf(fout, 
						"\tmovl	_%s(%%rip), %%esi\n"
						"\tmovl	$.LC0, %%edi\n"
						"\tmovl	$0, %%eax\n"
						"\tcall	printf\n", tac->res->text);
				}
				else{
					strings[i++] = tac->res->text;
					fprintf(fout, 
						"##TAC_PRINT\n"
						"\tmovl	%%eax, %%esi\n"
						"\tmovl	$.LC%d, %%edi\n"
						"\tmovl	$0, %%eax\n"
						"\tcall	printf\n", i);
				}
                break;
            case TAC_READ:
                fprintf(fout, "##TAC_READ\n");
                break;
            case TAC_PARAM:
                fprintf(fout, "##TAC_PARAM\n");
                break;
            case TAC_VAR_DEC:
                fprintf(fout, 
					"##TAC_VAR_DEC\n"
					"\t.globl \t_%s\n"
					"\t.data\n"
					"_%s:\n"
					"\t.long \t%s\n", tac->res->text, tac->res->text, tac->op1->text);
                break;
            case TAC_VEC_DEC:
                fprintf(fout, 
					"##TAC_VEC_DEC\n"
					"\t.comm _%s,%d,4\n", tac->res->text, atoi(tac->op1->text)*4);
                break;
            case TAC_VEC_DEC_INIT:
                fprintf(fout, 
					"##TAC_VEC_DEC_INIT\n"
					"\t.globl \t_%s\n"
					"\t.data\n"
					"_%s:\n", tac->res->text, tac->res->text);
				
				for(tacAux = tac->prev; tacAux->prev->type == TAC_SYMBOL; tacAux = tacAux->prev)
					;
				while(tacAux->type != TAC_VEC_DEC_INIT)
				{
					fprintf(fout, "\t.long \t%s\n", tacAux->res->text);
					tacAux = tacAux->next;
				}
                break;
        }
        // if(tac->res)
        //     fprintf(fout, ", %s", tac->res->text);
        // else 
        //     fprintf(fout, ",0");
        // if(tac->op1)
        //     fprintf(fout, ", %s", tac->op1->text);
        // else 
        //     fprintf(fout, ",0");
        // if(tac->op2)
        //     fprintf(fout, ", %s", tac->op2->text);
        // else 
        //     fprintf(fout, ",0");
        //fprintf(fout,"\n");
    }

	fprintf(fout, 	".LC0:\n"
		"\t.string \"%%d\\n\"\n");
	for(i = 0; strings[i]; i++){
		fprintf(fout, 	".LC%d:\n"
			"\t.string %s\n"
			, i+1, strings[i]);
	}
}
