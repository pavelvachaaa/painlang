#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include "../symbol_table.h"

typedef enum
{
    NODE_PROGRAM,
    NODE_STATEMENT_LIST,
    NODE_VAR_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_FOR_LOOP,
    NODE_PRINT,
    NODE_IF,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_VARIABLE,
    NODE_IMPORT_STATEMENT,

    NODE_NUMBER,
    NODE_STRING,
    NODE_BOOLEAN,

    NODE_CONDITION,

    NODE_FUNCTION_DECLARATION,
    NODE_FUNCTION_CALL,
    NODE_RETURN,
} NodeType;

typedef enum
{
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_LOGICAL_AND,
    OP_LOGICAL_OR,
} BinaryOpType;

typedef enum
{
    OP_LOGICAL_NOT,
    OP_INCREMENT, // TODO: Pak upravit z předchozí double plus na op_increment kvůli optimalizaci instrukcí (dec, inc) místo x + 1 = > ...
    OP_DECREMENT
} UnaryOpType;

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
            UnaryOpType op;
            ASTNode *value;
        } unary_op;
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
            char *value;
        } string;

        struct
        {
            uint8_t value;
        } boolean;

        struct
        {
            ASTNode *init_expression; // deklarace proměnné
            ASTNode *condition;
            ASTNode *update;
            ASTNode *body;
        } for_loop;

        struct
        {
            CondOpType op;
            ASTNode *left;
            ASTNode *right;
        } condition;

        struct
        {
            char *name;
            char **param_names;
            DataType *param_types;
            DataType return_type;
            int param_count;
            ASTNode *body;
        } function_declaration;

        struct
        {
            char *func_name;
            ASTNode **arguments;
            int argument_count;
        } function_call;

        struct
        {
            ASTNode *expr;
        } return_statement;
    } data;
    DataType type_annotation;
};

ASTNode *create_program_node(ASTNode **statements, int count);
ASTNode *create_statement_list_node(ASTNode **statements, int count);
ASTNode *create_var_declaration_node(char *name, ASTNode *init_expr);
ASTNode *create_assignment_node(char *name, ASTNode *value);
ASTNode *create_print_node(ASTNode *expr);
ASTNode *create_if_node(ASTNode *condition, ASTNode *if_block, ASTNode *else_block);
ASTNode *create_binary_op_node(BinaryOpType op, ASTNode *left, ASTNode *right);
ASTNode *create_unary_op_node(UnaryOpType op, ASTNode *value);
ASTNode *create_variable_node(char *name);

ASTNode *create_number_node(int value);
ASTNode *create_string_node(char *value);
ASTNode *create_boolean_node(uint8_t value);

ASTNode *create_condition_node(CondOpType op, ASTNode *left, ASTNode *right);
ASTNode *create_for_loop_node(ASTNode *init_expression, ASTNode *condition, ASTNode *update, ASTNode *body);

ASTNode *create_function_declaration_node(char *name, char **param_names, int param_count, DataType *types, DataType return_type, ASTNode *body);
ASTNode *create_function_call_node(char *name, ASTNode **arguments, int arg_count);
ASTNode *create_return_node(ASTNode *expr);

ASTNode *evaluate_expression(ASTNode *node, SymbolTable *table);

void find_and_set_variables(ASTNode *node, SymbolTable *table);
ASTNode *optimize_ast(ASTNode *node, SymbolTable *table);
ASTNode *optimize_program(ASTNode *node, SymbolTable *table);

void free_ast(ASTNode *node);

void generate_nasm_code(ASTNode *node, const char *output_file);

#endif // AST_H