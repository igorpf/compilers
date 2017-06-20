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
#define SYMBOL_LIT_INTEGER 4
#define SYMBOL_LIT_REAL 5
#define SYMBOL_LIT_CHAR 6
#define SYMBOL_LIT_STRING 7
#define SYMBOL_IDENTIFIER 8

#define DATATYPE_BOOL 1
#define DATATYPE_BYTE 2
#define DATATYPE_SHORT 3
#define DATATYPE_LONG 4
#define DATATYPE_FLOAT 5
#define DATATYPE_DOUBLE 6

typedef struct hash_struct {
	int type;
	int dataType;
	char* text;
	struct hash_struct *next;
	int numberOfParameters;
} HASH_NODE;

HASH_NODE* Table[HASH_SIZE];

void initMe();
int hashAddress(char* text);
HASH_NODE* hashFind(char* next);
HASH_NODE* hashInsert(int type, char* text);
void hashPrint();
HASH_NODE* makeTemp(void);
HASH_NODE* makeLabel(void);
#endif
