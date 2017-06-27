%{
#include<stdlib.h>
#include<stdio.h>
#include "hash.h"
#include "ast.h"
#include "semantic.h"
#include "tacs.h"
extern FILE * yyin;

%}

%union {
    HASH_NODE *symbol;
    AST* ast;
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

%token <symbol> TK_IDENTIFIER 
%token <symbol> LIT_INTEGER 
%token <symbol> LIT_REAL 
%token <symbol> LIT_CHAR 
%token <symbol> LIT_STRING 

%token TOKEN_ERROR



%left OPERATOR_OR OPERATOR_AND
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'


%type <ast> value type
%type <ast> expr 
%type <ast> cmd 
%type <ast> cmd_list 
%type <ast> program
%type <ast> vector_param_list
%type <ast> global_var_def
%type <ast> func_def
%type <ast> func_def_param_list
%type <ast> func_def_param_list_rest
%type <ast> func_def_param
%type <ast> func_call
%type <ast> func_call_param
%type <ast> func_call_param_list
%type <ast> func_call_param_list_rest
%type <ast> block
%type <ast> print_list
%type <ast> element
%type <ast> flux_control
%type <ast> start
%type <ast> lit_int

%%

start:	program   {astPrint(0, $$=$1);
                   astPrintSrc($$);
                   semanticSetDeclarations($$);
                   hashCheckUndeclared();
                   checkUtilization($$);
                   checkDataTypes($$);
                   tacPrintForward(tacReverse(tacGenerate($$)));
                  }
	;
program: 
        global_var_def ';' program     {$$=astCreate(AST_PROGRAM,0, $1,$3,0,0);}
        | func_def ';' program         {$$=astCreate(AST_PROGRAM,0, $1,$3,0,0);}
        |                              {$$=0;}
        ;

global_var_def:
        TK_IDENTIFIER ':' type value                                   {$$=astCreate(AST_VAR_DEF,$1, $3,$4,0,0);}
        | TK_IDENTIFIER ':' type '[' lit_int']'                    {$$=astCreate(AST_VECTOR_DEF,$1, $3,$5,0,0);}
        | TK_IDENTIFIER ':' type '[' lit_int']' vector_param_list  {$$=astCreate(AST_INIT_VECTOR_DEF,$1, $3,$5,$7,0);}
	;       

vector_param_list:
        value                       
        | value vector_param_list   {$$=astCreate(AST_VECTOR_PARAM_LIST,0, $1,$2,0,0);}  
	;

func_def:   
        type TK_IDENTIFIER '(' func_def_param_list')' cmd  {$$=astCreate(AST_FUNC_DEF,$2, $1,$4,$6,0);}
        ;

func_def_param_list:  
        func_def_param func_def_param_list_rest  {$$=astCreate(AST_FUNC_DEF_PARAM_LIST,0, $1,$2,0,0);}
        |                                        {$$=0;}
        ;

func_def_param_list_rest:  
       ',' func_def_param func_def_param_list_rest   {$$=astCreate(AST_FUNC_DEF_PARAM_LIST_REST,0, $2,$3,0,0);}
       |                                             {$$=0;}
        ;
func_def_param:  type TK_IDENTIFIER  {$$=astCreate(AST_FUNC_DEF_PARAM,$2, $1,0,0,0);}
        ;

func_call:   
        TK_IDENTIFIER '(' func_call_param_list')'  {$$=astCreate(AST_FUNC_CALL,$1, $3,0,0,0);}
        ;        

func_call_param: expr
        ;

func_call_param_list:                               
        func_call_param func_call_param_list_rest {$$=astCreate(AST_FUNC_CALL_PARAM_LIST,0, $1,$2,0,0);}
        |                                         {$$=0;}
           
	;

func_call_param_list_rest: 
        ',' func_call_param func_call_param_list_rest {$$=astCreate(AST_FUNC_CALL_PARAM_LIST_REST,0, $2,$3,0,0);}
        |                                             {$$=0;}
        ;

block:  '{' cmd_list'}'   {$$=astCreate(AST_CMD_BLOCK,0, $2,0,0,0);}
        ;

cmd_list: 
        cmd ';' cmd_list       {$$=astCreate(AST_CMDL,0, $1,$3,0,0);}
        |                      {$$=0;}
        ;

cmd:    
        TK_IDENTIFIER '=' expr           {$$=astCreate(AST_VAR_ASSIGNMENT,$1, $3,0,0,0);}
        | TK_IDENTIFIER'#'expr '=' expr  {$$=astCreate(AST_VECTOR_ASSIGNMENT,$1, $3,$5,0,0);}
        | flux_control
        | KW_READ TK_IDENTIFIER          {$$=astCreate(AST_READ,$2, 0,0,0,0);}
        | KW_PRINT print_list            {$$=astCreate(AST_PRINT,0, $2,0,0,0);}
        | KW_RETURN expr                 {$$=astCreate(AST_RETURN,0, $2,0,0,0);}
        | block
        |                                {$$=0;}
        ;

print_list:
        element               {$$=astCreate(AST_PRINT_LIST,0, $1,0,0,0);}
        | element print_list  {$$=astCreate(AST_PRINT_LIST,0, $1,$2,0,0);}
	;

element:
        LIT_STRING            {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0);} 
        | expr                
	;

flux_control:
        KW_WHEN '('expr')' KW_THEN cmd                        {$$=astCreate(AST_WHEN,0, $3,$6,0,0);}
        | KW_WHEN '('expr')' KW_THEN cmd KW_ELSE cmd          {$$=astCreate(AST_WHEN_ELSE,0, $3,$6,$8,0);}
        | KW_WHILE '('expr')' cmd                             {$$=astCreate(AST_WHILE,0, $3,$5,0,0);}
        | KW_FOR '('TK_IDENTIFIER '=' expr KW_TO expr')' cmd  {$$=astCreate(AST_FOR,$3, $5,$7,$9,0);}
        ;

expr:   expr '+' expr               {$$=astCreate(AST_ADD,0, $1,$3,0,0);}
        | expr '-' expr             {$$=astCreate(AST_SUB,0, $1,$3,0,0);}
        | expr '/' expr             {$$=astCreate(AST_DIV,0, $1,$3,0,0);}
        | expr '*' expr             {$$=astCreate(AST_MULT,0, $1,$3,0,0);}
        | expr '>' expr             {$$=astCreate(AST_OP_GREATER,0, $1,$3,0,0);}
        | expr '<' expr             {$$=astCreate(AST_OP_LESS,0, $1,$3,0,0);}
        | expr OPERATOR_LE expr     {$$=astCreate(AST_OP_LE,0, $1,$3,0,0);}
        | expr OPERATOR_GE expr     {$$=astCreate(AST_OP_GE,0, $1,$3,0,0);}
        | expr OPERATOR_EQ expr     {$$=astCreate(AST_OP_EQ,0, $1,$3,0,0);}
        | expr OPERATOR_NE expr     {$$=astCreate(AST_OP_NE,0, $1,$3,0,0);}
        | expr OPERATOR_AND expr    {$$=astCreate(AST_OP_AND,0, $1,$3,0,0);}
        | expr OPERATOR_OR expr     {$$=astCreate(AST_OP_OR,0, $1,$3,0,0);}      
        | '('expr')'                {$$=astCreate(AST_PARENTHESES,0, $2,0,0,0);}
        | func_call
        | LIT_INTEGER               {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0);}
    	| LIT_REAL                  {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0);}
        | LIT_CHAR                  {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0);}
        | TK_IDENTIFIER             {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0);}
        | TK_IDENTIFIER '['expr']'  {$$=astCreate(AST_VECTOR_ACCESS,$1, $3,0,0,0);}
        ;


type:   KW_BYTE     { $$ = astCreate(AST_T_BYT, 0, 0, 0, 0, 0); }
        | KW_SHORT  { $$ = astCreate(AST_T_SHO, 0, 0, 0, 0, 0); }    
        | KW_LONG   { $$ = astCreate(AST_T_LON, 0, 0, 0, 0, 0); }
        | KW_FLOAT  { $$ = astCreate(AST_T_FLO, 0, 0, 0, 0, 0); }
        | KW_DOUBLE { $$ = astCreate(AST_T_DOU, 0, 0, 0, 0, 0); }
        ;


value:  LIT_INTEGER   {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0); }
        | LIT_REAL    {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0); }
        | LIT_CHAR    {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0); }
        | LIT_STRING  {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0); }
        ;

lit_int:  LIT_INTEGER {$$=astCreate(AST_SYMBOL,$1, 0,0,0,0);}
          ;

%%
int yyerror(char *what){
	fprintf(stderr, "Syntax error. Line %d\n", getLineNumber());
	exit(3);
}
