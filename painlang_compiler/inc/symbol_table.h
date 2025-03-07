#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    SYMBOL_VAR,
    SYMBOL_PARAM,
    SYMBOL_ARG,
} SymbolType;

typedef struct
{
    char *name;
    int value;
    int is_initialized;
    int is_modified_in_loop;
    int is_used;
    SymbolType type;
    int scope_level; // Tohle je tak messy až to není pěkný 
    // Viděl jsem v nějakých implementacích, že tam měli něco jako block owner struct pointer..  ale to je mimo můj scope už

    // int is_const;
} SymbolEntry;

typedef struct
{
    SymbolEntry *entries;
    int count;
    int current_scope;
} SymbolTable;

void init_symbol_table(SymbolTable *table);
SymbolEntry *lookup_variable(SymbolTable *table, const char *name);
SymbolEntry *lookup_variable_all_scopes(SymbolTable *table, const char *name);

void set_variable(SymbolTable *table, const char *name, int value, int is_initialized);
void enter_scope(SymbolTable *table);
void exit_scope(SymbolTable *table);

void print_symbol_table(SymbolTable *table);