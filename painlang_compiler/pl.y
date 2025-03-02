%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prints.h"
#include "./inc/symbol_table.h"
#include "./inc/ast.h"
#include "./inc/ir.c"

int yylex();
int yyparse();
void yyerror(const char *str) {
    fprintf(stderr, "error: %s\n", str);
}

int yywrap() {
    return 1;
}

extern FILE *yyin;

ASTNode *ast_root = NULL;

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> [<output_file>]\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening the input file");
        return 1;
    }
    
    initSymbolTable();
    yyin = file;
    yyparse();
    fclose(file);
    
    const char *output_file = (argc == 3) ? argv[2] : "output.asm";

    SymbolTable *table;
    init_symbol_table(table);
    // Tohle asi udělam raději #define -> nejsem si jistý jestli to zanechává semantiku správně - neodladil jsem to
    optimize_ast(ast_root, table);

    // TODO: Z AST vygenerovat TAC (IR)


    generate_nasm_code(ast_root, output_file);
    
    free_ast(ast_root);
    freeSymbolTable();
    
    return 0;
}
%}

%union {
    int num;
    char *str;
    ASTNode *node;
    CondOpType cond_op;
}

%token <num> NUMBER DECLARE
%token <str> IDENTIFIER ASSIGN SEMICOLON PRINT IF ELSE
%token EQUALS NOT_EQUALS GREAT_OR_EQUALS LESS_OR_EQUALS GREATER_THAN LESS_THAN

%type <node> program statementList statement assignment varDeclaration vardec
%type <node> printStatement expression term factor ifStatement block
%type <node> condExpression
%type <cond_op> relop

%left '+' '-'
%left '*' '/'

%%
program: statementList
    {
        ast_root = $1;
    }
    ;

statementList: statement
    {
        ASTNode **statements = malloc(sizeof(ASTNode*));
        statements[0] = $1;
        $$ = create_statement_list_node(statements, 1);
    }
    | statement statementList
    {
        // přidáme příkaz na začátek a uděláme pro něj místo
        int count = $2->data.statement_list.statement_count + 1;
        ASTNode **statements = malloc(sizeof(ASTNode*) * count);
        
        statements[0] = $1;
        for (int i = 0; i < $2->data.statement_list.statement_count; i++) {
            statements[i+1] = $2->data.statement_list.statements[i];
        }
        
        $$ = create_statement_list_node(statements, count);
        
        free($2->data.statement_list.statements);
        free($2);
    }
    ;

statement: assignment SEMICOLON
    {
        $$ = $1;
    }
    | varDeclaration SEMICOLON
    {
        $$ = $1;
    }
    | ifStatement
    {
        $$ = $1;
    }
    | printStatement SEMICOLON
    {
        $$ = $1;
    }
    | block
    {
        $$ = $1;
    }
    | empty
    {
        $$ = NULL;
    }
    ;

printStatement: PRINT '(' expression ')'
    {
        $$ = create_print_node($3);
        debug_print("Created PRINT node\n");
    }
    ;

assignment: IDENTIFIER ASSIGN expression
    {
        $$ = create_assignment_node($1, $3);
        debug_print("Created ASSIGNMENT node for '%s'\n", $1);
    }
    ;

varDeclaration: DECLARE vardec
    {
        $$ = $2;
    }
    ;

vardec: IDENTIFIER
    {
        $$ = create_var_declaration_node($1, NULL);
        debug_print("Created VAR_DECLARATION node for '%s' with no init\n", $1);
    }
    | IDENTIFIER ASSIGN expression
    {
        $$ = create_var_declaration_node($1, $3);
        debug_print("Created VAR_DECLARATION node for '%s' with init\n", $1);
    }
    ;

expression: expression '+' term
    {
        $$ = create_binary_op_node(OP_ADD, $1, $3);
    }
    | expression '-' term
    {
        $$ = create_binary_op_node(OP_SUBTRACT, $1, $3);
    }
    | term
    {
        $$ = $1;
    }
    // Díky tomuhle můžeme spočítat hned hodnotu a nečekat
    | NUMBER '+' NUMBER
    {
        $$ = create_number_node($1 + $3);
    }
    | NUMBER '-' NUMBER
    {
        $$ = create_number_node($1 - $3);
    }
    | NUMBER '*' NUMBER
    {
        $$ = create_number_node($1 * $3);
    }
    | NUMBER '/' NUMBER
    {
        $$ = create_number_node($1 / $3);
    }
    ;

term: term '*' factor
    {
        $$ = create_binary_op_node(OP_MULTIPLY, $1, $3);
    }
    | term '/' factor
    {
        $$ = create_binary_op_node(OP_DIVIDE, $1, $3);
    }
    | factor
    {
        $$ = $1;
    }
    ;

factor: NUMBER
    {
        $$ = create_number_node($1);
    }
    | IDENTIFIER
    {
        $$ = create_variable_node($1);
    }
    | '(' expression ')'
    {
        $$ = $2;
    }
    ;

ifStatement: IF '(' condExpression ')' block
    {
        $$ = create_if_node($3, $5, NULL);
    }
    | IF '(' condExpression ')' block ELSE block
    {
        $$ = create_if_node($3, $5, $7);
    }
    ;

condExpression: expression relop expression
    {
        $$ = create_condition_node($2, $1, $3);
    }
    ;

relop: EQUALS
    {
        $$ = COND_EQUALS;
    }
    | NOT_EQUALS
    {
        $$ = COND_NOT_EQUALS;
    }
    | GREAT_OR_EQUALS
    {
        $$ = COND_GREATER_OR_EQUALS;
    }
    | LESS_OR_EQUALS
    {
        $$ = COND_LESS_OR_EQUALS;
    }
    | GREATER_THAN
    {
        $$ = COND_GREATER_THAN;
    }
    | LESS_THAN
    {
        $$ = COND_LESS_THAN;
    }
    ;

block: '{' { enterScope(); } statementList '}' { exitScope(); }
    {
        $$ = $3;
    }
    ;

empty:
    ;
%%