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

void init_symbol_table(SymbolTable *table)
{
    table->entries = NULL;
    table->count = 0;
}

SymbolEntry *lookup_variable(SymbolTable *table, const char *name)
{
    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->entries[i].name, name) == 0)
        {
            return &table->entries[i];
        }
    }
    return NULL;
}

void set_variable(SymbolTable *table, const char *name, int value, int is_constant)
{
    SymbolEntry *entry = lookup_variable(table, name);
    if (entry)
    {
        entry->value = value;
        entry->is_constant = is_constant;
    }
    else
    {
        table->count++;
        table->entries = realloc(table->entries, table->count * sizeof(SymbolEntry));
        table->entries[table->count - 1].name = strdup(name);
        table->entries[table->count - 1].value = value;
        table->entries[table->count - 1].is_constant = is_constant;
    }
}

ASTNode *evaluate_expression(ASTNode *node, SymbolTable *table)
{
    if (!node)
        return NULL;

    // Proměnná byla konstantní hodnota -> let x = 0;
    if (node->type == NODE_VARIABLE)
    {
        SymbolEntry *entry = lookup_variable(table, node->data.variable.name);
        if (entry && entry->is_constant)
        {
            return create_number_node(entry->value);
        }
    }

    if (node->type == NODE_BINARY_OP)
    {
        // evalujeme dokud nám nezbyde vlastně jen čísla, na kterých můžeme operovat
        node->data.binary_op.left = evaluate_expression(node->data.binary_op.left, table);
        node->data.binary_op.right = evaluate_expression(node->data.binary_op.right, table);

        if (node->data.binary_op.left->type == NODE_NUMBER && node->data.binary_op.right->type == NODE_NUMBER)
        {
            int left = node->data.binary_op.left->data.number.value;
            int right = node->data.binary_op.right->data.number.value;
            int result = 0;

            switch (node->data.binary_op.op)
            {
            case OP_ADD:
                result = left + right;
                break;
            case OP_SUBTRACT:
                result = left - right;
                break;
            case OP_MULTIPLY:
                result = left * right;
                break;
            case OP_DIVIDE:
                result = left / right;
                break;
            }

            free_ast(node->data.binary_op.left);
            free_ast(node->data.binary_op.right);
            return create_number_node(result);
        }
    }

    return node;
}

ASTNode *replace_variables(ASTNode *node, SymbolTable *table)
{
    if (!node)
        return NULL;

    node = evaluate_expression(node, table);

    // nahrazujeme v ifu proměnné za čísla
    if (node->type == NODE_VARIABLE)
    {
        SymbolEntry *entry = lookup_variable(table, node->data.variable.name);
        if (entry && entry->is_constant)
        {
            return create_number_node(entry->value);
        }
    }
    return node;
}

ASTNode *evaluate_condition(ASTNode *condition, SymbolTable *table)
{
    if (!condition)
        return NULL;

    condition->data.condition.left = replace_variables(condition->data.condition.left, table);
    condition->data.condition.right = replace_variables(condition->data.condition.right, table);

    if (condition->type == NODE_CONDITION &&
        condition->data.condition.left->type == NODE_NUMBER &&
        condition->data.condition.right->type == NODE_NUMBER)
    {
        int left = condition->data.condition.left->data.number.value;
        int right = condition->data.condition.right->data.number.value;
        int result = 0;

        switch (condition->data.condition.op)
        {
        case COND_GREATER_THAN:
            result = left > right;
            break;
        case COND_LESS_THAN:
            result = left < right;
            break;
        case COND_EQUALS:
            result = left == right;
            break;
        case COND_NOT_EQUALS:
            result = left != right;
            break;
        case COND_GREATER_OR_EQUALS:
            result = left >= right;
            break;
        case COND_LESS_OR_EQUALS:
            result = left <= right;
            break;
        }

        return create_number_node(result);
    }
    return condition;
}

// CPG optimalizování
ASTNode *optimize_ast(ASTNode *node, SymbolTable *table)
{
    if (!node)
        return NULL;

    switch (node->type)
    {
    case NODE_VAR_DECLARATION:
        // Máš konstantní hodnout?
        if (node->data.var_declaration.init_expr && node->data.var_declaration.init_expr->type == NODE_NUMBER)
        {
            set_variable(table, node->data.var_declaration.var_name, node->data.var_declaration.init_expr->data.number.value, 1);
        }
        break;

    case NODE_ASSIGNMENT:
        if (node->data.assignment.value->type == NODE_NUMBER)
        {
            set_variable(table, node->data.assignment.var_name, node->data.assignment.value->data.number.value, 1);
        }
        else
        {
            set_variable(table, node->data.assignment.var_name, 0, 0); // Nejsi konstantní
        }
        break;

    case NODE_IF:
        node->data.if_statement.condition = evaluate_condition(node->data.if_statement.condition, table);
        if (node->data.if_statement.condition->type == NODE_NUMBER)
        {
            int condition_value = node->data.if_statement.condition->data.number.value;
            free_ast(node->data.if_statement.condition);
            return condition_value ? optimize_ast(node->data.if_statement.if_block, table)
                                   : optimize_ast(node->data.if_statement.else_block, table);
        }
        break;

    case NODE_STATEMENT_LIST:
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
        {
            node->data.statement_list.statements[i] = optimize_ast(node->data.statement_list.statements[i], table);
        }
        break;

    case NODE_BINARY_OP:
        node->data.binary_op.left = optimize_ast(node->data.binary_op.left, table);
        node->data.binary_op.right = optimize_ast(node->data.binary_op.right, table);
        break;

    case NODE_VARIABLE:
        return replace_variables(node, table);

    default:
        break;
    }
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