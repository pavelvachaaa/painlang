#ifndef AST_CREATOR_H
#define AST_CREATOR_H

#include "ast.h"

ASTNode *create_while_loop_node(ASTNode *condition, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_WHILE_LOOP;
    node->data.while_loop.condition = condition;
    node->data.while_loop.body = body;
    return node;
}

ASTNode *create_function_declaration_node(char *name, char **param_names, int param_count, DataType *types, DataType return_type, ASTNode *body)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION_DECLARATION;
    node->data.function_declaration.name = strdup(name);
    node->data.function_declaration.param_count = param_count;

    if (param_count > 0)
    {
        node->data.function_declaration.param_types = (DataType *)malloc(sizeof(DataType) * param_count);

        node->data.function_declaration.param_names = (char **)malloc(sizeof(char *) * param_count);
        for (int i = 0; i < param_count; i++)
        {
            node->data.function_declaration.param_names[i] = strdup(param_names[i]);
            node->data.function_declaration.param_types[i] = types[i];
        }
    }
    else
    {
        node->data.function_declaration.param_names = NULL;
        node->data.function_declaration.param_types = NULL;
    }

    node->data.function_declaration.return_type = return_type;
    node->data.function_declaration.body = body;

    return node;
}

ASTNode *create_function_call_node(char *name, ASTNode **arguments, int arg_count)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION_CALL;
    node->data.function_call.func_name = strdup(name);
    node->data.function_call.arguments = arguments;
    node->data.function_call.argument_count = arg_count;
    return node;
}

ASTNode *create_return_node(ASTNode *expr)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->data.return_statement.expr = expr;
    return node;
}

ASTNode *create_for_loop_node(ASTNode *init_expression, ASTNode *condition, ASTNode *update, ASTNode *body)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_FOR_LOOP;
    node->data.for_loop.init_expression = init_expression;
    node->data.for_loop.condition = condition;
    node->data.for_loop.update = update;
    node->data.for_loop.body = body;
    return node;
}

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

ASTNode *create_string_node(char *value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_STRING;
    node->data.string.value = strdup(value);
    return node;
}

ASTNode *create_boolean_node(u_int8_t value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_BOOLEAN;
    node->data.boolean.value = value;
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

ASTNode *create_unary_op_node(UnaryOpType op, ASTNode *value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_UNARY_OP;
    node->data.unary_op.value = value;
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

#endif