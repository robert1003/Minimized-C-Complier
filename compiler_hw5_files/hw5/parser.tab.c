/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"
#include "symbolTable.h"
int linenumber = 1;
AST_NODE *prog;

int g_anyErrorOccur = 0;

static inline AST_NODE* makeSibling(AST_NODE *a, AST_NODE *b)
{ 
    while (a->rightSibling) {
        a = a->rightSibling;
    }
    if (b == NULL) {
        return a;
    }
    b = b->leftmostSibling;
    a->rightSibling = b;
    
    b->leftmostSibling = a->leftmostSibling;
    b->parent = a->parent;
    while (b->rightSibling) {
        b = b->rightSibling;
        b->leftmostSibling = a->leftmostSibling;
        b->parent = a->parent;
    }
    return b;
}

static inline AST_NODE* makeChild(AST_NODE *parent, AST_NODE *child)
{
    if (child == NULL) {
        return parent;
    }
    if (parent->child) {
        makeSibling(parent->child, child);
    } else {
        child = child->leftmostSibling;
        parent->child = child;
        while (child) {
            child->parent = parent;
            child = child->rightSibling;
        }
    }
    return parent;
}

static AST_NODE* makeFamily(AST_NODE *parent, int childrenCount, ...)
{
    va_list childrenList;
    va_start(childrenList, childrenCount);
    AST_NODE* child = va_arg(childrenList, AST_NODE*);
    makeChild(parent, child);
    AST_NODE* tmp = child;
    int index = 1;
    for (index = 1; index < childrenCount; ++index) {
        child = va_arg(childrenList, AST_NODE*);
        tmp = makeSibling(tmp, child);
    }
    va_end(childrenList);
    return parent;
}

static inline AST_NODE* makeIDNode(char *lexeme, IDENTIFIER_KIND idKind)
{
    AST_NODE* identifier = Allocate(IDENTIFIER_NODE);
    identifier->semantic_value.identifierSemanticValue.identifierName = lexeme;
    identifier->semantic_value.identifierSemanticValue.kind = idKind;
    identifier->semantic_value.identifierSemanticValue.symbolTableEntry = NULL;
    return identifier;                        
}

static inline AST_NODE* makeStmtNode(STMT_KIND stmtKind)
{
    AST_NODE* stmtNode = Allocate(STMT_NODE);
    stmtNode->semantic_value.stmtSemanticValue.kind = stmtKind;
    return stmtNode;                        
}

static inline AST_NODE* makeDeclNode(DECL_KIND declKind)
{
    AST_NODE* declNode = Allocate(DECLARATION_NODE);
    declNode->semantic_value.declSemanticValue.kind = declKind;
    return declNode;                        
}

static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)
{
    AST_NODE* exprNode = Allocate(EXPR_NODE);
    exprNode->semantic_value.exprSemanticValue.isConstEval = 0;
    exprNode->semantic_value.exprSemanticValue.kind = exprKind;
    if (exprKind == BINARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.binaryOp = operationEnumValue;
    } else if (exprKind == UNARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.unaryOp = operationEnumValue;
    } else {
        printf("Error in static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)\n");
    }
    return exprNode;                        
}


#line 178 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_CONST = 4,                      /* CONST  */
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_TYPEDEF = 12,                   /* TYPEDEF  */
  YYSYMBOL_OP_ASSIGN = 13,                 /* OP_ASSIGN  */
  YYSYMBOL_OP_OR = 14,                     /* OP_OR  */
  YYSYMBOL_OP_AND = 15,                    /* OP_AND  */
  YYSYMBOL_OP_NOT = 16,                    /* OP_NOT  */
  YYSYMBOL_OP_EQ = 17,                     /* OP_EQ  */
  YYSYMBOL_OP_NE = 18,                     /* OP_NE  */
  YYSYMBOL_OP_GT = 19,                     /* OP_GT  */
  YYSYMBOL_OP_LT = 20,                     /* OP_LT  */
  YYSYMBOL_OP_GE = 21,                     /* OP_GE  */
  YYSYMBOL_OP_LE = 22,                     /* OP_LE  */
  YYSYMBOL_OP_PLUS = 23,                   /* OP_PLUS  */
  YYSYMBOL_OP_MINUS = 24,                  /* OP_MINUS  */
  YYSYMBOL_OP_TIMES = 25,                  /* OP_TIMES  */
  YYSYMBOL_OP_DIVIDE = 26,                 /* OP_DIVIDE  */
  YYSYMBOL_MK_LB = 27,                     /* MK_LB  */
  YYSYMBOL_MK_RB = 28,                     /* MK_RB  */
  YYSYMBOL_MK_LPAREN = 29,                 /* MK_LPAREN  */
  YYSYMBOL_MK_RPAREN = 30,                 /* MK_RPAREN  */
  YYSYMBOL_MK_LBRACE = 31,                 /* MK_LBRACE  */
  YYSYMBOL_MK_RBRACE = 32,                 /* MK_RBRACE  */
  YYSYMBOL_MK_COMMA = 33,                  /* MK_COMMA  */
  YYSYMBOL_MK_SEMICOLON = 34,              /* MK_SEMICOLON  */
  YYSYMBOL_MK_DOT = 35,                    /* MK_DOT  */
  YYSYMBOL_ERROR = 36,                     /* ERROR  */
  YYSYMBOL_RETURN = 37,                    /* RETURN  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_global_decl_list = 40,          /* global_decl_list  */
  YYSYMBOL_global_decl = 41,               /* global_decl  */
  YYSYMBOL_function_decl = 42,             /* function_decl  */
  YYSYMBOL_param_list = 43,                /* param_list  */
  YYSYMBOL_param = 44,                     /* param  */
  YYSYMBOL_dim_fn = 45,                    /* dim_fn  */
  YYSYMBOL_expr_null = 46,                 /* expr_null  */
  YYSYMBOL_block = 47,                     /* block  */
  YYSYMBOL_decl_list = 48,                 /* decl_list  */
  YYSYMBOL_decl = 49,                      /* decl  */
  YYSYMBOL_type_decl = 50,                 /* type_decl  */
  YYSYMBOL_var_decl = 51,                  /* var_decl  */
  YYSYMBOL_type = 52,                      /* type  */
  YYSYMBOL_id_list = 53,                   /* id_list  */
  YYSYMBOL_dim_decl = 54,                  /* dim_decl  */
  YYSYMBOL_cexpr = 55,                     /* cexpr  */
  YYSYMBOL_mcexpr = 56,                    /* mcexpr  */
  YYSYMBOL_cfactor = 57,                   /* cfactor  */
  YYSYMBOL_init_id_list = 58,              /* init_id_list  */
  YYSYMBOL_init_id = 59,                   /* init_id  */
  YYSYMBOL_stmt_list = 60,                 /* stmt_list  */
  YYSYMBOL_stmt = 61,                      /* stmt  */
  YYSYMBOL_assign_expr_list = 62,          /* assign_expr_list  */
  YYSYMBOL_nonempty_assign_expr_list = 63, /* nonempty_assign_expr_list  */
  YYSYMBOL_test = 64,                      /* test  */
  YYSYMBOL_assign_expr = 65,               /* assign_expr  */
  YYSYMBOL_relop_expr = 66,                /* relop_expr  */
  YYSYMBOL_relop_term = 67,                /* relop_term  */
  YYSYMBOL_relop_factor = 68,              /* relop_factor  */
  YYSYMBOL_rel_op = 69,                    /* rel_op  */
  YYSYMBOL_relop_expr_list = 70,           /* relop_expr_list  */
  YYSYMBOL_nonempty_relop_expr_list = 71,  /* nonempty_relop_expr_list  */
  YYSYMBOL_expr = 72,                      /* expr  */
  YYSYMBOL_add_op = 73,                    /* add_op  */
  YYSYMBOL_term = 74,                      /* term  */
  YYSYMBOL_mul_op = 75,                    /* mul_op  */
  YYSYMBOL_factor = 76,                    /* factor  */
  YYSYMBOL_var_ref = 77,                   /* var_ref  */
  YYSYMBOL_dim_list = 78                   /* dim_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   256

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  215

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   166,   166,   167,   170,   174,   180,   184,   190,   197,
     205,   211,   220,   224,   230,   235,   241,   245,   251,   256,
     261,   266,   271,   276,   281,   285,   291,   295,   301,   306,
     314,   321,   325,   329,   335,   339,   343,   347,   352,   356,
     361,   366,   371,   376,   381,   386,   392,   397,   402,   408,
     412,   418,   422,   426,   432,   436,   444,   448,   453,   458,
     463,   468,   473,   478,   482,   487,   494,   499,   504,   508,
     514,   520,   526,   532,   536,   543,   547,   554,   558,   564,
     568,   572,   576,   580,   584,   591,   596,   601,   605,   611,
     615,   621,   625,   631,   635,   641,   645,   651,   655,   660,
     665,   670,   677,   684,   689,   696,   703,   707,   712,   719,
     723,   731,   735
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "CONST", "VOID",
  "INT", "FLOAT", "IF", "ELSE", "WHILE", "FOR", "TYPEDEF", "OP_ASSIGN",
  "OP_OR", "OP_AND", "OP_NOT", "OP_EQ", "OP_NE", "OP_GT", "OP_LT", "OP_GE",
  "OP_LE", "OP_PLUS", "OP_MINUS", "OP_TIMES", "OP_DIVIDE", "MK_LB",
  "MK_RB", "MK_LPAREN", "MK_RPAREN", "MK_LBRACE", "MK_RBRACE", "MK_COMMA",
  "MK_SEMICOLON", "MK_DOT", "ERROR", "RETURN", "$accept", "program",
  "global_decl_list", "global_decl", "function_decl", "param_list",
  "param", "dim_fn", "expr_null", "block", "decl_list", "decl",
  "type_decl", "var_decl", "type", "id_list", "dim_decl", "cexpr",
  "mcexpr", "cfactor", "init_id_list", "init_id", "stmt_list", "stmt",
  "assign_expr_list", "nonempty_assign_expr_list", "test", "assign_expr",
  "relop_expr", "relop_term", "relop_factor", "rel_op", "relop_expr_list",
  "nonempty_relop_expr_list", "expr", "add_op", "term", "mul_op", "factor",
  "var_ref", "dim_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
#endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-110)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     156,  -142,    30,  -142,  -142,   193,    52,   156,  -142,  -142,
     156,  -142,  -142,  -142,    42,    64,   141,   141,  -142,  -142,
    -142,  -142,    15,    37,  -142,    18,    81,    45,   103,   101,
      11,    43,   143,   177,  -142,   157,    58,  -142,   183,   143,
     191,  -142,  -142,   137,  -142,    27,    33,   101,   188,   199,
    -142,   155,   132,  -142,  -142,  -142,    11,    11,   105,   185,
    -142,   184,   171,    11,    -4,  -142,   108,   186,    94,   189,
      81,   101,   101,   192,   176,  -142,   101,  -142,   179,  -142,
     101,  -142,    66,   101,   101,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,   101,   101,  -142,  -142,   101,  -142,   126,
      11,    11,  -142,    11,    11,   108,   187,   159,    97,   194,
     195,   196,   108,  -142,    78,   190,   108,   177,    55,  -142,
     207,   108,  -142,   101,   200,   143,   161,   188,   198,   197,
     101,   101,    76,   101,   118,  -142,   199,  -142,   128,   132,
    -142,  -142,   185,   185,  -142,  -142,   201,   108,  -142,   101,
     131,   131,   131,   202,  -142,     5,  -142,    55,   180,  -142,
     101,   203,   204,   128,   101,  -142,  -142,   101,   167,   206,
    -142,   208,  -142,  -142,   205,   209,   114,   210,  -142,   188,
     211,   212,   214,  -142,  -142,  -142,    53,  -142,  -142,   169,
     188,  -142,  -142,  -142,  -142,   215,   101,    55,    55,   101,
     131,  -142,  -142,  -142,   188,   217,  -142,   216,  -142,    55,
     131,  -142,   213,    55,  -142
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    33,     0,    31,    32,     0,     0,     2,     5,     7,
       0,    25,    26,    27,     0,     0,     0,     0,     1,     4,
       6,    24,    51,     0,    49,     0,    34,     0,     0,     0,
       0,     0,    52,     0,    30,     0,     0,    13,     0,    37,
       0,    29,    28,   109,   100,     0,     0,     0,    53,    73,
      75,    77,    90,    94,   106,    46,     0,     0,     0,    42,
      45,     0,     0,     0,    51,    50,    23,     0,     0,    14,
      35,     0,    86,   110,   109,   102,     0,   108,   109,   101,
       0,   107,     0,     0,     0,    79,    82,    83,    84,    80,
      81,    91,    92,     0,     0,    95,    96,     0,    47,     0,
       0,     0,    38,     0,     0,    23,     0,     0,    33,     0,
       0,     0,    23,    63,     0,     0,    22,     0,    21,    55,
       0,    23,    12,    19,    15,    36,     0,    88,     0,    85,
       0,    86,     0,    86,     0,    97,    74,    76,    78,    89,
      93,    48,    40,    41,    43,    44,     0,    23,    39,    86,
       0,     0,    67,     0,    64,     0,    11,    20,   109,    54,
       0,     0,     0,    18,     0,   112,   103,     0,     0,     0,
      99,     0,    98,    10,     0,     0,   109,     0,    70,    72,
       0,     0,    66,    69,    56,    65,     0,     9,    16,     0,
      87,   111,   105,   104,     8,     0,     0,     0,     0,    86,
       0,    59,    17,    62,    71,    60,    57,     0,    68,     0,
      67,    61,     0,     0,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,   222,   221,   220,   153,  -142,  -142,   -92,
      34,    -7,  -142,  -142,     7,   225,   -10,    83,   112,   -50,
    -142,   219,   129,  -114,    38,  -142,    93,  -141,   -29,   170,
     172,  -142,  -123,  -142,   -66,  -142,   160,  -142,   158,   -44,
    -142
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    36,    37,   124,   162,   115,
     116,    11,    12,    13,   117,    27,    32,    58,    59,    60,
      23,    24,   118,   119,   181,   182,   177,   178,   127,    49,
      50,    93,   128,   129,    51,    94,    52,    97,    53,    54,
      73
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,    77,    81,    21,   159,   126,    98,    14,   169,    29,
     171,   183,    17,   146,    14,    55,    39,    14,    82,    83,
     153,     1,   120,    30,     3,     4,   175,   138,    29,   161,
      74,    75,    38,    15,    10,    56,    78,    79,    38,   185,
      57,    10,    30,   159,    31,    22,     1,   132,    35,     3,
       4,   134,    18,   144,   145,   174,    76,   163,   158,   208,
     125,   120,    80,   109,   168,   110,   111,    83,   120,   183,
      33,    34,   120,    61,   120,    38,   207,   120,    40,    41,
      83,    43,    44,   205,   206,   155,   112,   201,    67,   113,
      83,    68,   114,    25,    45,   211,   135,     1,   189,   214,
       3,     4,    46,   120,    43,    44,   170,    47,    30,    21,
    -109,   108,   154,   120,     3,     4,   109,    45,   110,   111,
       5,   179,   179,   179,    71,    46,   149,   196,   100,   101,
      47,   186,    83,   102,   176,    44,    40,    42,   190,   112,
      99,    71,   113,    72,    26,   114,   107,    45,   172,   100,
     101,    91,    92,   120,   120,    46,   141,    95,    96,     1,
      47,     2,     3,     4,    71,   120,    72,   204,     5,   120,
      63,   179,    85,    86,    87,    88,    89,    90,    91,    92,
      64,   179,   100,   101,    91,    92,    69,   148,    66,   165,
      91,    92,    91,    92,    70,   191,     1,   202,    16,     3,
       4,   106,    83,    71,    68,   131,    71,    71,   133,   149,
     103,   104,   142,   143,    84,   105,   123,   121,   147,   130,
     160,   122,   156,   150,   151,   152,   209,   164,   166,    19,
     167,    20,   188,   173,   184,   187,   192,   194,   193,   195,
     197,   198,    28,   213,   180,   157,   199,   200,   212,   203,
     210,    62,    65,   136,   139,   140,   137
};

static const yytype_uint8 yycheck[] =
{
      29,    45,    46,    10,   118,    71,    56,     0,   131,    13,
     133,   152,     5,   105,     7,     4,    26,    10,    47,    14,
     112,     3,    66,    27,     6,     7,   149,    93,    13,   121,
       3,     4,    25,     3,     0,    24,     3,     4,    31,    34,
      29,     7,    27,   157,    29,     3,     3,    76,    30,     6,
       7,    80,     0,   103,   104,   147,    29,   123,     3,   200,
      70,   105,    29,     8,   130,    10,    11,    14,   112,   210,
      33,    34,   116,    30,   118,    68,   199,   121,    33,    34,
      14,     3,     4,   197,   198,   114,    31,    34,    30,    34,
      14,    33,    37,    29,    16,   209,    30,     3,   164,   213,
       6,     7,    24,   147,     3,     4,    30,    29,    27,   116,
      13,     3,    34,   157,     6,     7,     8,    16,    10,    11,
      12,   150,   151,   152,    27,    24,    29,    13,    23,    24,
      29,   160,    14,    28,     3,     4,    33,    34,   167,    31,
      57,    27,    34,    29,     3,    37,    63,    16,    30,    23,
      24,    23,    24,   197,   198,    24,    30,    25,    26,     3,
      29,     5,     6,     7,    27,   209,    29,   196,    12,   213,
      27,   200,    17,    18,    19,    20,    21,    22,    23,    24,
       3,   210,    23,    24,    23,    24,     3,    28,    31,    28,
      23,    24,    23,    24,     3,    28,     3,    28,     5,     6,
       7,    30,    14,    27,    33,    29,    27,    27,    29,    29,
      25,    26,   100,   101,    15,    31,    27,    31,    31,    27,
      13,    68,    32,    29,    29,    29,     9,    27,    30,     7,
      33,    10,    28,    32,    32,    32,    30,    32,    30,    30,
      30,    30,    17,    30,   151,   116,    34,    33,   210,    34,
      34,    31,    33,    83,    94,    97,    84
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    39,    40,    41,    42,
      48,    49,    50,    51,    52,     3,     5,    52,     0,    41,
      42,    49,     3,    58,    59,    29,     3,    53,    53,    13,
      27,    29,    54,    33,    34,    30,    43,    44,    52,    54,
      33,    34,    34,     3,     4,    16,    24,    29,    66,    67,
      68,    72,    74,    76,    77,     4,    24,    29,    55,    56,
      57,    30,    43,    27,     3,    59,    31,    30,    33,     3,
       3,    27,    29,    78,     3,     4,    29,    77,     3,     4,
      29,    77,    66,    14,    15,    17,    18,    19,    20,    21,
      22,    23,    24,    69,    73,    25,    26,    75,    57,    55,
      23,    24,    28,    25,    26,    31,    30,    55,     3,     8,
      10,    11,    31,    34,    37,    47,    48,    52,    60,    61,
      77,    31,    44,    27,    45,    54,    72,    66,    70,    71,
      27,    29,    66,    29,    66,    30,    67,    68,    72,    74,
      76,    30,    56,    56,    57,    57,    47,    31,    28,    29,
      29,    29,    29,    47,    34,    66,    32,    60,     3,    61,
      13,    47,    46,    72,    27,    28,    30,    33,    72,    70,
      30,    70,    30,    32,    47,    70,     3,    64,    65,    66,
      64,    62,    63,    65,    32,    34,    66,    32,    28,    72,
      66,    28,    30,    30,    32,    30,    13,    30,    30,    34,
      33,    34,    28,    34,    66,    61,    61,    70,    65,     9,
      34,    61,    62,    30,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    52,    52,    52,    53,    53,    53,    53,    54,    54,
      55,    55,    55,    56,    56,    56,    57,    57,    57,    58,
      58,    59,    59,    59,    60,    60,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    62,    63,    63,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    77,
      77,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     3,     4,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     1,     4,     4,
       3,     1,     1,     1,     1,     3,     4,     2,     3,     4,
       3,     3,     1,     3,     3,     1,     1,     2,     3,     1,
       3,     1,     2,     3,     2,     1,     3,     5,     9,     4,
       5,     7,     5,     1,     2,     3,     1,     0,     3,     1,
       1,     3,     1,     1,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     4,     4,
       1,     2,     2,     4,     5,     5,     1,     2,     2,     1,
       2,     4,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: global_decl_list  */
#line 166 "parser.y"
                                   { (yyval.node)=Allocate(PROGRAM_NODE);  makeChild((yyval.node),(yyvsp[0].node)); prog=(yyval.node);}
#line 1397 "parser.tab.c"
    break;

  case 3: /* program: %empty  */
#line 167 "parser.y"
                  { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);}
#line 1403 "parser.tab.c"
    break;

  case 4: /* global_decl_list: global_decl_list global_decl  */
#line 171 "parser.y"
                    {
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                    }
#line 1411 "parser.tab.c"
    break;

  case 5: /* global_decl_list: global_decl  */
#line 175 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1419 "parser.tab.c"
    break;

  case 6: /* global_decl: decl_list function_decl  */
#line 181 "parser.y"
                {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), (yyvsp[0].node));
                }
#line 1427 "parser.tab.c"
    break;

  case 7: /* global_decl: function_decl  */
#line 185 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1435 "parser.tab.c"
    break;

  case 8: /* function_decl: type ID MK_LPAREN param_list MK_RPAREN MK_LBRACE block MK_RBRACE  */
#line 191 "parser.y"
                    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, (yyvsp[-7].node), makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
                    }
#line 1446 "parser.tab.c"
    break;

  case 9: /* function_decl: VOID ID MK_LPAREN param_list MK_RPAREN MK_LBRACE block MK_RBRACE  */
#line 198 "parser.y"
                    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, voidNode, makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
                    }
#line 1458 "parser.tab.c"
    break;

  case 10: /* function_decl: type ID MK_LPAREN MK_RPAREN MK_LBRACE block MK_RBRACE  */
#line 206 "parser.y"
                    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, (yyvsp[-6].node), makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
                    }
#line 1468 "parser.tab.c"
    break;

  case 11: /* function_decl: VOID ID MK_LPAREN MK_RPAREN MK_LBRACE block MK_RBRACE  */
#line 212 "parser.y"
                    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, voidNode, makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
                    }
#line 1479 "parser.tab.c"
    break;

  case 12: /* param_list: param_list MK_COMMA param  */
#line 221 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1487 "parser.tab.c"
    break;

  case 13: /* param_list: param  */
#line 225 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node); 
                }
#line 1495 "parser.tab.c"
    break;

  case 14: /* param: type ID  */
#line 231 "parser.y"
                {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1504 "parser.tab.c"
    break;

  case 15: /* param: type ID dim_fn  */
#line 236 "parser.y"
                {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1513 "parser.tab.c"
    break;

  case 16: /* dim_fn: MK_LB expr_null MK_RB  */
#line 242 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1521 "parser.tab.c"
    break;

  case 17: /* dim_fn: dim_fn MK_LB expr MK_RB  */
#line 246 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1529 "parser.tab.c"
    break;

  case 18: /* expr_null: expr  */
#line 252 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1537 "parser.tab.c"
    break;

  case 19: /* expr_null: %empty  */
#line 256 "parser.y"
                {
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 1545 "parser.tab.c"
    break;

  case 20: /* block: decl_list stmt_list  */
#line 262 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1554 "parser.tab.c"
    break;

  case 21: /* block: stmt_list  */
#line 267 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1563 "parser.tab.c"
    break;

  case 22: /* block: decl_list  */
#line 272 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1572 "parser.tab.c"
    break;

  case 23: /* block: %empty  */
#line 276 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                    }
#line 1580 "parser.tab.c"
    break;

  case 24: /* decl_list: decl_list decl  */
#line 282 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1588 "parser.tab.c"
    break;

  case 25: /* decl_list: decl  */
#line 286 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1596 "parser.tab.c"
    break;

  case 26: /* decl: type_decl  */
#line 292 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1604 "parser.tab.c"
    break;

  case 27: /* decl: var_decl  */
#line 296 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1612 "parser.tab.c"
    break;

  case 28: /* type_decl: TYPEDEF type id_list MK_SEMICOLON  */
#line 302 "parser.y"
                {
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1621 "parser.tab.c"
    break;

  case 29: /* type_decl: TYPEDEF VOID id_list MK_SEMICOLON  */
#line 307 "parser.y"
                {
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                    makeFamily((yyval.node), 2, voidNode, (yyvsp[-1].node));
                }
#line 1631 "parser.tab.c"
    break;

  case 30: /* var_decl: type init_id_list MK_SEMICOLON  */
#line 315 "parser.y"
                {
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1640 "parser.tab.c"
    break;

  case 31: /* type: INT  */
#line 322 "parser.y"
                {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);  
                }
#line 1648 "parser.tab.c"
    break;

  case 32: /* type: FLOAT  */
#line 326 "parser.y"
                {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                }
#line 1656 "parser.tab.c"
    break;

  case 33: /* type: ID  */
#line 330 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1664 "parser.tab.c"
    break;

  case 34: /* id_list: ID  */
#line 336 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1672 "parser.tab.c"
    break;

  case 35: /* id_list: id_list MK_COMMA ID  */
#line 340 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-2].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1680 "parser.tab.c"
    break;

  case 36: /* id_list: id_list MK_COMMA ID dim_decl  */
#line 344 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1688 "parser.tab.c"
    break;

  case 37: /* id_list: ID dim_decl  */
#line 348 "parser.y"
                {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 1696 "parser.tab.c"
    break;

  case 38: /* dim_decl: MK_LB cexpr MK_RB  */
#line 353 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1704 "parser.tab.c"
    break;

  case 39: /* dim_decl: dim_decl MK_LB cexpr MK_RB  */
#line 357 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1712 "parser.tab.c"
    break;

  case 40: /* cexpr: cexpr OP_PLUS mcexpr  */
#line 362 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1721 "parser.tab.c"
    break;

  case 41: /* cexpr: cexpr OP_MINUS mcexpr  */
#line 367 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1730 "parser.tab.c"
    break;

  case 42: /* cexpr: mcexpr  */
#line 372 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1738 "parser.tab.c"
    break;

  case 43: /* mcexpr: mcexpr OP_TIMES cfactor  */
#line 377 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1747 "parser.tab.c"
    break;

  case 44: /* mcexpr: mcexpr OP_DIVIDE cfactor  */
#line 382 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1756 "parser.tab.c"
    break;

  case 45: /* mcexpr: cfactor  */
#line 387 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1764 "parser.tab.c"
    break;

  case 46: /* cfactor: CONST  */
#line 393 "parser.y"
                {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1 = (yyvsp[0].const1);
                }
#line 1773 "parser.tab.c"
    break;

  case 47: /* cfactor: OP_MINUS cfactor  */
#line 398 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION,UNARY_OP_NEGATIVE);
                    makeFamily((yyval.node),1,(yyvsp[0].node));
                }
#line 1782 "parser.tab.c"
    break;

  case 48: /* cfactor: MK_LPAREN cexpr MK_RPAREN  */
#line 403 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1790 "parser.tab.c"
    break;

  case 49: /* init_id_list: init_id  */
#line 409 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node); 
                    }
#line 1798 "parser.tab.c"
    break;

  case 50: /* init_id_list: init_id_list MK_COMMA init_id  */
#line 413 "parser.y"
                    {
                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1806 "parser.tab.c"
    break;

  case 51: /* init_id: ID  */
#line 419 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1814 "parser.tab.c"
    break;

  case 52: /* init_id: ID dim_decl  */
#line 423 "parser.y"
                {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 1822 "parser.tab.c"
    break;

  case 53: /* init_id: ID OP_ASSIGN relop_expr  */
#line 427 "parser.y"
                {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-2].lexeme), WITH_INIT_ID), (yyvsp[0].node));
                }
#line 1830 "parser.tab.c"
    break;

  case 54: /* stmt_list: stmt_list stmt  */
#line 433 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1838 "parser.tab.c"
    break;

  case 55: /* stmt_list: stmt  */
#line 437 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1846 "parser.tab.c"
    break;

  case 56: /* stmt: MK_LBRACE block MK_RBRACE  */
#line 445 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1854 "parser.tab.c"
    break;

  case 57: /* stmt: WHILE MK_LPAREN test MK_RPAREN stmt  */
#line 449 "parser.y"
                {
                    (yyval.node) = makeStmtNode(WHILE_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1863 "parser.tab.c"
    break;

  case 58: /* stmt: FOR MK_LPAREN assign_expr_list MK_SEMICOLON relop_expr_list MK_SEMICOLON assign_expr_list MK_RPAREN stmt  */
#line 454 "parser.y"
                {
                    (yyval.node) = makeStmtNode(FOR_STMT);
                    makeFamily((yyval.node), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1872 "parser.tab.c"
    break;

  case 59: /* stmt: var_ref OP_ASSIGN relop_expr MK_SEMICOLON  */
#line 459 "parser.y"
                {
                    (yyval.node) = makeStmtNode(ASSIGN_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1881 "parser.tab.c"
    break;

  case 60: /* stmt: IF MK_LPAREN test MK_RPAREN stmt  */
#line 464 "parser.y"
                {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-2].node), (yyvsp[0].node), Allocate(NUL_NODE));
                }
#line 1890 "parser.tab.c"
    break;

  case 61: /* stmt: IF MK_LPAREN test MK_RPAREN stmt ELSE stmt  */
#line 469 "parser.y"
                {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1899 "parser.tab.c"
    break;

  case 62: /* stmt: ID MK_LPAREN relop_expr_list MK_RPAREN MK_SEMICOLON  */
#line 474 "parser.y"
                {
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-4].lexeme), NORMAL_ID), (yyvsp[-2].node));
                }
#line 1908 "parser.tab.c"
    break;

  case 63: /* stmt: MK_SEMICOLON  */
#line 479 "parser.y"
                {
                    (yyval.node) = Allocate(NUL_NODE);
                }
#line 1916 "parser.tab.c"
    break;

  case 64: /* stmt: RETURN MK_SEMICOLON  */
#line 483 "parser.y"
                {
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), Allocate(NUL_NODE));
                }
#line 1925 "parser.tab.c"
    break;

  case 65: /* stmt: RETURN relop_expr MK_SEMICOLON  */
#line 488 "parser.y"
                {
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 1934 "parser.tab.c"
    break;

  case 66: /* assign_expr_list: nonempty_assign_expr_list  */
#line 495 "parser.y"
                     {
                        (yyval.node) = makeChild(Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE), (yyvsp[0].node));
                     }
#line 1942 "parser.tab.c"
    break;

  case 67: /* assign_expr_list: %empty  */
#line 499 "parser.y"
                     {
                         (yyval.node) = Allocate(NUL_NODE); 
                     }
#line 1950 "parser.tab.c"
    break;

  case 68: /* nonempty_assign_expr_list: nonempty_assign_expr_list MK_COMMA assign_expr  */
#line 505 "parser.y"
                                    {
                                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                    }
#line 1958 "parser.tab.c"
    break;

  case 69: /* nonempty_assign_expr_list: assign_expr  */
#line 509 "parser.y"
                                    {
                                        (yyval.node) = (yyvsp[0].node);
                                    }
#line 1966 "parser.tab.c"
    break;

  case 70: /* test: assign_expr  */
#line 515 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1974 "parser.tab.c"
    break;

  case 71: /* assign_expr: ID OP_ASSIGN relop_expr  */
#line 521 "parser.y"
                    {
                        //TODO: for simpler implementation, use ASSIGN_STMT for now
                        (yyval.node) = makeStmtNode(ASSIGN_STMT);
                        makeFamily((yyval.node), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[0].node));
                    }
#line 1984 "parser.tab.c"
    break;

  case 72: /* assign_expr: relop_expr  */
#line 527 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1992 "parser.tab.c"
    break;

  case 73: /* relop_expr: relop_term  */
#line 533 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2000 "parser.tab.c"
    break;

  case 74: /* relop_expr: relop_expr OP_OR relop_term  */
#line 537 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2009 "parser.tab.c"
    break;

  case 75: /* relop_term: relop_factor  */
#line 544 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2017 "parser.tab.c"
    break;

  case 76: /* relop_term: relop_term OP_AND relop_factor  */
#line 548 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_AND);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2026 "parser.tab.c"
    break;

  case 77: /* relop_factor: expr  */
#line 555 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2034 "parser.tab.c"
    break;

  case 78: /* relop_factor: expr rel_op expr  */
#line 559 "parser.y"
                    {
                        (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2042 "parser.tab.c"
    break;

  case 79: /* rel_op: OP_EQ  */
#line 565 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
#line 2050 "parser.tab.c"
    break;

  case 80: /* rel_op: OP_GE  */
#line 569 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
#line 2058 "parser.tab.c"
    break;

  case 81: /* rel_op: OP_LE  */
#line 573 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
#line 2066 "parser.tab.c"
    break;

  case 82: /* rel_op: OP_NE  */
#line 577 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
#line 2074 "parser.tab.c"
    break;

  case 83: /* rel_op: OP_GT  */
#line 581 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
#line 2082 "parser.tab.c"
    break;

  case 84: /* rel_op: OP_LT  */
#line 585 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
#line 2090 "parser.tab.c"
    break;

  case 85: /* relop_expr_list: nonempty_relop_expr_list  */
#line 592 "parser.y"
                    {
                        (yyval.node) = makeChild(Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE), (yyvsp[0].node));
                    }
#line 2098 "parser.tab.c"
    break;

  case 86: /* relop_expr_list: %empty  */
#line 596 "parser.y"
                    {
                        (yyval.node) = Allocate(NUL_NODE);
                    }
#line 2106 "parser.tab.c"
    break;

  case 87: /* nonempty_relop_expr_list: nonempty_relop_expr_list MK_COMMA relop_expr  */
#line 602 "parser.y"
                                {
                                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                }
#line 2114 "parser.tab.c"
    break;

  case 88: /* nonempty_relop_expr_list: relop_expr  */
#line 606 "parser.y"
                                {
                                    (yyval.node) = (yyvsp[0].node);
                                }
#line 2122 "parser.tab.c"
    break;

  case 89: /* expr: expr add_op term  */
#line 612 "parser.y"
                {
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2130 "parser.tab.c"
    break;

  case 90: /* expr: term  */
#line 616 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2138 "parser.tab.c"
    break;

  case 91: /* add_op: OP_PLUS  */
#line 622 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
#line 2146 "parser.tab.c"
    break;

  case 92: /* add_op: OP_MINUS  */
#line 626 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
#line 2154 "parser.tab.c"
    break;

  case 93: /* term: term mul_op factor  */
#line 632 "parser.y"
                {
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2162 "parser.tab.c"
    break;

  case 94: /* term: factor  */
#line 636 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2170 "parser.tab.c"
    break;

  case 95: /* mul_op: OP_TIMES  */
#line 642 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
#line 2178 "parser.tab.c"
    break;

  case 96: /* mul_op: OP_DIVIDE  */
#line 646 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
#line 2186 "parser.tab.c"
    break;

  case 97: /* factor: MK_LPAREN relop_expr MK_RPAREN  */
#line 652 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2194 "parser.tab.c"
    break;

  case 98: /* factor: OP_MINUS MK_LPAREN relop_expr MK_RPAREN  */
#line 656 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2203 "parser.tab.c"
    break;

  case 99: /* factor: OP_NOT MK_LPAREN relop_expr MK_RPAREN  */
#line 661 "parser.y"
                {   
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2212 "parser.tab.c"
    break;

  case 100: /* factor: CONST  */
#line 666 "parser.y"
                {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 2221 "parser.tab.c"
    break;

  case 101: /* factor: OP_MINUS CONST  */
#line 671 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE *constNode = Allocate(CONST_VALUE_NODE);
                    constNode->semantic_value.const1 = (yyvsp[0].const1);
                    makeChild((yyval.node), constNode);
                }
#line 2232 "parser.tab.c"
    break;

  case 102: /* factor: OP_NOT CONST  */
#line 678 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE *constNode = Allocate(CONST_VALUE_NODE);
                    constNode->semantic_value.const1 = (yyvsp[0].const1);
                    makeChild((yyval.node), constNode);
                }
#line 2243 "parser.tab.c"
    break;

  case 103: /* factor: ID MK_LPAREN relop_expr_list MK_RPAREN  */
#line 685 "parser.y"
                {
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                }
#line 2252 "parser.tab.c"
    break;

  case 104: /* factor: OP_MINUS ID MK_LPAREN relop_expr_list MK_RPAREN  */
#line 690 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE* functionCallNode = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(functionCallNode, 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                    makeChild((yyval.node), functionCallNode);
                }
#line 2263 "parser.tab.c"
    break;

  case 105: /* factor: OP_NOT ID MK_LPAREN relop_expr_list MK_RPAREN  */
#line 697 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE* functionCallNode = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(functionCallNode, 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                    makeChild((yyval.node), functionCallNode);
                }
#line 2274 "parser.tab.c"
    break;

  case 106: /* factor: var_ref  */
#line 704 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2282 "parser.tab.c"
    break;

  case 107: /* factor: OP_MINUS var_ref  */
#line 708 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 2291 "parser.tab.c"
    break;

  case 108: /* factor: OP_NOT var_ref  */
#line 713 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 2300 "parser.tab.c"
    break;

  case 109: /* var_ref: ID  */
#line 720 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2308 "parser.tab.c"
    break;

  case 110: /* var_ref: ID dim_list  */
#line 724 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node),(yyvsp[0].node));
                }
#line 2317 "parser.tab.c"
    break;

  case 111: /* dim_list: dim_list MK_LB expr MK_RB  */
#line 732 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2325 "parser.tab.c"
    break;

  case 112: /* dim_list: MK_LB expr MK_RB  */
#line 736 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2333 "parser.tab.c"
    break;


#line 2337 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 742 "parser.y"


#include "lex.yy.c"
main (argc, argv)
int argc;
char *argv[];
  {
     yyin = fopen(argv[1],"r");
     yyparse();
     // printGV(prog, NULL);
     
     initializeSymbolTable();
     
     semanticAnalysis(prog);

     codegen(prog);
     
     symbolTableEnd();
     if (!g_anyErrorOccur) {
        printf("Parsing completed. No errors found.\n");
     }
  } /* main */


int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }
