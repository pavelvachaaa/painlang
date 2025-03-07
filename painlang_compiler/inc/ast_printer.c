#include <stdio.h>

#include "ast_printer.h"


void print_ast_helper(ASTNode *node, int indent)
{
    if (!node)
        return;

    for (int i = 0; i < indent; i++)
        printf("    ");

    switch (node->type)
    {
    case NODE_PROGRAM:
        printf("Program\n");
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
            print_ast_helper(node->data.statement_list.statements[i], indent + 1);
        break;
    case NODE_STATEMENT_LIST:
        printf("Statement List\n");
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
            print_ast_helper(node->data.statement_list.statements[i], indent + 1);
        break;
    case NODE_VAR_DECLARATION:
        printf("Var Declaration: %s\n", node->data.var_declaration.var_name);
        print_ast_helper(node->data.var_declaration.init_expr, indent + 1);
        break;
    case NODE_ASSIGNMENT:
        printf("Assignment: %s\n", node->data.assignment.var_name);
        print_ast_helper(node->data.assignment.value, indent + 1);
        break;
    case NODE_PRINT:
        printf("Print\n");
        print_ast_helper(node->data.print.expr, indent + 1);
        break;
    case NODE_IF:
        printf("If Statement\n");
        print_ast_helper(node->data.if_statement.condition, indent + 1);
        print_ast_helper(node->data.if_statement.if_block, indent + 1);
        if (node->data.if_statement.else_block)
            print_ast_helper(node->data.if_statement.else_block, indent + 1);
        break;
    case NODE_BINARY_OP:
        printf("Binary Operation\n");
        print_ast_helper(node->data.binary_op.left, indent + 1);
        print_ast_helper(node->data.binary_op.right, indent + 1);
        break;
    case NODE_VARIABLE:
        printf("Variable: %s\n", node->data.variable.name);
        break;
    case NODE_NUMBER:
        printf("Number: %d\n", node->data.number.value);
        break;
    case NODE_FOR_LOOP:
        printf("For Loop\n");
        print_ast_helper(node->data.for_loop.init_expression, indent + 1);
        print_ast_helper(node->data.for_loop.condition, indent + 1);
        print_ast_helper(node->data.for_loop.update, indent + 1);
        print_ast_helper(node->data.for_loop.body, indent + 1);
        break;
    case NODE_CONDITION:
        printf("Condition\n");
        print_ast_helper(node->data.condition.left, indent + 1);
        print_ast_helper(node->data.condition.right, indent + 1);
        break;
    default:
        printf("Unknown Node\n");
        break;
    }
}

void print_ast(ASTNode *root)
{
    print_ast_helper(root, 0);
}
