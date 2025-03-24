#include "ast_evaluator.h"

ASTNode *evaluate_unary_op_node(ASTNode *node, SymbolTable *table)
{

    node->data.unary_op.value = evaluate_expression(node->data.unary_op.value, table);

    if (node->data.unary_op.value->type == NODE_BOOLEAN)
    {
        if (node->data.unary_op.op == OP_LOGICAL_NOT)
        {
            uint8_t result = !node->data.unary_op.value->data.boolean.value;
            free_ast(node->data.unary_op.value);
            return create_boolean_node(result);
        }
    }

    if (node->data.unary_op.value->type == NODE_NUMBER)
    {
        int value = node->data.unary_op.value->data.number.value;
        int result = 0;

        if (node->data.unary_op.op == OP_INCREMENT)
        {
            result = value + 1;
        }
        else if (node->data.unary_op.op == OP_DECREMENT)
        {
            result = value - 1;
        }

        free_ast(node->data.unary_op.value);
        return create_number_node(result);
    }
}

ASTNode *evaluate_binary_op_node(ASTNode *node, SymbolTable *table)
{
    // evalujeme dokud nám nezbyde vlastně jen čísla, na kterých můžeme operovat
    node->data.binary_op.left = evaluate_expression(node->data.binary_op.left, table);
    node->data.binary_op.right = evaluate_expression(node->data.binary_op.right, table);

    if (node->data.binary_op.left->type == NODE_NUMBER && node->data.binary_op.right->type == NODE_NUMBER)
    {
        int left = node->data.binary_op.left->data.number.value;
        int right = node->data.binary_op.right->data.number.value;
        int result = evaluate_numeric_binary_op(node->data.binary_op.op, left, right);

        free_ast(node->data.binary_op.left);
        free_ast(node->data.binary_op.right);
        return create_number_node(result);
    }

    if (node->data.binary_op.left->type == NODE_STRING && node->data.binary_op.right->type == NODE_STRING)
    {
        char *left = node->data.binary_op.left->data.string.value;
        char *right = node->data.binary_op.right->data.string.value;
        uint8_t result = evaluate_string_condition_op(node->data.binary_op.op, left, right);

        free_ast(node->data.binary_op.left);
        free_ast(node->data.binary_op.right);
        
        return create_boolean_node(result);
    }

    if (node->data.binary_op.left->type == NODE_BOOLEAN && node->data.binary_op.right->type == NODE_BOOLEAN)
    {
        uint8_t left = node->data.binary_op.left->data.boolean.value;
        uint8_t right = node->data.binary_op.right->data.boolean.value;
        uint8_t result = evaluate_boolean_binary_op(node->data.binary_op.op, left, right);

        free_ast(node->data.binary_op.left);
        free_ast(node->data.binary_op.right);
        return create_boolean_node(result);
    }

    return node;
}

/*
 * TODO: Přidat mocnění atd...
 */
int evaluate_numeric_binary_op(BinaryOpType op, int left, int right)
{
    switch (op)
    {
    case OP_ADD:
        return left + right;
    case OP_SUBTRACT:
        return left - right;
    case OP_MULTIPLY:
        return left * right;
    case OP_DIVIDE:
        return right != 0 ? left / right : 0;
    default:
        return 0;
    }
}

/**
 * TODO: Další operace
 */
uint8_t evaluate_boolean_binary_op(BinaryOpType op, uint8_t left, uint8_t right)
{
    switch (op)
    {
    case OP_LOGICAL_OR:
        return left || right;
    case OP_LOGICAL_AND:
        return left && right;
    default:
        return 0;
    }
}

uint8_t evaluate_string_condition_op(CondOpType op, const char *left, const char *right)
{
    switch (op)
    {
    case COND_EQUALS:
        return strcmp(left, right);
    case COND_NOT_EQUALS:
        return !strcmp(left, right);
    default:
        return 0;
    }
}

/**
 * TODO: Možná vracet void pointer a passovat DataType? Protože budu chtít porovnávat třeba stringy a tak
 */
int evaluate_condition_op(CondOpType op, int left, int right)
{
    switch (op)
    {
    case COND_GREATER_THAN:
        return left > right;
    case COND_LESS_THAN:
        return left < right;
    case COND_EQUALS:
        return left == right;
    case COND_NOT_EQUALS:
        return left != right;
    case COND_GREATER_OR_EQUALS:
        return left >= right;
    case COND_LESS_OR_EQUALS:
        return left <= right;
    default:
        return 0;
    }
}

/**
 * TODO: Možná void pointer jako v evaluate_condition_op a pak je mergnout?
 */
uint8_t evaluate_boolean_condition_op(CondOpType op, uint8_t left, uint8_t right)
{
    switch (op)
    {
    case COND_EQUALS:
        return left == right;
    case COND_NOT_EQUALS:
        return left != right;
    default:
        return 0;
    }
}
