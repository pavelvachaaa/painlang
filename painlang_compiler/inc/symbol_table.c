
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

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
SymbolEntry *lookup_variable_all_scopes(SymbolTable *table, const char *name)
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

void set_variable(SymbolTable *table, const char *name, int value, int is_initialized)
{
    SymbolEntry *entry = lookup_variable(table, name);
    // Už jsi definovaná, tak tě aktualizujeme
    if (entry)
    {
        // if (entry->is_const)
        // {
        //     fprintf(stderr, "Error: tahle proměnná je konstantní, nezapisuj do ní vole");
        // }
        entry->value = value;
        entry->is_initialized = is_initialized;
    }
    else
    {
        // Ještě jsi neexistovala, teď už jo
        table->count++;
        table->entries = realloc(table->entries, table->count * sizeof(SymbolEntry));
        table->entries[table->count - 1].name = strdup(name);
        table->entries[table->count - 1].value = value;
        table->entries[table->count - 1].is_initialized = is_initialized;
        // table->entries[table->count - 1].is_initialized = is_const;
    }
}
