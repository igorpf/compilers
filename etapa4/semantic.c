#include "ast.h"
#include "semantic.h"
#include <stdlib.h>

int hasSemanticError = 0;

void semanticSetDeclarations(AST* node) {
    int i, numberOfArguments = 0;
	AST *nodeAux;
    if(!node)
        return;
    switch(node->type) {
        case AST_VAR_DEF:
		case AST_FUNC_DEF_PARAM:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "\nSemantic error, variable %s already defined",node->symbol->text);    
				hasSemanticError = 1;
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
                fprintf(stderr, "\nSemantic error, variable %s already defined",node->symbol->text);    
				hasSemanticError = 1;
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
			for(nodeAux = node->sons[1]; nodeAux; nodeAux = nodeAux->sons[1])
				numberOfArguments++;
			node->symbol->numberOfArguments = numberOfArguments;
            break;
        case AST_INIT_VECTOR_DEF:
        case AST_VECTOR_DEF:
            if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "\nSemantic error, variable %s already defined",node->symbol->text); 
				hasSemanticError = 1;   
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
            //fprintf(stderr, "Scalar %s %d\n", node->symbol->text, node->symbol->type);
            if(node->symbol->type == SYMBOL_VEC) {
                fprintf(stderr, "\nSemantic error, vector being used as scalar");
				hasSemanticError = 1;
            }
            else if(node->symbol->type == SYMBOL_FUN) {
                fprintf(stderr, "\nSemantic error, function being used as scalar");
				hasSemanticError = 1;
            }
            break;
        case AST_VECTOR_ACCESS:
        case AST_VECTOR_ASSIGNMENT:
            //fprintf(stderr, "Vector %s %d\n", node->symbol->text, node->symbol->type);
            if(node->symbol->type == SYMBOL_VAR) {
                fprintf(stderr, "\nSemantic error, scalar being used as vector");
				hasSemanticError = 1;
            }
            else if(node->symbol->type == SYMBOL_FUN) {
                fprintf(stderr, "\nSemantic error, function being used as vector");
				hasSemanticError = 1;
            }
            break;
        
        case AST_FUNC_CALL:
            //fprintf(stderr, "Function %s %d\n", node->symbol->text, node->symbol->type);
            if(node->symbol->type == SYMBOL_VAR) {
                fprintf(stderr, "\nSemantic error, scalar being used as function");
				hasSemanticError = 1;
            }
            else if(node->symbol->type == SYMBOL_VEC) {
                fprintf(stderr, "\nSemantic error, vector being used as function");
				hasSemanticError = 1;
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
	checkDataType(node);
	fprintf(stderr, "\n");
	if(hasSemanticError)
		exit(4);
}

void checkDataType(AST* node) {
	int i, numberOfParameters = 0;
	AST *nodeAux;
	if(!node)
		return;
	switch(node->type){
		case AST_ADD:
		case AST_SUB:
		case AST_MULT:
		case AST_DIV:
			if(dataType(node->sons[0]) < 2 || dataType(node->sons[1]) < 2){
				fprintf(stderr, "\nSemantic error, arithmetic operator applied to non-numeric operand");
				hasSemanticError = 1;
			}
			break;
		case AST_OP_GREATER:
		case AST_OP_LESS:
		case AST_OP_LE:
		case AST_OP_GE:
		case AST_OP_EQ:
		case AST_OP_NE:
			if(dataType(node->sons[0]) < 2 || dataType(node->sons[1]) < 2){
				fprintf(stderr, "\nSemantic error, relational operator applied to non-numeric operand");
				hasSemanticError = 1;
			}
			break;
		case AST_OP_AND:
		case AST_OP_OR:
			if(dataType(node->sons[0]) != 1 || dataType(node->sons[1]) != 1){
				fprintf(stderr, "\nSemantic error, logic operator applied to non-Boolean operand");
				hasSemanticError = 1;
			}
			break;
		case AST_VECTOR_ACCESS:
			if(!(dataType(node->sons[0]) >= 2 && dataType(node->sons[0]) <= 4)){
				fprintf(stderr, "\nSemantic error, vector index not integer");
				hasSemanticError = 1;
			}
			break;
		case AST_VAR_ASSIGNMENT:
			if(dataType(node->sons[0]) < 2){
				fprintf(stderr, "\nSemantic error, incompatible data types");
				hasSemanticError = 1;
			}
			break;
		case AST_VECTOR_ASSIGNMENT:
			if(!(dataType(node->sons[0]) >= 2 && dataType(node->sons[0]) <= 4)){
				fprintf(stderr, "\nSemantic error, vector index not integer");
				hasSemanticError = 1;
			}
			if(dataType(node->sons[1]) < 2){
				fprintf(stderr, "\nSemantic error, incompatible data types");
				hasSemanticError = 1;
			}
			break;
		case AST_WHEN:
		case AST_WHEN_ELSE:
		case AST_WHILE:
			if(dataType(node->sons[0]) != 1){
				fprintf(stderr, "\nSemantic error, the expression result must be Boolean for a conditional split");
				hasSemanticError = 1;
			}
			break;
		case AST_FOR:
			if(dataType(node->sons[0]) < 2 || dataType(node->sons[1]) < 2){
				fprintf(stderr, "\nSemantic error, invalid range in 'for' command");
				hasSemanticError = 1;
			}
			break;
		case AST_RETURN:
			if(dataType(node->sons[0]) < 2){
				fprintf(stderr, "\nSemantic error, invalid return data type");
				hasSemanticError = 1;
			}
			break;
		case AST_FUNC_CALL:
			for(nodeAux = node->sons[0]; nodeAux; nodeAux = nodeAux->sons[1])
				numberOfParameters++;
			if(numberOfParameters != (hashFind(node->symbol->text))->numberOfArguments){
				fprintf(stderr, "\nSemantic error, invalid number of parameters");
				hasSemanticError = 1;
			}
			break;
		case AST_FUNC_CALL_PARAM_LIST:
		case AST_FUNC_CALL_PARAM_LIST_REST:
			if(dataType(node->sons[0]) < 2){
				fprintf(stderr, "\nSemantic error, invalid parameter data type");
				hasSemanticError = 1;
			}
			break;
		
	}
	for(i = 0; i < MAX_SONS; i++)
		checkDataType(node->sons[i]);
}

int dataType(AST* node) {
	if(!node)
		return 0;
	switch(node->type){
		case AST_SYMBOL:
			if(!node->symbol)
				return 0;
			switch(node->symbol->type){
				case SYMBOL_LIT_INTEGER:
					return DATATYPE_LONG;
				case SYMBOL_LIT_CHAR:
					return DATATYPE_BYTE;
				case SYMBOL_LIT_REAL:
					return DATATYPE_DOUBLE;
				case SYMBOL_VAR:
				case SYMBOL_FUN:
				case SYMBOL_VEC:
					return node->symbol->dataType;
				default:
					return 0;
			}
			break;
		case AST_ADD:
		case AST_SUB:
		case AST_MULT:
		case AST_DIV:
			if(dataType(node->sons[0]) < 2 || dataType(node->sons[1]) < 2)
				return DATATYPE_SHORT;
				
			if(dataType(node->sons[0]) > dataType(node->sons[1])){
				return dataType(node->sons[0]);
			}
			else 
				return dataType(node->sons[1]);
			break;
		case AST_OP_AND:
		case AST_OP_OR:
		case AST_OP_GREATER:
		case AST_OP_LESS:
		case AST_OP_LE:
		case AST_OP_GE:
		case AST_OP_EQ:
		case AST_OP_NE:
			return DATATYPE_BOOL;
		case AST_FUNC_CALL:
			return node->symbol->type;
		case AST_VECTOR_ACCESS:
			if(!node->symbol)
				return 0;
			return node->symbol->dataType;
		case AST_PARENTHESES:
			return dataType(node->sons[0]);
			break;
		default:
			return 0;
	}
}

int hashCheckUndeclared(void) {
	 int i;
	 HASH_NODE* node;
	 for(i=0; i < HASH_SIZE; i++){
	 	for(node = Table[i]; node;node = node->next) {
	 		if(node->type == SYMBOL_IDENTIFIER) {
	 			fprintf(stderr, "\nSemantic error, %s not defined", node->text);	
	 			hasSemanticError = 1;
	 		}
	 	}		
	 }
}
/*
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
}*/
