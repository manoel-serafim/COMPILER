/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "parser.h"
#include "macros.h"
#define YYSTYPE syntax_t_node * //return of bison when ref to $
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1 // is defined before any use of it
#include "lexer.h"
#include <stdio.h>
#define yylex() get_next_token(glob_context.p_buffer, glob_context.stream, glob_context.p_token_rec)
void yyerror(char * err);

static syntax_t_node* syntax_tree_root; //root of the tree
syntax_t_node* parse(void);



#line 88 "parser.tab.c"

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
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_PLUS_ALOP = 11,                 /* PLUS_ALOP  */
  YYSYMBOL_MINUS_ALOP = 12,                /* MINUS_ALOP  */
  YYSYMBOL_MULT_PRE_ALOP = 13,             /* MULT_PRE_ALOP  */
  YYSYMBOL_DIV_PRE_ALOP = 14,              /* DIV_PRE_ALOP  */
  YYSYMBOL_EQ_RELOP = 15,                  /* EQ_RELOP  */
  YYSYMBOL_NOTEQ_RELOP = 16,               /* NOTEQ_RELOP  */
  YYSYMBOL_LESSEQ_RELOP = 17,              /* LESSEQ_RELOP  */
  YYSYMBOL_GREATEQ_RELOP = 18,             /* GREATEQ_RELOP  */
  YYSYMBOL_GREAT_RELOP = 19,               /* GREAT_RELOP  */
  YYSYMBOL_LESS_RELOP = 20,                /* LESS_RELOP  */
  YYSYMBOL_EQUAL = 21,                     /* EQUAL  */
  YYSYMBOL_CURLYOP_BRACKET = 22,           /* CURLYOP_BRACKET  */
  YYSYMBOL_CURLYCL_BRACKET = 23,           /* CURLYCL_BRACKET  */
  YYSYMBOL_CIRCLEOP_BRACKET = 24,          /* CIRCLEOP_BRACKET  */
  YYSYMBOL_CIRCLECL_BRACKET = 25,          /* CIRCLECL_BRACKET  */
  YYSYMBOL_SQUAREOP_BRACKET = 26,          /* SQUAREOP_BRACKET  */
  YYSYMBOL_SQUARECL_BRACKET = 27,          /* SQUARECL_BRACKET  */
  YYSYMBOL_SEMICOL_PUNCT = 28,             /* SEMICOL_PUNCT  */
  YYSYMBOL_COMMA_PUNCT = 29,               /* COMMA_PUNCT  */
  YYSYMBOL_WHITESPACE = 30,                /* WHITESPACE  */
  YYSYMBOL_COMMENT = 31,                   /* COMMENT  */
  YYSYMBOL_STRING = 32,                    /* STRING  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_program = 34,                   /* program  */
  YYSYMBOL_declaration_list = 35,          /* declaration_list  */
  YYSYMBOL_declaration = 36,               /* declaration  */
  YYSYMBOL_var_declaration = 37,           /* var_declaration  */
  YYSYMBOL_type_specifier = 38,            /* type_specifier  */
  YYSYMBOL_fun_declaration = 39,           /* fun_declaration  */
  YYSYMBOL_parameters = 40,                /* parameters  */
  YYSYMBOL_parameter_list = 41,            /* parameter_list  */
  YYSYMBOL_parameter = 42,                 /* parameter  */
  YYSYMBOL_compound_declaration = 43,      /* compound_declaration  */
  YYSYMBOL_local_declarations = 44,        /* local_declarations  */
  YYSYMBOL_statement_list = 45,            /* statement_list  */
  YYSYMBOL_statement = 46,                 /* statement  */
  YYSYMBOL_expression_declaration = 47,    /* expression_declaration  */
  YYSYMBOL_selection_declaration = 48,     /* selection_declaration  */
  YYSYMBOL_iteration_declaration = 49,     /* iteration_declaration  */
  YYSYMBOL_return_declaration = 50,        /* return_declaration  */
  YYSYMBOL_expression = 51,                /* expression  */
  YYSYMBOL_var = 52,                       /* var  */
  YYSYMBOL_simple_expression = 53,         /* simple_expression  */
  YYSYMBOL_relational = 54,                /* relational  */
  YYSYMBOL_sum_expression = 55,            /* sum_expression  */
  YYSYMBOL_sum = 56,                       /* sum  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_mult = 58,                      /* mult  */
  YYSYMBOL_factor = 59,                    /* factor  */
  YYSYMBOL_activation = 60,                /* activation  */
  YYSYMBOL_argument_list = 61,             /* argument_list  */
  YYSYMBOL_number = 62,                    /* number  */
  YYSYMBOL_identificator = 63              /* identificator  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   137

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    22,    22,    26,    39,    46,    50,    57,    65,    76,
      82,    91,   103,   107,   112,   125,   132,   137,   146,   159,
     163,   167,   172,   185,   192,   205,   212,   216,   220,   224,
     228,   235,   239,   244,   250,   260,   269,   273,   281,   287,
     294,   298,   307,   313,   320,   325,   330,   335,   340,   345,
     353,   359,   366,   371,   379,   385,   392,   397,   405,   409,
     413,   417,   424,   432,   441,   454,   461,   469
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUM", "IF",
  "ELSE", "WHILE", "RETURN", "INT", "VOID", "PLUS_ALOP", "MINUS_ALOP",
  "MULT_PRE_ALOP", "DIV_PRE_ALOP", "EQ_RELOP", "NOTEQ_RELOP",
  "LESSEQ_RELOP", "GREATEQ_RELOP", "GREAT_RELOP", "LESS_RELOP", "EQUAL",
  "CURLYOP_BRACKET", "CURLYCL_BRACKET", "CIRCLEOP_BRACKET",
  "CIRCLECL_BRACKET", "SQUAREOP_BRACKET", "SQUARECL_BRACKET",
  "SEMICOL_PUNCT", "COMMA_PUNCT", "WHITESPACE", "COMMENT", "STRING",
  "$accept", "program", "declaration_list", "declaration",
  "var_declaration", "type_specifier", "fun_declaration", "parameters",
  "parameter_list", "parameter", "compound_declaration",
  "local_declarations", "statement_list", "statement",
  "expression_declaration", "selection_declaration",
  "iteration_declaration", "return_declaration", "expression", "var",
  "simple_expression", "relational", "sum_expression", "sum", "term",
  "mult", "factor", "activation", "argument_list", "number",
  "identificator", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-14)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       0,   -40,   -40,    19,     0,   -40,   -40,    22,   -40,   -40,
     -40,   -40,    60,    98,    32,   -40,    -3,    22,    48,    58,
     -40,   -40,    79,    68,    91,     0,    86,    88,    35,   -40,
     -40,   -40,   -40,    92,    93,     2,   -40,    17,   -40,   -40,
      22,   -40,    67,    75,   -40,   -40,   -40,   -40,   -40,    90,
     101,   -40,    36,    96,   -40,   -40,   -40,    40,    17,    17,
     -40,    95,    99,    39,   -40,   -40,    97,   -40,   -40,   -40,
      17,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,    17,
      17,   -40,   -40,    17,     4,    17,   102,   103,   -40,   -40,
     -40,   -40,   -40,   100,    96,   -40,   -40,   -40,    56,   104,
       9,     9,   -40,    17,   -40,   120,   -40,   -40,     9,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,    67,     0,     0,     0,     7,    10,     0,     0,    12,
      15,    66,     0,    16,     0,     0,     0,     0,     0,    11,
      14,     8,    17,     0,     0,     0,    21,     0,    32,    23,
       0,    27,     0,     0,    25,    26,    28,    29,    30,     0,
      59,    39,    43,    51,    55,    60,    61,    40,     0,     0,
      36,     0,     0,     0,    19,    22,     0,    20,    24,    31,
       0,    52,    53,    44,    45,    46,    47,    48,    49,     0,
       0,    57,    56,     0,     0,     0,     0,     0,    37,    58,
      18,    38,    59,    42,    50,    54,    63,    65,     0,     0,
       0,     0,    62,     0,    41,    33,    35,    64,     0,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -40,   125,    18,   -10,   -40,   -40,   -40,   105,
     108,   -40,    94,   -39,   -40,   -40,   -40,   -40,   -35,    13,
     -40,   -40,    54,   -40,    55,   -40,    51,   -40,   -40,   123,
      -6
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,     8,    18,    19,    20,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    79,    52,    80,    53,    83,    54,    55,    98,    56,
      57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      61,    12,    62,    17,    68,    11,    21,    11,    21,     1,
       2,    23,    11,    21,    33,    17,    34,    35,    40,     9,
      11,    21,   -13,    86,    87,    11,    37,    68,    37,    96,
      60,    28,    40,    37,    63,    91,    21,    38,    11,    21,
      33,    37,    34,    35,     1,     2,    39,    71,    72,    97,
      99,    73,    74,    75,    76,    77,    78,    28,    36,    37,
      65,   105,   106,    38,    84,    14,    85,    15,   107,   109,
      11,    21,    33,    24,    34,    35,     1,     2,    11,    21,
      33,   102,    34,    35,    13,   103,    14,    25,    15,    28,
      64,    37,    92,    92,    27,    38,    92,    28,    67,    37,
      11,    21,    33,    38,    34,    35,    26,     1,    16,    81,
      82,    71,    72,    28,    31,    32,    58,    59,    69,    28,
      90,    37,    70,    88,    89,    38,   108,   100,   101,    10,
      30,   104,    29,    93,    95,    94,    66,    22
};

static const yytype_int8 yycheck[] =
{
      35,     7,    37,    13,    43,     3,     4,     3,     4,     9,
      10,    17,     3,     4,     5,    25,     7,     8,    28,     0,
       3,     4,    25,    58,    59,     3,    24,    66,    24,    25,
      28,    22,    42,    24,    40,    70,     4,    28,     3,     4,
       5,    24,     7,     8,     9,    10,    28,    11,    12,    84,
      85,    15,    16,    17,    18,    19,    20,    22,    23,    24,
      42,   100,   101,    28,    24,    26,    26,    28,   103,   108,
       3,     4,     5,    25,     7,     8,     9,    10,     3,     4,
       5,    25,     7,     8,    24,    29,    26,    29,    28,    22,
      23,    24,    79,    80,    26,    28,    83,    22,    23,    24,
       3,     4,     5,    28,     7,     8,    27,     9,    10,    13,
      14,    11,    12,    22,    28,    27,    24,    24,    28,    22,
      23,    24,    21,    28,    25,    28,     6,    25,    25,     4,
      25,    27,    24,    79,    83,    80,    42,    14
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    10,    34,    35,    36,    37,    38,    39,     0,
      36,     3,    63,    24,    26,    28,    10,    38,    40,    41,
      42,     4,    62,    63,    25,    29,    27,    26,    22,    43,
      42,    28,    27,     5,     7,     8,    23,    24,    28,    37,
      38,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    55,    57,    59,    60,    62,    63,    24,    24,
      28,    51,    51,    63,    23,    37,    45,    23,    46,    28,
      21,    11,    12,    15,    16,    17,    18,    19,    20,    54,
      56,    13,    14,    58,    24,    26,    51,    51,    28,    25,
      23,    51,    52,    55,    57,    59,    25,    51,    61,    51,
      25,    25,    25,    29,    27,    46,    46,    51,     6,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    37,    37,    38,
      38,    39,    40,    40,    41,    41,    42,    42,    43,    43,
      43,    43,    44,    44,    45,    45,    46,    46,    46,    46,
      46,    47,    47,    48,    48,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    54,    54,    54,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      59,    59,    60,    60,    61,    61,    62,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     1,     3,     1,     2,     4,     4,     3,
       3,     2,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     1,     5,     7,     5,     2,     3,     3,     1,
       1,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1,     4,     3,     3,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
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
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 2: /* program: declaration_list  */
#line 22 "parser.y"
                     { syntax_tree_root = yyvsp[0]; }
#line 1221 "parser.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 27 "parser.y"
    {   
        YYSTYPE temp = yyvsp[-1]; 
        if(temp == NULL){ //if it was not def, def it
            yyval = yyvsp[0];
        }else{
            while(temp->sibling != NULL){ //if was def, find the next brother to define sequentially
                temp = temp->sibling;
            }
            temp->sibling = yyvsp[0]; //found the sibling not def in the chained link and now will set value
            yyval = yyvsp[-1]; 
        }
    }
#line 1238 "parser.tab.c"
    break;

  case 4: /* declaration_list: declaration  */
#line 40 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1246 "parser.tab.c"
    break;

  case 5: /* declaration: var_declaration  */
#line 47 "parser.y"
    {
        yyval = yyvsp[0]; //set variable declaration as top
    }
#line 1254 "parser.tab.c"
    break;

  case 6: /* declaration: fun_declaration  */
#line 51 "parser.y"
    {
        yyval = yyvsp[0]; //set function declaration as top
    }
#line 1262 "parser.tab.c"
    break;

  case 7: /* var_declaration: type_specifier identificator SEMICOL_PUNCT  */
#line 58 "parser.y"
    {
        yyval = yyvsp[-2]; //type spec go down semantic value
        yyval->child[0]= yyvsp[-1]; // Set exp type node como filho de VAR_DECL 
        yyvsp[-1]->has.stmt = VAR_SK; //simple variable statement
        yyvsp[-1]->type= STMT_T; //declaration statement
        
    }
#line 1274 "parser.tab.c"
    break;

  case 8: /* var_declaration: type_specifier identificator SQUAREOP_BRACKET number SQUARECL_BRACKET SEMICOL_PUNCT  */
#line 66 "parser.y"
    {
        yyval = yyvsp[-5]; //type spec go down semantic value
        yyval->child[0]= yyvsp[-4]; // Set identificator como filho de VAR_DECL 
        yyvsp[-4]->has.stmt = VECT_SK; //vector declaration statement
        yyvsp[-4]->attr.size = yyvsp[-2]->attr.val; // vector[size]
        yyvsp[-4]->type = STMT_T; //declaration statement   
    }
#line 1286 "parser.tab.c"
    break;

  case 9: /* type_specifier: INT  */
#line 77 "parser.y"
    {
        //found leaf structure -semantic value of node
        yyval=new_exp_node(TYPE_EK); //create new exp node
        yyval->has.exp.type=INT_T;
    }
#line 1296 "parser.tab.c"
    break;

  case 10: /* type_specifier: VOID  */
#line 83 "parser.y"
    {
        //found leaf structure -semantic value of node
        yyval=new_exp_node(TYPE_EK); //create new void exp node
        yyval->has.exp.type=VOID_T;
    }
#line 1306 "parser.tab.c"
    break;

  case 11: /* fun_declaration: type_specifier identificator CIRCLEOP_BRACKET parameters CIRCLECL_BRACKET compound_declaration  */
#line 92 "parser.y"
    {
        yyval = yyvsp[-5]; //set semantic value to type spec, it will have a node for the specific type
        yyval->child[0] = yyvsp[-4]; //child + left = identificator (name of func)
        yyvsp[-4]->child[0] = yyvsp[-2]; //pointer to funct args
        yyvsp[-4]->child[1] = yyvsp[0]; // at the side of params it will have the declaration of the procedure
        yyvsp[-4]->has.stmt = FUNCT_SK; // this statement is a function
        yyvsp[-4]->type = STMT_T; //function declaration statement
    }
#line 1319 "parser.tab.c"
    break;

  case 12: /* parameters: parameter_list  */
#line 104 "parser.y"
    {
      yyval = yyvsp[0]; //set semantic value to get the parameter declarations
    }
#line 1327 "parser.tab.c"
    break;

  case 13: /* parameters: VOID  */
#line 108 "parser.y"
    { /*do nothing*/ }
#line 1333 "parser.tab.c"
    break;

  case 14: /* parameter_list: parameter_list COMMA_PUNCT parameter  */
#line 113 "parser.y"
    {
        YYSTYPE temp = yyvsp[-2]; // temp tree node of param list
        if(temp == NULL){
            yyval = yyvsp[0]; // if not def, get parameter definition
        }else{
            while(temp->sibling != NULL){ //get next empty sibling
                temp = temp->sibling;
            }
            temp->sibling = yyvsp[0];
            yyval = yyvsp[-2]; //get node from parameter_list
        }
    }
#line 1350 "parser.tab.c"
    break;

  case 15: /* parameter_list: parameter  */
#line 126 "parser.y"
    {
        yyval = yyvsp[0]; //get node from parameter
    }
#line 1358 "parser.tab.c"
    break;

  case 16: /* parameter: type_specifier identificator  */
#line 133 "parser.y"
    {
        yyval = yyvsp[-1]; // get node from spec
        yyval->child[0] = yyvsp[0]; // the identificator is the left child of the type spec
    }
#line 1367 "parser.tab.c"
    break;

  case 17: /* parameter: type_specifier identificator SQUAREOP_BRACKET SQUARECL_BRACKET  */
#line 138 "parser.y"
    {
        yyval = yyvsp[-3]; //get node from spec
        yyval->child[0] = yyvsp[-2]; //identificator is in left child
        yyvsp[-2]->has.exp.kind = VECT_ID_EK;
    }
#line 1377 "parser.tab.c"
    break;

  case 18: /* compound_declaration: CURLYOP_BRACKET local_declarations statement_list CURLYCL_BRACKET  */
#line 147 "parser.y"
    {
        YYSTYPE temp = yyvsp[-2];
        if(temp == NULL){
            yyval=yyvsp[-1];
        }else{
            while(temp->sibling != NULL){ //get next empty sibling
                temp = temp->sibling;
            }
            temp->sibling = yyvsp[-1];
            yyval = yyvsp[-2]; //get node from parameter_list
        }
    }
#line 1394 "parser.tab.c"
    break;

  case 19: /* compound_declaration: CURLYOP_BRACKET local_declarations CURLYCL_BRACKET  */
#line 160 "parser.y"
    {//getting rid of yyempty in local declartions
        yyval = yyvsp[-1];
    }
#line 1402 "parser.tab.c"
    break;

  case 20: /* compound_declaration: CURLYOP_BRACKET statement_list CURLYCL_BRACKET  */
#line 164 "parser.y"
    {//no empty in statement list
        yyval = yyvsp[-1];
    }
#line 1410 "parser.tab.c"
    break;

  case 21: /* compound_declaration: CURLYOP_BRACKET CURLYCL_BRACKET  */
#line 168 "parser.y"
    {   /*No action on empty*/}
#line 1416 "parser.tab.c"
    break;

  case 22: /* local_declarations: local_declarations var_declaration  */
#line 173 "parser.y"
    {
        YYSTYPE temp = yyvsp[-1];
        if(temp == NULL){
            yyval = yyvsp[0];
        }else{
            while(temp->sibling != NULL){
                temp = temp->sibling;
            }   
            temp->sibling = yyvsp[0];
            yyval = yyvsp[-1];
        }
    }
#line 1433 "parser.tab.c"
    break;

  case 23: /* local_declarations: var_declaration  */
#line 186 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1441 "parser.tab.c"
    break;

  case 24: /* statement_list: statement_list statement  */
#line 193 "parser.y"
    {
        YYSTYPE temp = yyvsp[-1];
        if(temp == NULL){
            yyval = yyvsp[0];
        }else{
            while(temp->sibling != NULL){
                temp = temp->sibling;
            }   
            temp->sibling = yyvsp[0];
            yyval = yyvsp[-1];
        }
    }
#line 1458 "parser.tab.c"
    break;

  case 25: /* statement_list: statement  */
#line 206 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1466 "parser.tab.c"
    break;

  case 26: /* statement: expression_declaration  */
#line 213 "parser.y"
    { //all get itself
        yyval = yyvsp[0];
    }
#line 1474 "parser.tab.c"
    break;

  case 27: /* statement: compound_declaration  */
#line 217 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1482 "parser.tab.c"
    break;

  case 28: /* statement: selection_declaration  */
#line 221 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1490 "parser.tab.c"
    break;

  case 29: /* statement: iteration_declaration  */
#line 225 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1498 "parser.tab.c"
    break;

  case 30: /* statement: return_declaration  */
#line 229 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1506 "parser.tab.c"
    break;

  case 31: /* expression_declaration: expression SEMICOL_PUNCT  */
#line 236 "parser.y"
    {
        yyval = yyvsp[-1];
    }
#line 1514 "parser.tab.c"
    break;

  case 32: /* expression_declaration: SEMICOL_PUNCT  */
#line 240 "parser.y"
    {/*no semantic value to associate*/}
#line 1520 "parser.tab.c"
    break;

  case 33: /* selection_declaration: IF CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement  */
#line 245 "parser.y"
    {
        yyval = new_stmt_node(IF_SK);
        yyval->child[0] = yyvsp[-2]; // get the op expression
        yyval->child[1] = yyvsp[0]; // get the then part
    }
#line 1530 "parser.tab.c"
    break;

  case 34: /* selection_declaration: IF CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement ELSE statement  */
#line 251 "parser.y"
    {
        yyval = new_stmt_node(IF_SK);
        yyval->child[0] = yyvsp[-4]; // get the op expression
        yyval->child[1] = yyvsp[-2]; // get the then part
        yyval->child[2] = yyvsp[0]; // else part statement
    }
#line 1541 "parser.tab.c"
    break;

  case 35: /* iteration_declaration: WHILE CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement  */
#line 261 "parser.y"
    {
        yyval = new_stmt_node(WHILE_SK);
        yyval->child[0]= yyvsp[-2]; //op expression
        yyval->child[1]= yyvsp[0]; // do part statement
    }
#line 1551 "parser.tab.c"
    break;

  case 36: /* return_declaration: RETURN SEMICOL_PUNCT  */
#line 270 "parser.y"
    {
        yyval = new_stmt_node(RETURN_SK);
    }
#line 1559 "parser.tab.c"
    break;

  case 37: /* return_declaration: RETURN expression SEMICOL_PUNCT  */
#line 274 "parser.y"
    {
        yyval = new_stmt_node(RETURN_SK);
        yyval->child[0]= yyvsp[-1]; // expression returned
    }
#line 1568 "parser.tab.c"
    break;

  case 38: /* expression: var EQUAL expression  */
#line 282 "parser.y"
    {
        yyval = new_stmt_node(ASSIGN_SK);
        yyval->child[0] = yyvsp[-2]; // get var of this expression op
        yyval->child[1] = yyvsp[0]; // expression assigned
    }
#line 1578 "parser.tab.c"
    break;

  case 39: /* expression: simple_expression  */
#line 288 "parser.y"
    {
        yyval= yyvsp[0]; //get itself
    }
#line 1586 "parser.tab.c"
    break;

  case 40: /* var: identificator  */
#line 295 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1594 "parser.tab.c"
    break;

  case 41: /* var: identificator SQUAREOP_BRACKET expression SQUARECL_BRACKET  */
#line 299 "parser.y"
    {
        yyval = yyvsp[-3];
        yyval->child[0] = yyvsp[-1]; //Child is the expression in [] use for indexing
        yyval->has.exp.kind = VECT_ID_EK; //Expression of vector identifier
    }
#line 1604 "parser.tab.c"
    break;

  case 42: /* simple_expression: sum_expression relational sum_expression  */
#line 308 "parser.y"
    {
        yyval = yyvsp[-1]; // get the relational op
        yyval->child[0] = yyvsp[-2]; //sum_express
        yyval->child[1] = yyvsp[0]; //sum_express
    }
#line 1614 "parser.tab.c"
    break;

  case 43: /* simple_expression: sum_expression  */
#line 314 "parser.y"
    {
        yyval=yyvsp[0];
    }
#line 1622 "parser.tab.c"
    break;

  case 44: /* relational: EQ_RELOP  */
#line 321 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= EQ_RELOP;
    }
#line 1631 "parser.tab.c"
    break;

  case 45: /* relational: NOTEQ_RELOP  */
#line 326 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= NOTEQ_RELOP;
    }
#line 1640 "parser.tab.c"
    break;

  case 46: /* relational: LESSEQ_RELOP  */
#line 331 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= LESSEQ_RELOP;
    }
#line 1649 "parser.tab.c"
    break;

  case 47: /* relational: GREATEQ_RELOP  */
#line 336 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= GREATEQ_RELOP;
    }
#line 1658 "parser.tab.c"
    break;

  case 48: /* relational: GREAT_RELOP  */
#line 341 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= GREAT_RELOP;
    }
#line 1667 "parser.tab.c"
    break;

  case 49: /* relational: LESS_RELOP  */
#line 346 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= LESS_RELOP;
    }
#line 1676 "parser.tab.c"
    break;

  case 50: /* sum_expression: sum_expression sum term  */
#line 354 "parser.y"
    {
        yyval = yyvsp[-1]; //sum node
        yyval->child[0] = yyvsp[-2]; //the expression is left associative
        yyval->child[1] = yyvsp[0]; //term tree is stored
    }
#line 1686 "parser.tab.c"
    break;

  case 51: /* sum_expression: term  */
#line 360 "parser.y"
    {
        yyval = yyvsp[0]; //get the three from itself
    }
#line 1694 "parser.tab.c"
    break;

  case 52: /* sum: PLUS_ALOP  */
#line 367 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= PLUS_ALOP;
    }
#line 1703 "parser.tab.c"
    break;

  case 53: /* sum: MINUS_ALOP  */
#line 372 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= MINUS_ALOP;
    }
#line 1712 "parser.tab.c"
    break;

  case 54: /* term: term mult factor  */
#line 380 "parser.y"
    {
        yyval = yyvsp[-1]; //get the left associative term
        yyval->child[0] = yyvsp[-2]; // get the operator
        yyval->child[1] = yyvsp[0]; // get the factor
    }
#line 1722 "parser.tab.c"
    break;

  case 55: /* term: factor  */
#line 386 "parser.y"
    {
        yyval=yyvsp[0]; //get itself
    }
#line 1730 "parser.tab.c"
    break;

  case 56: /* mult: DIV_PRE_ALOP  */
#line 393 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= DIV_PRE_ALOP;
    }
#line 1739 "parser.tab.c"
    break;

  case 57: /* mult: MULT_PRE_ALOP  */
#line 398 "parser.y"
    {
        yyval= new_exp_node(OP_EK);
        yyval->attr.op= MULT_PRE_ALOP;
    }
#line 1748 "parser.tab.c"
    break;

  case 58: /* factor: CIRCLEOP_BRACKET expression CIRCLECL_BRACKET  */
#line 406 "parser.y"
    {
        yyval = yyvsp[-1]; //get the expression value
    }
#line 1756 "parser.tab.c"
    break;

  case 59: /* factor: var  */
#line 410 "parser.y"
    {
        yyval = yyvsp[0]; //get the variable ident or vec
    }
#line 1764 "parser.tab.c"
    break;

  case 60: /* factor: activation  */
#line 414 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1772 "parser.tab.c"
    break;

  case 61: /* factor: number  */
#line 418 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1780 "parser.tab.c"
    break;

  case 62: /* activation: identificator CIRCLEOP_BRACKET argument_list CIRCLECL_BRACKET  */
#line 425 "parser.y"
    {
        //call a function
        yyval = yyvsp[-3];//addt
        yyval->child[0] = yyvsp[-1]; //args
        yyval->has.stmt = CALL_SK; 
        yyval->type = STMT_T;
    }
#line 1792 "parser.tab.c"
    break;

  case 63: /* activation: identificator CIRCLEOP_BRACKET CIRCLECL_BRACKET  */
#line 433 "parser.y"
    {//no empty in arguments
        yyval = yyvsp[-2];
        yyval->has.stmt = CALL_SK;
        yyval->type = STMT_T;
    }
#line 1802 "parser.tab.c"
    break;

  case 64: /* argument_list: argument_list COMMA_PUNCT expression  */
#line 442 "parser.y"
    {
        YYSTYPE temp = yyvsp[-2];
        if(temp == NULL){
            yyval = yyvsp[0];
        }else{
            while(temp->sibling != NULL){
                temp = temp->sibling;
            }   
            temp->sibling = yyvsp[0];
            yyval = yyvsp[-2];
        }
    }
#line 1819 "parser.tab.c"
    break;

  case 65: /* argument_list: expression  */
#line 455 "parser.y"
    {
        yyval = yyvsp[0];
    }
#line 1827 "parser.tab.c"
    break;

  case 66: /* number: NUM  */
#line 462 "parser.y"
    {
        yyval = new_exp_node(NUM_EK);
        yyval->has.exp.type = CONST_T;
        yyval->attr.val = atoi((glob_context.p_token_rec)->lexeme);
    }
#line 1837 "parser.tab.c"
    break;

  case 67: /* identificator: ID  */
#line 470 "parser.y"
    {
        yyval = new_exp_node(ID_EK);
        yyval->attr.content = cp_str((glob_context.p_token_rec)->lexeme);
    }
#line 1846 "parser.tab.c"
    break;


#line 1850 "parser.tab.c"

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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 474 "parser.y"



void yyerror(char* err) {
    puts(RED"__________________________________________[ SYNTATIC ERROR ]________________________________________");
    int in_line_placement = (glob_context.p_buffer)->line_char_pos;
    fpos_t line_placement = (glob_context.p_buffer)->line_pos;
    printf(RED"\t [!][!]message: %s"RESET, err);
    printf(CYN"\t[!] THE ERROR OCCURRED AT THE %zu-th LINE IN THE %zu-th CHAR [!]\n"RESET, (glob_context.p_buffer)->line_number, (glob_context.p_buffer)->line_char_pos);
    printf(YELLOW"\t[!] TOKEN LEXEME: "RED"%s "YELLOW"TOKEN TYPE: "RED"%s "YELLOW"[!]\n", (glob_context.p_token_rec)->lexeme, yytokentype_to_string((glob_context.p_token_rec)->type));
    puts(RED"____________________________________________________________________________________________________"RESET);
}

syntax_t_node* parse(void){
    yyparse();
    return syntax_tree_root;
}
