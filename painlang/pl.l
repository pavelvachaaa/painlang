%{
#include <stdio.h>
#include "y.tab.h"
%}
%%
;                                                   {printf("SEMICOLON "); return  SEMICOLON;};
let                                                 {printf("DECLARE "); return DECLARE;};
([1-9][0-9]*|0)                                      { yylval.num = atoi(yytext); printf("NUMBER "); return NUMBER; };
[a-zA-Z_][a-zA-Z0-9_]*                              { yylval.str = strdup(yytext); printf("IDENTIFIER "); return IDENTIFIER; };
=                                                   {printf("ASSIGN "); return ASSIGN;};
%%
