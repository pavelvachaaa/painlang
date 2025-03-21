%{
#include <stdio.h>
#include <string.h>
#include "prints.h"
#include "symbol_table.h"

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

    initSymbolTable();
    yyin = file;
    yyparse();
    fclose(file);
    freeSymbolTable();

    return 0;
}

%}

%union {
    int num;
    char *str;
}

%token <num> NUMBER DECLARE <str> IDENTIFIER ASSIGN SEMICOLON PRINT IF ELSE
%token EQUALS NOT_EQUALS GREAT_OR_EQUALS LESS_OR_EQUALS GREATER_THAN LESS_THAN
%type <num> expression term factor
%left '+' '-'
%left '*' '/'

%%
paingram: statementList;

statementList: statement 
            | statement statementList
            ;

// všechny takový keywordy jako ify a printy, ...
statement: assignment SEMICOLON
        | varDeclaration SEMICOLON
//        |  funDeclaration
        | ifStatement
        | printStatement SEMICOLON
        | block
        | empty // Jinak narazí kvulí <<ĘOF>> při čtení ze souboru
        ;

printStatement: PRINT '(' expression ')'
            {
                printf("%d\n", $3);
            }
            
 
assignment: IDENTIFIER ASSIGN expression
        {
            setSymbol($1, $3);
            debug_print("-> Assigned variable '%s' = %d \n", $1, $3);
        };

varDeclaration: DECLARE vardec;
vardec: IDENTIFIER 
        {
            // Defaultně řekneme, že proměnné jsou nula
            setSymbol($1, 0);
        }
        | IDENTIFIER ASSIGN expression
        {
            setSymbol($1, $3);
            debug_print("-> I just declared variable '%s' = %d\n", $1, $3);
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
    { $$ = getSymbol($1); }
    | '(' expression ')'
    { $$ = $2; }


ifStatement:  IF '(' condExpression ')' block 
            | IF '(' condExpression ')' block ELSE block 
condExpression: expression relop expression;
relop: EQUALS | NOT_EQUALS | GREAT_OR_EQUALS | LESS_OR_EQUALS | GREATER_THAN | LESS_THAN; 

block: '{' { enterScope();} statementList '}' { exitScope(); };
empty:;
%%


