/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     DECLARE = 259,
     IDENTIFIER = 260,
     ASSIGN = 261,
     SEMICOLON = 262,
     PRINT = 263,
     IF = 264,
     ELSE = 265,
     FOR = 266,
     FUNCTION = 267,
     RETURN = 268,
     STRING_LITERAL = 269,
     WHILE = 270,
     EQUALS = 271,
     NOT_EQUALS = 272,
     GREAT_OR_EQUALS = 273,
     LESS_OR_EQUALS = 274,
     GREATER_THAN = 275,
     LESS_THAN = 276,
     DOUBLE_PLUS = 277,
     DOUBLE_MINUS = 278,
     PLUS_ASSIGN = 279,
     MINUS_ASSIGN = 280,
     MULT_ASSIGN = 281,
     DIV_ASSIGN = 282,
     RETURN_TYPE = 283,
     BINARY_OP_OR = 284,
     BINARY_OP_AND = 285,
     BINARY_OP_XOR = 286,
     LOGICAL_AND = 287,
     LOGICAL_OR = 288,
     UNARY_OP_NOT = 289,
     IMPORT = 290,
     AS = 291,
     LITERAL_TRUE = 292,
     LITERAL_FALSE = 293,
     LL_TYPE_STRING = 294,
     LL_TYPE_NUMBER = 295,
     LL_TYPE_BOOLEAN = 296,
     INCLUDE = 297,
     UNARY_MINUS = 298
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define DECLARE 259
#define IDENTIFIER 260
#define ASSIGN 261
#define SEMICOLON 262
#define PRINT 263
#define IF 264
#define ELSE 265
#define FOR 266
#define FUNCTION 267
#define RETURN 268
#define STRING_LITERAL 269
#define WHILE 270
#define EQUALS 271
#define NOT_EQUALS 272
#define GREAT_OR_EQUALS 273
#define LESS_OR_EQUALS 274
#define GREATER_THAN 275
#define LESS_THAN 276
#define DOUBLE_PLUS 277
#define DOUBLE_MINUS 278
#define PLUS_ASSIGN 279
#define MINUS_ASSIGN 280
#define MULT_ASSIGN 281
#define DIV_ASSIGN 282
#define RETURN_TYPE 283
#define BINARY_OP_OR 284
#define BINARY_OP_AND 285
#define BINARY_OP_XOR 286
#define LOGICAL_AND 287
#define LOGICAL_OR 288
#define UNARY_OP_NOT 289
#define IMPORT 290
#define AS 291
#define LITERAL_TRUE 292
#define LITERAL_FALSE 293
#define LL_TYPE_STRING 294
#define LL_TYPE_NUMBER 295
#define LL_TYPE_BOOLEAN 296
#define INCLUDE 297
#define UNARY_MINUS 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 132 "pl.y"
{
    int num;
    u_int8_t boolean_value;
    char *str;
    ASTNode *node;
    CondOpType cond_op;
    struct {
        char **names;
        DataType *param_types;  
        int count;
    } param_list; // Pak to asi mergnout do sebe... Nebo taky ne ten param list musí být prostě jen var_declaration
    struct {
        ASTNode **args;
        int count;
    } arg_list;
}
/* Line 1529 of yacc.c.  */
#line 152 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

