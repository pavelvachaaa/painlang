%{
#include <stdio.h>
#include "./inc/ast/ast.h"    
#include "y.tab.h"
#include "./inc/prints.h"


char* process_string(char* text) {
    int len = strlen(text);
    char* result = malloc(len - 1); 
    
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    strncpy(result, text + 1, len - 2);
    result[len - 2] = '\0';
    
    char* src = result;
    char* dest = result;
    
    while (*src) {
        if (*src == '\\' && *(src + 1)) {
            src++;
            switch (*src) {
                case 'n': *dest++ = '\n'; break;
                case 't': *dest++ = '\t'; break;
                case 'r': *dest++ = '\r'; break;
                case '\\': *dest++ = '\\'; break;
                case '"': *dest++ = '"'; break;
                default: *dest++ = *src;
            }
        } else {
            *dest++ = *src;
        }
        src++;
    }
    *dest = '\0';
    
    return result;
}
%}

%%

"//".*                                      { debug_print("SL-COMMENT"); }
"/*"[^*]*"*"([^/][^*]*"*"[^/])*"/" { debug_print("ML-COMMENT"); }

:                                                   {debug_print(":"); return ':';};
;                                                   {debug_print("SEMICOLON "); return SEMICOLON;};
string                                                 {debug_print("string "); return LL_TYPE_STRING;};
number                                                 {debug_print("number "); return LL_TYPE_NUMBER;};
bool                                                  {debug_print("bool"); return LL_TYPE_BOOLEAN;}
true                                                  { yylval.boolean_value = 1;  debug_print("true"); return LITERAL_TRUE;}
false                                                 {yylval.boolean_value = 0;  debug_print("false"); return LITERAL_FALSE;}
let                                                 {debug_print("DECLARE "); return DECLARE;};
print                                               {debug_print("PRINT "); return PRINT;};
function                                               {debug_print("FUNCTION "); return FUNCTION;};
return                                               {debug_print("RETURN "); return RETURN;};
for                                                 {debug_print("FOR "); return FOR;};
if                                                  {debug_print("IF "); return IF;};
else                                                {debug_print("ELSE "); return ELSE;};
([1-9][0-9]*|0)                                     { yylval.num = atoi(yytext); debug_print("NUMBER "); return NUMBER; };
\"([^\\\"]|\\.)*\" { 
    yylval.str = process_string(yytext); 
    debug_print("STRING_LITERAL "); 
    return STRING_LITERAL; 
}
[a-zA-Z_][a-zA-Z0-9_]*                              { yylval.str = strdup(yytext); debug_print("IDENTIFIER "); return IDENTIFIER; };

"=="                                               {debug_print("EQUALS" ); return EQUALS;};
"!="                                                {debug_print("NOT_EQUALS" ); return NOT_EQUALS;};
">="                                                {debug_print("GREAT_OR_EQUALS" ); return GREAT_OR_EQUALS;};
"<="                                                {debug_print("LESS_OR_EQUALS" ); return LESS_OR_EQUALS;};
">"                                                 {debug_print("GREATER_THAN" ); return GREATER_THAN;};
"<"                                                 {debug_print("LESS_THAN" ); return LESS_THAN;};
","                                                 {debug_print("," ); return ',';};
=                                                   {debug_print("ASSIGN "); return ASSIGN;};


"!"                                                   {debug_print("UNARY_NOT "); return UNARY_OP_NOT;};
"&"                                                  {debug_print("BINARY_AND "); return BINARY_OP_AND;};
"|"                                                   {debug_print("BINARY_OR "); return BINARY_OP_OR;};
"^"                                                   {debug_print("BINARY_XOR "); return BINARY_OP_XOR;};




"+="                                                { return PLUS_ASSIGN; }
"-="                                                { return MINUS_ASSIGN; }
"*="                                                { return MULT_ASSIGN; }
"/="                                                { return DIV_ASSIGN; }
"++"                                                  {debug_print("++"); return DOUBLE_PLUS;};
"--"                                                  {debug_print("--"); return DOUBLE_MINUS;};
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
