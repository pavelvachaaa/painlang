#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

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
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION_CALL;
    node->data.function_call.func_name = strdup(name);
    node->data.function_call.arguments = arguments;
    node->data.function_call.argument_count = arg_count;
    return node;
}

ASTNode *create_return_node(ASTNode *expr)
{
    ASTNode *node = malloc(sizeof(ASTNode));
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

ASTNode *create_boolean_node(uint8_t value)
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

DataType ast_to_st_type(NodeType type)
{
    switch (type)
    {
    case NODE_STRING:
        return TYPE_STRING;
        break;
    case NODE_NUMBER:
        return TYPE_NUMBER;
        break;
    case NODE_BOOLEAN:
        return TYPE_BOOLEAN;
        break;

    default:
        return TYPE_UNKNOWN;
        break;
    }
}

ASTNode *evaluate_expression(ASTNode *node, SymbolTable *table)
{

    if (!node)
        return NULL;

    if (node->type == NODE_VARIABLE)
    {

        printf("THIS MOTHER FUCKER! %s\n", node->data.variable.name);

        SymbolEntry *entry = lookup_variable(table, node->data.variable.name);
        if (entry)
        {
            if (entry->data_type == TYPE_NUMBER)
            {
                return create_number_node(entry->value);
            }
            else if (entry->data_type == TYPE_STRING)
            {
                return create_string_node(entry->string_value);
            }
            else if (entry->data_type == TYPE_BOOLEAN)
            {
                printf("THIS MOTHER FUCKER!");

                return create_boolean_node(entry->boolean_value);
            }
        }
    }

    if (node->type == NODE_ASSIGNMENT)
    {

        SymbolEntry *entry = lookup_variable(table, node->data.assignment.var_name);
        if (entry)
        {

            ASTNode *evaluated_value = evaluate_expression(node->data.assignment.value, table);

            printf("Zde jsem a %d", entry->data_type);

            if (evaluated_value->type == NODE_NUMBER)
            {
                entry->value = evaluated_value->data.number.value;
                entry->data_type = TYPE_NUMBER;
            }
            else if (evaluated_value->type == NODE_STRING)
            {
                entry->string_value = strdup(evaluated_value->data.string.value);
                entry->data_type = TYPE_STRING;
            }
            else if (evaluated_value->type == NODE_BOOLEAN)
            {
                entry->boolean_value = evaluated_value->data.boolean.value;
                entry->data_type = TYPE_BOOLEAN;
            }
            entry->is_initialized = 1;

            if (evaluated_value != node->data.assignment.value)
            {
                free_ast(evaluated_value);
            }
            entry->is_initialized = 1;
        }
    }

    if (node->type == NODE_UNARY_OP)
    {

        node->data.unary_op.value = evaluate_expression(node->data.unary_op.value, table);

        if (node->data.unary_op.value->type == NODE_BOOLEAN)
        {
            uint8_t result;
            switch (node->data.unary_op.op)
            {

            case OP_LOGICAL_NOT:
                printf("THIS MOTHER FUCKER!");
                result = !node->data.unary_op.value->data.boolean.value;
                free_ast(node->data.unary_op.value);
                return create_boolean_node(result);
                break;

            default:
                break;
            }
        }

        // TODO: Domyslet jestli to dává smysl (hlavně pokud nedojde k evaluaci..)
        if (node->data.unary_op.value->type == NODE_NUMBER)
        {
            int result = 0;
            switch (node->data.unary_op.op)
            {

            case OP_INCREMENT:
                free_ast(node->data.unary_op.value);
                return create_number_node(result);
                break;
            case OP_DECREMENT:
                free_ast(node->data.unary_op.value);
                return create_number_node(result);
                break;

            default:
                break;
            }
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

        if (node->data.binary_op.left->type == NODE_BOOLEAN && node->data.binary_op.right->type == NODE_BOOLEAN)
        {
            uint8_t left = node->data.binary_op.left->data.boolean.value;
            uint8_t right = node->data.binary_op.right->data.boolean.value;
            uint8_t result = 0;

            switch (node->data.binary_op.op)
            {
            case OP_LOGICAL_OR:
                result = left || right;
                break;
            case OP_LOGICAL_AND:
                result = left && right;
                break;
            }

            free_ast(node->data.binary_op.left);
            free_ast(node->data.binary_op.right);
            return create_boolean_node(result);
        }
    }

    return node;
}

ASTNode *replace_variables(ASTNode *node, SymbolTable *table)
{
    if (!node)
        return NULL;

    node = evaluate_expression(node, table);

    // nahrazujeme v ifu proměnné za literály
    if (node->type == NODE_VARIABLE)
    {
        SymbolEntry *entry = lookup_variable(table, node->data.variable.name);
        if (entry && entry->is_initialized)
        {
            if (entry->data_type == TYPE_NUMBER)
            {
                return create_number_node(entry->value);
            }
            else if (entry->data_type == TYPE_STRING)
            {
                return create_string_node(entry->string_value);
            }
            else if (entry->data_type == TYPE_BOOLEAN)
            {
                return create_boolean_node(entry->boolean_value);
            }
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

void find_and_set_variables(ASTNode *node, SymbolTable *table)
{
    if (!node)
        return;

    switch (node->type)
    {
    case NODE_PROGRAM:
    case NODE_STATEMENT_LIST:
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
        {
            find_and_set_variables(node->data.statement_list.statements[i], table);
        }
        break;

    case NODE_VAR_DECLARATION:
        if (!lookup_variable(table, node->data.var_declaration.var_name))
        {
            if (node->data.var_declaration.init_expr)
            {

                node->data.var_declaration.init_expr = replace_variables(node->data.var_declaration.init_expr, table);
                NodeType type = node->data.var_declaration.init_expr->type;
                if (type == NODE_NUMBER)
                {
                    int value = node->data.var_declaration.init_expr->data.number.value;

                    set_variable(table, node->data.var_declaration.var_name,
                                 &value, 1, TYPE_NUMBER);
                }
                else if (type == NODE_STRING)
                {
                    char *value = node->data.var_declaration.init_expr->data.string.value;
                    set_variable(table, node->data.var_declaration.var_name, value, 1, TYPE_STRING);
                }
                else if (type == NODE_BOOLEAN)
                {
                    uint8_t value = node->data.var_declaration.init_expr->data.boolean.value;
                    set_variable(table, node->data.var_declaration.var_name, &value, 1, TYPE_BOOLEAN);
                }
                else if (type == NODE_FUNCTION_CALL)
                {

                    char *func_name = node->data.var_declaration.init_expr->data.function_call.func_name;
                    FunctionEntry *function = lookup_function(table, func_name);
                    DataType type = function->return_type;

                    if (function->return_type == TYPE_STRING)
                    {
                        set_variable(table, node->data.var_declaration.var_name,
                                     "", 1, type);
                    }
                    else
                    {
                        int value = 1;
                        set_variable(table, node->data.var_declaration.var_name,
                                     &value, 1, type);
                    }

                    SymbolEntry *entry = lookup_variable(table, node->data.var_declaration.var_name);
                    if (entry)
                    {
                        entry->is_used = 1;
                    }
                }
                else
                {

                    int value = 0;

                    set_variable(table, node->data.var_declaration.var_name, &value, 0, TYPE_NUMBER);
                }
            }
            else
            {
                SymbolEntry *entry = lookup_variable(table, node->data.var_declaration.var_name);
                node->data.var_declaration.init_expr = replace_variables(node->data.var_declaration.init_expr, table);

                if (entry && node->data.var_declaration.init_expr->type == NODE_NUMBER)
                {
                    entry->value = node->data.var_declaration.init_expr->data.number.value;
                    entry->is_initialized = 1;
                    entry->data_type = TYPE_NUMBER;
                }
                else if (entry && node->data.var_declaration.init_expr->type == NODE_STRING)
                {
                    entry->string_value = strdup(node->data.var_declaration.init_expr->data.string.value);
                    entry->is_initialized = 1;
                    entry->data_type = TYPE_STRING;
                }
                else if (entry && node->data.var_declaration.init_expr->type == NODE_BOOLEAN)
                {
                    entry->boolean_value = node->data.var_declaration.init_expr->data.boolean.value;
                    entry->is_initialized = 1;
                    entry->data_type = TYPE_BOOLEAN;
                }
            }
        }

        if (node->data.var_declaration.init_expr)
        {
            find_and_set_variables(node->data.var_declaration.init_expr, table);
        }
        break;

    case NODE_ASSIGNMENT:
        if (!lookup_variable(table, node->data.assignment.var_name))
        {
            // TODO: Promyslet jestli zde je potřeba
            node->data.assignment.value = replace_variables(node->data.assignment.value, table);

            if (node->data.assignment.value->type == NODE_NUMBER)
            {
                set_variable(table, node->data.assignment.var_name,
                             &(node->data.assignment.value->data.number.value), 1, TYPE_NUMBER);
            }
            else if (node->data.assignment.value->type == NODE_STRING)
            {
                set_variable(table, node->data.assignment.var_name,
                             node->data.assignment.value->data.string.value, 1, TYPE_STRING);
            }
            else if (node->data.assignment.value->type == NODE_BOOLEAN)
            {
                uint8_t value = node->data.assignment.value->data.boolean.value;
                set_variable(table, node->data.assignment.var_name, &value, 1, TYPE_BOOLEAN);
            }
            else if (node->data.assignment.value->type == NODE_FUNCTION_CALL)
            {
                char *func_name = node->data.assignment.value->data.function_call.func_name;
                FunctionEntry *function = lookup_function(table, func_name);
                DataType type = function->return_type;

                if (function->return_type == TYPE_STRING)
                {
                    set_variable(table, node->data.assignment.var_name,
                                 "", 1, type);
                }
                else
                {
                    int value = 1;
                    set_variable(table, node->data.assignment.var_name,
                                 &value, 1, type);
                }

                SymbolEntry *entry = lookup_variable(table, node->data.assignment.var_name);
                if (entry)
                {
                    entry->is_used = 1;
                }
            }
            else
            {
                int value = 0;
                set_variable(table, node->data.assignment.var_name, &value, 0, TYPE_NUMBER);
            }
        }
        else
        {
            SymbolEntry *entry = lookup_variable(table, node->data.assignment.var_name);
            node->data.assignment.value = replace_variables(node->data.assignment.value, table);

            if (entry && node->data.assignment.value->type == NODE_NUMBER)
            {
                entry->value = node->data.assignment.value->data.number.value;
                entry->is_initialized = 1;
                entry->data_type = TYPE_NUMBER;
            }
            else if (entry && node->data.assignment.value->type == NODE_STRING)
            {
                entry->string_value = strdup(node->data.assignment.value->data.string.value);
                entry->is_initialized = 1;
                entry->data_type = TYPE_STRING;
            }
            else if (entry && node->data.assignment.value->type == NODE_BOOLEAN)
            {
                entry->boolean_value = node->data.assignment.value->data.boolean.value;
                entry->is_initialized = 1;
                entry->data_type = TYPE_BOOLEAN;
            }
        }

        find_and_set_variables(node->data.assignment.value, table);
        break;

    case NODE_VARIABLE:
    {
        SymbolEntry *entry = lookup_variable(table, node->data.variable.name);
        if (entry)
        {
            entry->is_used = 1;
        }
        else
        {

            int value = 0;
            set_variable(table, node->data.variable.name, &value, 0, TYPE_NUMBER);

            entry = lookup_variable(table, node->data.variable.name);
            if (entry)
            {
                entry->is_used = 1;
            }
        }
    }
    break;

    case NODE_PRINT:
        find_and_set_variables(node->data.print.expr, table);
        break;

    case NODE_IF:
        find_and_set_variables(node->data.if_statement.condition, table);
        if (node->data.if_statement.if_block)
        {
            find_and_set_variables(node->data.if_statement.if_block, table);
        }
        if (node->data.if_statement.else_block)
        {
            find_and_set_variables(node->data.if_statement.else_block, table);
        }
        break;

    case NODE_BINARY_OP:
        find_and_set_variables(node->data.binary_op.left, table);
        find_and_set_variables(node->data.binary_op.right, table);
        break;
    case NODE_UNARY_OP:
        find_and_set_variables(node->data.unary_op.value, table);
        break;

    case NODE_CONDITION:
        find_and_set_variables(node->data.condition.left, table);
        find_and_set_variables(node->data.condition.right, table);
        break;

    case NODE_FOR_LOOP:
        if (node->data.for_loop.init_expression)
        {
            find_and_set_variables(node->data.for_loop.init_expression, table);
        }
        if (node->data.for_loop.condition)
        {
            find_and_set_variables(node->data.for_loop.condition, table);
        }
        if (node->data.for_loop.update)
        {
            find_and_set_variables(node->data.for_loop.update, table);
        }
        if (node->data.for_loop.body)
        {
            find_and_set_variables(node->data.for_loop.body, table);
        }
        break;

    case NODE_FUNCTION_CALL:
        for (int i = 0; i < node->data.function_call.argument_count; i++)
        {
            find_and_set_variables(node->data.function_call.arguments[i], table);
        }
        break;

    case NODE_FUNCTION_DECLARATION:
        for (int i = 0; i < node->data.function_declaration.param_count; i++)
        {
            int value = 0;
            set_variable(table, node->data.function_declaration.param_names[i], &value, 0, node->data.function_declaration.param_types[i]);
            SymbolEntry *entry = lookup_variable(table, node->data.function_declaration.param_names[i]);
            if (entry)
            {
                entry->is_used = 1;
            }
        }

        if (node->data.function_declaration.body)
        {
            find_and_set_variables(node->data.function_declaration.body, table);
        }
        break;

    case NODE_RETURN:
        if (node->data.return_statement.expr)
        {
            find_and_set_variables(node->data.return_statement.expr, table);
        }
        break;

    default:
        break;
    }
}

void mark_modified_variables(ASTNode *node, SymbolTable *table);
void remove_unused_variables(ASTNode *node, SymbolTable *table);

// CPG optimalizování
ASTNode *optimize_ast(ASTNode *node, SymbolTable *table)
{
    if (!node)
        return NULL;

    switch (node->type)
    {
    case NODE_PROGRAM:
    case NODE_STATEMENT_LIST:
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
        {
            node->data.statement_list.statements[i] = optimize_ast(node->data.statement_list.statements[i], table);
        }
        break;

    case NODE_VAR_DECLARATION:
        if (node->data.var_declaration.init_expr)
        {
            node->data.var_declaration.init_expr = optimize_ast(node->data.var_declaration.init_expr, table);

            if (node->data.var_declaration.init_expr->type == NODE_NUMBER)
            {
                int value = node->data.var_declaration.init_expr->data.number.value;
                set_variable(table, node->data.var_declaration.var_name, &value, 1, TYPE_NUMBER);
            }
            else if (node->data.var_declaration.init_expr->type == NODE_STRING)
            {
                set_variable(table, node->data.var_declaration.var_name, node->data.var_declaration.init_expr->data.string.value, 1, TYPE_STRING);
            }
            else if (node->data.var_declaration.init_expr->type == NODE_BOOLEAN)
            {
                set_variable(table, node->data.var_declaration.var_name, &(node->data.var_declaration.init_expr->data.boolean.value), 1, TYPE_BOOLEAN);
            }
            else if (node->data.var_declaration.init_expr->type == NODE_FUNCTION_CALL)
            {
                char *func_name = node->data.var_declaration.init_expr->data.function_call.func_name;
                FunctionEntry *function = lookup_function(table, func_name);
                DataType type = function->return_type;

                if (function->return_type == TYPE_STRING)
                {
                    set_variable(table, node->data.var_declaration.var_name,
                                 "", 1, type);
                }
                else
                {
                    int value = 1;
                    set_variable(table, node->data.var_declaration.var_name,
                                 &value, 1, type);
                }

                SymbolEntry *entry = lookup_variable(table, node->data.var_declaration.var_name);
                if (entry)
                {
                    entry->is_used = 1;
                    entry->is_modified_in_loop = 1;
                }
            }
            // else if (node->data.var_declaration.init_expr->type == NODE_FUNCTION_CALL)
            // {
            //     set_is_used(table, node->data.var_declaration.var_name);
            // }
            else
            {
                int value = 0;

                set_variable(table, node->data.var_declaration.var_name, &value, 0, TYPE_NUMBER);
            }
        }
        break;

    case NODE_ASSIGNMENT:
        node->data.assignment.value = optimize_ast(node->data.assignment.value, table);

        SymbolEntry *entry = lookup_variable(table, node->data.assignment.var_name);
        if (entry && entry->is_modified_in_loop)
        {
            int value = 0;

            set_variable(table, node->data.assignment.var_name, &value, 0, TYPE_NUMBER);
            break;
        }

        if (node->data.assignment.value->type == NODE_NUMBER)
        {
            int value = node->data.assignment.value->data.number.value;
            set_variable(table, node->data.assignment.var_name, &value, 1, TYPE_NUMBER);
        }
        else if (node->data.assignment.value->type == NODE_STRING)
        {
            set_variable(table, node->data.assignment.var_name, node->data.assignment.value->data.string.value, 1, TYPE_STRING);
        }
        else if (node->data.assignment.value->type == NODE_BOOLEAN)
        {
            set_variable(table, node->data.assignment.var_name, &(node->data.assignment.value->data.boolean.value), 1, TYPE_BOOLEAN);
        }
        else
        {
            int value = 0;

            set_variable(table, node->data.assignment.var_name, &value, 0, TYPE_NUMBER);
        }
        break;

    case NODE_PRINT:
        node->data.print.expr = optimize_ast(node->data.print.expr, table);
        break;

    case NODE_IF:
        node->data.if_statement.condition = optimize_ast(node->data.if_statement.condition, table);

        if (node->data.if_statement.condition->type == NODE_NUMBER)
        {
            int condition_value = node->data.if_statement.condition->data.number.value;
            ASTNode *result = NULL;

            if (condition_value)
            {
                if (node->data.if_statement.if_block)
                {
                    result = optimize_ast(node->data.if_statement.if_block, table);
                }
            }
            else
            {
                if (node->data.if_statement.else_block)
                {
                    result = optimize_ast(node->data.if_statement.else_block, table);
                }
            }

            ASTNode *condition = node->data.if_statement.condition;
            ASTNode *if_block = node->data.if_statement.if_block;
            ASTNode *else_block = node->data.if_statement.else_block;

            node->data.if_statement.condition = NULL;
            node->data.if_statement.if_block = NULL;
            node->data.if_statement.else_block = NULL;

            free_ast(node);

            if (condition_value)
            {
                free_ast(else_block);
            }
            else
            {
                free_ast(if_block);
            }

            free_ast(condition);

            return result ? result : create_statement_list_node(NULL, 0);
        }
        else
        {
            if (node->data.if_statement.if_block)
            {
                node->data.if_statement.if_block = optimize_ast(node->data.if_statement.if_block, table);
            }
            if (node->data.if_statement.else_block)
            {
                node->data.if_statement.else_block = optimize_ast(node->data.if_statement.else_block, table);
            }
        }
        break;

    case NODE_BINARY_OP:
        node->data.binary_op.left = optimize_ast(node->data.binary_op.left, table);
        node->data.binary_op.right = optimize_ast(node->data.binary_op.right, table);

        if (node->data.binary_op.left->type == NODE_NUMBER &&
            node->data.binary_op.right->type == NODE_NUMBER)
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
                if (right != 0)
                    result = left / right;
                else
                    return node;
                break;
            }

            ASTNode *number_node = create_number_node(result);

            ASTNode *left_node = node->data.binary_op.left;
            ASTNode *right_node = node->data.binary_op.right;

            node->data.binary_op.left = NULL;
            node->data.binary_op.right = NULL;

            free_ast(node);
            free_ast(left_node);
            free_ast(right_node);

            return number_node;
        }
        else if (node->data.binary_op.left->type == NODE_BOOLEAN &&
                 node->data.binary_op.right->type == NODE_BOOLEAN)
        {
            uint8_t left = node->data.binary_op.left->data.boolean.value;
            uint8_t right = node->data.binary_op.right->data.boolean.value;
            uint8_t result = 0;

            switch (node->data.binary_op.op)
            {
            case OP_LOGICAL_OR:
                result = left || right;
                break;
            case OP_LOGICAL_AND:
                result = left && right;
                break;
            }

            ASTNode *boolean_node = create_boolean_node(result);

            ASTNode *left_node = node->data.binary_op.left;
            ASTNode *right_node = node->data.binary_op.right;

            node->data.binary_op.left = NULL;
            node->data.binary_op.right = NULL;

            free_ast(node);
            free_ast(left_node);
            free_ast(right_node);

            return boolean_node;
        }
        break;

    case NODE_VARIABLE:
    {
        SymbolEntry *entry = lookup_variable(table, node->data.variable.name);
        if (entry && entry->is_initialized && !entry->is_modified_in_loop)
        {
            ASTNode *new_node = NULL;

            if (entry->data_type == TYPE_NUMBER)
            {

                new_node = create_number_node(entry->value);
            }
            else if (entry->data_type == TYPE_STRING)
            {
                new_node = create_string_node(entry->string_value);
            }
            else if (entry->data_type == TYPE_BOOLEAN)
            {
                new_node = create_boolean_node(entry->boolean_value);
            } 

            if (new_node)
            {
                free(node->data.variable.name);
                free(node);
                return new_node;
            }
        }
    }
    break;

    case NODE_FUNCTION_DECLARATION:
    {
        // add_function(table, node->data.function_declaration.name, node->data.function_declaration.param_count);
    }
    break;

    case NODE_UNARY_OP:
        node->data.unary_op.value = optimize_ast(node->data.unary_op.value, table);

        if (node->data.unary_op.op == OP_LOGICAL_NOT &&
            node->data.unary_op.value->type == NODE_BOOLEAN)
        {
            uint8_t value = node->data.unary_op.value->data.boolean.value;
            uint8_t result = !value;

            ASTNode *boolean_node = create_boolean_node(result);

            ASTNode *value_node = node->data.unary_op.value;
            node->data.unary_op.value = NULL;

            free_ast(node);
            free_ast(value_node);

            return boolean_node;
        }

        else if ((node->data.unary_op.op == OP_INCREMENT ||
                  node->data.unary_op.op == OP_DECREMENT) &&
                 node->data.unary_op.value->type == NODE_NUMBER)
        {
            int value = node->data.unary_op.value->data.number.value;
            int result;

            if (node->data.unary_op.op == OP_INCREMENT)
                result = value + 1;
            else
                result = value - 1;

            ASTNode *number_node = create_number_node(result);

            ASTNode *value_node = node->data.unary_op.value;
            node->data.unary_op.value = NULL;

            free_ast(node);
            free_ast(value_node);

            return number_node;
        }
        break;

    case NODE_FUNCTION_CALL:
        // výrazy v argumentech
        for (int i = 0; i < node->data.function_call.argument_count; i++)
        {
            printf("Ahoj světe");
            node->data.function_call.arguments[i] = optimize_ast(node->data.function_call.arguments[i], table);
        }
        break;

    case NODE_CONDITION:
        node->data.condition.left = optimize_ast(node->data.condition.left, table);
        node->data.condition.right = optimize_ast(node->data.condition.right, table);

        // Tady můžeme eliminovat rovnou jednu branch..
        if (node->data.condition.left->type == NODE_NUMBER &&
            node->data.condition.right->type == NODE_NUMBER)
        {
            int left = node->data.condition.left->data.number.value;
            int right = node->data.condition.right->data.number.value;
            int result = 0;

            switch (node->data.condition.op)
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

            ASTNode *number_node = create_number_node(result);

            ASTNode *left_node = node->data.condition.left;
            ASTNode *right_node = node->data.condition.right;

            node->data.condition.left = NULL;
            node->data.condition.right = NULL;

            free_ast(node);
            free_ast(left_node);
            free_ast(right_node);

            return number_node;
        }
        else if (node->data.condition.left->type == NODE_BOOLEAN &&
                 node->data.condition.right->type == NODE_BOOLEAN)
        {
            uint8_t left = node->data.condition.left->data.boolean.value;
            uint8_t right = node->data.condition.right->data.boolean.value;
            uint8_t result = 0;

            switch (node->data.condition.op)
            {
            case COND_EQUALS:
                result = left == right;
                break;
            case COND_NOT_EQUALS:
                result = left != right;
                break;
            }

            ASTNode *boolean_node = create_boolean_node(result);

            ASTNode *left_node = node->data.condition.left;
            ASTNode *right_node = node->data.condition.right;

            node->data.condition.left = NULL;
            node->data.condition.right = NULL;

            free_ast(node);
            free_ast(left_node);
            free_ast(right_node);

            return boolean_node;
        }
        break;

    case NODE_FOR_LOOP:
    {
        SymbolTable loop_table;
        init_symbol_table(&loop_table);

        // Překopírijeme si tabulku
        for (int i = 0; i < table->count; i++)
        {
            if (table->entries[i].data_type == TYPE_STRING)
            {
                set_variable(&loop_table, table->entries[i].name,
                             table->entries[i].string_value,
                             table->entries[i].is_initialized, TYPE_STRING);
            }
            else if (table->entries[i].data_type == TYPE_BOOLEAN)
            {
                set_variable(&loop_table, table->entries[i].name,
                             &(table->entries[i].boolean_value),
                             table->entries[i].is_initialized, TYPE_BOOLEAN);
            }
            else
            {
                set_variable(&loop_table, table->entries[i].name,
                             &(table->entries[i].value),
                             table->entries[i].is_initialized, TYPE_NUMBER);
            }
        }

        if (node->data.for_loop.init_expression)
        {
            node->data.for_loop.init_expression = optimize_ast(node->data.for_loop.init_expression, &loop_table);
        }

        if (node->data.for_loop.update)
        {
            mark_modified_variables(node->data.for_loop.update, &loop_table);
        }

        if (node->data.for_loop.body)
        {
            mark_modified_variables(node->data.for_loop.body, &loop_table);
        }

        // Mám to jako optimalizaci... ale bez toho is_modified_loop to budě dělat píčoviny
        // Takže to pak dát někde při setování...
        for (int i = 0; i < loop_table.count; i++)
        {
            if (loop_table.entries[i].is_modified_in_loop)
            {
                // TODO: Promyslet to s těma zasranejme scopama a vnitřní tabulkou for loopu
                SymbolEntry *main_entry = lookup_variable(table, loop_table.entries[i].name);
                if (main_entry)
                {
                    main_entry->is_modified_in_loop = 1;
                    main_entry->is_used = 1;
                    main_entry->is_initialized = 0; // Přezdívka pro konsantu to moje is_initiliazed
                }
            }
        }

        remove_unused_variables(node->data.for_loop.body, &loop_table);

        // if (node->data.for_loop.update)
        //  {
        //      node->data.for_loop.update = optimize_ast(node->data.for_loop.update, &loop_table);
        // }

        // TODO: Mazat loop, když bude vždycky neplatná podmínka
        break;
    }
    case NODE_STRING:

        break;

    case NODE_NUMBER:
        // Numbers are already optimized
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

    case NODE_STRING:
        free(node->data.string.value);
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

void mark_modified_variables(ASTNode *node, SymbolTable *table)
{
    if (!node)
        return;

    switch (node->type)
    {
    case NODE_ASSIGNMENT:
    {

        SymbolEntry *entry = lookup_variable(table, node->data.assignment.var_name);
        if (entry)
        {
            entry->is_modified_in_loop = 1;
            entry->is_initialized = 0;
        }
        else
        {
            if (entry->data_type == TYPE_STRING)
            {
                set_variable(table, node->data.assignment.var_name, node->data.assignment.value->data.string.value, 0, TYPE_STRING);
            }
            else if (entry->data_type == TYPE_BOOLEAN)
            {
                set_variable(table, node->data.assignment.var_name, &(node->data.assignment.value->data.boolean.value), 0, TYPE_BOOLEAN);
            }
            else
            {
                int value = 0;
                set_variable(table, node->data.assignment.var_name, &value, 0, TYPE_NUMBER);
            }

            entry = lookup_variable(table, node->data.assignment.var_name);
            if (entry)
            {
                entry->is_modified_in_loop = 1;
            }
        }

        mark_modified_variables(node->data.assignment.value, table);
    }
    break;

    case NODE_VAR_DECLARATION:
    {
        SymbolEntry *entry = lookup_variable(table, node->data.var_declaration.var_name);
        if (entry)
        {
            entry->is_modified_in_loop = 1;
            entry->is_initialized = 0;
        }
        else
        {
            if (entry->data_type == TYPE_STRING)
            {
                set_variable(table, node->data.var_declaration.var_name, node->data.var_declaration.init_expr->data.string.value, 0, TYPE_STRING);
            }
            else if (entry->data_type == TYPE_BOOLEAN)
            {
                set_variable(table, node->data.var_declaration.var_name, &(node->data.var_declaration.init_expr->data.boolean.value), 0, TYPE_BOOLEAN);
            }
            else
            {
                int value = 0;
                set_variable(table, node->data.var_declaration.var_name, &value, 0, TYPE_NUMBER);
            }

            entry = lookup_variable(table, node->data.var_declaration.var_name);
            if (entry)
            {
                entry->is_modified_in_loop = 1;
            }
        }

        if (node->data.var_declaration.init_expr)
        {
            mark_modified_variables(node->data.var_declaration.init_expr, table);
        }
    }
    break;

    case NODE_STATEMENT_LIST:
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
        {
            mark_modified_variables(node->data.statement_list.statements[i], table);
        }
        break;

    case NODE_IF:
        mark_modified_variables(node->data.if_statement.condition, table);
        if (node->data.if_statement.if_block)
        {
            mark_modified_variables(node->data.if_statement.if_block, table);
        }
        if (node->data.if_statement.else_block)
        {
            mark_modified_variables(node->data.if_statement.else_block, table);
        }
        break;

    case NODE_FOR_LOOP:
        if (node->data.for_loop.init_expression)
        {
            mark_modified_variables(node->data.for_loop.init_expression, table);
        }
        if (node->data.for_loop.condition)
        {
            mark_modified_variables(node->data.for_loop.condition, table);
        }
        if (node->data.for_loop.update)
        {
            mark_modified_variables(node->data.for_loop.update, table);
        }
        if (node->data.for_loop.body)
        {
            mark_modified_variables(node->data.for_loop.body, table);
        }
        break;

    case NODE_BINARY_OP:
        mark_modified_variables(node->data.binary_op.left, table);
        mark_modified_variables(node->data.binary_op.right, table);
        break;

    case NODE_CONDITION:
        mark_modified_variables(node->data.condition.left, table);
        mark_modified_variables(node->data.condition.right, table);
        break;

    case NODE_PRINT:
        mark_modified_variables(node->data.print.expr, table);
        break;

    default:
        break;
    }
}

void remove_unused_variables(ASTNode *node, SymbolTable *table)
{
    if (!node)
        return;

    if (node->type == NODE_VAR_DECLARATION)
    {

        SymbolEntry *entry = lookup_variable(table, node->data.var_declaration.var_name);
        if (entry && !entry->is_used)
        {
            free_ast(node);
            return;
        }
    }

    if (node->type == NODE_BINARY_OP)
    {
        remove_unused_variables(node->data.binary_op.left, table);
        remove_unused_variables(node->data.binary_op.right, table);
    }

    if (node->type == NODE_CONDITION)
    {
        remove_unused_variables(node->data.condition.left, table);
        remove_unused_variables(node->data.condition.right, table);
    }

    if (node->type == NODE_ASSIGNMENT)
    {
        remove_unused_variables(node->data.assignment.value, table);
    }

    if (node->type == NODE_PRINT)
    {
        remove_unused_variables(node->data.print.expr, table);
    }

    if (node->type == NODE_FOR_LOOP)
    {
        remove_unused_variables(node->data.for_loop.init_expression, table);
        remove_unused_variables(node->data.for_loop.condition, table);
        remove_unused_variables(node->data.for_loop.update, table);
        remove_unused_variables(node->data.for_loop.body, table);
    }

    if (node->type == NODE_STATEMENT_LIST)
    {
        ASTNode **new_statements = (ASTNode **)malloc(sizeof(ASTNode *) * node->data.statement_list.statement_count);
        int new_count = 0;

        for (int i = 0; i < node->data.statement_list.statement_count; ++i)
        {
            ASTNode *stmt = node->data.statement_list.statements[i];
            // stmt->data.var_declaration.init_expr->type != NODE_FUNCTION_CALL automaticky in-used když se deklaruješ z function callu
            if (stmt->type == NODE_VAR_DECLARATION && stmt->data.var_declaration.init_expr->type != NODE_FUNCTION_CALL)
            {
                SymbolEntry *entry = lookup_variable(table, stmt->data.var_declaration.var_name);
                if (entry && entry->is_used)
                {
                    new_statements[new_count++] = stmt;
                }
                else
                {
                    free_ast(stmt);
                }
            }
            else
            {
                new_statements[new_count++] = stmt;
            }
        }

        free(node->data.statement_list.statements);
        node->data.statement_list.statements = new_statements;
        node->data.statement_list.statement_count = new_count;
    }
}

// passnout optimizeLevel a podle toho dělat jednotlivé optimalizace
ASTNode *optimize_program(ASTNode *node, SymbolTable *table)
{
    optimize_ast(node, table);
    remove_unused_variables(node, table);
}
