
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

// void set_const(SymbolTable *table, const char *name, int value)
// {
//     set_variable(table, name, value, 1);
// }

// #include "symbol_table.h"

// // Initialize the symbol table
// void init_symbol_table(SymbolTable *table)
// {
//     table->currentScope = 0;
//     for (int i = 0; i < MAX_SCOPES; i++)
//     {
//         table->scopes[i].varCount = 0;
//         table->scopes[i].funcCount = 0;
//     }
// }

// // Enter a new scope
// void enter_scope(SymbolTable *table)
// {
//     if (table->currentScope < MAX_SCOPES - 1)
//     {
//         table->currentScope++;
//     }
//     else
//     {
//         printf("Error: Maximum scope limit reached!\n");
//     }
// }

// // Exit the current scope
// void exit_scope(SymbolTable *table)
// {
//     if (table->currentScope > 0)
//     {
//         table->currentScope--;
//     }
//     else
//     {
//         printf("Error: Cannot exit global scope!\n");
//     }
// }

// // Declare a variable in the current scope
// void declare_variable(SymbolTable *table, const char *name, int value, int is_initialized)
// {
//     Scope *currentScope = &table->scopes[table->currentScope];

//     if (currentScope->varCount < MAX_VARS)
//     {
//         Variable *var = &currentScope->vars[currentScope->varCount];
//         strncpy(var->name, name, MAX_VAR_NAME);
//         var->value = value;
//         var->is_initialized = is_initialized;
//         var->type = SYMBOL_VAR;
//         currentScope->varCount++;
//     }
//     else
//     {
//         printf("Error: Maximum variable count reached in this scope!\n");
//     }
// }

// // Declare a function in the current scope
// void declare_function(SymbolTable *table, const char *name, const char *param_names[], int param_count)
// {
//     Scope *currentScope = &table->scopes[table->currentScope];

//     if (currentScope->funcCount < MAX_VARS)
//     {
//         Function *func = &currentScope->funcs[currentScope->funcCount];
//         strncpy(func->name, name, MAX_FUNC_NAME);
//         func->paramCount = param_count;

//         // Add parameters to the function
//         for (int i = 0; i < param_count; i++)
//         {
//             strncpy(func->params[i].name, param_names[i], MAX_VAR_NAME);
//             func->params[i].type = SYMBOL_PARAM;
//             func->params[i].is_initialized = 0; // Params are not initialized by default
//         }

//         currentScope->funcCount++;
//     }
//     else
//     {
//         printf("Error: Maximum function count reached in this scope!\n");
//     }
// }

// // Assign a value to a variable in the current scope
// void assign_variable(SymbolTable *table, const char *name, int value)
// {
//     Variable *var = lookup_variable(table, name);
//     if (var)
//     {
//         var->value = value;
//         var->is_initialized = 1; // Mark the variable as initialized
//     }
//     else
//     {
//         printf("Error: Variable '%s' not declared!\n", name);
//     }
// }

// // Lookup a variable in the current and previous scopes
// Variable *lookup_variable(SymbolTable *table, const char *name)
// {
//     for (int i = table->currentScope; i >= 0; i--)
//     {
//         Scope *currentScope = &table->scopes[i];
//         for (int j = 0; j < currentScope->varCount; j++)
//         {
//             if (strcmp(currentScope->vars[j].name, name) == 0)
//             {
//                 return &currentScope->vars[j];
//             }
//         }
//     }
//     return NULL; // Not found
// }

// // Lookup a function by name in the current and previous scopes
// Function *lookup_function(SymbolTable *table, const char *name)
// {
//     for (int i = table->currentScope; i >= 0; i--)
//     {
//         Scope *currentScope = &table->scopes[i];
//         for (int j = 0; j < currentScope->funcCount; j++)
//         {
//             if (strcmp(currentScope->funcs[j].name, name) == 0)
//             {
//                 return &currentScope->funcs[j];
//             }
//         }
//     }
//     return NULL; // Not found
// }

// // Print all symbols in the table for debugging
// void print_symbol_table(SymbolTable *table)
// {
//     for (int i = 0; i <= table->currentScope; i++)
//     {
//         Scope *currentScope = &table->scopes[i];
//         printf("Scope %d:\n", i);

//         // Print variables
//         printf("  Variables:\n");
//         for (int j = 0; j < currentScope->varCount; j++)
//         {
//             printf("    %s = %d (Initialized: %s)\n", currentScope->vars[j].name,
//                    currentScope->vars[j].value, currentScope->vars[j].is_initialized ? "Yes" : "No");
//         }

//         // Print functions
//         printf("  Functions:\n");
//         for (int j = 0; j < currentScope->funcCount; j++)
//         {
//             printf("    Function %s with %d parameters:\n", currentScope->funcs[j].name, currentScope->funcs[j].paramCount);
//             for (int k = 0; k < currentScope->funcs[j].paramCount; k++)
//             {
//                 printf("      Parameter: %s\n", currentScope->funcs[j].params[k].name);
//             }
//         }
//     }
// }
