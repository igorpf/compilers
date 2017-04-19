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
%token KW_TO 
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
        |global_var_def program
        | func_def program
        ;

global_var_def:
        type TK_IDENTIFIER ':' value ';'
        | type TK_IDENTIFIER '[' LIT_INTEGER']' ';'
        | type TK_IDENTIFIER '[' LIT_INTEGER']' ':'  vector_param_list ';'        

vector_param_list:
        value
        | value vector_param_list

func_def:   
        type TK_IDENTIFIER '(' func_def_param_list')' block
        ;

func_def_param_list: 
        | func_param ',' func_def_param_list
        | func_param 
        ;
        
func_param:  type TK_IDENTIFIER
        ;

func_call:   
        TK_IDENTIFIER '(' func_call_param_list')' 
        ;        

func_call_param:
        TK_IDENTIFIER
        | value
        ;

func_call_param_list:
        | func_call_param
        | func_call_param ',' func_call_param_list
        ;




block:  '{' cmd_list'}'
        ;

cmd_list:
        cmd ';' cmd_list
        | cmd ';'
        ;


cmd:    
        |TK_IDENTIFIER '=' expr
        | TK_IDENTIFIER'['expr']' '=' expr
        | flux_control
        | KW_READ TK_IDENTIFIER
        | KW_PRINT print_list
        | KW_RETURN expr
        | expr
        | block
        ;
print_list:
        element
        | element print_list
element:
        LIT_STRING
        | expr

flux_control:
        KW_IF '(' expr')' KW_THEN cmd
        KW_IF '(' expr')' KW_THEN cmd KW_ELSE cmd
        KW_FOR '(' expr')' cmd
        KW_FOR '(' TK_IDENTIFIER '=' expr KW_TO expr ')' cmd
        ;










expr:   expr op expr
        | '('expr')'
        | func_call
        | LIT_INTEGER
        | LIT_CHAR
        | TK_IDENTIFIER
        | TK_IDENTIFIER '[' LIT_CHAR']'
        | TK_IDENTIFIER '[' LIT_INTEGER']'
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