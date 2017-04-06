%{
#define KW_WORD       256
#define KW_BOOL       258
#define KW_BYTE       259
#define KW_IF         261
#define KW_THEN       262
#define KW_ELSE       263
#define KW_LOOP       264
#define KW_INPUT      266
#define KW_RETURN     267
#define KW_OUTPUT     268

#define OPERATOR_LE   270
#define OPERATOR_GE   271
#define OPERATOR_EQ   272
#define OPERATOR_NE   273
#define OPERATOR_AND  274
#define OPERATOR_OR   275

#define TK_IDENTIFIER 280
#define LIT_INTEGER   281
#define LIT_FALSE     283
#define LIT_TRUE      284
#define LIT_CHAR      285
#define LIT_STRING    286

#define TOKEN_ERROR   290

#define TRUE 1
#define FALSE 0

int isRunning();
int getLineNumber();
int yywrap();

int lineNumber;
int running = TRUE;

#include "hash.h"
#include "tokens.h"

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
[A-Za-z][A-Za-z_0-9]*      {/*hashInsert(TK_IDENTIFIER, yytext);*/return TK_IDENTIFIER;}
"'"."'"             {/*hashInsert(LIT_CHAR, yytext);*/return LIT_CHAR;}
["][^\"]*["]            {/*hashInsert(LIT_STRING, yytext);*/return LIT_STRING;}
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
#include "main.c"
int isRunning(){ return running;}
int getLineNumber(){return lineNumber;}
int yywrap(){running = FALSE; return 1;}