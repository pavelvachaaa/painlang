#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_VARS 100
#define MAX_SCOPES 10

typedef struct
{
    char name[32];
    int value;
} Variable;

typedef struct
{
    Variable vars[MAX_VARS];
    int varCount;
} Scope;

void initSymbolTable();
void freeSymbolTable();
void enterScope();
void exitScope();
void setSymbol(char *name, int value);
int getSymbol(char *name);

#endif
