#include "ast.h"
#include <stdlib.h>


void semanticSetDeclarations(AST* node) {
    int i;
    if(!node)
        return;
    switch(node->type) {
        case AST_VAR_DEF:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic error, variable %s already defined\n",node->symbol->text);    
                exit(4);
            }
            node->symbol->type = SYMBOL_VAR;
            switch(node->sons[0]->type){
                case AST_T_BYT:
                    node->symbol->dataType = DATATYPE_BYTE;
			        break;
                case AST_T_SHO:
                    node->symbol->dataType = DATATYPE_SHORT;
			        break;
                case AST_T_LON:
                    node->symbol->dataType = DATATYPE_LONG;
			        break;
                case AST_T_FLO:
                    node->symbol->dataType = DATATYPE_FLOAT;
			        break;
                case AST_T_DOU:
                    node->symbol->dataType = DATATYPE_DOUBLE;
			        break;
			}
            break;
        case AST_FUNC_DEF:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic error, variable %s already defined\n",node->symbol->text);    
                exit(4);
            }
            node->symbol->type = SYMBOL_FUN;
            switch(node->sons[0]->type){
                case AST_T_BYT:
                    node->symbol->dataType = DATATYPE_BYTE;
			        break;
                case AST_T_SHO:
                    node->symbol->dataType = DATATYPE_SHORT;
			        break;
                case AST_T_LON:
                    node->symbol->dataType = DATATYPE_LONG;
			        break;
                case AST_T_FLO:
                    node->symbol->dataType = DATATYPE_FLOAT;
			        break;
                case AST_T_DOU:
                    node->symbol->dataType = DATATYPE_DOUBLE;
			        break;
			}
            break;
        case AST_VECTOR_DEF:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic error, variable %s already defined\n",node->symbol->text);    
                exit(4);
            }
            node->symbol->type = SYMBOL_VEC;
            switch(node->sons[0]->type){
                case AST_T_BYT:
                    node->symbol->dataType = DATATYPE_BYTE;
			        break;
                case AST_T_SHO:
                    node->symbol->dataType = DATATYPE_SHORT;
			        break;
                case AST_T_LON:
                    node->symbol->dataType = DATATYPE_LONG;
			        break;
                case AST_T_FLO:
                    node->symbol->dataType = DATATYPE_FLOAT;
			        break;
                case AST_T_DOU:
                    node->symbol->dataType = DATATYPE_DOUBLE;
			        break;
			}
            break;
        default:
            break;
    }
    for(i=0; i < MAX_SONS; i++) {
        semanticSetDeclarations(node->sons[i]);
    }
}
void checkUtilization(AST* node) {
    if(!node)
        return;

    switch(node->type) {
        case AST_SYMBOL:
        case AST_VAR_ASSIGNMENT:
            fprintf(stderr, "Scalar %s %d\n", node->symbol->text, node->symbol->type);
            if(node->symbol->type == SYMBOL_VEC) {
                fprintf(stderr, "Vector being used as scalar");
            }
            else if(node->symbol->type == SYMBOL_FUN) {
                fprintf(stderr, "Function being used as scalar");
            }
            break;
        case AST_VECTOR_ACCESS:
        case AST_VECTOR_ASSIGNMENT:
            fprintf(stderr, "Vector %s %d\n", node->symbol->text, node->symbol->type);
            if(node->symbol->type == SYMBOL_VAR) {
                fprintf(stderr, "Scalar being used as vector");
            }
            else if(node->symbol->type == SYMBOL_FUN) {
                fprintf(stderr, "Function being used as vector");
            }
            break;
        
        case AST_FUNC_CALL:
            fprintf(stderr, "Function %s %d\n", node->symbol->text, node->symbol->type);
            if(node->symbol->type == SYMBOL_VAR) {
                fprintf(stderr, "Scalar being used as function");
            }
            else if(node->symbol->type == SYMBOL_VEC) {
                fprintf(stderr, "Vector being used as function");
            }
            break;
        default:
            break;
    }
    int i;
    for(i=0; i < MAX_SONS; i++) {
        checkUtilization(node->sons[i]);
    }
}

void checkDataTypes(AST* node) {
        if(isArithmeticOp(node)) {
        if(!isArithmeticOp(node->children[0])) {
            if(isValidOperand(node->children[0])) {
                if(!isNumericDatatype(node->children[0])) {
                    fprintf(stderr, "Line %d: Operator %s is of an invalid type for arithmetic expression.\n", node->lineNumber, node->children[0]->symbol->text);
                }
            }
            else 
                fprintf(stderr, "Line %d: Operator is of an invalid type for arithmetic expression.\n", node->lineNumber);

            if(isValidOperand(node->children[1])) {
                if(!isNumericDatatype(node->children[1])) {
                    fprintf(stderr, "Line %d: Operator %s is of an invalid type for arithmetic expression.\n", node->lineNumber, node->children[1]->symbol->text);
                }
            }
            else 
                fprintf(stderr, "Line %d: Operator is of an invalid type for arithmetic expression.\n", node->lineNumber);
        }
}
int isValidOperand(AST* node) {
    return node->type == AST_SYMBOL 
        || node->type == AST_SYMBOL_VEC 
        || node->type == AST_SYMBOL_LIT;
}
int isArithmeticOp(AST* node) {
    return node->type == AST_ADD 
        || node->type == AST_SUB 
        || node->type == AST_MULT 
        || node->type == AST_DIV;
}
int isRelationalOp(AST* node) {
    return node->type == AST_OP_GREATER 
        || node->type == AST_OP_LESS 
        || node->type == AST_OP_LE 
        || node->type == AST_OP_GE
        || node->type == AST_OP_EQ
        || node->type == AST_OP_NE;
}
int isNumericDatatype(AST* node) {
    return node->symbol->dataType == DATATYPE_BYTE 
        || node->symbol->dataType == DATATYPE_SHORT 
        || node->symbol->dataType == DATATYPE_FLOAT 
        || node->symbol->dataType == DATATYPE_LONG 
        || node->symbol->dataType == DATATYPE_DOUBLE;
}
