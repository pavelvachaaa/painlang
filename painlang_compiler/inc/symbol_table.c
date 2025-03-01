#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "prints.h"

static Scope scopes[MAX_SCOPES];
static int scopeLevel = -1;

void initSymbolTable()
{
    scopeLevel = -1;
    enterScope();
}

void freeSymbolTable()
{
    while (scopeLevel >= 0)
    {
        exitScope();
    }
}

void enterScope()
{
    debug_print("-> Entering new scope\n");
    if (scopeLevel < MAX_SCOPES - 1)
    {
        scopeLevel++;
        scopes[scopeLevel].varCount = 0;
    }
    else
    {
        printf("Error: Maximum scope depth exceeded!\n");
    }
}

void exitScope()
{
    if (scopeLevel >= 0)
    {
        scopeLevel--;
    }
    else
    {
        printf("Error: No scope to exit!\n");
    }
    debug_print("-> Exiting scope, returning to scope %d\n", scopeLevel);
}

void setSymbol(char *name, int value)
{
    for (int i = scopes[scopeLevel].varCount - 1; i >= 0; i--)
    {
        if (strcmp(scopes[scopeLevel].vars[i].name, name) == 0)
        {
            scopes[scopeLevel].vars[i].value = value;
            return;
        }
    }

    if (scopes[scopeLevel].varCount < MAX_VARS)
    {
        strcpy(scopes[scopeLevel].vars[scopes[scopeLevel].varCount].name, name);
        scopes[scopeLevel].vars[scopes[scopeLevel].varCount].value = value;
        scopes[scopeLevel].varCount++;
    }
    else
    {
        printf("Error: Variable limit exceeded in current scope!\n");
    }
}

int getSymbol(char *name)
{
    for (int s = scopeLevel; s >= 0; s--)
    {
        for (int i = 0; i < scopes[s].varCount; i++)
        {
            if (strcmp(scopes[s].vars[i].name, name) == 0)
            {
                return scopes[s].vars[i].value;
            }
        }
    }
    printf("Error: Undefined variable '%s'\n", name);
    return 0;
}
