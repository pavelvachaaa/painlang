#ifndef AST_EVALUATOR_H
#define AST_EVALUATOR_H

#include "ast.h"
ASTNode *evaluate_binary_op_node(ASTNode *node, SymbolTable *table);
ASTNode *evaluate_unary_op_node(ASTNode *node, SymbolTable *table);

int evaluate_numeric_binary_op(BinaryOpType op, int left, int right);
u_int8_t evaluate_boolean_binary_op(BinaryOpType op, u_int8_t left, u_int8_t right);
int evaluate_condition_op(CondOpType op, int left, int right);
u_int8_t evaluate_boolean_condition_op(CondOpType op, u_int8_t left, u_int8_t right);
u_int8_t evaluate_string_condition_op(CondOpType op, const char *left, const char *right);
#endif