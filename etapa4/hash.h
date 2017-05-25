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

typedef struct hash_struct {
	int type;
	int dataType;
	char* text;
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