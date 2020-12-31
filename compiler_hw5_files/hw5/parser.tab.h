/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
    CONST = 259,                   /* CONST  */
    VOID = 260,                    /* VOID  */
    INT = 261,                     /* INT  */
    FLOAT = 262,                   /* FLOAT  */
    IF = 263,                      /* IF  */
    ELSE = 264,                    /* ELSE  */
    WHILE = 265,                   /* WHILE  */
    FOR = 266,                     /* FOR  */
    TYPEDEF = 267,                 /* TYPEDEF  */
    OP_ASSIGN = 268,               /* OP_ASSIGN  */
    OP_OR = 269,                   /* OP_OR  */
    OP_AND = 270,                  /* OP_AND  */
    OP_NOT = 271,                  /* OP_NOT  */
    OP_EQ = 272,                   /* OP_EQ  */
    OP_NE = 273,                   /* OP_NE  */
    OP_GT = 274,                   /* OP_GT  */
    OP_LT = 275,                   /* OP_LT  */
    OP_GE = 276,                   /* OP_GE  */
    OP_LE = 277,                   /* OP_LE  */
    OP_PLUS = 278,                 /* OP_PLUS  */
    OP_MINUS = 279,                /* OP_MINUS  */
    OP_TIMES = 280,                /* OP_TIMES  */
    OP_DIVIDE = 281,               /* OP_DIVIDE  */
    MK_LB = 282,                   /* MK_LB  */
    MK_RB = 283,                   /* MK_RB  */
    MK_LPAREN = 284,               /* MK_LPAREN  */
    MK_RPAREN = 285,               /* MK_RPAREN  */
    MK_LBRACE = 286,               /* MK_LBRACE  */
    MK_RBRACE = 287,               /* MK_RBRACE  */
    MK_COMMA = 288,                /* MK_COMMA  */
    MK_SEMICOLON = 289,            /* MK_SEMICOLON  */
    MK_DOT = 290,                  /* MK_DOT  */
    ERROR = 291,                   /* ERROR  */
    RETURN = 292                   /* RETURN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 112 "parser.y"

	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;

#line 107 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
