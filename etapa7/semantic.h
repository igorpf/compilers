#include "ast.h"

void semanticSetDeclarations(AST* node);
void checkUtilization(AST* node);
int dataType(AST* node);
void checkDataTypes(AST* node);
void checkDataType(AST* node);
int hashCheckUndeclared(void);
