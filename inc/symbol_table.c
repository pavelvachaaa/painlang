
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

void add_function(SymbolTable *table, const char *name, int number_of_params, DataType return_type)
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
    table->functions[table->countF].return_type = return_type;
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

// Mám to jako optimalizaci... ale bez toho is_modified_loop to budě dělat píčoviny
// Takže to pak dát někde při setování...
void update_loop_modified_variables(SymbolTable *main_table, SymbolTable *loop_table)
{
    for (int i = 0; i < loop_table->count; i++)
    {
        if (loop_table->entries[i].is_modified_in_loop)
        {
            // TODO: Promyslet to s těma zasranejme scopama a vnitřní tabulkou for loopu

            SymbolEntry *main_entry = lookup_variable(main_table, loop_table->entries[i].name);
            if (main_entry)
            {
                main_entry->is_modified_in_loop = 1;
                main_entry->is_used = 1;
                main_entry->is_initialized = 0; // TODO: O tomhle popřemýšlet..
            }
        }
    }
}

void merge_symbol_table(SymbolTable *loop_table, SymbolTable *main_table)
{
    for (int i = 0; i < loop_table->count; i++)
    {
        SymbolEntry *loop_entry = &loop_table->entries[i];
        SymbolEntry *main_entry = lookup_variable(main_table, loop_entry->name);

        if (main_entry)
        { // Merguj, když existuje o téhle variable záznam i v mainu

            main_entry->is_modified_in_loop = loop_entry->is_modified_in_loop;
            main_entry->is_used = loop_entry->is_used;
        }
    }
}

void copy_symbol_table(SymbolTable *dest, SymbolTable *src)
{
    if (!dest || !src)
        return;

    init_symbol_table(dest);

    for (int i = 0; i < src->count; i++)
    {
        if (src->entries[i].data_type == TYPE_STRING)
        {
            set_variable(dest, src->entries[i].name,
                         src->entries[i].string_value,
                         src->entries[i].is_initialized, TYPE_STRING);
        }
        else if (src->entries[i].data_type == TYPE_BOOLEAN)
        {
            set_variable(dest, src->entries[i].name,
                         &(src->entries[i].boolean_value),
                         src->entries[i].is_initialized, TYPE_BOOLEAN);
        }
        else
        {
            set_variable(dest, src->entries[i].name,
                         &(src->entries[i].value),
                         src->entries[i].is_initialized, TYPE_NUMBER);
        }
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
    return 0;
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
        return;
    }

    if (entry)
    {
        entry->is_used = 1;
        entry->is_modified_in_loop = 1;
    }
}

void set_variable_in_use(SymbolTable *table, const char *name, void *value, int is_initialized, DataType data_type)
{
    set_variable(table, name, value, is_initialized, data_type);
    set_is_used(table, name);
}

void set_variable(SymbolTable *table, const char *name, void *value, int is_initialized, DataType data_type)
{
    SymbolEntry *entry = lookup_variable(table, name);

    if (entry) // Jsi v hlavním scopu?
    {
        entry->is_initialized = is_initialized;

        if (entry->data_type != data_type)
        {
            fprintf(stderr, "Error: Datové typy nesedí '%s'\n", name);
            return;
        }

        if (data_type == TYPE_NUMBER)
        {
            entry->value = *(int *)value;
        }
        else if (data_type == TYPE_STRING)
        {
            free(entry->string_value);
            entry->string_value = strdup((char *)value);
        }
        else if (data_type == TYPE_BOOLEAN)
        {
            debug_print("I have set boolean");

            entry->boolean_value = *(u_int8_t *)value;
        }
    }
    else // Není v aktuálním scopu? Podívej se do outer scopu
    {
        entry = lookup_variable_all_scopes(table, name);

        if (entry)
        {
            entry->is_initialized = is_initialized;

            if (entry->data_type != data_type)
            {
                fprintf(stderr, "[Error]: Datové typy nesedí '%s'\n", name);
                return;
            }

            if (data_type == TYPE_NUMBER)
            {
                entry->value = *(int *)value;
            }
            else if (data_type == TYPE_STRING)
            {
                free(entry->string_value);
                entry->string_value = strdup((char *)value);
            }
            else if (data_type == TYPE_BOOLEAN)
            {
                debug_print("I have set boolean");
                entry->boolean_value = *(u_int8_t *)value;
            }
        }
        else // Není ani v outerscopu, vytvoříme pro tebe místo
        {
            table->entries = realloc(table->entries, sizeof(SymbolEntry) * (table->count + 1));
            if (!table->entries)
            {
                fprintf(stderr, "Error: MemAlloc Fail \n");
                return;
            }

            entry = &table->entries[table->count];
            entry->name = strdup(name);
            entry->is_initialized = is_initialized;
            entry->scope_level = table->current_scope;
            entry->data_type = data_type;

            if (data_type == TYPE_NUMBER)
            {
                entry->value = *(int *)value;
                entry->string_value = NULL;
            }
            else if (data_type == TYPE_STRING)
            {
                entry->string_value = strdup((char *)value);
                entry->value = 0;
            }
            else if (data_type == TYPE_BOOLEAN)
            {
                entry->boolean_value = *(u_int8_t *)value;
            }

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
