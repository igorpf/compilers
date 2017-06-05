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
                fprintf(stderr, "Semantic error, function %s already defined\n",node->symbol->text);    
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
                fprintf(stderr, "Semantic error, vector %s already defined\n",node->symbol->text);    
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
