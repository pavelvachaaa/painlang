%{
#include <stdio.h>
#include <string.h>

// Miluju makra
//#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        do { printf(fmt, __VA_ARGS__); } while (0)
#else
    #define DEBUG_PRINT(fmt, ...) 
#endif


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
    printf("Error: Undefined variable name: %s\n", name);
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

extern FILE *yyin;
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening the file");
        return 1;
    }

    yyin = file;

    yyparse();
    fclose(file);

    return 0;
}

%}




%union {
    int num;
    char *str;
}

%token <num> NUMBER DECLARE <str> IDENTIFIER ASSIGN SEMICOLON PRINT
%type <num> expression term factor
%left '+' '-'
%left '*' '/'

%%
paingram: statementList;

statementList: statement 
            | statement SEMICOLON statementList
            ;

// všechny takový keywordy jako ify a printy, ...
statement: assignment
        | varDeclaration
//        |  funDeclaration
        | printStatement
        | block
        | empty // Jinak narazí kvulí <<ĘOF>> při čtení ze souboru
        ;

printStatement: PRINT '(' expression ')'
            {
                printf("%d\n", $3);
            }
            
 
assignment: IDENTIFIER ASSIGN expression
        {
            putVar($1, $3);
            DEBUG_PRINT("-> Assigned variable '%s' = %d\n", $1, $3);
        };

varDeclaration: DECLARE vardec;
vardec: IDENTIFIER 
        {
        // Defaultně řekneme, že proměnné jsou nula
            putVar($1, 0); 
        }
        | IDENTIFIER ASSIGN expression
        {
            putVar($1, $3); 
            DEBUG_PRINT("-> I just declared variable '%s' = %d\n", $1, $3);
        }

expression: expression '+' term
    { $$ = $1 + $3; }
    | expression '-' term
    { $$ = $1 - $3; }
    | term
    { $$ = $1; }
    // Když jsou oba operandy konstantní -> můžeme je hned spočítat a nečekat na runtime
        | NUMBER '+' NUMBER { $$ = $1 + $3; }
        | NUMBER '-' NUMBER { $$ = $1 - $3; }
        | NUMBER '*' NUMBER { $$ = $1 * $3; }
        | NUMBER '/' NUMBER { $$ = $1 / $3; }

term: term '*' factor
    { $$ = $1 * $3; }
    | term '/' factor
    { $$ = $1 / $3; }
    | factor
    { $$ = $1; }
    ;

factor: NUMBER
    { $$ = $1; }
    | IDENTIFIER
    { $$ = getVar($1); }
    | '(' expression ')'
    { $$ = $2; }



block: '{' statementList '}'
empty:;
%%


