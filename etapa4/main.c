/*
Igor Pires Ferreira - 242267
Thor Castilhos Sanchotene - 242261 
*/

#include "hash.h"
#include "ast.h"
#include "lex.yy.h"
#include "y.tab.h"


int isRunning();
int getLineNumber();
int yywrap();
void initMe();
int yyparse(void);


int main(int argc, char **argv)
{
    
    if(argc <  3) {
        printf("Use etapa3 <in_file_name> <out_file_name>\n");
        exit(1);
    }
    
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");
    
    initMe();
    
    yyparse();
    

    fclose(yyin);
    
    exit(0);
}
