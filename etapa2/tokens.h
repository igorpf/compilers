/*
* Lista dos tokens, com valores constantes associados.
* Este arquivo serah posterioremente substituido, nao acrescente nada.
* Os valores das constantes sao arbitrarios, mas nao podem ser alterados.
* Cada valor deve ser distinto e fora da escala ascii.
* Assim, nao conflitam entre si e com os tokens representados pelo proprio
* valor ascii de caracteres isolados.
*/
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
/* END OF FILE */

