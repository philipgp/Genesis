/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "ObjCompiler.y"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "Compiler.h"
#define YY_NO_UNISTD_H 1
extern int yylex();
//#define YYLEX_PARAM &yylval, &yylloc
extern FILE *yyin;
char basePath[255];

void yyerror(const char *str)
{
 fprintf(stderr,"error:Lineno:%d\n",iLineNo+1);
 //fprintf(stderr,"error:Lineno:%d\n",yyget_lineno());
 
}



int yywrap()
{
      return 1;
}

/* Line 371 of yacc.c  */
#line 94 "ObjCompiler.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "ObjCompiler.tab.h".  */
#ifndef YY_YY_OBJCOMPILER_TAB_H_INCLUDED
# define YY_YY_OBJCOMPILER_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     ID = 259,
     STRING = 260,
     DATATYPE = 261,
     ASMStatement = 262,
     DEREFERENCE = 263,
     CompilerRequest = 264,
     STRINGLITERAL = 265,
     MemberReference = 266,
     WS = 267,
     AND_OP = 268,
     OR_OP = 269,
     LTE_OP = 270,
     GTE_OP = 271,
     IMPORT_KW = 272,
     NTE_OP = 273,
     ISE_OP = 274,
     IF_KW = 275,
     INTERRUPT_KW = 276,
     THN_KW = 277,
     EIF_KW = 278,
     STATEMENT_DELIM = 279,
     ELSE_KW = 280,
     TASK_KW = 281,
     ELSIF_KW = 282,
     WHILE_KW = 283,
     LOOP_KW = 284,
     ENDLOOP_KW = 285,
     LFT_SQ_BKT_OP = 286,
     RYT_SQ_BKT_OP = 287,
     FUNCTION_KW = 288,
     RETURNS_KW = 289,
     RETURN_KW = 290,
     COMMA_OP = 291,
     BREAK_LOOP_KW = 292,
     CONTINUE_LOOP_KW = 293,
     DATATYPE_KW = 294,
     WORKER_KW = 295,
     LFT_SIMP_BKT_OP = 296,
     RYT_SIMP_BKT_OP = 297,
     DEFINE_KW = 298,
     OBJECTTYPE_KW = 299,
     NEW_KW = 300,
     RYT_CRLY_BKT_OP = 301,
     LFT_CRLY_BKT_OP = 302,
     END_DEFINE_KW = 303,
     MINUS_OP = 304,
     MODULUS_OP = 305,
     IN_KW = 306,
     OUT_KW = 307,
     OPERATION_KW = 308,
     OPERATOR_KW = 309
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 28 "ObjCompiler.y"

int SymId;
struct Optab *optabs;


/* Line 387 of yacc.c  */
#line 197 "ObjCompiler.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_OBJCOMPILER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 225 "ObjCompiler.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   573

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNRULES -- Number of states.  */
#define YYNSTATES  271

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    64,     2,
       2,     2,    60,    59,     2,     2,    63,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    55,
      57,    56,    58,     2,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    62,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    11,    13,    17,    20,    24,
      29,    33,    36,    38,    40,    43,    48,    52,    56,    59,
      61,    64,    66,    72,    79,    86,    94,   100,   107,   113,
     117,   120,   122,   124,   126,   128,   130,   132,   134,   136,
     138,   140,   142,   146,   148,   151,   153,   156,   159,   161,
     167,   173,   175,   177,   180,   186,   192,   200,   207,   214,
     220,   225,   230,   237,   245,   248,   250,   258,   265,   268,
     270,   274,   279,   283,   285,   289,   291,   295,   299,   301,
     305,   309,   313,   317,   319,   323,   327,   329,   333,   337,
     341,   343,   347,   349,   353,   355,   358,   360,   364,   369,
     372,   378,   383,   387,   393,   400,   408,   411,   416,   418,
     421,   423,   426,   428,   430,   432,   436,   438,   440,   442,
     444,   446,   449,   453,   456,   459,   465,   469,   473,   476,
     479,   482,   486,   491
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,    79,    69,    -1,    79,    68,    -1,    68,
      -1,    69,    -1,    69,    79,    68,    -1,    69,    68,    -1,
      79,    69,    68,    -1,   115,    92,    73,    48,    -1,   115,
      73,    48,    -1,    69,    70,    -1,    70,    -1,    71,    -1,
      71,    92,    -1,   114,    92,    72,    48,    -1,   114,    72,
      48,    -1,   114,    92,    48,    -1,    72,    75,    -1,    75,
      -1,    73,    74,    -1,    74,    -1,    26,     4,    41,    42,
      76,    -1,    26,     4,    41,   107,    42,    76,    -1,    33,
       4,    41,   107,    42,    76,    -1,    33,     4,    41,   107,
      42,    84,    76,    -1,    33,     4,    41,    42,    76,    -1,
      33,     4,    41,    42,    84,    76,    -1,    21,     4,    41,
      42,    76,    -1,    47,    77,    46,    -1,    77,    78,    -1,
      78,    -1,    88,    -1,    86,    -1,    85,    -1,   105,    -1,
      93,    -1,   116,    -1,   117,    -1,    83,    -1,    89,    -1,
      82,    -1,    35,    99,    55,    -1,    81,    -1,    35,    55,
      -1,    80,    -1,    79,    80,    -1,    17,     4,    -1,    89,
      -1,    51,     6,     4,     4,    55,    -1,    52,     6,     4,
       4,    55,    -1,     9,    -1,     7,    -1,    34,     6,    -1,
      28,    95,    29,    77,    30,    -1,    20,    95,    22,    77,
      23,    -1,    20,    95,    22,    77,    25,    77,    23,    -1,
      20,    95,    22,    77,    87,    23,    -1,    27,    95,    22,
      77,    25,    77,    -1,    27,    95,    22,    77,    87,    -1,
      27,    95,    22,    77,    -1,   108,    56,    95,    55,    -1,
      43,    39,     4,    47,    92,    46,    -1,    43,    39,     4,
      47,    92,    90,    46,    -1,    90,    91,    -1,    91,    -1,
      53,     4,    41,    94,    42,    84,    76,    -1,    53,     4,
      41,    42,    84,    76,    -1,    92,    93,    -1,    93,    -1,
       6,   102,    55,    -1,     6,     4,    36,   109,    -1,    95,
      14,    96,    -1,    96,    -1,    96,    13,    97,    -1,    97,
      -1,    97,    19,    98,    -1,    97,    18,    98,    -1,    98,
      -1,    98,    57,    99,    -1,    98,    58,    99,    -1,    98,
      15,    99,    -1,    98,    16,    99,    -1,    99,    -1,    99,
      59,   100,    -1,    99,    49,   100,    -1,   100,    -1,   100,
      60,   101,    -1,   100,    61,   101,    -1,   100,    50,   101,
      -1,   101,    -1,   108,    62,   101,    -1,   108,    -1,   103,
      36,   102,    -1,   103,    -1,     4,   104,    -1,     4,    -1,
      31,     3,    32,    -1,   104,    31,     3,    32,    -1,   106,
      55,    -1,     4,    41,   118,    99,    42,    -1,     4,    41,
      99,    42,    -1,     4,    41,    42,    -1,   119,    63,     4,
      41,    42,    -1,   119,    63,     4,    41,    99,    42,    -1,
     119,    63,     4,    41,   118,    99,    42,    -1,     6,     4,
      -1,   107,    36,     6,     4,    -1,     4,    -1,    49,     4,
      -1,     3,    -1,    49,     3,    -1,   119,    -1,   106,    -1,
      11,    -1,    41,    95,    42,    -1,   112,    -1,   111,    -1,
     113,    -1,    10,    -1,   110,    -1,    54,    59,    -1,   119,
      63,     4,    -1,    64,     4,    -1,    45,   106,    -1,    65,
      41,     6,    42,     4,    -1,    43,    44,     4,    -1,    43,
      40,     4,    -1,    37,    55,    -1,    38,    55,    -1,    99,
      36,    -1,   118,    99,    36,    -1,     4,    31,    99,    32,
      -1,   119,    31,    99,    32,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    90,    90,    91,    92,    93,    94,    95,    96,    99,
     100,   101,   102,   103,   104,   106,   107,   108,   110,   111,
     113,   113,   115,   116,   120,   121,   122,   123,   124,   126,
     129,   130,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   146,   147,   148,   149,   155,
     156,   158,   160,   162,   164,   166,   167,   168,   170,   171,
     172,   174,   177,   178,   180,   181,   182,   183,   188,   189,
     193,   195,   197,   198,   200,   201,   203,   204,   205,   207,
     208,   209,   210,   211,   213,   214,   215,   217,   218,   219,
     220,   222,   223,   226,   227,   229,   229,   232,   233,   238,
     241,   242,   243,   244,   245,   246,   250,   251,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   267,   270,   271,   272,   274,   275,   278,   280,   283,
     285,   285,   290,   291
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "ID", "STRING", "DATATYPE",
  "ASMStatement", "DEREFERENCE", "CompilerRequest", "STRINGLITERAL",
  "MemberReference", "WS", "AND_OP", "OR_OP", "LTE_OP", "GTE_OP",
  "IMPORT_KW", "NTE_OP", "ISE_OP", "IF_KW", "INTERRUPT_KW", "THN_KW",
  "EIF_KW", "STATEMENT_DELIM", "ELSE_KW", "TASK_KW", "ELSIF_KW",
  "WHILE_KW", "LOOP_KW", "ENDLOOP_KW", "LFT_SQ_BKT_OP", "RYT_SQ_BKT_OP",
  "FUNCTION_KW", "RETURNS_KW", "RETURN_KW", "COMMA_OP", "BREAK_LOOP_KW",
  "CONTINUE_LOOP_KW", "DATATYPE_KW", "WORKER_KW", "LFT_SIMP_BKT_OP",
  "RYT_SIMP_BKT_OP", "DEFINE_KW", "OBJECTTYPE_KW", "NEW_KW",
  "RYT_CRLY_BKT_OP", "LFT_CRLY_BKT_OP", "END_DEFINE_KW", "MINUS_OP",
  "MODULUS_OP", "IN_KW", "OUT_KW", "OPERATION_KW", "OPERATOR_KW", "';'",
  "'='", "'<'", "'>'", "'+'", "'*'", "'/'", "'^'", "'.'", "'&'", "'@'",
  "$accept", "Program", "WorkerDefineBlock", "Objects",
  "ObjectWithGlobals", "ObjectDefineBlock", "FunctionBlock", "TaskBlock",
  "TaskDeclaration", "FunctionDeclaration", "FunctionBody",
  "Statement_Block", "Statement", "Forward_Declaration_Block",
  "Forward_Declaration", "ServiceParameter", "CompilerRequestStatement",
  "AsmStatement", "ReturnsStatement", "While_Statement", "If_Statement",
  "Else_If_Statement", "Assignment_Statement", "Datatype_Declaration",
  "Datatype_Body_Block", "DatatypeOperations", "Declare_Block",
  "Declare_Statement", "Datatype_Declare_Block", "Or_Logic_Expr",
  "And_Logic_Expr", "Comp_Expr", "Relat_Expr", "AddSub_Arith_Expr",
  "MulDiv_Arith_Expr", "Exp_Arith_Expr", "Declare_ID_List", "DeclareID",
  "DeclareSubscriptList", "FunctionCallStatement", "FunctionCall",
  "FormalParameterList", "ExprID", "Operator_Declaration",
  "ArrayAndMemberRef", "AddressOfExpr", "NewStatement", "DereferenceExpr",
  "DefineObjectName", "DefineWorkerName", "BreakStatement",
  "ContinueStatement", "ActualParameterList", "ArrayReference", YY_NULL
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,    59,    61,    60,    62,    43,
      42,    47,    94,    46,    38,    64
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    71,    72,    72,
      73,    73,    74,    74,    75,    75,    75,    75,    75,    76,
      77,    77,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    79,    79,    80,    80,    81,
      81,    82,    83,    84,    85,    86,    86,    86,    87,    87,
      87,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      93,    94,    95,    95,    96,    96,    97,    97,    97,    98,
      98,    98,    98,    98,    99,    99,    99,   100,   100,   100,
     100,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     106,   106,   106,   106,   106,   106,   107,   107,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   118,   119,   119
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     3,     2,     3,     4,
       3,     2,     1,     1,     2,     4,     3,     3,     2,     1,
       2,     1,     5,     6,     6,     7,     5,     6,     5,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     1,     2,     2,     1,     5,
       5,     1,     1,     2,     5,     5,     7,     6,     6,     5,
       4,     4,     6,     7,     2,     1,     7,     6,     2,     1,
       3,     4,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     3,     1,     3,     1,     2,     1,     3,     4,     2,
       5,     4,     3,     5,     6,     7,     2,     4,     1,     2,
       1,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     2,     3,     2,     2,     5,     3,     3,     2,     2,
       2,     3,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     5,    12,    13,     0,    45,
      48,     0,     0,    47,     0,     0,     0,     1,     7,    11,
       0,     0,    14,    69,     3,     2,    46,     0,     0,     0,
      19,     0,     0,     0,    21,     0,     0,   127,   126,     0,
       6,    96,     0,    94,    68,     0,     8,     0,     0,    16,
      18,    17,     0,     0,    10,    20,     0,     0,     0,    95,
      70,     0,     0,     0,    15,     0,     9,     0,     0,     0,
      93,     0,     0,     0,     0,     0,     0,    62,     0,     0,
      65,    97,     0,     0,    28,   106,     0,    26,     0,     0,
       0,    22,     0,     0,    63,    64,    98,   110,   108,    52,
      51,   119,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    43,    41,
      39,    34,    33,    32,    40,    36,    35,   113,     0,   120,
     117,   116,   118,    37,    38,   112,    53,    27,     0,    24,
       0,    23,     0,     0,     0,     0,    73,    75,    78,    83,
      86,    90,   113,    92,     0,    44,     0,   128,   129,     0,
       0,   124,     0,   111,   109,     0,     0,   123,     0,    29,
      30,    99,     0,     0,     0,   107,    25,     0,     0,     0,
       0,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,   115,     0,     0,     0,     0,     0,     0,   122,     0,
       0,     0,   132,   130,   101,     0,    72,     0,    74,    77,
      76,    81,    82,    79,    80,    85,    84,    89,    87,    88,
      91,     0,     0,     0,     0,     0,    61,   133,     0,     0,
      67,     0,   131,   100,    55,     0,     0,     0,    54,    49,
      50,   125,   103,     0,     0,     0,    71,    66,     0,     0,
      57,   104,     0,   121,    56,     0,   105,    60,     0,    59,
      58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    29,    33,    34,    30,
      84,   116,   117,     8,     9,   118,   119,   120,    88,   121,
     122,   247,   123,   124,    79,    80,    22,   125,   179,   145,
     146,   147,   148,   149,   150,   151,    42,    43,    59,   126,
     152,    74,   153,   256,   129,   130,   131,   132,    11,    12,
     133,   134,   183,   135
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -170
static const yytype_int16 yypact[] =
{
       0,    44,   164,    80,  -170,     0,  -170,   170,     0,  -170,
    -170,    77,   107,  -170,   186,   190,   197,  -170,  -170,  -170,
      24,   207,   170,  -170,  -170,   140,  -170,   214,   216,    21,
    -170,    76,   219,    39,  -170,   107,   159,  -170,  -170,   124,
    -170,   194,   176,   201,  -170,   121,  -170,   192,   198,  -170,
    -170,  -170,    93,   203,  -170,  -170,    82,   170,   244,   220,
    -170,   207,   210,     8,  -170,    13,  -170,     3,   228,   258,
    -170,   215,   259,   125,   177,   215,   179,  -170,   261,    20,
    -170,  -170,   236,   439,  -170,  -170,   263,  -170,   215,   264,
     125,  -170,   215,   230,  -170,  -170,  -170,  -170,    31,  -170,
    -170,  -170,  -170,   508,   508,   452,   217,   218,   508,   240,
     271,   108,   272,   275,   279,   245,   289,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,   232,   229,  -170,
    -170,  -170,  -170,  -170,  -170,    -3,  -170,  -170,   285,  -170,
     215,  -170,    15,   508,    36,   156,   281,   162,    37,    69,
     -26,  -170,  -170,   235,    50,  -170,   118,  -170,  -170,    17,
      31,  -170,    -2,  -170,  -170,   297,   298,  -170,   299,  -170,
    -170,  -170,   508,   508,   302,  -170,  -170,   303,   274,   268,
      56,  -170,    83,   508,   508,   439,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   508,   508,   508,   439,
    -170,  -170,   307,   308,   309,   273,    -4,    72,   277,   278,
     215,   274,  -170,  -170,  -170,    87,   281,   189,   162,    37,
      37,    69,    69,    69,    69,   -26,   -26,  -170,  -170,  -170,
    -170,   339,   277,   265,   266,   312,  -170,  -170,   495,   269,
    -170,   215,  -170,  -170,  -170,   439,   508,   296,  -170,  -170,
    -170,  -170,  -170,   101,   508,   270,  -170,  -170,   389,   183,
    -170,  -170,   109,  -170,  -170,   439,  -170,   239,   439,  -170,
     439
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,  -170,   149,   314,   102,  -170,   294,   293,   -18,    34,
     -70,  -169,  -114,   326,   127,  -170,  -170,  -170,   -89,  -170,
    -170,    66,  -170,   202,  -170,   257,    14,     1,  -170,   -97,
     153,   158,    41,   -99,    42,    60,   286,  -170,  -170,  -170,
     -83,   287,   -79,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,   113,   246
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     127,   140,   170,    87,   128,    91,   156,   154,    23,    21,
     184,   159,    23,    23,    72,    55,   217,     1,   137,    72,
     139,   177,   141,    44,   195,    31,    35,   161,   173,   173,
     231,   184,    44,   127,   196,   197,    44,   128,    55,    97,
      98,     1,    27,     2,   180,   182,   101,   102,    13,    77,
      73,   236,   189,   190,    28,    75,    78,   178,    23,   201,
     174,   202,   143,    50,   184,    32,    94,    39,    44,    49,
     176,    67,   144,    78,   207,   206,   258,   108,   181,   199,
      17,   110,    21,    21,   215,   111,    50,    54,   212,   210,
     221,   222,   223,   224,   191,   192,   267,    27,    27,   270,
     114,   115,   127,   170,   237,   193,   128,    19,    32,    28,
      28,   163,   164,    21,    27,   194,   127,   170,   193,   213,
     128,   193,   241,   242,    51,   214,    28,    19,   194,   243,
      66,   194,   193,    32,   127,    26,   193,   213,   128,   253,
     240,    64,   194,   261,   170,   242,   194,    26,   127,   259,
     193,   266,   128,   170,    18,   262,   170,    24,   193,    86,
     194,    15,   127,    14,    15,    16,   128,   193,   194,    40,
     184,   257,    83,   200,    46,   127,    21,   194,   185,   128,
     187,   188,   127,    45,   127,   127,   128,   127,   128,   128,
      36,   128,    97,    98,    37,    21,    99,   184,   100,   101,
     102,    38,    10,    14,    15,   265,    57,    10,    16,   103,
      10,    41,   244,    89,   245,    89,   246,   104,    47,    90,
      48,    92,    10,    53,   105,    58,   106,   107,   219,   220,
     108,    60,   109,    62,   110,   225,   226,    61,   111,    63,
     112,   113,    97,    98,    65,    21,    99,    68,   100,   101,
     102,    69,    71,   114,   115,   227,   228,   229,   230,   103,
      81,    82,    83,    85,   268,    93,   246,   104,    96,   136,
     138,   142,   157,   158,   105,   160,   106,   107,   165,    14,
     108,   166,   109,   167,   110,   172,   168,   171,   111,   175,
     112,   113,    97,    98,   186,    21,    99,   198,   100,   101,
     102,   203,   204,   114,   115,   205,   208,   209,    86,   103,
     211,   232,   233,   234,   239,   235,   251,   104,   238,   260,
     249,   250,    25,   255,   105,    52,   106,   107,    56,   263,
     108,    20,   109,   269,   110,   169,    95,   216,   111,     0,
     112,   113,    97,    98,   218,    21,    99,    70,   100,   101,
     102,   254,    76,   114,   115,     0,   162,     0,     0,   103,
       0,     0,     0,     0,     0,     0,     0,   104,     0,   248,
       0,     0,     0,     0,   105,     0,   106,   107,     0,     0,
     108,     0,   109,     0,   110,     0,     0,     0,   111,     0,
     112,   113,    97,    98,     0,    21,    99,     0,   100,   101,
     102,     0,     0,   114,   115,     0,     0,     0,     0,   103,
       0,     0,   264,     0,     0,     0,     0,   104,     0,     0,
       0,     0,     0,     0,   105,     0,   106,   107,     0,     0,
     108,     0,   109,     0,   110,     0,     0,     0,   111,     0,
     112,   113,    97,    98,     0,    21,    99,     0,   100,   101,
     102,     0,     0,   114,   115,    97,    98,     0,     0,   103,
       0,     0,   101,   102,     0,     0,     0,   104,     0,     0,
       0,     0,     0,     0,   105,     0,   106,   107,     0,     0,
     108,     0,   109,     0,   110,     0,     0,     0,   111,     0,
     112,   113,     0,   108,     0,     0,     0,   110,    97,    98,
       0,   111,     0,   114,   115,   101,   102,   155,     0,     0,
       0,    97,    98,     0,     0,     0,   114,   115,   101,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   252,     0,     0,
     110,     0,     0,     0,   111,     0,     0,     0,     0,   108,
       0,     0,     0,   110,     0,     0,     0,   111,     0,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,   115
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-170)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      83,    90,   116,    73,    83,    75,   105,   104,     7,     6,
      14,   108,    11,    12,     6,    33,   185,    17,    88,     6,
      90,     6,    92,    22,    50,    11,    12,   110,    31,    31,
     199,    14,    31,   116,    60,    61,    35,   116,    56,     3,
       4,    17,    21,    43,   143,   144,    10,    11,     4,    46,
      42,    55,    15,    16,    33,    42,    53,    42,    57,    42,
      63,    63,    31,    29,    14,    26,    46,    43,    67,    48,
     140,    57,    41,    53,   173,   172,   245,    41,    42,    29,
       0,    45,     6,     6,   183,    49,    52,    48,    32,   178,
     189,   190,   191,   192,    57,    58,   265,    21,    21,   268,
      64,    65,   185,   217,    32,    49,   185,     5,    26,    33,
      33,     3,     4,     6,    21,    59,   199,   231,    49,    36,
     199,    49,   211,    36,    48,    42,    33,    25,    59,    42,
      48,    59,    49,    26,   217,     8,    49,    36,   217,   238,
     210,    48,    59,    42,   258,    36,    59,    20,   231,   246,
      49,    42,   231,   267,     5,   254,   270,     8,    49,    34,
      59,    40,   245,    39,    40,    44,   245,    49,    59,    20,
      14,   241,    47,    55,    25,   258,     6,    59,    22,   258,
      18,    19,   265,    43,   267,   268,   265,   270,   267,   268,
       4,   270,     3,     4,     4,     6,     7,    14,     9,    10,
      11,     4,     0,    39,    40,    22,    47,     5,    44,    20,
       8,     4,    23,    36,    25,    36,    27,    28,     4,    42,
       4,    42,    20,     4,    35,    31,    37,    38,   187,   188,
      41,    55,    43,    41,    45,   193,   194,    36,    49,    41,
      51,    52,     3,     4,    41,     6,     7,     3,     9,    10,
      11,    31,    42,    64,    65,   195,   196,   197,   198,    20,
      32,     3,    47,     4,    25,     4,    27,    28,    32,     6,
       6,    41,    55,    55,    35,     4,    37,    38,     6,    39,
      41,     6,    43,     4,    45,    56,    41,    55,    49,     4,
      51,    52,     3,     4,    13,     6,     7,    62,     9,    10,
      11,     4,     4,    64,    65,     6,     4,     4,    34,    20,
      42,     4,     4,     4,    36,    42,     4,    28,    41,    23,
      55,    55,     8,    54,    35,    31,    37,    38,    35,    59,
      41,     5,    43,   267,    45,    46,    79,   184,    49,    -1,
      51,    52,     3,     4,   186,     6,     7,    61,     9,    10,
      11,   238,    65,    64,    65,    -1,   110,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      -1,    -1,    -1,    -1,    35,    -1,    37,    38,    -1,    -1,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    49,    -1,
      51,    52,     3,     4,    -1,     6,     7,    -1,     9,    10,
      11,    -1,    -1,    64,    65,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    37,    38,    -1,    -1,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    49,    -1,
      51,    52,     3,     4,    -1,     6,     7,    -1,     9,    10,
      11,    -1,    -1,    64,    65,     3,     4,    -1,    -1,    20,
      -1,    -1,    10,    11,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    37,    38,    -1,    -1,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    49,    -1,
      51,    52,    -1,    41,    -1,    -1,    -1,    45,     3,     4,
      -1,    49,    -1,    64,    65,    10,    11,    55,    -1,    -1,
      -1,     3,     4,    -1,    -1,    -1,    64,    65,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    49,    -1,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    43,    67,    68,    69,    70,    71,    79,    80,
      89,   114,   115,     4,    39,    40,    44,     0,    68,    70,
      79,     6,    92,    93,    68,    69,    80,    21,    33,    72,
      75,    92,    26,    73,    74,    92,     4,     4,     4,    43,
      68,     4,   102,   103,    93,    43,    68,     4,     4,    48,
      75,    48,    72,     4,    48,    74,    73,    47,    31,   104,
      55,    36,    41,    41,    48,    41,    48,    92,     3,    31,
     102,    42,     6,    42,   107,    42,   107,    46,    53,    90,
      91,    32,     3,    47,    76,     4,    34,    76,    84,    36,
      42,    76,    42,     4,    46,    91,    32,     3,     4,     7,
       9,    10,    11,    20,    28,    35,    37,    38,    41,    43,
      45,    49,    51,    52,    64,    65,    77,    78,    81,    82,
      83,    85,    86,    88,    89,    93,   105,   106,   108,   110,
     111,   112,   113,   116,   117,   119,     6,    76,     6,    76,
      84,    76,    41,    31,    41,    95,    96,    97,    98,    99,
     100,   101,   106,   108,    95,    55,    99,    55,    55,    95,
       4,   106,   119,     3,     4,     6,     6,     4,    41,    46,
      78,    55,    56,    31,    63,     4,    76,     6,    42,    94,
      99,    42,    99,   118,    14,    22,    13,    18,    19,    15,
      16,    57,    58,    49,    59,    50,    60,    61,    62,    29,
      55,    42,    63,     4,     4,     6,    95,    99,     4,     4,
      84,    42,    32,    36,    42,    99,    96,    77,    97,    98,
      98,    99,    99,    99,    99,   100,   100,   101,   101,   101,
     101,    77,     4,     4,     4,    42,    55,    32,    41,    36,
      76,    84,    36,    42,    23,    25,    27,    87,    30,    55,
      55,     4,    42,    99,   118,    54,   109,    76,    77,    95,
      23,    42,    99,    59,    23,    22,    42,    77,    25,    87,
      77
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

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1787 of yacc.c  */
#line 90 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(2) - (2)].optabs);}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 91 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(2) - (2)].optabs);}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 92 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 93 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 94 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(2) - (3)].optabs);}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 95 "ObjCompiler.y"
    {}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 96 "ObjCompiler.y"
    {}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 99 "ObjCompiler.y"
    {}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 100 "ObjCompiler.y"
    {}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 101 "ObjCompiler.y"
    {(yyval.optabs)=NULL;}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 102 "ObjCompiler.y"
    {(yyval.optabs)=NULL;}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 103 "ObjCompiler.y"
    {(yyval.optabs)=NULL;}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 104 "ObjCompiler.y"
    {(yyval.optabs)=MakeGlobalVariable((yyvsp[(2) - (2)].optabs));}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 106 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeObjectDefinition((yyvsp[(1) - (4)].SymId),(yyvsp[(2) - (4)].optabs),(yyvsp[(3) - (4)].optabs));}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 107 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeObjectDefinition((yyvsp[(1) - (3)].SymId),NULL,(yyvsp[(2) - (3)].optabs));}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 108 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeObjectDefinition((yyvsp[(1) - (3)].SymId),(yyvsp[(2) - (3)].optabs),NULL);}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 110 "ObjCompiler.y"
    {(yyval.optabs)=ConcatSubscriptNode((yyvsp[(1) - (2)].optabs),(yyvsp[(2) - (2)].optabs));}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 111 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 113 "ObjCompiler.y"
    {}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 113 "ObjCompiler.y"
    {}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 115 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeTaskDeclaration((yyvsp[(2) - (5)].SymId),NULL,(yyvsp[(5) - (5)].optabs));}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 116 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeTaskDeclaration((yyvsp[(2) - (6)].SymId),(yyvsp[(4) - (6)].optabs),(yyvsp[(6) - (6)].optabs));}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 120 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeFunctionDeclaration(0,(yyvsp[(2) - (6)].SymId),(yyvsp[(4) - (6)].optabs),(yyvsp[(6) - (6)].optabs),FUNCTION_KW);}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 121 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeFunctionDeclaration((yyvsp[(6) - (7)].SymId),(yyvsp[(2) - (7)].SymId),(yyvsp[(4) - (7)].optabs),(yyvsp[(7) - (7)].optabs),FUNCTION_KW);}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 122 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeFunctionDeclaration(0,(yyvsp[(2) - (5)].SymId),NULL,(yyvsp[(5) - (5)].optabs),FUNCTION_KW);}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 123 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeFunctionDeclaration((yyvsp[(5) - (6)].SymId),(yyvsp[(2) - (6)].SymId),NULL,(yyvsp[(6) - (6)].optabs),FUNCTION_KW);}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 124 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeFunctionDeclaration(0,(yyvsp[(2) - (5)].SymId),NULL,(yyvsp[(5) - (5)].optabs),INTERRUPT_KW);}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 126 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(2) - (3)].optabs);}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 129 "ObjCompiler.y"
    {(yyval.optabs)=MakeStatementBlock((yyvsp[(1) - (2)].optabs),(yyvsp[(2) - (2)].optabs));}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 130 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 132 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 133 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 134 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 135 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 136 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 137 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 138 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 139 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 140 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 141 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 142 "ObjCompiler.y"
    {(yyval.optabs)=MakeReturnStatement((yyvsp[(2) - (3)].optabs));}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 143 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 144 "ObjCompiler.y"
    {(yyval.optabs)=MakeReturnStatement(NULL);}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 146 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 147 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (2)].optabs);}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 148 "ObjCompiler.y"
    {(yyval.optabs)=MakeForwardDeclaration((yyvsp[(2) - (2)].SymId));}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 149 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 155 "ObjCompiler.y"
    {(yyval.optabs)=MakeINparameter((yyvsp[(2) - (5)].SymId),(yyvsp[(3) - (5)].SymId),(yyvsp[(4) - (5)].SymId));}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 156 "ObjCompiler.y"
    {(yyval.optabs)=MakeOUTparameter((yyvsp[(2) - (5)].SymId),(yyvsp[(3) - (5)].SymId),(yyvsp[(4) - (5)].SymId));}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 158 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].SymId);}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 160 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].SymId);}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 162 "ObjCompiler.y"
    {MakeReturnsStatement((yyvsp[(2) - (2)].SymId));(yyval.SymId)=(yyvsp[(2) - (2)].SymId);}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 164 "ObjCompiler.y"
    {(yyval.optabs)=MakeWhile((yyvsp[(2) - (5)].optabs),(yyvsp[(4) - (5)].optabs));}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 166 "ObjCompiler.y"
    {(yyval.optabs)=MakeIfThen((yyvsp[(2) - (5)].optabs),(yyvsp[(4) - (5)].optabs));}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 167 "ObjCompiler.y"
    {(yyval.optabs)=MakeIfThenElse((yyvsp[(2) - (7)].optabs),(yyvsp[(4) - (7)].optabs),(yyvsp[(6) - (7)].optabs));}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 168 "ObjCompiler.y"
    {(yyval.optabs)=MakeIfElseIf((yyvsp[(2) - (6)].optabs),(yyvsp[(4) - (6)].optabs),(yyvsp[(5) - (6)].optabs));}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 170 "ObjCompiler.y"
    {(yyval.optabs)=MakeElseIfElse((yyvsp[(2) - (6)].optabs),(yyvsp[(4) - (6)].optabs),(yyvsp[(6) - (6)].optabs));}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 171 "ObjCompiler.y"
    {(yyval.optabs)=MakeElseIfElseIf((yyvsp[(2) - (5)].optabs),(yyvsp[(4) - (5)].optabs),(yyvsp[(5) - (5)].optabs));}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 172 "ObjCompiler.y"
    {(yyval.optabs)=MakeElseIf((yyvsp[(2) - (4)].optabs),(yyvsp[(4) - (4)].optabs));}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 174 "ObjCompiler.y"
    {(yyval.optabs)=MakeAssignment((yyvsp[(1) - (4)].optabs),(yyvsp[(3) - (4)].optabs));}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 177 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeStructDeclaration((yyvsp[(3) - (6)].SymId),(yyvsp[(5) - (6)].optabs));}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 178 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeStructDeclaration((yyvsp[(3) - (7)].SymId),(yyvsp[(5) - (7)].optabs));}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 180 "ObjCompiler.y"
    {(yyval.optabs)=ConcatSubscriptNode((yyvsp[(1) - (2)].optabs),(yyvsp[(2) - (2)].optabs));}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 181 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 182 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeOperationDeclaration((yyvsp[(6) - (7)].SymId),(yyvsp[(2) - (7)].SymId),(yyvsp[(4) - (7)].optabs),(yyvsp[(7) - (7)].optabs));}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 183 "ObjCompiler.y"
    {TermOldBlock();(yyval.optabs)=MakeOperationDeclaration((yyvsp[(5) - (6)].SymId),(yyvsp[(2) - (6)].SymId),NULL,(yyvsp[(6) - (6)].optabs));}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 188 "ObjCompiler.y"
    {(yyval.optabs)=AddToDeclareBlock((yyvsp[(1) - (2)].optabs),(yyvsp[(2) - (2)].optabs));}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 189 "ObjCompiler.y"
    {(yyval.optabs)=AddToDeclareBlock(NULL,(yyvsp[(1) - (1)].optabs));}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 193 "ObjCompiler.y"
    {(yyval.optabs)=MakeDeclareStatement((yyvsp[(1) - (3)].SymId),(yyvsp[(2) - (3)].optabs));}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 195 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(2) - (4)].SymId);}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 197 "ObjCompiler.y"
    {Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("||"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 198 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 200 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("&&"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 201 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 203 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("=="),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 204 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("!="),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 205 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 207 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("<"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 208 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId(">"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 209 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("<="),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 210 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId(">="),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 211 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 213 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("+"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 214 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("-"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 215 "ObjCompiler.y"
    { (yyval.optabs) = (yyvsp[(1) - (1)].optabs);}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 217 "ObjCompiler.y"
    {struct  Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("*"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 218 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("/"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 219 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("%"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 220 "ObjCompiler.y"
    { (yyval.optabs) = (yyvsp[(1) - (1)].optabs); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 222 "ObjCompiler.y"
    {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));(yyval.optabs)=AddOperation(TempResult,GetOperatorId("^"),(yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 223 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 226 "ObjCompiler.y"
    {(yyval.optabs)=ConcatSubscriptNode((yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].optabs));}
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 227 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 229 "ObjCompiler.y"
    {struct Optab * ID_Node=MakeNode((yyvsp[(1) - (2)].SymId));(yyval.optabs)=MakeDeclareIDSubscript(ID_Node,(yyvsp[(2) - (2)].optabs));}
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 229 "ObjCompiler.y"
    {(yyval.optabs)=MakeNode((yyvsp[(1) - (1)].SymId));}
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 232 "ObjCompiler.y"
    {(yyval.optabs)=MakeNode((yyvsp[(2) - (3)].SymId));}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 233 "ObjCompiler.y"
    {struct Optab * Subscript;Subscript=MakeNode((yyvsp[(3) - (4)].SymId));(yyval.optabs)=ConcatSubscriptNode((yyvsp[(1) - (4)].optabs),Subscript);}
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 238 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (2)].optabs);}
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 241 "ObjCompiler.y"
    {(yyval.optabs)=MakeFunctionCallMultipleParam((yyvsp[(1) - (5)].SymId),(yyvsp[(3) - (5)].optabs),(yyvsp[(4) - (5)].optabs));}
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 242 "ObjCompiler.y"
    {(yyval.optabs)=MakeFunctionCallSingleParam((yyvsp[(1) - (4)].SymId),(yyvsp[(3) - (4)].optabs));}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 243 "ObjCompiler.y"
    {(yyval.optabs)=MakeFunctionCallNoParam((yyvsp[(1) - (3)].SymId));}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 244 "ObjCompiler.y"
    {Optab *Nl=NULL;(yyval.optabs)=ObjectArray_FunctionCall((yyvsp[(1) - (5)].optabs),(yyvsp[(3) - (5)].SymId),NULL,NULL);}
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 245 "ObjCompiler.y"
    {(yyval.optabs)=ObjectArray_FunctionCall((yyvsp[(1) - (6)].optabs),(yyvsp[(3) - (6)].SymId),(yyvsp[(5) - (6)].optabs),NULL);}
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 246 "ObjCompiler.y"
    {(yyval.optabs)=ObjectArray_FunctionCall((yyvsp[(1) - (7)].optabs),(yyvsp[(3) - (7)].SymId),(yyvsp[(6) - (7)].optabs),(yyvsp[(5) - (7)].optabs));}
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 250 "ObjCompiler.y"
    {(yyval.optabs)=MakeDeclareStatement((yyvsp[(1) - (2)].SymId),MakeNode((yyvsp[(2) - (2)].SymId)));}
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 251 "ObjCompiler.y"
    {struct Optab * ID_Node=MakeDeclareStatement((yyvsp[(3) - (4)].SymId),MakeNode((yyvsp[(4) - (4)].SymId)));(yyval.optabs)=ConcatSubscriptNode((yyvsp[(1) - (4)].optabs),ID_Node);}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 253 "ObjCompiler.y"
    {(yyval.optabs)=MakeNode((yyvsp[(1) - (1)].SymId));}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 254 "ObjCompiler.y"
    {int SymIdOperand2;struct Optab *Operand2,*Operand1,*TempResult;Operand1=MakeNode((yyvsp[(2) - (2)].SymId));SymIdOperand2=AddSymbol("-1");Operand2=MakeNode(SymIdOperand2);TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,(yyvsp[(2) - (2)].SymId),NULL);(yyval.optabs)=AddOperation(TempResult,GetOperatorId("*"),Operand1,Operand2);}
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 255 "ObjCompiler.y"
    {(yyval.optabs)=MakeNode((yyvsp[(1) - (1)].SymId));}
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 256 "ObjCompiler.y"
    {(yyval.optabs)=MakeNegativeLiteral((yyvsp[(2) - (2)].SymId));}
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 257 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 258 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 259 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 260 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(2) - (3)].optabs);}
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 261 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 262 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 263 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 264 "ObjCompiler.y"
    {(yyval.optabs)=MakeStringLiteral((yyvsp[(1) - (1)].SymId));}
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 265 "ObjCompiler.y"
    {(yyval.optabs)=(yyvsp[(1) - (1)].optabs);}
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 267 "ObjCompiler.y"
    {}
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 270 "ObjCompiler.y"
    {(yyval.optabs)=MakeArrayAndMemberRef((yyvsp[(1) - (3)].optabs),(yyvsp[(3) - (3)].SymId));}
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 271 "ObjCompiler.y"
    {(yyval.optabs)=MakeAddressOf((yyvsp[(2) - (2)].SymId));}
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 272 "ObjCompiler.y"
    {(yyval.optabs)=MakeNewStatment((yyvsp[(2) - (2)].optabs));}
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 274 "ObjCompiler.y"
    {(yyval.optabs)=MakeDereferenceOperation((yyvsp[(3) - (5)].SymId),(yyvsp[(5) - (5)].SymId));}
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 275 "ObjCompiler.y"
    {(yyval.SymId)=SetCurrentClassName((yyvsp[(3) - (3)].SymId));}
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 278 "ObjCompiler.y"
    {(yyval.SymId)=SetWorkerName((yyvsp[(3) - (3)].SymId));}
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 280 "ObjCompiler.y"
    {struct Optab  * Operand1,*Operand2,*TempResult; Operand1=MakeNode(-1);Operand2=MakeNode(-1);TempResult=MakeNode(-1);(yyval.optabs)=AddOperation(TempResult,GetOperatorId("BRK_LOOP"),Operand1,Operand2);}
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 283 "ObjCompiler.y"
    {struct Optab  * Operand1,*Operand2,*TempResult; Operand1=MakeNode(-1);Operand2=MakeNode(-1);TempResult=MakeNode(-1);(yyval.optabs)=AddOperation(TempResult,GetOperatorId("CONT_LOOP"),Operand1,Operand2);}
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 285 "ObjCompiler.y"
    {(yyval.optabs)=MakeFunctionCallAddFirstParam((yyvsp[(1) - (2)].optabs));}
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 285 "ObjCompiler.y"
    {(yyval.optabs)=MakeFunctionCallAddParam((yyvsp[(1) - (3)].optabs),(yyvsp[(2) - (3)].optabs));}
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 290 "ObjCompiler.y"
    {(yyval.optabs)=MakeSingleExprSubscript((yyvsp[(1) - (4)].SymId),(yyvsp[(3) - (4)].optabs));}
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 291 "ObjCompiler.y"
    {(yyval.optabs)=MakeExprSubscript((yyvsp[(1) - (4)].optabs),(yyvsp[(3) - (4)].optabs));}
    break;


/* Line 1787 of yacc.c  */
#line 2535 "ObjCompiler.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2050 of yacc.c  */
#line 295 "ObjCompiler.y"


void ParseFile(char *LpszFileLocation)
{
FILE *fp,*fpsave;
printf("ParseFile:%s",LpszFileLocation);
fp=fopen(LpszFileLocation,"r");
if(fp==NULL)
{
printf("error opening file\n");
getch();
}
else
yyin=fp;
/*yydebug=1;*/
do
{
yyparse();
}while(!feof(yyin));
fclose(yyin);
}
void ProcessFile(char *LpszFileLocation)
{
char szFileName[255];
char szImportDec[8],szImportVal[32];
char *LpszFolder;
FILE *fp;
fp=NULL;
iLineNo=0;
LpszFolder=strrchr(LpszFileLocation,'\\');
if(LpszFolder!=NULL)
{
strncpy(basePath,LpszFileLocation,LpszFolder-LpszFileLocation+1);
}

if(strchr(LpszFileLocation,'\\')==NULL)
	{
		strcpy(szFileName,basePath);
		strcat(szFileName,LpszFileLocation);
		LpszFileLocation=szFileName;
	}
fp=fopen(LpszFileLocation,"r");
if(fp==NULL)
{
printf("error opening file %s\n",LpszFileLocation);
getch();
}
else
{
	while(1)
	{
fscanf(fp,"%s%s",&szImportDec,&szImportVal);
if(strcmp(szImportDec,"Import")==0)
{
//szImportVal[strlen(szImportVal)-1]='\0';
ProcessFile(szImportVal);
}
else
{
fclose(fp);
ParseFile(LpszFileLocation);
break;
}
	}
}

}
int main(int argc,char *argv[])
{
int i;
yyin=NULL;
basePath[0]='\0';
initDataTypeTable();

if(argc>2)
{
for(i=1;i<argc;i++)
{
if(argv[i][0]=='-')
{
if(argv[i][1]=='i')
{
ProcessFile(argv[++i]);
}
else if(argv[i][1]=='o')
{
initOutputFile(argv[++i]);
ProcessFile("C:\\Genesis\\SRC\\Compiler\\Compiler\\\Debug\\heapobject");
ProcessFile("C:\\Genesis\\SRC\\Compiler\\Compiler\\\Debug\\String.txt");
ProcessFile("C:\\Genesis\\SRC\\Compiler\\Compiler\\\Debug\\DisplayObj");

}
else if(argv[i][1]=='c')
{
++i;
if(argv[i][0]=='G')
iCompileOption = eGenesis;
else if(argv[i][0]=='W')
iCompileOption = eWindows;
else if(argv[i][0]=='U')
iCompileOption = eUnitTest;
}
}

}
}
printf("Compile Mode:%s",szCompileOption[iCompileOption]);
closeOutputFile();
//ParseFile("C:\\Users\\pgpanick\\Desktop\\DUMP\\Genesis\\SRC\\Compiler\\Compiler\\Debug\\input.txt");
//WriteToFile("C:\\Users\\pgpanick\\AppData\\Local\\nasm\\Compilerout.asm");
if(iCompileOption!=eUnitTest)
getch();
return 0;
}
