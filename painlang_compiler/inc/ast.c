#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode *create_program_node(ASTNode **statements, int count)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_PROGRAM;
    node->data.statement_list.statements = statements;
    node->data.statement_list.statement_count = count;
    return node;
}

ASTNode *create_statement_list_node(ASTNode **statements, int count)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_STATEMENT_LIST;
    node->data.statement_list.statements = statements;
    node->data.statement_list.statement_count = count;
    return node;
}

ASTNode *create_var_declaration_node(char *name, ASTNode *init_expr)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_VAR_DECLARATION;
    node->data.var_declaration.var_name = strdup(name);
    node->data.var_declaration.init_expr = init_expr;
    return node;
}

ASTNode *create_assignment_node(char *name, ASTNode *value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGNMENT;
    node->data.assignment.var_name = strdup(name);
    node->data.assignment.value = value;
    return node;
}

ASTNode *create_print_node(ASTNode *expr)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->data.print.expr = expr;
    return node;
}

ASTNode *create_if_node(ASTNode *condition, ASTNode *if_block, ASTNode *else_block)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->data.if_statement.condition = condition;
    node->data.if_statement.if_block = if_block;
    node->data.if_statement.else_block = else_block;
    return node;
}

ASTNode *create_binary_op_node(BinaryOpType op, ASTNode *left, ASTNode *right)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_BINARY_OP;
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

ASTNode *create_variable_node(char *name)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_VARIABLE;
    node->data.variable.name = strdup(name);
    return node;
}

ASTNode *create_number_node(int value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_NUMBER;
    node->data.number.value = value;
    return node;
}

ASTNode *create_condition_node(CondOpType op, ASTNode *left, ASTNode *right)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_CONDITION;
    node->data.condition.op = op;
    node->data.condition.left = left;
    node->data.condition.right = right;
    return node;
}

void free_ast(ASTNode *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case NODE_PROGRAM:
    case NODE_STATEMENT_LIST:
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
        {
            free_ast(node->data.statement_list.statements[i]);
        }
        free(node->data.statement_list.statements);
        break;

    case NODE_VAR_DECLARATION:
        free(node->data.var_declaration.var_name);
        if (node->data.var_declaration.init_expr)
        {
            free_ast(node->data.var_declaration.init_expr);
        }
        break;

    case NODE_ASSIGNMENT:
        free(node->data.assignment.var_name);
        free_ast(node->data.assignment.value);
        break;

    case NODE_PRINT:
        free_ast(node->data.print.expr);
        break;

    case NODE_IF:
        free_ast(node->data.if_statement.condition);
        free_ast(node->data.if_statement.if_block);
        if (node->data.if_statement.else_block)
        {
            free_ast(node->data.if_statement.else_block);
        }
        break;

    case NODE_BINARY_OP:
        free_ast(node->data.binary_op.left);
        free_ast(node->data.binary_op.right);
        break;

    case NODE_VARIABLE:
        free(node->data.variable.name);
        break;

    case NODE_NUMBER:
        break;

    case NODE_CONDITION:
        free_ast(node->data.condition.left);
        free_ast(node->data.condition.right);
        break;
    }

    free(node);
}