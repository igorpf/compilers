%{
#include "hash.h"
#include "tokens.h"

#define TRUE 1
#define FALSE 0

int isRunning();
int getLineNumber();
int yywrap();

int lineNumber;
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
[A-Za-z_][A-Za-z_0-9]* {hashInsert(TK_IDENTIFIER, yytext);return TK_IDENTIFIER;}
[0-9]+\.[0-9]+         {hashInsert(LIT_REAL, yytext);return LIT_REAL;}
[0-9]+                 {hashInsert(LIT_INTEGER, yytext);return LIT_INTEGER;}
"'"."'"                {hashInsert(LIT_CHAR, yytext);return LIT_CHAR;}
["][^\"]*["]           {hashInsert(LIT_STRING, yytext);return LIT_STRING;}
" "
"\t"                
"//".*
"/*"                   BEGIN(COMMENT);
<COMMENT>\n            {lineNumber++;}
<COMMENT>.  
<COMMENT>"*/"          BEGIN(INITIAL);
[0-9]+[A-Za-z_]+[A-Za-z_0-9]* {return TOKEN_ERROR;}
.                      {return TOKEN_ERROR;}


%%
int isRunning(){ return running;}
int getLineNumber(){return lineNumber;}
int yywrap(){running = FALSE; return 1;}
