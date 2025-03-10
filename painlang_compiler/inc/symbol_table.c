
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"
#include "config.h"
#include "prints.h"

void init_symbol_table(SymbolTable *table)
{
    table->entries = NULL;
    table->functions = NULL;
    table->countF = 0;
    table->count = 0;
    table->current_scope = 0;
}

void add_function(SymbolTable *table, const char *name, int number_of_params)
{
    FunctionEntry *entry = lookup_function(table, name);
    if (entry)
    {
        fprintf(stderr, "Error: Tahle funkce již existuje");
        return;
    }

    printf("Funkce declaration vole: %s \n", name);
    table->functions = realloc(table->functions, sizeof(FunctionEntry) * (table->countF + 1));
    table->functions[table->countF].name = strdup(name);
    table->functions[table->countF].number_of_params = number_of_params;
    table->countF++;
}

FunctionEntry *lookup_function(SymbolTable *table, const char *name)
{

    if (table->functions == NULL && table->countF > 0)
    {
        return NULL;
    }

    for (int i = table->countF - 1; i >= 0; i--)
    {
        if (table->functions[i].name == NULL)
        {
            continue;
        }

        if (strcmp(table->functions[i].name, name) == 0)
        {
            return &table->functions[i];
        }
    }

    return NULL;
}

void enter_scope(SymbolTable *table)
{

    table->current_scope++;
    if (table->current_scope >= MAX_SCOPES)
    {
        fprintf(stderr, "Error: překročili jste maximální scope");
        // Jenom ho vrátíme do posledního možného
        table->current_scope = MAX_SCOPES - 1;
    }

    debug_print("Entering scope");
}

void exit_scope(SymbolTable *table)
{
    if (table->current_scope <= 0)
    {
        fprintf(stderr, "Error: nemůžeš jít pod globální scope");
        exit(1);
    }

    debug_print("Exiting scope");

    int i = 0;
    while (i < table->count)
    {
        // Smažeme všechno z current scopu
        int i = 0;
        while (i < table->count)
        {
            if (table->entries[i].scope_level == table->current_scope)
            {
                free(table->entries[i].name);

                for (int j = i; j < table->count - 1; j++)
                {
                    table->entries[j] = table->entries[j + 1];
                }

                table->count--;
            }
            else
            {
                i++;
            }
        }

        if (table->count > 0)
        {
            table->entries = realloc(table->entries, table->count * sizeof(SymbolEntry));
        }
        else
        {
            free(table->entries);
            table->entries = NULL;
        }

        table->current_scope--;
    }
}

SymbolEntry *lookup_variable(SymbolTable *table, const char *name)
{
    for (int i = table->count - 1; i >= 0; i--) // Prioritizujeme vnitřní scope
    {
        if (strcmp(table->entries[i].name, name) == 0 && table->entries[i].scope_level == table->current_scope)
        {
            return &table->entries[i];
        }
    }
    return NULL;
}
SymbolEntry *lookup_variable_all_scopes(SymbolTable *table, const char *name)
{
    for (int i = table->count - 1; i >= 0; i--)
    {
        if (strcmp(table->entries[i].name, name) == 0)
        {
            return &table->entries[i];
        }
    }
    return NULL;
}
void set_is_used(SymbolTable *table, const char *name)
{
    SymbolEntry *entry = lookup_variable(table, name);
    if (!entry)
    {
        fprintf(stderr, "Error: proměnná neexistuje");
        set_variable(table, name, 0, 0);
        return;
    }

    set_is_used(table, name);
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
        entry = lookup_variable_all_scopes(table, name);
        if (entry) // Existuje mimo inner scope
        {
            entry->value = value;
            entry->is_initialized = is_initialized;
        }
        else
        {
            table->entries = realloc(table->entries, sizeof(SymbolEntry) * (table->count + 1));
            table->entries[table->count].name = strdup(name);
            table->entries[table->count].value = value;
            table->entries[table->count].is_initialized = is_initialized;
            table->entries[table->count].scope_level = table->current_scope;
            table->count++;
        }
    }
}

void free_symbol_table(SymbolTable *table)
{
    for (int i = 0; i < table->count; i++)
    {
        free(table->entries[i].name);
    }
    free(table->entries);
    table->entries = NULL;
    table->count = 0;
    table->current_scope = 0;
}
