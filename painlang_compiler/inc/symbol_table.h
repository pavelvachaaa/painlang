#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TBA v další iteraci symbol_table
#define MAX_VARS 100
#define MAX_SCOPES 10
#define MAX_PARAMS 10
#define MAX_FUNC_NAME 32
#define MAX_VAR_NAME 32

typedef enum
{
    SYMBOL_VAR,
    SYMBOL_PARAM,
    SYMBOL_FUNC
} SymbolType;

typedef struct
{
    char *name;
    int value;
    int is_initialized;
    int is_modified_in_loop;
    int is_used;
    // int is_const;
} SymbolEntry;

typedef struct
{
    SymbolEntry *entries;
    int count;
} SymbolTable;

void init_symbol_table(SymbolTable *table);
SymbolEntry *lookup_variable(SymbolTable *table, const char *name);
void set_variable(SymbolTable *table, const char *name, int value, int is_initialized);

// void set_const(SymbolTable *table, const char *name, int value);

// #ifndef SYMBOL_TABLE_H
// #define SYMBOL_TABLE_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_VARS 100
// #define MAX_SCOPES 10
// #define MAX_PARAMS 10
// #define MAX_FUNC_NAME 32
// #define MAX_VAR_NAME 32

// typedef enum
// {
//     SYMBOL_VAR,
//     SYMBOL_PARAM,
//     SYMBOL_FUNC
// } SymbolType;

// typedef struct
// {
//     char name[MAX_VAR_NAME];
//     int value;
//     int is_initialized;
//     SymbolType type;
// } Variable;

// typedef struct
// {
//     char name[MAX_FUNC_NAME];
//     Variable params[MAX_PARAMS];
//     int paramCount;
// } Function;

// typedef struct
// {
//     Variable vars[MAX_VARS];
//     Function funcs[MAX_VARS];
//     int varCount;
//     int funcCount;
// } Scope;

// typedef struct
// {
//     Scope scopes[MAX_SCOPES];
//     int currentScope;
// } SymbolTable;

// void init_symbol_table(SymbolTable *table);
// void enter_scope(SymbolTable *table);
// void exit_scope(SymbolTable *table);
// void declare_variable(SymbolTable *table, const char *name, int value, int is_initialized);
// void declare_function(SymbolTable *table, const char *name, const char *param_names[], int param_count);
// void assign_variable(SymbolTable *table, const char *name, int value);
// Variable* lookup_variable(SymbolTable *table, const char *name);
// Function* lookup_function(SymbolTable *table, const char *name);
// void print_symbol_table(SymbolTable *table);

// #endif // SYMBOL_TABLE_H

// // #ifndef SYMBOL_TABLE_H
// // #define SYMBOL_TABLE_H

// // #define MAX_VARS 100
// // #define MAX_SCOPES 10

// // typedef struct
// // {
// //     char name[32];
// //     int value;
// // } Variable;

// // typedef struct
// // {
// //     Variable vars[MAX_VARS];
// //     int varCount;
// // } Scope;

// // void initSymbolTable();
// // void freeSymbolTable();
// // void enterScope();
// // void exitScope();
// // void setSymbol(char *name, int value);
// // int getSymbol(char *name);

// // #endif
