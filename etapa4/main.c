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
    
    if(argc <  2) {
        printf("Use etapa4 <in_file_name>\n");
        exit(1);
    }
    
    yyin = fopen(argv[1], "r");
    if(!yyin)
        exit(2);
    
    initMe();
    
    yyparse();

	hashPrint();
    

    fclose(yyin);
    
    exit(0);
}
