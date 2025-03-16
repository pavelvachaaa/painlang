#ifndef AST_HELPER_H
#define AST_HELPER_H

#include "ast.h"

DataType get_node_data_type(ASTNode *node);
uint8_t is_literal_node(ASTNode *node);
ASTNode *create_node_from_symbol(SymbolEntry *entry);
void set_variable_from_node(SymbolTable *table, const char *name, ASTNode *value_node);

#endif