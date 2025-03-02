#ifndef AST_H
#define AST_H

#include <stdlib.h>

typedef enum
{
    NODE_PROGRAM,
    NODE_STATEMENT_LIST,
    NODE_VAR_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_PRINT,
    NODE_IF,
    NODE_BINARY_OP,
    NODE_VARIABLE,
    NODE_NUMBER,
    NODE_CONDITION
} NodeType;

typedef enum
{
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE
} BinaryOpType;

typedef enum
{
    COND_EQUALS,
    COND_NOT_EQUALS,
    COND_GREATER_THAN,
    COND_LESS_THAN,
    COND_GREATER_OR_EQUALS,
    COND_LESS_OR_EQUALS
} CondOpType;

typedef struct ASTNode ASTNode;

struct ASTNode
{
    NodeType type;
    union
    {
        struct
        {
            ASTNode **statements;
            int statement_count;
        } statement_list;

        struct
        {
            char *var_name;
            ASTNode *init_expr; 
        } var_declaration;

        struct
        {
            char *var_name;
            ASTNode *value;
        } assignment;

        struct
        {
            ASTNode *expr;
        } print;

        struct
        {
            ASTNode *condition;
            ASTNode *if_block;
            ASTNode *else_block; 
        } if_statement;

        struct
        {
            BinaryOpType op;
            ASTNode *left;
            ASTNode *right;
        } binary_op;

        struct
        {
            char *name;
        } variable;

        struct
        {
            int value;
        } number;

        struct
        {
            CondOpType op;
            ASTNode *left;
            ASTNode *right;
        } condition;
    } data;
};

typedef struct {
    char *name;
    int value;
    int is_constant;
} SymbolEntry;

typedef struct {
    SymbolEntry *entries;
    int count;
} SymbolTable;



ASTNode *create_program_node(ASTNode **statements, int count);
ASTNode *create_statement_list_node(ASTNode **statements, int count);
ASTNode *create_var_declaration_node(char *name, ASTNode *init_expr);
ASTNode *create_assignment_node(char *name, ASTNode *value);
ASTNode *create_print_node(ASTNode *expr);
ASTNode *create_if_node(ASTNode *condition, ASTNode *if_block, ASTNode *else_block);
ASTNode *create_binary_op_node(BinaryOpType op, ASTNode *left, ASTNode *right);
ASTNode *create_variable_node(char *name);
ASTNode *create_number_node(int value);
ASTNode *create_condition_node(CondOpType op, ASTNode *left, ASTNode *right);
ASTNode *optimize_ast(ASTNode *node, SymbolTable* table);
void init_symbol_table(SymbolTable *table);

void free_ast(ASTNode *node);

void generate_nasm_code(ASTNode *node, const char *output_file);

#endif // AST_H