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



%left '+' '-'
%left '*' '/'
%left '>' '<'

 
%left KW_IF KW_ELSE


%%

program:
        cmdlist
        ;
cmdlist:
        cmd cmdlist
        | cmd
        ;


cmd:    flux_control
        | TK_IDENTIFIER '=' expr
        | KW_PRINT
        | KW_READ
        | KW_RETURN
        | func
        | expr
        | block
        ;

flux_control:
        ;


func:   type TK_IDENTIFIER '(' paramlist')' block
        | type TK_IDENTIFIER '(' ')' block
        ;


paramlist: 
        | param ',' paramlist
        | param 
        ;

param:  type TK_IDENTIFIER
        ;

block:  '{' cmdlist'}'
        ;


expr:   expr op expr
        | '('expr')'
        | LIT_INTEGER
        | TK_IDENTIFIER
        ;


op:     '+'
        | '-'
        | '/'
        | '*'
        | '>'
        | '<'
        | OPERATOR_LE
        | OPERATOR_GE
        | OPERATOR_EQ
        | OPERATOR_NE
        | OPERATOR_AND
        | OPERATOR_OR
        ;


type:   KW_BYTE
        | KW_SHORT 
        | KW_LONG 
        | KW_FLOAT 
        | KW_DOUBLE
        ;


value:  LIT_INTEGER 
        | LIT_REAL 
        | LIT_CHAR 
        | LIT_STRING 
        ;

%%
int yyerror(char *what){
	fprintf(stderr, "Syntax error. Line %d\n", getLineNumber());
	exit(3);
}