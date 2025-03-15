#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
typedef enum
{
    SYMBOL_VAR,
    SYMBOL_PARAM,
    SYMBOL_ARG,
} SymbolType;

typedef struct
{
    char *name;
    char *string_value;
    int value; // TODO: Pak z toho udělat void* (bude nutné přepsat kompletně uvolňování paměti a získávání hodnot:)))))
    int is_initialized;
    int is_modified_in_loop;
    int is_used;
    uint8_t boolean_value;
    SymbolType type;
    DataType data_type;
    int scope_level; // Tohle je tak messy až to není pěkný
    // Viděl jsem v nějakých implementacích, že tam měli něco jako block owner struct pointer..  ale to je mimo můj scope už

    // int is_const;
} SymbolEntry;

// Je to taková slátanina, chtělo by to vrazit do symbolentry... se symboltype function
typedef struct
{
    char *name;
    int number_of_params;
} FunctionEntry;

typedef struct
{
    SymbolEntry *entries;
    FunctionEntry *functions;
    int count;
    int countF;
    int current_scope;
} SymbolTable;

void init_symbol_table(SymbolTable *table);
SymbolEntry *lookup_variable(SymbolTable *table, const char *name);
SymbolEntry *lookup_variable_all_scopes(SymbolTable *table, const char *name);

void set_variable(SymbolTable *table, const char *name, void *value, int is_initialized, DataType data_type);

void enter_scope(SymbolTable *table);
void exit_scope(SymbolTable *table);

void add_function(SymbolTable *table, const char *name, int number_of_params);
FunctionEntry *lookup_function(SymbolTable *table, const char *name);

void set_is_used(SymbolTable *table, const char *name);

void print_symbol_table(SymbolTable *table);

void free_symbol_table(SymbolTable *table);