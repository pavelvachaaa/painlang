#include "ast_helper.h"

DataType get_node_data_type(SymbolTable *table, ASTNode *node)
{
    if (!node)
        return TYPE_UNKNOWN;

    switch (node->type)
    {
    case NODE_STRING:
        return TYPE_STRING;
    case NODE_NUMBER:
        return TYPE_NUMBER;
    case NODE_BOOLEAN:
        return TYPE_BOOLEAN;
    case NODE_FUNCTION_CALL:
    {
        FunctionEntry *func = lookup_function(table, node->data.function_call.func_name);
        return func ? func->return_type : TYPE_UNKNOWN;
    }
    default:
        fprintf(stderr, "[Error] get_node_data_type - nepodporovaný node pro konverzi");
        return TYPE_UNKNOWN;
    }
}

uint8_t is_literal_node(ASTNode *node)
{
    return node && (node->type == NODE_NUMBER ||
                    node->type == NODE_STRING ||
                    node->type == NODE_BOOLEAN);
}

ASTNode *create_node_from_symbol(SymbolEntry *entry)
{
    if (!entry || !entry->is_initialized)
        return NULL;

    switch (entry->data_type)
    {
    case TYPE_NUMBER:
        return create_number_node(entry->value);
    case TYPE_STRING:
        return create_string_node(entry->string_value);
    case TYPE_BOOLEAN:
        return create_boolean_node(entry->boolean_value);
    default:
        return NULL;
    }
}

void set_variable_from_node(SymbolTable *table, const char *name, ASTNode *value_node)
{
    if (!table || !name || !value_node)
        return;

    DataType type = get_node_data_type(table, value_node);

    switch (value_node->type)
    {
    case NODE_NUMBER:
        set_variable(table, name, &(value_node->data.number.value), 1, TYPE_NUMBER);
        break;
    case NODE_STRING:
        set_variable(table, name, value_node->data.string.value, 1, TYPE_STRING);
        break;
    case NODE_BOOLEAN:
        set_variable(table, name, &(value_node->data.boolean.value), 1, TYPE_BOOLEAN);
        break;
    case NODE_FUNCTION_CALL:
    {
        char *func_name = value_node->data.function_call.func_name;
        FunctionEntry *function = lookup_function(table, func_name);

        if (function)
        {
            if (function->return_type == TYPE_STRING)
            {
                set_variable(table, name, "", 1, function->return_type);
            }
            else
            {
                int value = 1;
                set_variable(table, name, &value, 1, function->return_type);
            }

            SymbolEntry *entry = lookup_variable(table, name);
            if (entry)
            {
                entry->is_used = 1;
            }
        }
        break;
    }
    default:
    {
        int value = 0;
        set_variable(table, name, &value, 0, TYPE_NUMBER);
        break;
    }
    }
}
