#include "hash.h"
#include "tokens.h"
#include "lex.yy.h"
#define TRUE 1
#define FALSE 0


int isRunning();
int getLineNumber();
int yywrap();
void initMe();


int main() {
    int token;
    initMe();
    while (isRunning()) {
        token = yylex();
        switch (token) {
            case KW_INT:
                printf(" KW_INT ");
                break;
            case KW_FLOAT:
                printf(" KW_FLOAT ");
                break;
            case KW_BOOL:
                printf(" KW_BOOL ");
                break;
            case KW_CHAR:
                printf(" KW_CHAR ");
                break;
            case KW_IF:
                printf(" KW_IF ");
                break;
            case KW_THEN:
                printf(" KW_THEN ");
                break;
            case KW_ELSE:
                printf(" KW_ELSE ");
                break;
            case KW_FOR:
                printf(" KW_FOR ");
                break;
            case KW_READ:
                printf(" KW_READ ");
                break;
            case KW_RETURN:
                printf(" KW_RETURN ");
                break;
            case KW_PRINT:
                printf(" KW_PRINT ");
                break;
            case OPERATOR_LE:
                printf(" OPERATOR_LE ");
                break;
            case OPERATOR_GE:
                printf(" OPERATOR_GE ");
                break;
            case OPERATOR_EQ:
                printf(" OPERATOR_EQ ");
                break;
            case OPERATOR_NE:
                printf(" OPERATOR_NE ");
                break;
            case OPERATOR_AND:
                printf(" OPERATOR_AND ");
                break;
            case OPERATOR_OR:
                printf(" OPERATOR_OR ");
                break;
            case TK_IDENTIFIER:
                printf(" TK_IDENTIFIER ");
                break;
            case LIT_INTEGER:
                printf(" LIT_INTEGER ");
                break;
            case LIT_TRUE:
                printf(" LIT_TRUE ");
                break;
            case LIT_FALSE:
                printf(" LIT_FALSE ");
                break;
            case LIT_CHAR:
                printf(" LIT_CHAR ");
                break;
            case LIT_STRING:
                printf(" LIT_STRING ");
                break;
            case TOKEN_ERROR:
                printf(" TOKEN_ERROR ");
                break;
            default:
                printf("%c", token);
        }
    }
    printf("\n");
    hashPrint();
}
