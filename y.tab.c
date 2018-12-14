/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "mini_c.y"

#include "Tag.hpp"
#include "Lexer.hpp"
#include "parser.hpp"
#include "ParseTree.hpp"

extern ParseTree* root;

void yyerror(std::string s);
int yylex();


/* Line 189 of yacc.c  */
#line 85 "y.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GREATER = 258,
     LESS = 259,
     EQUAL = 260,
     NEQUAL = 261,
     T = 262,
     F = 263,
     ADD = 264,
     SUB = 265,
     MUL = 266,
     DIV = 267,
     MOD = 268,
     MINUS = 269,
     ASSIGN = 270,
     POINTER = 271,
     ARRAY = 272,
     ADDR = 273,
     INC = 274,
     DEC = 275,
     BASIC = 276,
     IF = 277,
     ELSE = 278,
     FOR = 279,
     TEMP = 280,
     INDEX = 281,
     NUM = 282,
     REAL = 283,
     ID = 284,
     COMMA = 285,
     FUNC = 286,
     INT = 287,
     FLOAT = 288,
     VOID = 289,
     CONTINUE = 290,
     BREAK = 291,
     RETURN = 292,
     PRINTF = 293,
     PRINTFARG = 294,
     NONTERMINAL = 295
   };
#endif
/* Tokens.  */
#define GREATER 258
#define LESS 259
#define EQUAL 260
#define NEQUAL 261
#define T 262
#define F 263
#define ADD 264
#define SUB 265
#define MUL 266
#define DIV 267
#define MOD 268
#define MINUS 269
#define ASSIGN 270
#define POINTER 271
#define ARRAY 272
#define ADDR 273
#define INC 274
#define DEC 275
#define BASIC 276
#define IF 277
#define ELSE 278
#define FOR 279
#define TEMP 280
#define INDEX 281
#define NUM 282
#define REAL 283
#define ID 284
#define COMMA 285
#define FUNC 286
#define INT 287
#define FLOAT 288
#define VOID 289
#define CONTINUE 290
#define BREAK 291
#define RETURN 292
#define PRINTF 293
#define PRINTFARG 294
#define NONTERMINAL 295




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 207 "y.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   153

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNRULES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    54,     2,     2,
      41,    42,    43,    51,    44,    52,     2,    53,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      55,    45,    56,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    16,    22,    24,    26,
      28,    31,    33,    35,    37,    38,    42,    44,    46,    49,
      53,    55,    57,    61,    64,    66,    69,    71,    73,    76,
      79,    83,    87,    90,    91,    94,    97,    99,   101,   103,
     105,   107,   115,   119,   122,   124,   128,   130,   132,   134,
     138,   142,   144,   148,   152,   156,   158,   161,   164,   169,
     173,   178,   182,   184,   186,   189,   192,   195,   197,   199,
     201,   205,   211,   219,   229,   231,   235,   239,   241,   245
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    59,    -1,    59,    60,    -1,    -1,    62,
      29,    41,    63,    42,    74,    -1,    29,    41,    63,    42,
      74,    -1,    32,    -1,    33,    -1,    34,    -1,    62,    43,
      -1,    61,    -1,    64,    -1,    34,    -1,    -1,    64,    44,
      65,    -1,    65,    -1,    69,    -1,    70,    67,    -1,    67,
      44,    68,    -1,    68,    -1,    71,    -1,    71,    45,    80,
      -1,    70,    71,    -1,    61,    -1,    43,    71,    -1,    72,
      -1,    29,    -1,    29,    73,    -1,    46,    47,    -1,    46,
      27,    47,    -1,    48,    75,    49,    -1,    75,    76,    -1,
      -1,    80,    50,    -1,    66,    50,    -1,    74,    -1,    88,
      -1,    89,    -1,    78,    -1,    77,    -1,    38,    41,    39,
      44,    80,    42,    50,    -1,    37,    80,    50,    -1,    37,
      50,    -1,    91,    -1,    91,    45,    91,    -1,    79,    -1,
      82,    -1,    83,    -1,    82,    51,    83,    -1,    82,    52,
      83,    -1,    86,    -1,    83,    43,    86,    -1,    83,    53,
      86,    -1,    83,    54,    86,    -1,    87,    -1,    84,    20,
      -1,    84,    19,    -1,    84,    46,    80,    47,    -1,    84,
      41,    42,    -1,    84,    41,    85,    42,    -1,    85,    44,
      79,    -1,    79,    -1,    84,    -1,    43,    86,    -1,    19,
      86,    -1,    20,    86,    -1,    29,    -1,    27,    -1,    28,
      -1,    41,    80,    42,    -1,    22,    41,    80,    42,    76,
      -1,    22,    41,    80,    42,    76,    23,    76,    -1,    24,
      41,    80,    50,    80,    50,    80,    42,    76,    -1,    81,
      -1,    81,    55,    81,    -1,    81,    56,    81,    -1,    90,
      -1,    90,     5,    90,    -1,    90,     6,    90,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    26,    26,    31,    34,    38,    40,    45,    47,    49,
      54,    56,    61,    63,    66,    70,    72,    77,    82,    87,
      89,    94,    96,   101,   106,   111,   113,   118,   120,   125,
     127,   132,   137,   140,   144,   146,   148,   150,   152,   154,
     156,   161,   166,   168,   173,   175,   180,   185,   190,   192,
     194,   199,   201,   203,   205,   210,   212,   214,   216,   218,
     220,   225,   227,   232,   234,   236,   238,   243,   245,   247,
     249,   254,   256,   261,   266,   268,   270,   275,   277,   279
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GREATER", "LESS", "EQUAL", "NEQUAL",
  "T", "F", "ADD", "SUB", "MUL", "DIV", "MOD", "MINUS", "ASSIGN",
  "POINTER", "ARRAY", "ADDR", "INC", "DEC", "BASIC", "IF", "ELSE", "FOR",
  "TEMP", "INDEX", "NUM", "REAL", "ID", "COMMA", "FUNC", "INT", "FLOAT",
  "VOID", "CONTINUE", "BREAK", "RETURN", "PRINTF", "PRINTFARG",
  "NONTERMINAL", "'('", "')'", "'*'", "','", "'='", "'['", "']'", "'{'",
  "'}'", "';'", "'+'", "'-'", "'/'", "'%'", "'<'", "'>'", "$accept",
  "start_symbol", "procedures", "procedure", "type",
  "return_type_declarator", "parameters", "parameters_list", "parameter",
  "declaration", "declaration_list", "single_declaration",
  "ID_type_declaration", "type_declarator", "pointer_declaration",
  "ID_declaration", "array_declaration", "block", "statements",
  "statement", "printf_statement", "return_statement", "assignment",
  "expression", "arithmetic_expr", "add_expr", "mult_expr", "postfix_expr",
  "args_list", "unary_expr", "single_expr", "branch_statement",
  "loop_statement", "comparison_expr", "equality_expr", 0
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
     295,    40,    41,    42,    44,    61,    91,    93,   123,   125,
      59,    43,    45,    47,    37,    60,    62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    61,    61,    61,
      62,    62,    63,    63,    63,    64,    64,    65,    66,    67,
      67,    68,    68,    69,    70,    71,    71,    72,    72,    73,
      73,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    77,    78,    78,    79,    79,    80,    81,    82,    82,
      82,    83,    83,    83,    83,    84,    84,    84,    84,    84,
      84,    85,    85,    86,    86,    86,    86,    87,    87,    87,
      87,    88,    88,    89,    90,    90,    90,    91,    91,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     6,     5,     1,     1,     1,
       2,     1,     1,     1,     0,     3,     1,     1,     2,     3,
       1,     1,     3,     2,     1,     2,     1,     1,     2,     2,
       3,     3,     2,     0,     2,     2,     1,     1,     1,     1,
       1,     7,     3,     2,     1,     3,     1,     1,     1,     3,
       3,     1,     3,     3,     3,     1,     2,     2,     4,     3,
       4,     3,     1,     1,     2,     2,     2,     1,     1,     1,
       3,     5,     7,     9,     1,     3,     3,     1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,     0,     7,     8,     9,     3,    11,
       0,    14,     0,    10,     9,    24,     0,    12,    16,    17,
       0,    14,     0,     0,    27,     0,    23,    26,     0,    33,
       6,    15,     0,    28,    25,     0,     0,     0,    29,     5,
       0,     0,     0,     0,    68,    69,    67,     0,     0,     0,
       0,    31,     0,     0,    36,    32,    40,    39,    46,     0,
      74,    47,    48,    63,    51,    55,    37,    38,    77,    44,
      30,    65,    66,     0,     0,    43,     0,     0,     0,    64,
      35,    18,    20,    21,    34,     0,     0,     0,     0,     0,
       0,     0,    57,    56,     0,     0,     0,     0,     0,     0,
       0,    42,     0,    70,     0,     0,    75,    76,    49,    50,
      52,    53,    54,    59,    62,     0,     0,    78,    79,    45,
       0,     0,     0,    19,    22,    60,     0,    58,    71,     0,
       0,    61,     0,     0,     0,    72,     0,    41,     0,    73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     8,    15,    10,    16,    17,    18,    52,
      81,    82,    19,    53,    83,    27,    33,    54,    36,    55,
      56,    57,    58,    59,    60,    61,    62,    63,   115,    64,
      65,    66,    67,    68,    69
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -110
static const yytype_int8 yypact[] =
{
    -110,    40,     9,  -110,   -17,  -110,  -110,  -110,  -110,  -110,
     -21,    23,    10,  -110,    20,  -110,    25,    21,  -110,  -110,
     -11,    23,    48,    27,    52,   -11,  -110,  -110,    58,  -110,
    -110,  -110,   -22,  -110,  -110,    48,    44,    54,  -110,  -110,
     105,   105,    64,    65,  -110,  -110,  -110,   -13,    69,   105,
     105,  -110,    61,   -11,  -110,  -110,  -110,  -110,  -110,    67,
     -36,    18,    -4,   -10,  -110,  -110,  -110,  -110,    74,    70,
    -110,  -110,  -110,   105,   105,  -110,    71,    83,    72,  -110,
    -110,    82,  -110,    85,  -110,   105,   105,   105,   105,   105,
     105,   105,  -110,  -110,   100,   105,   105,   105,   105,    89,
      86,  -110,    91,  -110,   -11,   105,  -110,  -110,    -4,    -4,
    -110,  -110,  -110,  -110,  -110,     2,    90,  -110,  -110,  -110,
      75,   105,   105,  -110,  -110,  -110,   105,  -110,   115,    94,
      97,  -110,    75,   105,    95,  -110,    98,  -110,    75,  -110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -110,  -110,  -110,  -110,   145,  -110,   128,  -110,   127,  -110,
    -110,    47,  -110,    24,    -8,  -110,  -110,    -1,  -110,  -109,
    -110,  -110,   -93,   -47,    -2,  -110,     1,  -110,  -110,   -37,
    -110,  -110,  -110,    -6,    55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -14
static const yytype_int16 yytable[] =
{
      76,   114,    78,    71,    72,    37,    40,    41,    12,    92,
      93,   128,    26,    79,    44,    45,    46,    34,    24,    85,
      86,    30,    13,   135,    11,    38,    99,   100,    49,   139,
      50,    94,    25,   131,    39,    20,    95,    75,     4,    89,
       3,     5,     6,     7,   125,    20,   126,    20,   116,    90,
      91,    21,   110,   111,   112,     5,     6,    14,   124,     5,
       6,     7,   -13,    40,    41,    23,    42,    22,    43,    87,
      88,    44,    45,    46,   129,   130,     5,     6,     7,    96,
      97,    47,    48,   106,   107,    49,   136,    50,   108,   109,
     117,   118,    29,    51,    40,    41,    29,    42,    32,    43,
      35,    70,    44,    45,    46,    73,    74,     5,     6,     7,
      77,    80,    47,    48,   103,    98,    49,    84,    50,    40,
      41,   101,   102,    29,    40,    41,   104,    44,    45,    46,
     105,   120,    44,    45,    46,   122,   121,   127,   132,   134,
     138,    49,   113,    50,   133,   137,    49,     9,    50,    28,
      31,   123,     0,   119
};

static const yytype_int16 yycheck[] =
{
      47,    94,    49,    40,    41,    27,    19,    20,    29,    19,
      20,   120,    20,    50,    27,    28,    29,    25,    29,    55,
      56,    22,    43,   132,    41,    47,    73,    74,    41,   138,
      43,    41,    43,   126,    35,    11,    46,    50,    29,    43,
       0,    32,    33,    34,    42,    21,    44,    23,    95,    53,
      54,    41,    89,    90,    91,    32,    33,    34,   105,    32,
      33,    34,    42,    19,    20,    44,    22,    42,    24,    51,
      52,    27,    28,    29,   121,   122,    32,    33,    34,     5,
       6,    37,    38,    85,    86,    41,   133,    43,    87,    88,
      96,    97,    48,    49,    19,    20,    48,    22,    46,    24,
      42,    47,    27,    28,    29,    41,    41,    32,    33,    34,
      41,    50,    37,    38,    42,    45,    41,    50,    43,    19,
      20,    50,    39,    48,    19,    20,    44,    27,    28,    29,
      45,    42,    27,    28,    29,    44,    50,    47,    23,    42,
      42,    41,    42,    43,    50,    50,    41,     2,    43,    21,
      23,   104,    -1,    98
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    58,    59,     0,    29,    32,    33,    34,    60,    61,
      62,    41,    29,    43,    34,    61,    63,    64,    65,    69,
      70,    41,    42,    44,    29,    43,    71,    72,    63,    48,
      74,    65,    46,    73,    71,    42,    75,    27,    47,    74,
      19,    20,    22,    24,    27,    28,    29,    37,    38,    41,
      43,    49,    66,    70,    74,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    86,    87,    88,    89,    90,    91,
      47,    86,    86,    41,    41,    50,    80,    41,    80,    86,
      50,    67,    68,    71,    50,    55,    56,    51,    52,    43,
      53,    54,    19,    20,    41,    46,     5,     6,    45,    80,
      80,    50,    39,    42,    44,    45,    81,    81,    83,    83,
      86,    86,    86,    42,    79,    85,    80,    90,    90,    91,
      42,    50,    44,    68,    80,    42,    44,    47,    76,    80,
      80,    79,    23,    50,    42,    76,    80,    50,    42,    76
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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
        case 2:

/* Line 1464 of yacc.c  */
#line 27 "mini_c.y"
    {root = (yyvsp[(1) - (1)]);}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 32 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)]));(yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 34 "mini_c.y"
    {auto pt=new ParseTree(); pt->tag=NONTERMINAL; pt->wordData="procedures"; (yyval)=pt;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 39 "mini_c.y"
    {auto pt=new ParseTree((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); pt->tag=NONTERMINAL; pt->wordData="procedure"; (yyval)=pt;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 41 "mini_c.y"
    {}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 46 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 48 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 50 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 55 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)]));(yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 57 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 62 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 64 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 66 "mini_c.y"
    {(yyval) = new ParseTree();}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 71 "mini_c.y"
    {(yyvsp[(1) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval) = (yyvsp[(1) - (3)]);}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 73 "mini_c.y"
    {auto pt=new ParseTree(); pt->tag=NONTERMINAL; pt->wordData="parameters_list"; (yyval)=pt;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 78 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 83 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)])); (yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 88 "mini_c.y"
    {(yyvsp[(1) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(1) - (3)]);}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 90 "mini_c.y"
    {auto pt=new ParseTree((yyvsp[(1) - (1)])); pt->tag=NONTERMINAL; pt->wordData="declaration_list"; (yyval)=pt;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 95 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 97 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 102 "mini_c.y"
    {auto pt=new ParseTree((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); pt->tag=NONTERMINAL; pt->wordData="IDtypeDeclaration"; (yyval)=pt;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 107 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 112 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)])); (yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 114 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 119 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 121 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)])); (yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 126 "mini_c.y"
    {auto pt=new ParseTree(); pt->tag=NONTERMINAL; pt->wordData="variable_array"; (yyval)=pt;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 128 "mini_c.y"
    {auto pt=new ParseTree((yyvsp[(2) - (3)])); pt->tag=NONTERMINAL; pt->wordData="fixed_array"; (yyval)=pt;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 133 "mini_c.y"
    {(yyval) = (yyvsp[(2) - (3)]);}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 138 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)])); (yyval) = (yyvsp[(1) - (2)]);}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 140 "mini_c.y"
    {auto pt=new ParseTree(); pt->tag=NONTERMINAL; pt->wordData="statements"; (yyval)=pt;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 145 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (2)]);}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 147 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (2)]);}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 149 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 151 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 153 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 155 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 157 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 162 "mini_c.y"
    {(yyvsp[(1) - (7)])->addChild((yyvsp[(3) - (7)])); (yyvsp[(1) - (7)])->addChild((yyvsp[(5) - (7)])); (yyval)=(yyvsp[(1) - (7)]);}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 167 "mini_c.y"
    {(yyvsp[(1) - (3)])->addChild((yyvsp[(2) - (3)])); (yyval)=(yyvsp[(1) - (3)]);}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 169 "mini_c.y"
    {(yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 174 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 176 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 181 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 186 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 191 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 193 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 195 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 200 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 202 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 204 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 206 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 211 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 213 "mini_c.y"
    {(yyvsp[(2) - (2)])->addChild((yyvsp[(1) - (2)])); (yyval)=(yyvsp[(2) - (2)]);}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 215 "mini_c.y"
    {(yyvsp[(2) - (2)])->addChild((yyvsp[(1) - (2)])); (yyval)=(yyvsp[(2) - (2)]);}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 217 "mini_c.y"
    {auto pt = new ParseTree((yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])); pt->tag=NONTERMINAL; pt->wordData="subscript"; (yyval)=pt;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 219 "mini_c.y"
    {auto pt=new ParseTree((yyvsp[(1) - (3)])); pt->tag=NONTERMINAL; pt->wordData="call"; (yyval)=pt;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 221 "mini_c.y"
    {auto pt=new ParseTree((yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])); pt->tag=NONTERMINAL; pt->wordData="call"; (yyval)=pt;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 226 "mini_c.y"
    {(yyvsp[(1) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(1) - (3)]);}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 228 "mini_c.y"
    {auto pt=new ParseTree((yyvsp[(1) - (1)])); pt->tag=NONTERMINAL; pt->wordData="args_list"; (yyval)=pt;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 233 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 235 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)])); (yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 237 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)])); (yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 239 "mini_c.y"
    {(yyvsp[(1) - (2)])->addChild((yyvsp[(2) - (2)])); (yyval)=(yyvsp[(1) - (2)]);}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 244 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 246 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 248 "mini_c.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 250 "mini_c.y"
    {(yyval) = (yyvsp[(2) - (3)]);}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 255 "mini_c.y"
    {(yyvsp[(1) - (5)])->addChild((yyvsp[(3) - (5)])); (yyvsp[(1) - (5)])->addChild((yyvsp[(5) - (5)])); (yyval)=(yyvsp[(1) - (5)]);}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 257 "mini_c.y"
    {(yyvsp[(1) - (7)])->addChild((yyvsp[(3) - (7)])); (yyvsp[(1) - (7)])->addChild((yyvsp[(5) - (7)])); (yyvsp[(1) - (7)])->addChild((yyvsp[(7) - (7)])); (yyval)=(yyvsp[(1) - (7)]);}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 262 "mini_c.y"
    {(yyvsp[(1) - (9)])->addChild((yyvsp[(3) - (9)])); (yyvsp[(1) - (9)])->addChild((yyvsp[(5) - (9)])); (yyvsp[(1) - (9)])->addChild((yyvsp[(7) - (9)])); (yyvsp[(1) - (9)])->addChild((yyvsp[(9) - (9)])); (yyval)=(yyvsp[(1) - (9)]);}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 267 "mini_c.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 269 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 271 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 276 "mini_c.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 278 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 280 "mini_c.y"
    {(yyvsp[(2) - (3)])->addChild((yyvsp[(1) - (3)])); (yyvsp[(2) - (3)])->addChild((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(2) - (3)]);}
    break;



/* Line 1464 of yacc.c  */
#line 2089 "y.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1684 of yacc.c  */
#line 282 "mini_c.y"


extern char yytext[];

void yyerror(std::string s)
{
  std::cout << s << std::endl;
}

