%{
#include<stdlib.h>
#include<stdio.h>
#include"hash.h"
extern FILE * yyin;

%}

%union {
    HASH_NODE *symbol;
}

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
%token OPERATOR_NOT 

%token TK_IDENTIFIER 
%token LIT_INTEGER 
%token LIT_REAL 
%token LIT_CHAR 
%token LIT_STRING 

%token TOKEN_ERROR



%left OPERATOR_OR OPERATOR_AND
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'


 


%%

program: 
        |global_var_def ';' program 
        | func_def ';' program 
        ;

global_var_def:
        TK_IDENTIFIER ':' type value 
        | TK_IDENTIFIER ':' type '[' LIT_INTEGER']' 
        | TK_IDENTIFIER ':' type '[' LIT_INTEGER']'  vector_param_list 
	;       

vector_param_list:
        value
        | value vector_param_list
	;

func_def:   
        type TK_IDENTIFIER '(' func_def_param_list')' cmd 
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

func_call_param: expr
        ;

func_call_param_list: 
        | func_call_param func_call_param_list_rest

func_call_param_list_rest: 
        |',' func_call_param func_call_param_list_rest
        ;

block:  '{' cmd_list'}'
        ;

cmd_list:
        | cmd ';' cmd_list
        ;

cmd:    
        | TK_IDENTIFIER '=' expr
        | TK_IDENTIFIER'#'expr '=' expr
        | flux_control
        | KW_READ TK_IDENTIFIER
        | KW_PRINT print_list
        | KW_RETURN expr        
        | block
        ;

print_list:
        element
        | element print_list
	;

element:
        LIT_STRING
        | expr
	;

flux_control:
        KW_WHEN '('expr')' KW_THEN cmd
        | KW_WHEN '('expr')' KW_THEN cmd KW_ELSE cmd
        | KW_WHILE '('expr')' cmd
        | KW_FOR '('TK_IDENTIFIER '=' expr KW_TO expr')' cmd
        ;

expr:   expr '+' expr
        | expr '-' expr
        | expr '/' expr
        | expr '*' expr
        | expr '>' expr
        | expr '<' expr
        | expr OPERATOR_LE expr
        | expr OPERATOR_GE expr
        | expr OPERATOR_EQ expr
        | expr OPERATOR_NE expr
        | expr OPERATOR_AND expr
        | expr OPERATOR_OR expr        
        | '('expr')'
        | func_call
        | LIT_INTEGER
    	| LIT_REAL
        | LIT_CHAR
        | TK_IDENTIFIER
        | TK_IDENTIFIER '['expr']'
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
