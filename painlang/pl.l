%{
#include <stdio.h>
#include "y.tab.h"
#include "prints.h"

%}

%%
;                                                   {debug_print("SEMICOLON "); return SEMICOLON;};
let                                                 {debug_print("DECLARE "); return DECLARE;};
print                                               {debug_print("PRINT "); return PRINT;};
([1-9][0-9]*|0)                                      { yylval.num = atoi(yytext); debug_print("NUMBER "); return NUMBER; };
[a-zA-Z_][a-zA-Z0-9_]*                              { yylval.str = strdup(yytext); debug_print("IDENTIFIER "); return IDENTIFIER; };
=                                                   {debug_print("ASSIGN "); return ASSIGN;};
"-"        {debug_print(""); return '-';}
"{"        {debug_print(""); return '{';}
"}"        {debug_print(""); return '}';}
"+"        {debug_print(""); return '+';}
"*"        {debug_print(""); return '*';}
"/"        {debug_print(""); return '/';}
"("        {debug_print(""); return '(';}
")"        {debug_print(""); return ')';}

.           { }
%%
