%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prints.h"
#include "./inc/ast.h"
#include "./inc/ast_printer.h"
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
SymbolTable *table = NULL;
int main(int argc, char **argv) {
        table = malloc(sizeof(SymbolTable));
        if(!table) {
            fprintf(stderr,"ale notak");
            return EXIT_FAILURE;
        }

        init_symbol_table(table);


    
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
        optimize_program(ast_root,table);
    }

    print_ast(ast_root);
    
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
    struct {
        char **names;
        int count;
    } param_list; // Pak to asi mergnout do sebe... Nebo taky ne ten param list musí být prostě jen var_declaration
    struct {
        ASTNode **args;
        int count;
    } arg_list;
}

%token <num> NUMBER DECLARE
%token <str> IDENTIFIER ASSIGN SEMICOLON PRINT IF ELSE FOR FUNCTION RETURN
%token EQUALS NOT_EQUALS GREAT_OR_EQUALS LESS_OR_EQUALS GREATER_THAN LESS_THAN

%type <node> program statementList statement assignment varDeclaration vardec
%type <node> printStatement expression term factor ifStatement block
%type <node> funDeclaration functionCall returnStatement
%type <node> condExpression
%type <node> forLoop forInitExpression
%type <cond_op> relop
%type <param_list> parameterList parameters
%type <arg_list> argumentList arguments

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
    | funDeclaration
    | functionCall SEMICOLON
    | returnStatement SEMICOLON
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
        // Jinak je problém s for loopem sakra
        // if(!lookup_variable(table, $1)) {
        //     printf("\n Proměnná %s neexistuje!\n", $1);
        //     return 1;
        // }

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

block: '{' { enter_scope(table); } statementList '}' { exit_scope(table);  }
    {
        $$ = $3;
    }
    ;



funDeclaration: FUNCTION IDENTIFIER '(' parameterList ')' block 
{
    // ten count kvůli tomu, že pojedeme scope odznova a potřebuji vědět kolik jich bude..
    $$ = create_function_declaration_node($2, $4.names, $4.count, $6);
    debug_print("Created FUNCTION_DECLARATION node for '%s' with %d parameters\n", $2, $4.count);

};

parameterList: parameters
    {
        $$ = $1;
    }
    | 
    {
        $$.names = NULL;
        $$.count = 0;    
    }
    ;

parameters: IDENTIFIER
    {
        $$.names = malloc(sizeof(char*));
        $$.names[0] = $1;
        $$.count = 1;
    }
    | IDENTIFIER ',' parameters
    {
      $$.names = malloc(sizeof(char*) * ($3.count + 1));
        $$.names[0] = $1;
        memcpy($$.names + 1, $3.names, sizeof(char*) * $3.count);
        $$.count = $3.count + 1;
        free($3.names);
    }
    ;

functionCall: IDENTIFIER '(' argumentList ')'
    {
        $$ = create_function_call_node($1, $3.args, $3.count);
        debug_print("Created FUNCTION_CALL node for '%s' with %d arguments\n", $1, $3.count);
    }
    ;

argumentList: arguments
    {
        $$ = $1;
    }
    | 
    {
        $$.args = NULL;
        $$.count = 0;
    }
    ;

arguments: expression
    {
        $$.args = malloc(sizeof(ASTNode*));
        $$.args[0] = $1;
        $$.count = 1;
    }
    | expression ',' arguments
    {
        $$.args = malloc(sizeof(ASTNode*) * ($3.count + 1));
        $$.args[0] = $1;
        memcpy($$.args + 1, $3.args, sizeof(ASTNode*) * $3.count);
        $$.count = $3.count + 1;
        free($3.args);
    }
    ;

returnStatement: RETURN expression
{
    $$ = create_return_node($2);
    debug_print("Created RETURN node\n");
}



empty:
    ;
%%