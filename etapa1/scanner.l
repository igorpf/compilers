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

int                 {return KW_INT;}
float               {return KW_FLOAT;}
bool                {return KW_BOOL;}
char                {return KW_CHAR;}
if                  {return KW_IF;}
then                {return KW_THEN;}
else                {return KW_ELSE;}
for                 {return KW_FOR;}
read                {return KW_READ;}
return              {return KW_RETURN;}
print               {return KW_PRINT;}
[-,;:(){}+*/<>=!&$] {return yytext[0];}
"["                 {return yytext[0];}
"]"                 {return yytext[0];}
"<="                {return OPERATOR_LE;}
">="                {return OPERATOR_GE;}
"=="                {return OPERATOR_EQ;}
"!="                {return OPERATOR_NE;}
"&&"                {return OPERATOR_AND;}
"||"                {return OPERATOR_OR;}
"\n"                {lineNumber++;}
[0-9]+              {return LIT_INTEGER;}
FALSE               {return LIT_FALSE;}
TRUE                {return LIT_TRUE;}
[A-Za-z][A-Za-z_0-9]*      {hashInsert(TK_IDENTIFIER, yytext);return TK_IDENTIFIER;}
"'"."'"             {hashInsert(LIT_CHAR, yytext);return LIT_CHAR;}
["][^\"]*["]            {hashInsert(LIT_STRING, yytext);return LIT_STRING;}
" "
"\t"                
"//".*
"/*"                BEGIN(COMMENT);
<COMMENT>\n         {lineNumber++;}
<COMMENT>.  
<COMMENT>"*/"           BEGIN(INITIAL);
[0-9]+[A-Za-z_]+[A-Za-z_0-9]*   {return TOKEN_ERROR;}
.               {return TOKEN_ERROR;}


%%
int isRunning(){ return running;}
int getLineNumber(){return lineNumber;}
int yywrap(){running = FALSE; return 1;}
