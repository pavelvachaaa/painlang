%{
#include <stdio.h>
#include "y.tab.h"
// Miluju makra
//#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        do { printf(fmt, __VA_ARGS__); } while (0)
#else
    #define DEBUG_PRINT(fmt, ...) 
#endif

%}

%%
;                                                   {DEBUG_PRINT("SEMICOLON "); return SEMICOLON;};
let                                                 {DEBUG_PRINT("DECLARE "); return DECLARE;};
print                                               {DEBUG_PRINT("PRINT "); return PRINT;};
([1-9][0-9]*|0)                                      { yylval.num = atoi(yytext); DEBUG_PRINT("NUMBER "); return NUMBER; };
[a-zA-Z_][a-zA-Z0-9_]*                              { yylval.str = strdup(yytext); DEBUG_PRINT("IDENTIFIER "); return IDENTIFIER; };
=                                                   {DEBUG_PRINT("ASSIGN "); return ASSIGN;};
"-"        {DEBUG_PRINT(""); return '-';}
"+"        {DEBUG_PRINT(""); return '+';}
"*"        {DEBUG_PRINT(""); return '*';}
"/"        {DEBUG_PRINT(""); return '/';}
"("        {DEBUG_PRINT(""); return '(';}
")"        {DEBUG_PRINT(""); return ')';}

.           { }
%%
