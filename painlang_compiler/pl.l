%option header-file="lexer.h"
%x incl

%{
#include <stdio.h>
#include "./inc/ast/ast.h"    
#include "y.tab.h"
#include "./inc/prints.h"
extern FILE *yyin;
int yylex();

#define MAX_INCLUDE_DEPTH 10
#define MAX_INCLUDED_FILES 100

YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

char *included_files[MAX_INCLUDED_FILES];
int included_files_count = 0;

int is_already_included(const char *filename) {
    for (int i = 0; i < included_files_count; i++) {
        if (strcmp(included_files[i], filename) == 0) {
            return 1; 
        }
    }
    return 0;
}


void add_to_included_files(const char *filename) {
    if (included_files_count < MAX_INCLUDED_FILES) {
        included_files[included_files_count] = strdup(filename);
        included_files_count++;
    } else {
        fprintf(stderr, "To už nepůjde... \n");
        exit(EXIT_FAILURE);
    }
}


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



char* process_import(char* file_name) {
    
}

%}


%%
include   BEGIN(incl);

<incl>[ \t]*  // Mezery

<incl>\"[^\"]+\"   {
    char filename[256];

    strncpy(filename, yytext + 1, strlen(yytext) - 2);  
    filename[strlen(yytext) - 2] = '\0';

    if (is_already_included(filename)) {
        debug_print("Přeskoč tento soubor: %s\n", filename);
        BEGIN(INITIAL); // https://westes.github.io/flex/manual/Multiple-Input-Buffers.html#Multiple-Input-Buffers HODNĚ GOOGLENÍ :))
    } else {
        add_to_included_files(filename);

        FILE *new_file = fopen(filename, "r");
        if (!new_file) {
            fprintf(stderr, "Neexistuje: %s\n", filename);
        } else {
            if (include_stack_ptr >= MAX_INCLUDE_DEPTH) {
                fprintf(stderr, "Ponořil ses too deep!\n");
                exit(EXIT_FAILURE);
            }

            include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;

            // dali jsme si na stack aktuální buffer a teď je nutné aktualizovat na nový 
            yyin = new_file;
            yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
        }
    }

    BEGIN(INITIAL);
}

<<EOF>> {
    if (include_stack_ptr > 0) {
        yypop_buffer_state();
        include_stack_ptr--;
    } else {
        yyterminate();
    }
}

"//".*                                      { debug_print("SL-COMMENT"); }
"/*"[^*]*"*"([^/][^*]*"*"[^/])*"/" { debug_print("ML-COMMENT"); }


:                                                   {debug_print(":"); return ':';};
;                                                   {debug_print("SEMICOLON "); return SEMICOLON;};
string                                                 {debug_print("string "); return LL_TYPE_STRING;};
import                                                 {debug_print("IMPORT "); return IMPORT;};
as                                                   {debug_print("AS "); return AS;};
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
"->"                                                {debug_print("RETURN_TYPE "); return RETURN_TYPE;};



"!"                                                   {debug_print("UNARY_NOT "); return UNARY_OP_NOT;};

"&"                                                  {debug_print("BINARY_AND "); return BINARY_OP_AND;};
"|"                                                   {debug_print("BINARY_OR "); return BINARY_OP_OR;};
"^"                                                   {debug_print("BINARY_XOR "); return BINARY_OP_XOR;};

"&&"                                                   {debug_print("LOGICAL_AND "); return LOGICAL_AND;};
"||"                                                   {debug_print("LOGICAL_OR "); return LOGICAL_OR;};





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
