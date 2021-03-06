%{
/*
Igor Pires Ferreira - 242267
Thor Castilhos Sanchotene - 242261 
*/
#include "hash.h"
#include "ast.h"
#include "y.tab.h"
#define TRUE 1
#define FALSE 0

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_IDENTIFIER 5

int isRunning();
int getLineNumber();
int yywrap();

int lineNumber = 1;
int running = TRUE;

%}



%x COMMENT

%%

byte                   {return KW_BYTE;}
short                  {return KW_SHORT;}
long                   {return KW_LONG;}
float                  {return KW_FLOAT;}
double                 {return KW_DOUBLE;}
when                   {return KW_WHEN;}
then                   {return KW_THEN;}
else                   {return KW_ELSE;}
while                  {return KW_WHILE;}
for                    {return KW_FOR;}
to                     {return KW_TO;}
read                   {return KW_READ;}
print                  {return KW_PRINT;}
return                 {return KW_RETURN;}
[-,;:(){}+*/<>=!&$#]   {return yytext[0];}
"["                    {return yytext[0];}
"]"                    {return yytext[0];}
"<="                   {return OPERATOR_LE;}
">="                   {return OPERATOR_GE;}
"=="                   {return OPERATOR_EQ;}
"!="                   {return OPERATOR_NE;}
"&&"                   {return OPERATOR_AND;}
"||"                   {return OPERATOR_OR;}
"\n"                   {lineNumber++;}
[A-Za-z_][A-Za-z_0-9]* {yylval.symbol=hashInsert(SYMBOL_IDENTIFIER, yytext);return TK_IDENTIFIER;}
[0-9]+\.[0-9]+         {yylval.symbol=hashInsert(SYMBOL_LIT_REAL, yytext);return LIT_REAL;}
[0-9]+                 {yylval.symbol=hashInsert(SYMBOL_LIT_INTEGER, yytext);return LIT_INTEGER;}
"'"."'"                {yylval.symbol=hashInsert(SYMBOL_LIT_CHAR, yytext);return LIT_CHAR;}
["][^\"]*["]           {yylval.symbol=hashInsert(SYMBOL_LIT_STRING, yytext);return LIT_STRING;}
" "
"\t"                
"//".*
"/*"                   BEGIN(COMMENT);
<COMMENT>\n            {lineNumber++;}
<COMMENT>.  
<COMMENT>"*/"          BEGIN(INITIAL);
.                      {return TOKEN_ERROR;}


%%
int isRunning(){ return running;}
int getLineNumber(){return lineNumber;}
int yywrap(){running = FALSE; return 1;}
