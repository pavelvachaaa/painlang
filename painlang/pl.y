%{
#include <stdio.h>
#include <string.h>

#define MAX_VARS 100
typedef struct {
        char name[32];
        int value;
} Variable;

Variable symbolTable[MAX_VARS];
int varCount = 0;

void putVar(char* name, int value) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            symbolTable[i].value = value; 
            return;
        }
    }
    
    if (varCount < MAX_VARS) {
        strcpy(symbolTable[varCount].name, name);
        symbolTable[varCount].value = value;
        varCount++;
    }
}

int getVar(char *name) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return symbolTable[i].value;
        }
    }
    printf("Error: Undefined variable %s\n", name);
    return 0;
}


int yylex();
int yyparse();

void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
} 
  
int main()
{
        yyparse();
        return 0;
} 


%}
%union {
    int num;
    char *str;
}
%token <num> NUMBER DECLARE <str> IDENTIFIER ASSIGN SEMICOLON

%%


paingram: block 
        | declarations block;

declarations: declaration '\n'
        | declaration declarations;

declaration: varDeclaration;

varDeclaration: 
        DECLARE IDENTIFIER ASSIGN NUMBER SEMICOLON
        {
                putVar($2, $4); 
                printf("-> I just declared variable '%s' = %d\n", $2, $4);
        }
    ;

block: ;



%%


