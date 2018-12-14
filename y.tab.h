/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

extern YYSTYPE yylval;


