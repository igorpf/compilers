#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initMe(){
	for(int i = 0; i<1;i++){
		Table[i] = 0;
	}
}
int hashAddress(char* text){
	int address = 1;
	for(int i = 0; i < strlen(text) ;i++){
		address = (address * text[i]) % HASH_SIZE + 1;
	}
	return address - 1;
}

HASH_NODE* hashFind(char* text) {
    //HASH_NODE* node;
    for(int i = 0; i < HASH_SIZE;i++) {
        for (HASH_NODE* node=Table[i]; node; node = node->next) {
            if (strcmp(node->text, text)==0) {
                return node;
            }
        }
    }
    return NULL;
}

HASH_NODE* hashInsert(int type, char* text){
	HASH_NODE* newNode;
	int address = hashAddress(text);
	newNode = calloc(1, sizeof(HASH_NODE));
	newNode->type = type;
	newNode->text = calloc(strlen(text)+1, sizeof(char));
	stpcpy(newNode->text, text);
	newNode->next = Table[address];
	Table[address] = newNode;
	return newNode;
}

void hashPrint(){
	//HASH_NODE* node;
	for(int i = 0; i < HASH_SIZE;i++) {
		for (HASH_NODE* node=Table[i]; node; node = node->next) {
			printf("Table[%d] has %s\n", i, node->text);
		}
	}
}
