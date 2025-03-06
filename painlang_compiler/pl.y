%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prints.h"
#include "./inc/symbol_table.h"
#include "./inc/ast.h"
#include "./inc/ir.h"
#include <unistd.h>

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


void print_usage(const char *prog_name) {
    fprintf(stderr, "Použití: %s -i input_file [-o output-file] [-O] [-m ir_file]  \n", prog_name);
}

int main(int argc, char **argv) {
    const char *output_file = NULL;
    const char *ir_file = NULL;
    const char *input_file = NULL;
    
    int optimizeLevel = 0;

    int opt;
    while ((opt = getopt(argc, argv, "i:o:m:O")) != -1) {
        switch (opt) {
            case 'm': // mezikod
                ir_file = optarg;
                break;
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'O':
                optimizeLevel = 1;
                break;
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (!input_file) {
        fprintf(stderr, "Error: Potřebuji vstupní soubor.\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if(!output_file) {
        output_file = "output.asm";
    }
    
    if(!ir_file) {
        ir_file = "output.ir";
    }

    FILE *file = fopen(input_file, "r");
    if (!file) {
        perror("ale vole");
        return EXIT_FAILURE;
    }

    yyin = file;
    yyparse();
    fclose(file);

    // ten level pak passovat do funkce a podle toho rozhodovat jak optimalizovat
    if (optimizeLevel == 1) {
        SymbolTable *table = malloc(sizeof(SymbolTable));
        if(!table) {
            fprintf(stderr,"ale notak");
            return EXIT_FAILURE;
        }

        init_symbol_table(table);
        optimize_ast(ast_root, table);
    }

    // IR reprezentace a struktura
    IRProgram *program = malloc(sizeof(IRProgram));
    if (!program) {
        fprintf(stderr,"dopíči už");
        return EXIT_FAILURE;
    }

    ir_init(program);
    generate_ir_from_ast(ast_root, program);
    output_ir_to_file(program, ir_file);

    //NASM
    generate_nasm_from_ir(program, output_file);
    //generate_nasm_code(ast_root, output_file);
    
    ir_free(program);
    free_ast(ast_root);
    //freeSymbolTable();
    
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
%token <str> IDENTIFIER ASSIGN SEMICOLON PRINT IF ELSE FOR
%token EQUALS NOT_EQUALS GREAT_OR_EQUALS LESS_OR_EQUALS GREATER_THAN LESS_THAN

%type <node> program statementList statement assignment varDeclaration vardec
%type <node> printStatement expression term factor ifStatement block
%type <node> condExpression
%type <node> forLoop forInitExpression
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
    | forLoop
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

forLoop: FOR '(' forInitExpression SEMICOLON condExpression SEMICOLON assignment ')' block
    {
        $$ = create_for_loop_node($3, $5, $7, $9);
        debug_print("Created FOR_LOOP node\n");
    }
    ;

forInitExpression: assignment { $$ = $1; }
       | varDeclaration { $$ = $1; }
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