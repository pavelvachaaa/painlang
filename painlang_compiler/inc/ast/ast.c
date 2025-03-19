#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ast_helper.h"
#include "ast_evaluator.h"
#include "ast_creator.h"

ASTNode *evaluate_expression(ASTNode *node, SymbolTable *table)
{

    if (!node)
        return NULL;

    if (node->type == NODE_VARIABLE)
    {
        SymbolEntry *entry = lookup_variable(table, node->data.variable.name);
        return create_node_from_symbol(entry);
    }

    if (node->type == NODE_ASSIGNMENT)
    {

        SymbolEntry *entry = lookup_variable(table, node->data.assignment.var_name);
        if (entry)
        {

            ASTNode *evaluated_value = evaluate_expression(node->data.assignment.value, table);
            update_symbol_entry_from_node(entry, evaluated_value);

            if (evaluated_value != node->data.assignment.value)
            {
                free_ast(evaluated_value);
            }
        }
    }

    if (node->type == NODE_UNARY_OP)
    {
        return evaluate_unary_op_node(node, table);
    }

    if (node->type == NODE_BINARY_OP)
    {
        return evaluate_binary_op_node(node, table);
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
        return create_node_from_symbol(entry);
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
        int result = evaluate_condition_op(condition->data.condition.op, left, right);

        return create_number_node(result);
    }
    return condition;
}

void mark_modified_variables(ASTNode *node, SymbolTable *table);
void remove_unused_variables(ASTNode *node, SymbolTable *table);

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
    
    // case NODE_IMPORT_STATEMENT: 
    //     find_and_set_variables(node->data.import_statement.imported_ast, table);
    // break;

    case NODE_VAR_DECLARATION:
        if (!lookup_variable(table, node->data.var_declaration.var_name))
        {
            if (node->data.var_declaration.init_expr)
            {

                node->data.var_declaration.init_expr = replace_variables(node->data.var_declaration.init_expr, table);
                set_variable_from_node(table, node->data.var_declaration.var_name, node->data.var_declaration.init_expr, 0);
            }
            else
            {
                SymbolEntry *entry = lookup_variable(table, node->data.var_declaration.var_name);
                node->data.var_declaration.init_expr = replace_variables(node->data.var_declaration.init_expr, table);
                update_symbol_entry_from_node(entry, node->data.var_declaration.init_expr);
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
            set_variable_from_node(table, node->data.assignment.var_name, node->data.assignment.value, 0);
        }
        else
        {
            SymbolEntry *entry = lookup_variable(table, node->data.assignment.var_name);
            node->data.assignment.value = replace_variables(node->data.assignment.value, table);
            update_symbol_entry_from_node(entry, node->data.assignment.value);
        }

        // TODO: Prozkoumat proč jsem to sem dal??
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

    // Tohle je i v optimize AST. Pak to vyseparovat do nějaké funkce...
    case NODE_FOR_LOOP:
    {
        SymbolTable loop_table;
        init_symbol_table(&loop_table);
        copy_symbol_table(&loop_table, table);

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

        update_loop_modified_variables(table, &loop_table);
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
            set_variable_from_node(table, node->data.var_declaration.var_name, node->data.var_declaration.init_expr, 1);
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

        set_variable_from_node(table, node->data.assignment.var_name, node->data.assignment.value, 0);

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
        return evaluate_binary_op_node(node, table);
        break;

    case NODE_VARIABLE:
    {
        SymbolEntry *entry = lookup_variable(table, node->data.variable.name);
        if (entry && entry->is_initialized && !entry->is_modified_in_loop)
        {
            ASTNode *new_node = create_node_from_symbol(entry);

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
        return evaluate_unary_op_node(node, table);
        break;

    case NODE_FUNCTION_CALL:
        // výrazy v argumentech
        for (int i = 0; i < node->data.function_call.argument_count; i++)
        {
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
            int result = evaluate_condition_op(node->data.condition.op, left, right);

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
            uint8_t result = evaluate_boolean_condition_op(node->data.condition.op, left, right);

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
        copy_symbol_table(&loop_table, table);

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

        update_loop_modified_variables(table, &loop_table);

        remove_unused_variables(node->data.for_loop.body, &loop_table);
        break;
    }
    case NODE_STRING:
        break;

    case NODE_NUMBER:
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
