/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "pl.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prints.h"
#include "./inc/ast/ast.h"
#include "./inc/printers/ast/ast_printer.h"
#include "./inc/printers/symbol/symbol_printer.h"
#include "./inc/ir/ir.h"
#include <unistd.h>
#include "lexer.h"

// #include "./inc/import_handler.h"
int yylex();
int yyparse();
void yyerror(const char *str) {
    fprintf(stderr, "error: %s\n", str);
}

int yywrap() {
    return 1;
}


ASTNode *ast_root = NULL;
ASTNode *imported_ast = NULL;

void print_usage(const char *prog_name) {
    fprintf(stderr, "Použití: %s -i input_file [-o output-file] [-O] [-m ir_file]  \n", prog_name);
}



SymbolTable *table = NULL;
  FILE *file = NULL;
int main(int argc, char **argv) {
        table = malloc(sizeof(SymbolTable));
        if(!table) {
            fprintf(stderr,"ale notak");
            return EXIT_FAILURE;
        }

        init_symbol_table(table);


    
    const char *output_file = NULL;
    const char *ir_file = NULL;
    const char *input_file = NULL;
    
    int optimizeLevel = 0;

    int opt;
    while ((opt = getopt(argc, argv, "i:o:m:O")) != -1) {
        switch (opt) {
            case 'm': // mezikod
                ir_file = optarg;
                break;
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'O':
                optimizeLevel = 1;
                break;
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (!input_file) {
        fprintf(stderr, "Error: Potřebuji vstupní soubor.\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if(!output_file) {
        output_file = "output.asm";
    }
    
    if(!ir_file) {
        ir_file = "output.ir";
    }

    file = fopen(input_file, "r");
    if (!file) {
        perror("ale vole");
        return EXIT_FAILURE;
    }

    yyin = file;
    yyparse();
    fclose(file);
    // ten level pak passovat do funkce a podle toho rozhodovat jak optimalizovat
    if (optimizeLevel == 1) {
        optimize_program(ast_root,table);
    }

    find_and_set_variables(ast_root, table);

    printf("============ AST_TREE_START ============ \n");
    print_ast(ast_root);
    printf("============ AST_TREE_END ============ \n");


    print_symbol_table(table);
    // IR reprezentace a struktura
    IRProgram *program = malloc(sizeof(IRProgram));
    if (!program) {
        fprintf(stderr,"dopíči už");
        return EXIT_FAILURE;
    }

    ir_init(program, table);
    generate_ir_from_ast(ast_root, program);
     output_ir_to_file(program, ir_file);

    // //NASM
    generate_nasm_from_ir(program, table, output_file);
    
    ir_free(program);
    free_ast(ast_root);
    //freeSymbolTable();
    
    return 0;
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 330 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 343 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  52
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   141

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    49,    46,    44,    53,    45,     2,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    50,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    14,    17,    19,
      22,    24,    26,    28,    30,    33,    36,    38,    44,    49,
      53,    57,    61,    65,    69,    72,    75,    78,    82,    88,
      90,    92,    94,   104,   106,   108,   112,   116,   120,   124,
     126,   130,   134,   138,   142,   144,   146,   148,   150,   152,
     155,   158,   160,   164,   166,   172,   180,   184,   186,   188,
     190,   192,   194,   196,   197,   198,   204,   213,   215,   216,
     220,   226,   231,   233,   234,   236,   240,   243
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    -1,    56,    -1,    57,    -1,    57,    56,
      -1,    60,     7,    -1,    61,     7,    -1,    69,    -1,    59,
       7,    -1,    72,    -1,    64,    -1,    75,    -1,    58,    -1,
      78,     7,    -1,    81,     7,    -1,    82,    -1,    15,    48,
      70,    49,    72,    -1,     8,    48,    66,    49,    -1,     5,
       6,    66,    -1,     5,    24,    66,    -1,     5,    25,    66,
      -1,     5,    26,    66,    -1,     5,    27,    66,    -1,     5,
      22,    -1,     5,    23,    -1,     4,    62,    -1,     5,    50,
      63,    -1,     5,    50,    63,     6,    66,    -1,    39,    -1,
      40,    -1,    41,    -1,    11,    48,    65,     7,    70,     7,
      60,    49,    72,    -1,    60,    -1,    61,    -1,    66,    44,
      67,    -1,    66,    45,    67,    -1,    66,    32,    67,    -1,
      66,    33,    67,    -1,    67,    -1,    67,    46,    68,    -1,
      67,    47,    68,    -1,    67,    32,    68,    -1,    67,    33,
      68,    -1,    68,    -1,     3,    -1,    14,    -1,    37,    -1,
      38,    -1,    34,    68,    -1,    45,    68,    -1,     5,    -1,
      48,    66,    49,    -1,    78,    -1,     9,    48,    70,    49,
      72,    -1,     9,    48,    70,    49,    72,    10,    72,    -1,
      66,    71,    66,    -1,    16,    -1,    17,    -1,    18,    -1,
      19,    -1,    20,    -1,    21,    -1,    -1,    -1,    51,    73,
      56,    52,    74,    -1,    12,     5,    48,    76,    49,    28,
      63,    72,    -1,    77,    -1,    -1,     5,    50,    63,    -1,
       5,    50,    63,    53,    77,    -1,     5,    48,    79,    49,
      -1,    80,    -1,    -1,    66,    -1,    66,    53,    80,    -1,
      13,    66,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   177,   177,   178,   186,   192,   210,   214,   218,   222,
     226,   230,   232,   233,   234,   235,   236,   243,   250,   257,
     268,   277,   284,   291,   303,   313,   323,   329,   335,   343,
     347,   351,   357,   364,   365,   367,   371,   375,   379,   383,
     391,   395,   399,   403,   408,   415,   419,   423,   427,   431,
     436,   442,   447,   451,   457,   461,   467,   473,   477,   481,
     485,   489,   493,   499,   499,   499,   506,   517,   522,   529,
     537,   552,   559,   564,   570,   576,   586,   594
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "DECLARE", "IDENTIFIER",
  "ASSIGN", "SEMICOLON", "PRINT", "IF", "ELSE", "FOR", "FUNCTION",
  "RETURN", "STRING_LITERAL", "WHILE", "EQUALS", "NOT_EQUALS",
  "GREAT_OR_EQUALS", "LESS_OR_EQUALS", "GREATER_THAN", "LESS_THAN",
  "DOUBLE_PLUS", "DOUBLE_MINUS", "PLUS_ASSIGN", "MINUS_ASSIGN",
  "MULT_ASSIGN", "DIV_ASSIGN", "RETURN_TYPE", "BINARY_OP_OR",
  "BINARY_OP_AND", "BINARY_OP_XOR", "LOGICAL_AND", "LOGICAL_OR",
  "UNARY_OP_NOT", "IMPORT", "AS", "LITERAL_TRUE", "LITERAL_FALSE",
  "LL_TYPE_STRING", "LL_TYPE_NUMBER", "LL_TYPE_BOOLEAN", "INCLUDE",
  "UNARY_MINUS", "'+'", "'-'", "'*'", "'/'", "'('", "')'", "':'", "'{'",
  "'}'", "','", "$accept", "program", "statementList", "statement",
  "whileLoop", "printStatement", "assignment", "varDeclaration", "vardec",
  "typeRule", "forLoop", "forInitExpression", "expression", "term",
  "factor", "ifStatement", "condExpression", "relop", "block", "@1", "@2",
  "funDeclaration", "parameterList", "parameters", "functionCall",
  "argumentList", "arguments", "returnStatement", "empty", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    43,    45,    42,    47,    40,    41,
      58,   123,   125,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    56,    56,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    58,    59,    60,
      60,    60,    60,    60,    60,    60,    61,    62,    62,    63,
      63,    63,    64,    65,    65,    66,    66,    66,    66,    66,
      67,    67,    67,    67,    67,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    69,    69,    70,    71,    71,    71,
      71,    71,    71,    73,    74,    72,    75,    76,    76,    77,
      77,    78,    79,    79,    80,    80,    81,    82
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     2,     2,     1,     2,
       1,     1,     1,     1,     2,     2,     1,     5,     4,     3,
       3,     3,     3,     3,     2,     2,     2,     3,     5,     1,
       1,     1,     9,     1,     1,     3,     3,     3,     3,     1,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     2,
       2,     1,     3,     1,     5,     7,     3,     1,     1,     1,
       1,     1,     1,     0,     0,     5,     8,     1,     0,     3,
       5,     4,     1,     0,     1,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     0,     0,     0,    63,
       0,     3,     4,    13,     0,     0,     0,    11,     8,    10,
      12,     0,     0,    16,     0,    26,     0,    24,    25,     0,
       0,     0,     0,    73,     0,     0,     0,     0,    45,    51,
      46,     0,    47,    48,     0,     0,    76,    39,    44,    53,
       0,    77,     1,     5,     9,     6,     7,    14,    15,     0,
      19,    20,    21,    22,    23,    74,     0,    72,     0,     0,
       0,     0,    33,    34,     0,    68,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
      30,    31,    27,     0,    71,    18,    57,    58,    59,    60,
      61,    62,     0,     0,     0,     0,     0,    67,    52,    37,
      38,    35,    36,    42,    43,    40,    41,     0,    64,     0,
      75,    56,    54,     0,     0,     0,    17,    65,    28,     0,
       0,    69,     0,    55,     0,     0,     0,     0,    70,    66,
      32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,    15,    16,    25,    92,
      17,    74,    69,    47,    48,    18,    70,   102,    19,    51,
     127,    20,   106,   107,    49,    66,    67,    22,    23
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -96
static const yytype_int16 yypact[] =
{
       1,    35,    52,   -40,    -6,    -4,    38,    25,     5,   -96,
      56,   -96,     1,   -96,    44,    53,    54,   -96,   -96,   -96,
     -96,    59,    60,   -96,    21,   -96,    25,   -96,   -96,    25,
      25,    25,    25,    25,    25,    25,    13,    24,   -96,    34,
     -96,    25,   -96,   -96,    25,    25,    81,    51,   -96,   -96,
      25,     1,   -96,   -96,   -96,   -96,   -96,   -96,   -96,    -5,
      81,    81,    81,    81,    81,   -12,    50,   -96,    36,    71,
      58,    95,   -96,   -96,   101,    97,   -96,   -96,    61,    25,
      25,    25,    25,    25,    25,    25,    25,    62,    57,   -96,
     -96,   -96,   117,    25,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,    25,    73,    25,    82,    84,   -96,   -96,    51,
      51,    51,    51,   -96,   -96,   -96,   -96,    73,   -96,    25,
     -96,    81,   121,   127,    -5,   107,   -96,   -96,    81,    73,
     131,    85,    -5,   -96,    88,    97,    73,    73,   -96,   -96,
     -96
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,    -1,   -96,   -96,   -96,   -34,   103,   -96,   -95,
     -96,   -96,    -7,    48,   -37,   -96,   -49,   -96,   -72,   -96,
     -96,   -96,   -96,     6,     3,   -96,    47,   -96,   -96
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      46,    87,    72,    21,    76,     1,     2,    77,    34,     3,
       4,    53,     5,     6,     7,    21,     8,     1,    71,    60,
      79,    80,    61,    62,    63,    64,    65,    68,    38,   131,
      39,   122,    81,    82,    89,    90,    91,   136,    78,    40,
      24,    93,    35,    37,    36,   126,   113,   114,   115,   116,
      88,    54,     9,    50,    21,   123,    52,   133,    26,    41,
      55,    56,    42,    43,   139,   140,    57,    58,    79,    80,
      44,    59,    75,    45,    27,    28,    29,    30,    31,    32,
      81,    82,    33,    83,    84,    95,    65,    96,    97,    98,
      99,   100,   101,    79,    80,   121,   134,    85,    86,    94,
      33,    26,   105,    79,    80,    81,    82,   103,   104,   118,
     108,   117,   128,    79,    80,    81,    82,    27,    28,    29,
      30,    31,    32,   119,     9,    81,    82,   109,   110,   111,
     112,   129,   124,   125,   130,   132,    71,   137,   135,    73,
     120,   138
};

static const yytype_uint8 yycheck[] =
{
       7,    50,    36,     0,    41,     4,     5,    44,    48,     8,
       9,    12,    11,    12,    13,    12,    15,     4,     5,    26,
      32,    33,    29,    30,    31,    32,    33,    34,     3,   124,
       5,   103,    44,    45,    39,    40,    41,   132,    45,    14,
       5,    53,    48,     5,    48,   117,    83,    84,    85,    86,
      51,     7,    51,    48,    51,   104,     0,   129,     6,    34,
       7,     7,    37,    38,   136,   137,     7,     7,    32,    33,
      45,    50,    48,    48,    22,    23,    24,    25,    26,    27,
      44,    45,    48,    32,    33,    49,    93,    16,    17,    18,
      19,    20,    21,    32,    33,   102,   130,    46,    47,    49,
      48,     6,     5,    32,    33,    44,    45,    49,     7,    52,
      49,    49,   119,    32,    33,    44,    45,    22,    23,    24,
      25,    26,    27,     6,    51,    44,    45,    79,    80,    81,
      82,    10,    50,    49,     7,    28,     5,    49,    53,    36,
      93,   135
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     8,     9,    11,    12,    13,    15,    51,
      55,    56,    57,    58,    59,    60,    61,    64,    69,    72,
      75,    78,    81,    82,     5,    62,     6,    22,    23,    24,
      25,    26,    27,    48,    48,    48,    48,     5,     3,     5,
      14,    34,    37,    38,    45,    48,    66,    67,    68,    78,
      48,    73,     0,    56,     7,     7,     7,     7,     7,    50,
      66,    66,    66,    66,    66,    66,    79,    80,    66,    66,
      70,     5,    60,    61,    65,    48,    68,    68,    66,    32,
      33,    44,    45,    32,    33,    46,    47,    70,    56,    39,
      40,    41,    63,    53,    49,    49,    16,    17,    18,    19,
      20,    21,    71,    49,     7,     5,    76,    77,    49,    67,
      67,    67,    67,    68,    68,    68,    68,    49,    52,     6,
      80,    66,    72,    70,    50,    49,    72,    74,    66,    10,
       7,    63,    28,    72,    60,    53,    63,    49,    77,    72,
      72
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 179 "pl.y"
    {
        ast_root = (yyvsp[(1) - (1)].node);
            printf("AST root set in program rule\n");

    }
    break;

  case 4:
#line 187 "pl.y"
    {
        ASTNode **statements = malloc(sizeof(ASTNode*));
        statements[0] = (yyvsp[(1) - (1)].node);
        (yyval.node) = create_statement_list_node(statements, 1);
    }
    break;

  case 5:
#line 193 "pl.y"
    {
        // přidáme příkaz na začátek a uděláme pro něj místo
        int count = (yyvsp[(2) - (2)].node)->data.statement_list.statement_count + 1;
        ASTNode **statements = malloc(sizeof(ASTNode*) * count);
        
        statements[0] = (yyvsp[(1) - (2)].node);
        for (int i = 0; i < (yyvsp[(2) - (2)].node)->data.statement_list.statement_count; i++) {
            statements[i+1] = (yyvsp[(2) - (2)].node)->data.statement_list.statements[i];
        }
        
        (yyval.node) = create_statement_list_node(statements, count);
        
        free((yyvsp[(2) - (2)].node)->data.statement_list.statements);
        free((yyvsp[(2) - (2)].node));
    }
    break;

  case 6:
#line 211 "pl.y"
    {
        (yyval.node) = (yyvsp[(1) - (2)].node);
    }
    break;

  case 7:
#line 215 "pl.y"
    {
        (yyval.node) = (yyvsp[(1) - (2)].node);
    }
    break;

  case 8:
#line 219 "pl.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 9:
#line 223 "pl.y"
    {
        (yyval.node) = (yyvsp[(1) - (2)].node);
    }
    break;

  case 10:
#line 227 "pl.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 16:
#line 237 "pl.y"
    {
        (yyval.node) = NULL;
    }
    break;

  case 17:
#line 244 "pl.y"
    {
        (yyval.node) = create_while_loop_node((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
        debug_print("Created WHILE_LOOP node\n");
    }
    break;

  case 18:
#line 251 "pl.y"
    {
        (yyval.node) = create_print_node((yyvsp[(3) - (4)].node));
        debug_print("Created PRINT node\n");
    }
    break;

  case 19:
#line 258 "pl.y"
    {
        // Jinak je problém s for loopem sakra
        // if(!lookup_variable(table, $1)) {
        //     printf("\n Proměnná %s neexistuje!\n", $1);
        //     return 1;
        // }

        (yyval.node) = create_assignment_node((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].node));
        debug_print("Created ASSIGNMENT node for '%s'\n", (yyvsp[(1) - (3)].str));
    }
    break;

  case 20:
#line 269 "pl.y"
    {
        ASTNode *var_node = create_variable_node((yyvsp[(1) - (3)].str));
        
        ASTNode *add_node = create_binary_op_node(OP_ADD, var_node, (yyvsp[(3) - (3)].node));
        
        (yyval.node) = create_assignment_node((yyvsp[(1) - (3)].str), add_node);
        debug_print("Created += node for '%s'\n", (yyvsp[(1) - (3)].str));
    }
    break;

  case 21:
#line 278 "pl.y"
    {
        ASTNode *var_node = create_variable_node((yyvsp[(1) - (3)].str));
        ASTNode *sub_node = create_binary_op_node(OP_SUBTRACT, var_node, (yyvsp[(3) - (3)].node));
        (yyval.node) = create_assignment_node((yyvsp[(1) - (3)].str), sub_node);
        debug_print("Created -= node for '%s'\n", (yyvsp[(1) - (3)].str));
    }
    break;

  case 22:
#line 285 "pl.y"
    {
        ASTNode *var_node = create_variable_node((yyvsp[(1) - (3)].str));
        ASTNode *mult_node = create_binary_op_node(OP_MULTIPLY, var_node, (yyvsp[(3) - (3)].node));
        (yyval.node) = create_assignment_node((yyvsp[(1) - (3)].str), mult_node);
        debug_print("Created *= node for '%s'\n", (yyvsp[(1) - (3)].str));
    }
    break;

  case 23:
#line 292 "pl.y"
    {
        ASTNode *var_node = create_variable_node((yyvsp[(1) - (3)].str));
        ASTNode *div_node = create_binary_op_node(OP_DIVIDE, var_node, (yyvsp[(3) - (3)].node));
        debug_print("Created /= node for '%s'\n", (yyvsp[(1) - (3)].str));
    }
    break;

  case 24:
#line 304 "pl.y"
    {
        /* For var++, create var = var + 1 */
        ASTNode *var_node = create_variable_node((yyvsp[(1) - (2)].str));
        ASTNode *num_node = create_number_node(1);
        ASTNode *add_node = create_binary_op_node(OP_ADD, var_node, num_node);
        (yyval.node) = create_assignment_node((yyvsp[(1) - (2)].str), add_node);
        debug_print("Created ++ node for '%s'\n", (yyvsp[(1) - (2)].str));
    }
    break;

  case 25:
#line 314 "pl.y"
    {
        ASTNode *var_node = create_variable_node((yyvsp[(1) - (2)].str));
        ASTNode *num_node = create_number_node(1);
        ASTNode *sub_node = create_binary_op_node(OP_SUBTRACT, var_node, num_node);
        (yyval.node) = create_assignment_node((yyvsp[(1) - (2)].str), sub_node);
        debug_print("Created -- node for '%s'\n", (yyvsp[(1) - (2)].str));
    }
    break;

  case 26:
#line 324 "pl.y"
    {
        (yyval.node) = (yyvsp[(2) - (2)].node);
    }
    break;

  case 27:
#line 330 "pl.y"
    {
        (yyval.node) = create_var_declaration_node((yyvsp[(1) - (3)].str), NULL);
        (yyval.node)->type_annotation = (yyvsp[(3) - (3)].num);
        debug_print("Created VAR_DECLARATION node for '%s' with no init\n", (yyvsp[(1) - (3)].str));
    }
    break;

  case 28:
#line 336 "pl.y"
    {
        (yyval.node) = create_var_declaration_node((yyvsp[(1) - (5)].str), (yyvsp[(5) - (5)].node));
        (yyval.node)->type_annotation = (yyvsp[(3) - (5)].num);
        debug_print("Created VAR_DECLARATION node for '%s' with init\n", (yyvsp[(1) - (5)].str));
    }
    break;

  case 29:
#line 344 "pl.y"
    {
        (yyval.num) = TYPE_STRING;
    }
    break;

  case 30:
#line 348 "pl.y"
    {
        (yyval.num) = TYPE_NUMBER;
    }
    break;

  case 31:
#line 352 "pl.y"
    {
        (yyval.num) = TYPE_BOOLEAN;
    }
    break;

  case 32:
#line 358 "pl.y"
    {
        (yyval.node) = create_for_loop_node((yyvsp[(3) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(9) - (9)].node));
        debug_print("Created FOR_LOOP node\n");
    }
    break;

  case 33:
#line 364 "pl.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 34:
#line 365 "pl.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 35:
#line 368 "pl.y"
    {
        (yyval.node) = create_binary_op_node(OP_ADD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 36:
#line 372 "pl.y"
    {
        (yyval.node) = create_binary_op_node(OP_SUBTRACT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 37:
#line 376 "pl.y"
    {
        (yyval.node) = create_binary_op_node(OP_LOGICAL_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 38:
#line 380 "pl.y"
    {
        (yyval.node) = create_binary_op_node(OP_LOGICAL_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 39:
#line 384 "pl.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 40:
#line 392 "pl.y"
    {
        (yyval.node) = create_binary_op_node(OP_MULTIPLY, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 41:
#line 396 "pl.y"
    {
        (yyval.node) = create_binary_op_node(OP_DIVIDE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 42:
#line 400 "pl.y"
    {
        (yyval.node) = create_binary_op_node(OP_LOGICAL_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 43:
#line 404 "pl.y"
    {
        (yyval.node) = create_binary_op_node(OP_LOGICAL_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 44:
#line 409 "pl.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 45:
#line 416 "pl.y"
    {
        (yyval.node) = create_number_node((yyvsp[(1) - (1)].num));
    }
    break;

  case 46:
#line 420 "pl.y"
    {
        (yyval.node) = create_string_node((yyvsp[(1) - (1)].str));
    }
    break;

  case 47:
#line 424 "pl.y"
    {
        (yyval.node) = create_boolean_node((yyvsp[(1) - (1)].boolean_value));
    }
    break;

  case 48:
#line 428 "pl.y"
    {
        (yyval.node) = create_boolean_node((yyvsp[(1) - (1)].boolean_value));
    }
    break;

  case 49:
#line 432 "pl.y"
    {
        (yyval.node) = create_unary_op_node(OP_LOGICAL_NOT, (yyvsp[(2) - (2)].node));
        debug_print("Created UNARY_OP_NOT node\n");
    }
    break;

  case 50:
#line 437 "pl.y"
    {
        (yyval.node) = create_unary_op_node(OP_UNARY_MINUS, (yyvsp[(2) - (2)].node));
        debug_print("Created UNARY_OP_MINUS node\n");
    }
    break;

  case 51:
#line 443 "pl.y"
    {
        (yyval.node) = create_variable_node((yyvsp[(1) - (1)].str));
    }
    break;

  case 52:
#line 448 "pl.y"
    {
        (yyval.node) = (yyvsp[(2) - (3)].node);
    }
    break;

  case 53:
#line 452 "pl.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 54:
#line 458 "pl.y"
    {
        (yyval.node) = create_if_node((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL);
    }
    break;

  case 55:
#line 462 "pl.y"
    {
        (yyval.node) = create_if_node((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node));
    }
    break;

  case 56:
#line 468 "pl.y"
    {
        (yyval.node) = create_condition_node((yyvsp[(2) - (3)].cond_op), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 57:
#line 474 "pl.y"
    {
        (yyval.cond_op) = COND_EQUALS;
    }
    break;

  case 58:
#line 478 "pl.y"
    {
        (yyval.cond_op) = COND_NOT_EQUALS;
    }
    break;

  case 59:
#line 482 "pl.y"
    {
        (yyval.cond_op) = COND_GREATER_OR_EQUALS;
    }
    break;

  case 60:
#line 486 "pl.y"
    {
        (yyval.cond_op) = COND_LESS_OR_EQUALS;
    }
    break;

  case 61:
#line 490 "pl.y"
    {
        (yyval.cond_op) = COND_GREATER_THAN;
    }
    break;

  case 62:
#line 494 "pl.y"
    {
        (yyval.cond_op) = COND_LESS_THAN;
    }
    break;

  case 63:
#line 499 "pl.y"
    { enter_scope(table); }
    break;

  case 64:
#line 499 "pl.y"
    { exit_scope(table);  }
    break;

  case 65:
#line 500 "pl.y"
    {
        (yyval.node) = (yyvsp[(3) - (5)].node);
    }
    break;

  case 66:
#line 507 "pl.y"
    {
    // ten count kvůli tomu, že pojedeme scope odznova a potřebuji vědět kolik jich bude..
    (yyval.node) = create_function_declaration_node((yyvsp[(2) - (8)].str), (yyvsp[(4) - (8)].param_list).names, (yyvsp[(4) - (8)].param_list).count, (yyvsp[(4) - (8)].param_list).param_types, (yyvsp[(7) - (8)].num), (yyvsp[(8) - (8)].node));
    debug_print("Created FUNCTION_DECLARATION node for '%s' with %d parameters\n", (yyvsp[(2) - (8)].str), (yyvsp[(4) - (8)].param_list).count);
    // Zaeviduju tě, ale pozor v optimalitaci zkontrolovat jestli se volá a kdyžtak odstranit
    add_function(table, (yyvsp[(2) - (8)].str), (yyvsp[(4) - (8)].param_list).count,  (yyvsp[(7) - (8)].num));


}
    break;

  case 67:
#line 518 "pl.y"
    {
        (yyval.param_list) = (yyvsp[(1) - (1)].param_list);
    }
    break;

  case 68:
#line 522 "pl.y"
    {
        (yyval.param_list).names = NULL;
        (yyval.param_list).param_types = NULL;
        (yyval.param_list).count = 0;    
    }
    break;

  case 69:
#line 530 "pl.y"
    {
        (yyval.param_list).names = malloc(sizeof(char*));
        (yyval.param_list).param_types = malloc(sizeof(DataType));
        (yyval.param_list).names[0] = (yyvsp[(1) - (3)].str);
        (yyval.param_list).param_types[0] = (yyvsp[(3) - (3)].num); 
        (yyval.param_list).count = 1;
    }
    break;

  case 70:
#line 538 "pl.y"
    {
        (yyval.param_list).names = malloc(sizeof(char*) * ((yyvsp[(5) - (5)].param_list).count + 1));
        (yyval.param_list).param_types = malloc(sizeof(DataType) * ((yyvsp[(5) - (5)].param_list).count + 1));
        (yyval.param_list).names[0] = (yyvsp[(1) - (5)].str);
        (yyval.param_list).param_types[0] = (yyvsp[(3) - (5)].num); 

        memcpy((yyval.param_list).names + 1, (yyvsp[(5) - (5)].param_list).names, sizeof(char*) * (yyvsp[(5) - (5)].param_list).count);
        memcpy((yyval.param_list).param_types + 1, (yyvsp[(5) - (5)].param_list).param_types, sizeof(DataType) * (yyvsp[(5) - (5)].param_list).count);

        (yyval.param_list).count = (yyvsp[(5) - (5)].param_list).count + 1;
        free((yyvsp[(5) - (5)].param_list).names);
    }
    break;

  case 71:
#line 553 "pl.y"
    {
        (yyval.node) = create_function_call_node((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].arg_list).args, (yyvsp[(3) - (4)].arg_list).count);
        debug_print("Created FUNCTION_CALL node for '%s' with %d arguments\n", (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].arg_list).count);
    }
    break;

  case 72:
#line 560 "pl.y"
    {
        (yyval.arg_list) = (yyvsp[(1) - (1)].arg_list);
    }
    break;

  case 73:
#line 564 "pl.y"
    {
        (yyval.arg_list).args = NULL;
        (yyval.arg_list).count = 0;
    }
    break;

  case 74:
#line 571 "pl.y"
    {
        (yyval.arg_list).args = malloc(sizeof(ASTNode*));
        (yyval.arg_list).args[0] = (yyvsp[(1) - (1)].node);
        (yyval.arg_list).count = 1;
    }
    break;

  case 75:
#line 577 "pl.y"
    {
        (yyval.arg_list).args = malloc(sizeof(ASTNode*) * ((yyvsp[(3) - (3)].arg_list).count + 1));
        (yyval.arg_list).args[0] = (yyvsp[(1) - (3)].node);
        memcpy((yyval.arg_list).args + 1, (yyvsp[(3) - (3)].arg_list).args, sizeof(ASTNode*) * (yyvsp[(3) - (3)].arg_list).count);
        (yyval.arg_list).count = (yyvsp[(3) - (3)].arg_list).count + 1;
        free((yyvsp[(3) - (3)].arg_list).args);
    }
    break;

  case 76:
#line 587 "pl.y"
    {
    (yyval.node) = create_return_node((yyvsp[(2) - (2)].node));
    debug_print("Created RETURN node\n");
}
    break;


/* Line 1267 of yacc.c.  */
#line 2230 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 596 "pl.y"



