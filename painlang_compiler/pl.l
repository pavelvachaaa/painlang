%{
#include <stdio.h>
#include "ast.h"    // Include this before y.tab.h
#include "y.tab.h"
#include "prints.h"

%}

%%

"//".*               { debug_print("SL-COMMENT"); }
"/*"[^*]*"*"([^/][^*]*"*"[^/])*"/" { debug_print("ML-COMMENT"); }


;                                                   {debug_print("SEMICOLON "); return SEMICOLON;};
let                                                 {debug_print("DECLARE "); return DECLARE;};
print                                               {debug_print("PRINT "); return PRINT;};
function                                               {debug_print("FUNCTION "); return FUNCTION;};
return                                               {debug_print("RETURN "); return RETURN;};
for                                                 {debug_print("FOR "); return FOR;};
if                                                  {debug_print("IF "); return IF;};
else                                                {debug_print("ELSE "); return ELSE;};
([1-9][0-9]*|0)                                     { yylval.num = atoi(yytext); debug_print("NUMBER "); return NUMBER; };
[a-zA-Z_][a-zA-Z0-9_]*                              { yylval.str = strdup(yytext); debug_print("IDENTIFIER "); return IDENTIFIER; };

"=="                                               {debug_print("EQUALS" ); return EQUALS;};
"!="                                                {debug_print("NOT_EQUALS" ); return NOT_EQUALS;};
">="                                                {debug_print("GREAT_OR_EQUALS" ); return GREAT_OR_EQUALS;};
"<="                                                {debug_print("LESS_OR_EQUALS" ); return LESS_OR_EQUALS;};
">"                                                 {debug_print("GREATER_THAN" ); return GREATER_THAN;};
"<"                                                 {debug_print("LESS_THAN" ); return LESS_THAN;};
","                                                 {debug_print("," ); return ',';};
=                                                   {debug_print("ASSIGN "); return ASSIGN;};


"-"                                                 {debug_print("MINUSOP "); return '-';}
"{"                                                 {debug_print("LBR "); return '{';}
"}"                                                 {debug_print("RBR "); return '}';}
"+"                                                 {debug_print("PLUSOP "); return '+';}
"*"                                                 {debug_print("MULTOP "); return '*';}
"/"                                                 {debug_print("DIVOP "); return '/';}
"("                                                 {debug_print("LB "); return '(';}
")"                                                 {debug_print("RB "); return ')';}

.           { }
%%
