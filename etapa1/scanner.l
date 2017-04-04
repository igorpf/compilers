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

%}



%x COMMENT

%%

word                {return KW_WORD;}
bool                {return KW_BOOL;}
byte                {return KW_BYTE;}
if                  {return KW_IF;}
then                {return KW_THEN;}
else                {return KW_ELSE;}
loop                {return KW_LOOP;}
input               {return KW_INPUT;}
return              {return KW_RETURN;}
output              {return KW_OUTPUT;}
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
[A-Za-z_][A-Za-z_0-9]*      {return TK_IDENTIFIER;}
"'"."'"             {return LIT_CHAR;}
["].*["]            {return LIT_STRING;}
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

int main () {
    
    int token;

    int i = 0;
    while(isRunning()) {   
        token =  yylex();
        switch(token) {
            case KW_WORD: 
            printf(" KW_WORD ");break;
            case KW_BOOL: 
            printf(" KW_BOOL ");break;
            case KW_BYTE: 
            printf(" KW_BYTE ");break;
            case KW_LOOP: 
            printf(" KW_LOOP ");break;
            case KW_INPUT: 
            printf(" KW_INPUT ");break;
            case KW_IF: 
            printf(" KW_IF ");break;
            case KW_THEN:
            printf(" KW_THEN ");break;
            case KW_ELSE:
            printf(" KW_ELSE ");break;
            case KW_RETURN: 
            printf(" KW_RETURN ");break;
            case KW_OUTPUT: 
            printf(" KW_OUTPUT ");break;
            case TK_IDENTIFIER: 
            printf(" TK_IDENTIFIER ");break;
            case LIT_INTEGER: 
            printf(" LIT_INTEGER ");break;
            case OPERATOR_LE: 
            printf(" OPERATOR_LE ");break;
            case OPERATOR_GE: 
            printf(" OPERATOR_GE ");break;
            case OPERATOR_EQ: 
            printf(" OPERATOR_EQ ");break;
            case OPERATOR_NE: 
            printf(" OPERATOR_NE ");break;
            case OPERATOR_AND: 
            printf(" OPERATOR_AND ");break;
            case OPERATOR_OR: 
            printf(" OPERATOR_OR ");break; 
            case LIT_TRUE: 
            printf(" LIT_TRUE ");break;
            case LIT_FALSE: 
            printf(" LIT_FALSE ");break;
            case LIT_CHAR: 
            printf(" LIT_CHAR ");break;
            case LIT_STRING: 
            printf(" LIT_STRING ");break;
            case TOKEN_ERROR: 
            printf(" TOKEN_ERROR ");break;
            default: 
            printf("%c", token);
        }       
    }
}
int isRunning(){ return running;}
int getLineNumber(){return lineNumber;}
int yywrap(){
    //running = FALSE; 
    return 1;}
