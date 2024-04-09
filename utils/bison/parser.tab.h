/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    NUM = 259,                     /* NUM  */
    IF = 260,                      /* IF  */
    ELSE = 261,                    /* ELSE  */
    WHILE = 262,                   /* WHILE  */
    RETURN = 263,                  /* RETURN  */
    INT = 264,                     /* INT  */
    VOID = 265,                    /* VOID  */
    PLUS_ALOP = 266,               /* PLUS_ALOP  */
    MINUS_ALOP = 267,              /* MINUS_ALOP  */
    MULT_PRE_ALOP = 268,           /* MULT_PRE_ALOP  */
    DIV_PRE_ALOP = 269,            /* DIV_PRE_ALOP  */
    EQ_RELOP = 270,                /* EQ_RELOP  */
    NOTEQ_RELOP = 271,             /* NOTEQ_RELOP  */
    LESSEQ_RELOP = 272,            /* LESSEQ_RELOP  */
    GREATEQ_RELOP = 273,           /* GREATEQ_RELOP  */
    GREAT_RELOP = 274,             /* GREAT_RELOP  */
    LESS_RELOP = 275,              /* LESS_RELOP  */
    EQUAL = 276,                   /* EQUAL  */
    CURLYOP_BRACKET = 277,         /* CURLYOP_BRACKET  */
    CURLYCL_BRACKET = 278,         /* CURLYCL_BRACKET  */
    CIRCLEOP_BRACKET = 279,        /* CIRCLEOP_BRACKET  */
    CIRCLECL_BRACKET = 280,        /* CIRCLECL_BRACKET  */
    SQUAREOP_BRACKET = 281,        /* SQUAREOP_BRACKET  */
    SQUARECL_BRACKET = 282,        /* SQUARECL_BRACKET  */
    SEMICOL_PUNCT = 283,           /* SEMICOL_PUNCT  */
    COMMA_PUNCT = 284,             /* COMMA_PUNCT  */
    WHITESPACE = 285,              /* WHITESPACE  */
    COMMENT = 286,                 /* COMMENT  */
    STRING = 287                   /* STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
