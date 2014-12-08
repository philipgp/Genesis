/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2053 of yacc.c  */
#line 28 "ObjCompiler.y"

int SymId;
struct Optab *optabs;


/* Line 2053 of yacc.c  */
#line 117 "ObjCompiler.tab.h"
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
