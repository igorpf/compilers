/*
Igor Pires Ferreira - 242267
Thor Castilhos Sanchotene - 242261 
*/
#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997
#define SYMBOL_VAR 1
#define SYMBOL_VEC 2
#define SYMBOL_FUN 3

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_IDENTIFIER 5

#define DATATYPE_BYTE 1
#define DATATYPE_SHORT 2
#define DATATYPE_LONG 3
#define DATATYPE_FLOAT 4
#define DATATYPE_DOUBLE 5
#define DATATYPE_BOOLEAN 6
#define DATATYPE_STRING 7

typedef struct hash_struct {
	int type;
	int dataType;
	char* text;
    struct ast *symbol;
	struct hash_struct *next;
} HASH_NODE;

HASH_NODE* Table[HASH_SIZE];

void initMe();
int hashAddress(char* text);
HASH_NODE* hashFind(char* next);
HASH_NODE* hashInsert(int type, char* text);
void hashPrint();
void hashCheckUndeclared(void);
#endif