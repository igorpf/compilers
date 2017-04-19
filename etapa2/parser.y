%{
#include<stdlib.h>
#include<stdio.h>
#include"hash.h"
extern FILE * yyin;

%}

%token KW_INT 
%token KW_BYTE 
%token KW_SHORT 
%token KW_LONG 
%token KW_FLOAT 
%token KW_DOUBLE 
%token KW_WHEN 
%token KW_THEN 
%token KW_ELSE 
%token KW_WHILE 
%token KW_FOR 
%token KW_READ 
%token KW_RETURN 
%token KW_PRINT 

%token OPERATOR_LE 
%token OPERATOR_GE 
%token OPERATOR_EQ 
%token OPERATOR_NE 
%token OPERATOR_AND 
%token OPERATOR_OR 

%token TK_IDENTIFIER 
%token LIT_INTEGER 
%token LIT_REAL 
%token LIT_CHAR 
%token LIT_STRING 

%token TOKEN_ERROR

%%

program:
        cmdlist
        ;
cmdlist:
        cmd cmdlist
        | cmd
        ;
cmd:    LIT_INTEGER
        | TK_IDENTIFIER '=' LIT_INTEGER
        | expr;
expr:
        expr '+' expr
        | '('expr')'
        | LIT_INTEGER
        | TK_IDENTIFIER
        ;
%%

int yyerror(char *what){
	fprintf(stderr, "Syntax error. Line %d\n", getLineNumber());
	exit(3);
}