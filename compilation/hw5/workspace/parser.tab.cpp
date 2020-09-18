/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.ypp" /* yacc.c:339  */

	#include "attributes.hpp"
	#include "SymbolTable.hpp"
	#include <iostream>
	#include <vector>
	#include "output.hpp"
	#include "registers_pool.hpp"
	#include "bp.hpp"
	#include <sstream>

	using namespace std;
	using namespace output;

    SymbolTable symbolTable;
    vector<int> offsets;
    int inWhiles = 0;
    int inIfs =0;
    bool inFunction = false;
    string retLastFunction;
    int preCondCounter = 0;


    RegistersPool registerPool;

    extern int yylex();
    extern int yylineno;
	// #define YYDEBUG 1 
	void yyerror(const char*);
	void emitPrintIandPrint();
	void emitPreCondError(string function_name);

	void checkIfExpIsBool(Node* n, int yylineno){
		if (n->types.size() == 0){
			errorSyn(yylineno);
			exit(1);
		}

		if (n->types[0] != "BOOL"){
			errorMismatch(yylineno);
			exit(1);
		}
	};


	vector<string> argsTypesToStr(vector<string> args){
		vector<string> args_s;

		for (std::vector<string>::const_iterator it = args.begin(); 
			        	it != args.end(); ++it){
			args_s.push_back(*it);
		}
		return args_s;
	}

#line 121 "parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EF = 258,
    VOID = 259,
    INT = 260,
    BYTE = 261,
    B = 262,
    BOOL = 263,
    TRUE = 264,
    FALSE = 265,
    RETURN = 266,
    ELSE = 268,
    IF = 269,
    WHILE = 270,
    BREAK = 271,
    CONTINUE = 272,
    PRECOND = 273,
    SC = 274,
    COMMA = 275,
    LBRACE = 276,
    RBRACE = 277,
    ID = 278,
    NUM = 279,
    STRING = 280,
    OR = 281,
    AND = 282,
    ASSIGN = 283,
    RELOP_EQ = 284,
    RELOP = 285,
    PLUS = 286,
    MINUS = 287,
    MULT = 288,
    DIV = 289,
    NOT = 290,
    LPAREN = 291,
    RPAREN = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 209 "parser.tab.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,   138,   147,   148,   151,   187,   150,   244,
     245,   247,   248,   250,   255,   265,   277,   286,   292,   305,
     311,   344,   364,   385,   445,   498,   509,   526,   580,   592,
     603,   611,   647,   649,   649,   671,   677,   677,   707,   714,
     737,   742,   750,   755,   827,   879,   926,   925,   995,   996,
     997,  1000,  1001,  1013,  1026,  1036,  1047,  1078,  1085,  1092,
    1104,  1108,  1115,  1124,  1130,  1137,  1147,  1160,  1181,  1187
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EF", "VOID", "INT", "BYTE", "B", "BOOL",
  "TRUE", "FALSE", "RETURN", "\"then\"", "ELSE", "IF", "WHILE", "BREAK",
  "CONTINUE", "PRECOND", "SC", "COMMA", "LBRACE", "RBRACE", "ID", "NUM",
  "STRING", "OR", "AND", "ASSIGN", "RELOP_EQ", "RELOP", "PLUS", "MINUS",
  "MULT", "DIV", "NOT", "LPAREN", "RPAREN", "$accept", "program", "M1",
  "funcs", "funcdecl", "$@1", "$@2", "retype", "formals", "formalslist",
  "formaldecl", "preconditions", "precondition", "statements", "statement",
  "IF_SCOPE", "$@3", "M_IF_SCOPE", "WHILE_SCOPE", "$@4", "M_WHILE_SCOPE",
  "ELSE_SCOPE", "M_ELSE_SCOPE", "N", "M_PROLOGUE", "call", "explist",
  "$@5", "type", "exp", "N_BP", "M_BP", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF -51

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-51)))

#define YYTABLE_NINF -47

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-47)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -51,     3,     2,   -51,   -51,   -51,   -51,   -51,    -1,     2,
     -10,   -51,   -51,   -51,    -8,    25,   -51,   -51,    12,    20,
      13,    25,   -51,   -51,   -51,   -51,    34,    18,    36,   -51,
      72,   -51,   -51,   -51,    24,    54,   -51,    72,    72,   -51,
     185,   144,    26,   -51,   -51,   194,   -51,   -51,    72,    72,
      72,    72,    72,    72,   -51,    80,    46,    48,    40,   106,
     -51,    56,    58,   -51,    63,    52,    64,    62,    11,   -51,
      72,    72,     8,   167,   -16,   -16,   -51,   -51,   -51,   143,
     -51,   -51,    72,   -51,   -51,   -51,   -51,    57,    65,   144,
     -51,   -14,   -51,    51,   176,   211,   217,   -51,   152,   -51,
     -51,    72,   -51,   125,   -51,   -51,    72,   -51,    82,   -51,
     -51,   203,    72,   -51,   161,    72,   144,    55,   203,   -51,
     -51,   -51,   -51,    69,   144,   -51,   -51,   144,   -51,   -51,
     -51
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     5,     1,    10,    48,    49,    50,     0,     5,
       0,     9,     2,     4,     0,    12,     6,    11,    13,     0,
       0,     0,    15,    17,    14,    69,     7,     0,     0,    16,
       0,    69,    61,    62,    56,    58,    60,     0,     0,    57,
       0,    35,     0,    59,    63,     0,    69,    69,     0,     0,
       0,     0,     0,     0,    18,     0,     0,     0,    42,    35,
      19,    30,     0,    32,     0,     0,     0,     0,     0,    51,
       0,     0,    66,    67,    52,    53,    54,    55,    26,     0,
      28,    29,     0,     8,    20,    68,    69,     0,     0,    35,
      69,     0,    44,     0,    45,    65,    64,    27,     0,    40,
      31,     0,    69,    35,    25,    22,     0,    43,     0,    24,
      69,    33,     0,    21,     0,     0,    35,     0,    36,    23,
      47,    39,    69,     0,    35,    69,    34,    35,    68,    69,
      37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,   -51,    91,   -51,   -51,   -51,   -51,   -51,    88,
     -51,   -51,   -51,    21,   -50,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -40,    -2,   -51,    49,   -26,
      -9,   -31
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     8,     9,    20,    28,    10,    16,    17,
      18,    25,    29,    59,    60,    61,   117,    62,    63,   123,
      64,    86,   110,    65,    42,    39,    93,   108,    67,    94,
      99,    26
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    66,    12,     3,    40,   105,     4,     5,     6,    84,
       7,    44,    45,    14,   106,    70,    71,    52,    53,    66,
      32,    33,    72,    73,    74,    75,    76,    77,    15,    79,
       5,     6,    21,     7,    34,    35,    36,   -47,    49,    50,
      51,    52,    53,    22,    95,    96,    37,    38,    92,    66,
      23,    11,    27,    84,    30,   100,    98,    31,    11,   104,
     -42,    43,    68,    66,    19,    80,   121,    81,    82,    85,
      19,   112,    87,    89,   126,   111,    66,   128,    88,   116,
     114,    32,    33,    90,    66,    91,   118,    66,   107,    32,
      33,   124,   122,   101,   127,    34,    35,    36,   130,    78,
      13,   102,   115,    34,    35,    36,   125,    37,    38,    24,
     103,     5,     6,   120,     7,    37,    38,    55,     0,   129,
       0,   -38,    56,    57,     0,     0,     0,   -41,    83,    58,
       5,     6,     0,     7,     0,     0,    55,     0,     0,     0,
     -38,    56,    57,     0,     0,     0,   -41,   113,    58,     5,
       6,     0,     7,     0,     0,    55,     0,     0,     0,   -38,
      56,    57,    97,     0,     0,   -41,     0,    58,     0,    46,
      47,   109,    48,    49,    50,    51,    52,    53,    46,    47,
     119,    48,    49,    50,    51,    52,    53,    46,    47,     0,
      48,    49,    50,    51,    52,    53,   -46,   -47,    50,    51,
      52,    53,    46,    47,     0,    48,    49,    50,    51,    52,
      53,    46,    47,     0,    48,    49,    50,    51,    52,    53,
      46,    47,    54,    48,    49,    50,    51,    52,    53,    46,
      47,    69,    48,    49,    50,    51,    52,    53,    47,     0,
      48,    49,    50,    51,    52,    53,    48,    49,    50,    51,
      52,    53
};

static const yytype_int16 yycheck[] =
{
      31,    41,     3,     0,    30,    19,     4,     5,     6,    59,
       8,    37,    38,    23,    28,    46,    47,    33,    34,    59,
       9,    10,    48,    49,    50,    51,    52,    53,    36,    55,
       5,     6,    20,     8,    23,    24,    25,    29,    30,    31,
      32,    33,    34,    23,    70,    71,    35,    36,    37,    89,
      37,     2,    18,   103,    36,    86,    82,    21,     9,    90,
      36,     7,    36,   103,    15,    19,   116,    19,    28,    13,
      21,   102,    14,    21,   124,   101,   116,   127,    15,   110,
     106,     9,    10,    19,   124,    23,   112,   127,    37,     9,
      10,   122,    37,    36,   125,    23,    24,    25,   129,    19,
       9,    36,    20,    23,    24,    25,    37,    35,    36,    21,
      89,     5,     6,   115,     8,    35,    36,    11,    -1,   128,
      -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,    23,
       5,     6,    -1,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    16,    17,    -1,    -1,    -1,    21,    22,    23,     5,
       6,    -1,     8,    -1,    -1,    11,    -1,    -1,    -1,    15,
      16,    17,    19,    -1,    -1,    21,    -1,    23,    -1,    26,
      27,    19,    29,    30,    31,    32,    33,    34,    26,    27,
      19,    29,    30,    31,    32,    33,    34,    26,    27,    -1,
      29,    30,    31,    32,    33,    34,    20,    30,    31,    32,
      33,    34,    26,    27,    -1,    29,    30,    31,    32,    33,
      34,    26,    27,    -1,    29,    30,    31,    32,    33,    34,
      26,    27,    37,    29,    30,    31,    32,    33,    34,    26,
      27,    37,    29,    30,    31,    32,    33,    34,    27,    -1,
      29,    30,    31,    32,    33,    34,    29,    30,    31,    32,
      33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    39,    40,     0,     4,     5,     6,     8,    41,    42,
      45,    66,     3,    41,    23,    36,    46,    47,    48,    66,
      43,    20,    23,    37,    47,    49,    69,    18,    44,    50,
      36,    21,     9,    10,    23,    24,    25,    35,    36,    63,
      67,    69,    62,     7,    67,    67,    26,    27,    29,    30,
      31,    32,    33,    34,    37,    11,    16,    17,    23,    51,
      52,    53,    55,    56,    58,    61,    63,    66,    36,    37,
      69,    69,    67,    67,    67,    67,    67,    67,    19,    67,
      19,    19,    28,    22,    52,    13,    59,    14,    15,    21,
      19,    23,    37,    64,    67,    67,    67,    19,    67,    68,
      69,    36,    36,    51,    69,    19,    28,    37,    65,    19,
      60,    67,    69,    22,    67,    20,    69,    54,    67,    19,
      64,    52,    37,    57,    69,    37,    52,    69,    52,    68,
      69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    41,    41,    43,    44,    42,    45,
      45,    46,    46,    47,    47,    48,    49,    49,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    54,    53,    55,    57,    56,    58,    59,
      60,    61,    62,    63,    63,    64,    65,    64,    66,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    68,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     2,     0,     0,     0,    13,     1,
       1,     1,     0,     1,     3,     2,     3,     0,     4,     1,
       2,     4,     3,     5,     4,     3,     2,     3,     2,     2,
       1,     3,     1,     0,     8,     0,     0,    11,     0,     5,
       0,     0,     0,     5,     4,     1,     0,     4,     1,     1,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     2,
       1,     1,     1,     2,     4,     4,     3,     3,     0,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
        case 2:
#line 92 "parser.ypp" /* yacc.c:1646  */
    {	
			// check if void main() is in tables if not error
			if (!symbolTable.checkIfFunctionExists("main")){
				errorMainMissing();
				exit(1);
			}
			if (symbolTable.getFunctionRetType("main") != "VOID"){
				errorMainMissing();
				exit(1);	
			}

			vector<string> args = symbolTable.getFunctionArgs("main");
			if (args.size() != 0){
				errorMainMissing();
				exit(1);		
			}

			// endScope();

			Table table = symbolTable.top();
			for (int i=0; i< table.entries.size(); i++){

				if (table.entries[i]->entry_type == "VARIABLE"){
					// printID(table.entries[i]->name, 
					// 		table.entries[i]->offset, 
					// 		table.entries[i]->type);
				}
				else if (table.entries[i]->entry_type == "FUNCTION"){
					vector<string> args = argsTypesToStr(symbolTable.getFunctionArgs(table.entries[i]->name));
					string type = makeFunctionType(table.entries[i]->ret_type, 
													args);
					// printID(table.entries[i]->name, 
					// 		0, 
					// 		type);
				}
			}
			symbolTable.pop();
			offsets.pop_back();

			CodeBuffer::instance().printDataBuffer();
            CodeBuffer::instance().printCodeBuffer(); 

			return 0;
		}
#line 1445 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 138 "parser.ypp" /* yacc.c:1646  */
    {
		symbolTable.maketable();
		offsets.push_back(0);
		symbolTable.insertFunctionPrint();
		symbolTable.insertFunctionPrintI();
		emitPrintIandPrint();
		
	}
#line 1458 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 151 "parser.ypp" /* yacc.c:1646  */
    {
			// initiate function
			// add function to symbol table in current scope
			// create new scope for function
			// add arguments to new scope

			preCondCounter = 0;
			inFunction = true;
			retLastFunction = (yyvsp[-3])->value;

			if (symbolTable.checkIfIdExists((yyvsp[-2])->value)){
    			errorDef(yylineno, (yyvsp[-2])->value);
    			exit(1);
			}


			symbolTable.insertFunction((yyvsp[-2])->value, 
										(yyvsp[-3])->value, 
										offsets.back(),
										(yyvsp[0])->types);
			offsets.back();

			symbolTable.maketable();
			offsets.push_back(offsets.back());


			std::vector<string> args = symbolTable.getFunctionArgs((yyvsp[-2])->value);
			for (int i=0; i<args.size(); i++){
				symbolTable.insertVariable((yyvsp[0])->names[i], (yyvsp[0])->types[i], (i+1)*-1);
			}

			CodeBuffer::instance().emit((yyvsp[-2])->names[0] + ":");
			CodeBuffer::instance().emit("addu $fp, $sp, 0");
			CodeBuffer::instance().emitData((yyvsp[-2])->names[0]+"_data: \t .asciiz \t \""+(yyvsp[-2])->names[0]+"\"");

		}
#line 1499 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 187 "parser.ypp" /* yacc.c:1646  */
    {
		  	// RPAREN = $6
		  	if ((*(yyvsp[-1])->truelist).size() > 0){ // not null
		  		emitPreCondError((yyvsp[-6])->names[0]+"_data");
		  	}
		  }
#line 1510 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 195 "parser.ypp" /* yacc.c:1646  */
    {	
			// RPAERN = $6
			// LBRACE $ 10
			// check if last statment in statements is return type which similar to retype
			

			// endScope();
			// printPreconditions($2->value, preCondCounter);
			Table table = symbolTable.top();
			for (int i=0; i< table.entries.size(); i++){

				// printID(table.entries[i]->name, 
				// 		table.entries[i]->offset, 
				// 		table.entries[i]->type);
			}

			inFunction = false;
			preCondCounter = 0;

			symbolTable.pop();
			offsets.pop_back();


			// cout << $1->value << endl;
			if ((*(yyvsp[-6])->truelist).size() > 0){
				CodeBuffer::instance().bpatch((*(yyvsp[-6])->truelist), (yyvsp[-2])->quad);
				// cout << "noam " << endl;
			}
			if ((*(yyvsp[-6])->truelist).size() > 0){
				// cout << "noam " << endl;
				CodeBuffer::instance().bpatch((*(yyvsp[-6])->falselist), (yyvsp[-5])->quad);
				// cout << "noam " << endl;
			}
			// CodeBuffer::instance().bpatch((*$6->truelist), $8->quad);

			// CodeBuffer::instance().emit("addu $sp, $fp, 0");
			// if ($1->value == "VOID"){
			CodeBuffer::instance().emit("addu $sp, $fp, 0");
			CodeBuffer::instance().emit("li $v0, 0"); // what is v0?
			CodeBuffer::instance().emit("jr $ra");
			// }

			// backpath all precond falselist to M_BP FAIL
			// backpath nextlist of statments to last M_BP
			// backpath nextlist of last precond to statments
			// cout << "finish declaring function " << endl;

		}
#line 1563 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 244 "parser.ypp" /* yacc.c:1646  */
    {(yyval)->types[0] = (yyvsp[0])->value;}
#line 1569 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 245 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]);}
#line 1575 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 247 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1581 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 248 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new Node();}
#line 1587 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 250 "parser.ypp" /* yacc.c:1646  */
    {
				(yyval) = new Node();
				(yyval)->names.push_back((yyvsp[0])->names[0]);
				(yyval)->types.push_back((yyvsp[0])->types[0]);
			}
#line 1597 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 255 "parser.ypp" /* yacc.c:1646  */
    {
				(yyval) = new Node();
				(yyval)->names.push_back((yyvsp[-2])->names[0]);
				(yyval)->types.push_back((yyvsp[-2])->types[0]);
				for (int i=0; i < (yyvsp[0])->names.size(); ++i){
					(yyval)->names.push_back((yyvsp[0])->names[i]);
					(yyval)->types.push_back((yyvsp[0])->types[i]);
				}
			}
#line 1611 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 266 "parser.ypp" /* yacc.c:1646  */
    {
				(yyval) = new Node();
				(yyval)->names.push_back((yyvsp[0])->names[0]);
				(yyval)->types.push_back((yyvsp[-1])->types[0]);

				if (symbolTable.checkIfIdExists((yyvsp[0])->names[0])){
	    			errorDef(yylineno, (yyvsp[0])->names[0]);
	    			exit(1);
				}
			}
#line 1626 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 278 "parser.ypp" /* yacc.c:1646  */
    {
					(yyval) = new Node();
					CodeBuffer::instance().bpatch((*(yyvsp[-2])->truelist), (yyvsp[-1])->quad);
					(yyval)->falselist = new vector<int>(CodeBuffer::instance().merge(*(yyvsp[-2])->falselist,*(yyvsp[0])->falselist));
					delete (yyvsp[-2])->falselist;
					delete (yyvsp[-1])->falselist;
					(yyval)->truelist = (yyvsp[0])->truelist;
				}
#line 1639 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 286 "parser.ypp" /* yacc.c:1646  */
    {
					(yyval) = new Node();
					(yyval)->falselist = new vector<int>();;
					(yyval)->truelist = new vector<int>();;
				}
#line 1649 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 292 "parser.ypp" /* yacc.c:1646  */
    {
				checkIfExpIsBool((yyvsp[-1]), yylineno);
				preCondCounter += 1;

				// code - checking each exp somehow - already been coded in exp
				// truelist? to other precond
				// falselist? N_BP and will be backpathed
				(yyval) = new Node();
				(yyval)->truelist = (yyvsp[-1])->truelist;
				(yyval)->falselist = (yyvsp[-1])->falselist;
				
			}
#line 1666 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 306 "parser.ypp" /* yacc.c:1646  */
    {
				(yyval) = new Node();
				(yyval)->continuelist = (yyvsp[0])->continuelist;
				(yyval)->breaklist = (yyvsp[0])->breaklist;
			}
#line 1676 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 312 "parser.ypp" /* yacc.c:1646  */
    {
				(yyval) = new Node();
				if((yyvsp[-1])->breaklist != NULL && (yyvsp[0])->breaklist != NULL)
				{
					(yyval)->breaklist = new vector<int>(CodeBuffer::instance().merge(*(yyvsp[-1])->breaklist,*(yyvsp[0])->breaklist));
					delete (yyvsp[-1])->breaklist;
					delete (yyvsp[0])->breaklist;
				} 
				else if((yyvsp[-1])->breaklist == NULL)
				{
					(yyval)->breaklist = (yyvsp[0])->breaklist;
				} 
				else 
				{
					(yyval)->breaklist = (yyvsp[-1])->breaklist;	
				}
				
				if((yyvsp[-1])->continuelist != NULL && (yyvsp[0])->continuelist != NULL){
					(yyval)->continuelist = new vector<int>(CodeBuffer::instance().merge(*(yyvsp[-1])->continuelist,*(yyvsp[0])->continuelist));
					delete (yyvsp[-1])->continuelist;
					delete (yyvsp[0])->continuelist;
				} 
				else if((yyvsp[-1])->continuelist == NULL)
				{
					(yyval)->continuelist = (yyvsp[0])->continuelist;
				} 
				else 
				{
					(yyval)->continuelist = (yyvsp[-1])->continuelist;	
				}
			}
#line 1712 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 344 "parser.ypp" /* yacc.c:1646  */
    {
					// endScope();

					Table table = symbolTable.top();
					for (int i=0; i< table.entries.size(); i++){
						// printID(table.entries[i]->name, 
						// 		table.entries[i]->offset, 
						// 		table.entries[i]->type);
					}

					symbolTable.pop();
					
					int prev_offset = offsets.back();
					offsets.pop_back();

					(yyval) = new Node();
					(yyval)->continuelist = (yyvsp[-1])->continuelist;
					(yyval)->breaklist = (yyvsp[-1])->breaklist;
					CodeBuffer::instance().emit("addu $sp, $sp, "+intToString(4 * (prev_offset - offsets.back())));
				}
#line 1737 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 364 "parser.ypp" /* yacc.c:1646  */
    {
					// check if ID is not already exists
					if (symbolTable.checkIfIdExists((yyvsp[-1])->names[0])){
						errorDef(yylineno, (yyvsp[-1])->names[0]);
						exit(1);
					}
					
					// initiate ID in symbol table with type
					symbolTable.insertVariable((yyvsp[-1])->names[0],(yyvsp[-2])->value,offsets.back());
					offsets.back() += 1;

					(yyval) = new Node();
					(yyval)->types.push_back((yyvsp[-2])->value);
					(yyval)->names.push_back((yyvsp[-1])->value);

					CodeBuffer::instance().emit("subu $sp, $sp, 4");
					CodeBuffer::instance().emit("sw $0, 0($sp)"); // what is it?
					(yyval)->continuelist = NULL;
					(yyval)->breaklist = NULL;

				}
#line 1763 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 385 "parser.ypp" /* yacc.c:1646  */
    {
					// check if ID is not already exists
					if (symbolTable.checkIfIdExists((yyvsp[-3])->names[0])){
						errorDef(yylineno, (yyvsp[-3])->names[0]);
						exit(1);
					}
					
					if ((yyvsp[-1])->types.size() == 0){
						errorMismatch(yylineno);
						exit(1);
					}

					(yyval) = new Node();
					// exp should have the same type unless it is byte to int
					if ( (yyvsp[-1])->types[0] != (yyvsp[-4])->value){
						if ((yyvsp[-1])->types[0] == "BYTE" && (yyvsp[-4])->value == "INT"){
							symbolTable.insertVariable((yyvsp[-3])->names[0],(yyvsp[-4])->value,offsets.back());
							offsets.back() += 1;
						}
						else{
							errorMismatch(yylineno);
							exit(1);
						}
					}
					else{
						symbolTable.insertVariable((yyvsp[-3])->names[0],(yyvsp[-4])->value,offsets.back());
						offsets.back() += 1;
					}

					if ((yyvsp[-1])->types[0] != "BOOL") 
					{
						CodeBuffer::instance().emit("subu $sp, $sp, 4");
						CodeBuffer::instance().emit("sw $"+intToString((yyvsp[-1])->reg)+", 0($sp)");
						registerPool.deallocateRegister((yyvsp[-1])->reg);
					}
					else if( (yyvsp[-1])->types[0] == "BOOL")
					{
						(yyvsp[-1])->reg = registerPool.allocateRegister();
						// int offset = (-4) * symbolTable.getIdOffset($2->names[0]);

						string false_label = CodeBuffer::instance().genLabel();
						CodeBuffer::instance().emit("li $"+intToString((yyvsp[-1])->reg)+", 0");
						std::vector<int> next_backpatch = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));

						string true_label = CodeBuffer::instance().genLabel();
						CodeBuffer::instance().emit("li $"+intToString((yyvsp[-1])->reg)+", 1"); 

						string next_label = CodeBuffer::instance().genLabel();
						CodeBuffer::instance().bpatch((*(yyvsp[-1])->truelist), true_label);
						CodeBuffer::instance().bpatch((*(yyvsp[-1])->falselist), false_label);
						CodeBuffer::instance().bpatch(next_backpatch, next_label);
						CodeBuffer::instance().emit("subu $sp, $sp, 4");
						CodeBuffer::instance().emit("sw $"+intToString((yyvsp[-1])->reg)+", 0($sp)");
						registerPool.deallocateRegister((yyvsp[-1])->reg);
						
						(yyval)->continuelist = NULL;
						(yyval)->breaklist = NULL;
					}

				}
#line 1828 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 445 "parser.ypp" /* yacc.c:1646  */
    {
					// check if ID is exists
					if (!symbolTable.checkIfVariableExists((yyvsp[-3])->names[0])){
						errorUndef(yylineno, (yyvsp[-3])->names[0]);
						exit(1);
					}

					(yyvsp[-3])->types.push_back(symbolTable.getIdType((yyvsp[-3])->names[0]));
					// check id ID.type is equal to exp.type
					if ((yyvsp[-1])->types.size() == 0){
						errorMismatch(yylineno);
						exit(1);
					}
					if ((yyvsp[-3])->types[0] != (yyvsp[-1])->types[0] && 
						!((yyvsp[-3])->types[0] == "INT" && (yyvsp[-1])->types[0] =="BYTE")){
							errorMismatch(yylineno);
							exit(1);	
						}
					(yyval) = new Node();
					(yyval)->types.push_back((yyvsp[-3])->types[0]);

					(yyval)->continuelist = NULL;
                	(yyval)->breaklist = NULL;
					if((yyvsp[-3])->types[0] == "INT" || (yyvsp[-1])->types[0] =="BYTE" || (yyvsp[-1])->types[0] == "STRING")
					{
						int offset = (-4) * symbolTable.getIdOffset((yyvsp[-3])->names[0]) - 4;
						
						CodeBuffer::instance().emit("sw $"+intToString((yyvsp[-1])->reg)+", "+intToString(offset)+"($fp)");
						registerPool.deallocateRegister((yyvsp[-1])->reg);
					}
					else if( (yyvsp[-3])->types[0] == "BOOL")
					{
						(yyvsp[-1])->reg = registerPool.allocateRegister();
						int offset = (-4) * symbolTable.getIdOffset((yyvsp[-3])->names[0]) - 4;
						


						string false_label = CodeBuffer::instance().genLabel();
						CodeBuffer::instance().emit("li $"+intToString((yyvsp[-1])->reg)+", 0");
						
						std::vector<int> next_backpatch = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
						
						string true_label = CodeBuffer::instance().genLabel();
						CodeBuffer::instance().emit("li $"+intToString((yyvsp[-1])->reg)+", 1"); 

						string next_label = CodeBuffer::instance().genLabel();
						CodeBuffer::instance().bpatch((*(yyvsp[-1])->truelist), true_label);
						CodeBuffer::instance().bpatch((*(yyvsp[-1])->falselist), false_label);
						CodeBuffer::instance().bpatch(next_backpatch, next_label);
						CodeBuffer::instance().emit("sw $"+intToString((yyvsp[-1])->reg)+", "+intToString(offset)+"($fp)");
						registerPool.deallocateRegister((yyvsp[-1])->reg);
					}
				}
#line 1886 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 498 "parser.ypp" /* yacc.c:1646  */
    {
					// something to do here?
					registerPool.deallocateRegister((yyvsp[-2])->reg);
					(yyval) = new Node();
					(yyval)->continuelist = NULL;
					(yyval)->breaklist = NULL;
					if((yyvsp[-2])->truelist != NULL){
						CodeBuffer::instance().bpatch((*(yyvsp[-2])->truelist), (yyvsp[0])->quad);
						CodeBuffer::instance().bpatch((*(yyvsp[-2])->falselist), (yyvsp[0])->quad);
					}
				}
#line 1902 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 509 "parser.ypp" /* yacc.c:1646  */
    {
					// only for functions with VOID or else Mismatch
					if (inFunction){
						// checkif last declared function is of rettype VOID
						if (retLastFunction != "VOID"){
							errorMismatch(yylineno);
							exit(1);
						}
						(yyval) = new Node();
						(yyval)->continuelist = NULL;
						(yyval)->breaklist = NULL;
						CodeBuffer::instance().emit("addu $sp, $fp, 0");
						CodeBuffer::instance().emit("li $v0, 0");
						CodeBuffer::instance().emit("jr $ra");
					}

				}
#line 1924 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 526 "parser.ypp" /* yacc.c:1646  */
    {
					// only for functions not in void or else Mismatch
					if (inFunction){
						// checkif last declared function is of rettype VOID

						if ((retLastFunction == "VOID")){
							errorMismatch(yylineno);
							exit(1);
						}
						else if ((retLastFunction == "INT") && ((yyvsp[-1])->types[0] != "INT")&&
							((yyvsp[-1])->types[0] != "BYTE") ){
							errorMismatch(yylineno);
							exit(1);
						}
						if ((retLastFunction == "BOOL") && ((yyvsp[-1])->types[0] != "BOOL") ){
							errorMismatch(yylineno);
							exit(1);
						}
						if ((retLastFunction == "BYTE") && ((yyvsp[-1])->types[0] != "BYTE")) {
							errorMismatch(yylineno);
							exit(1);
						}
						if ((retLastFunction == "STRING") && ((yyvsp[-1])->types[0] != "STRING") ){
							errorMismatch(yylineno);
							exit(1);
						}

						(yyval) = new Node();

						(yyval)->continuelist = NULL;
						(yyval)->breaklist = NULL;

						if((yyvsp[-1])->types[0] == "BOOL")
						{
							(yyvsp[-1])->reg = registerPool.allocateRegister();
							string f_label = CodeBuffer::instance().genLabel();
							CodeBuffer::instance().emit("li $"+intToString((yyvsp[-1])->reg)+", 0");

							std::vector<int> next_backpatch = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
							
							string t_label = CodeBuffer::instance().genLabel();
							CodeBuffer::instance().emit("li $"+intToString((yyvsp[-1])->reg)+", 1"); 

							string next_label = CodeBuffer::instance().genLabel();
							CodeBuffer::instance().bpatch((*(yyvsp[-1])->truelist), t_label);
							CodeBuffer::instance().bpatch((*(yyvsp[-1])->falselist), f_label);
							CodeBuffer::instance().bpatch(next_backpatch, next_label);
						}
						CodeBuffer::instance().emit("addu $sp, $fp, 0");
						CodeBuffer::instance().emit("move $v0, $"+intToString((yyvsp[-1])->reg));
						CodeBuffer::instance().emit("jr $ra");
						registerPool.deallocateRegister((yyvsp[-1])->reg);
					}
				}
#line 1983 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 580 "parser.ypp" /* yacc.c:1646  */
    {
					// check if inside a while or forloop
					// else UnexpectedBreak;

					if (inWhiles == 0){
						errorUnexpectedBreak(yylineno);
						exit(1);
					}
					(yyval) = new Node();
					(yyval)->breaklist = new vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
					(yyval)->continuelist = NULL;
				}
#line 2000 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 592 "parser.ypp" /* yacc.c:1646  */
    {
					// check if inside a while or forloop
					// else UnexpectedContinue;
					if (inWhiles == 0){
						errorUnexpectedContinue(yylineno);
						exit(1);
					}
					(yyval) = new Node();
					(yyval)->continuelist = new vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
					(yyval)->breaklist = NULL;
				}
#line 2016 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 603 "parser.ypp" /* yacc.c:1646  */
    {
					CodeBuffer::instance().bpatch(*((yyvsp[0])->truelist), (yyvsp[0])->quad);
					CodeBuffer::instance().bpatch(*((yyvsp[0])->falselist), CodeBuffer::instance().genLabel());

					(yyval) = new Node();
					(yyval)->breaklist = (yyvsp[0])->breaklist;
					(yyval)->continuelist = (yyvsp[0])->continuelist;
				}
#line 2029 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 611 "parser.ypp" /* yacc.c:1646  */
    {
					
					(yyval) = new Node();
					if((yyvsp[-2])->breaklist != NULL && (yyvsp[-1])->breaklist != NULL)
					{
						(yyval)->breaklist = new vector<int>(CodeBuffer::instance().merge(*(yyvsp[-2])->breaklist,*(yyvsp[-1])->breaklist));
						delete (yyvsp[-2])->breaklist;
						delete (yyvsp[-1])->breaklist;
					} 
					else if((yyvsp[-2])->breaklist == NULL)
					{
						(yyval)->breaklist = (yyvsp[-1])->breaklist;
					} 
					else 
					{
						(yyval)->breaklist = (yyvsp[-2])->breaklist;	
					}
					if((yyvsp[-2])->continuelist != NULL && (yyvsp[-1])->continuelist != NULL)
					{
						(yyval)->continuelist = new vector<int>(CodeBuffer::instance().merge(*(yyvsp[-2])->continuelist,*(yyvsp[-1])->continuelist));
						delete (yyvsp[-2])->continuelist;
						delete (yyvsp[-1])->continuelist;
					} 
					else if((yyvsp[-2])->continuelist == NULL)
					{
						(yyval)->continuelist = (yyvsp[-1])->continuelist;
					} 
					else 
					{
						(yyval)->continuelist = (yyvsp[-2])->continuelist;	
					}
					CodeBuffer::instance().bpatch(*((yyvsp[-2])->truelist), (yyvsp[-2])->quad);
					CodeBuffer::instance().bpatch(*((yyvsp[-2])->falselist), (yyvsp[-1])->quad);
					CodeBuffer::instance().bpatch(*((yyvsp[-1])->nextlist), (yyvsp[0])->quad);

				}
#line 2070 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 649 "parser.ypp" /* yacc.c:1646  */
    {checkIfExpIsBool((yyvsp[0]), (yyvsp[0])->line_num);}
#line 2076 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 650 "parser.ypp" /* yacc.c:1646  */
    {
			// endScope();
			Table table = symbolTable.top();
			for (int i=0; i< table.entries.size(); i++){
				// printID(table.entries[i]->name, 
				// 		table.entries[i]->offset, 
				// 		table.entries[i]->type);
			}
			symbolTable.pop();
			offsets.pop_back();
			
			(yyval) = new Node();
			(yyval)->breaklist = (yyvsp[0])->breaklist;
			(yyval)->continuelist = (yyvsp[0])->continuelist;
			// $$.type = $3.type; 
			// $$.lineno = $3.lineno;
			(yyval)->truelist = (yyvsp[-4])->truelist;
			(yyval)->falselist =(yyvsp[-4])->falselist;
			(yyval)->quad = (yyvsp[-1])->quad;
		}
#line 2101 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 671 "parser.ypp" /* yacc.c:1646  */
    { 
			// std::cout << "start if scope" << std::endl;
			symbolTable.maketable(); 
			offsets.push_back(offsets.back());
		}
#line 2111 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 677 "parser.ypp" /* yacc.c:1646  */
    {checkIfExpIsBool((yyvsp[0]), (yyvsp[0])->line_num);}
#line 2117 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 678 "parser.ypp" /* yacc.c:1646  */
    {
				// endScope();
				Table table = symbolTable.top();
				for (int i=0; i< table.entries.size(); i++){
					// printID(table.entries[i]->name, 
					// 		table.entries[i]->offset, 
					// 		table.entries[i]->type);
				}
				symbolTable.pop();
				offsets.pop_back();
				inWhiles -= 1;

				(yyval) = new Node();
				//nested loops checking
				CodeBuffer::instance().bpatch(*((yyvsp[-6])->truelist), (yyvsp[-3])->quad);
				CodeBuffer::instance().bpatch(*((yyvsp[-6])->falselist), (yyvsp[0])->quad);
				CodeBuffer::instance().bpatch(*((yyvsp[-1])->nextlist), (yyvsp[-7])->quad);
				if((yyvsp[-2])->breaklist != NULL)
				{
					CodeBuffer::instance().bpatch(*((yyvsp[-2])->breaklist), (yyvsp[0])->quad);
				}
				if((yyvsp[-2])->continuelist != NULL)
				{
					CodeBuffer::instance().bpatch(*((yyvsp[-2])->continuelist), (yyvsp[-7])->quad);
				}
				(yyval)->continuelist = NULL;
				(yyval)->breaklist = NULL;
			}
#line 2150 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 707 "parser.ypp" /* yacc.c:1646  */
    { 
	// std::cout << "while if scope" << std::endl;
	symbolTable.maketable(); 
	offsets.push_back(offsets.back());
	inWhiles += 1;
}
#line 2161 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 714 "parser.ypp" /* yacc.c:1646  */
    {
	// endScope();
	Table table = symbolTable.top();
	for (int i=0; i< table.entries.size(); i++){
		// printID(table.entries[i]->name, 
		// 		table.entries[i]->offset, 
		// 		table.entries[i]->type);
	}
	symbolTable.pop();
	offsets.pop_back();

	(yyval) = new Node();
	(yyval)->breaklist = (yyvsp[0])->breaklist;
	(yyval)->continuelist = (yyvsp[0])->continuelist;
	// $$.type = $3.type; 
	// $$.lineno = $3.lineno;
	// $$->truelist = $3->truelist;
	// $$->falselist =$3->falselist;
	(yyval)->quad = (yyvsp[-1])->quad;
	(yyval)->nextlist = (yyvsp[-3])->nextlist;
}
#line 2187 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 737 "parser.ypp" /* yacc.c:1646  */
    {
		symbolTable.maketable(); 
		offsets.push_back(offsets.back());
	}
#line 2196 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 742 "parser.ypp" /* yacc.c:1646  */
    {
		symbolTable.maketable();
		offsets.push_back(offsets.back());
	}
#line 2205 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 750 "parser.ypp" /* yacc.c:1646  */
    {
		registerPool.storeRegsInUse();
		registerPool.storeFramePointerReturnAddress();
	}
#line 2214 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 756 "parser.ypp" /* yacc.c:1646  */
    {
		// call type is from Id type
		// explist must fit the function from symbol table
		//noamha check that func in syblme table - important!
		//noamha ID - name of the  funciton 
		if (!symbolTable.checkIfFunctionExists((yyvsp[-4])->names[0])){
			errorUndefFunc(yylineno, (yyvsp[-4])->names[0]);
			exit(1);
		}
		
		//noamha ret type of the funtions
		string rettype = symbolTable.getFunctionRetType((yyvsp[-4])->names[0]);
		std::vector<string> v_args = symbolTable.getFunctionArgs((yyvsp[-4])->names[0]);

        vector<string> v_args_s = argsTypesToStr(symbolTable.getFunctionArgs((yyvsp[-4])->names[0]));
		//check all arguments
		//noamha 
		if ((yyvsp[-1])->types.size() != v_args.size()){
			// error
			errorPrototypeMismatch(yylineno, (yyvsp[-4])->value, v_args_s);
			exit(1);
		}

		for (int i=0; i< (yyvsp[-1])->types.size(); i++){
			if (v_args[i] != (yyvsp[-1])->types[i]){
				if ((v_args[i] == "INT") && ((yyvsp[-1])->types[i] == "BYTE")){
					// do nothing
				}
				else{
					errorPrototypeMismatch(yylineno, (yyvsp[-4])->value, v_args_s);
					exit(1);
				}
			}
		}

		//<noamha
		//noamha here need to add all code:
		//open scope, calling convention
		//need to have in the symle table the label to jump - we will do it later
		string funcLabel = (yyvsp[-4])->names[0];
		registerPool.jumpAndLink(funcLabel);

		CodeBuffer::instance().emit("addu $sp, $sp, "+intToString((yyvsp[-1])->types.size()*4));

		/*close frame for arguments that were passed on the stack :num of arguments on the stack * 4 */
		
		registerPool.restoreReturnAddressFramePointer();
		registerPool.restoreRegsInUse();
		
		//noamha>

		(yyval) = new Node();
		string s_retype = rettype;
		(yyval)->types.push_back(s_retype);

		(yyval)->reg = registerPool.allocateRegister();

		CodeBuffer::instance().emit("addu $"+intToString((yyval)->reg)+", $v0, 0");
		if (s_retype == "BOOL")
		{
			(yyval)->falselist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("beq $"+intToString((yyval)->reg)+",0, ")));
			(yyval)->truelist =  new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
			registerPool.deallocateRegister((yyval)->reg);
        }

		//nothing if VOID
		(yyval)->nonterminal = "call";
		(yyval)->line_num = yylineno;


	}
#line 2290 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 828 "parser.ypp" /* yacc.c:1646  */
    {
		// call type is from Id type
		// empty explist must fit the function from symbol table

		if (!symbolTable.checkIfFunctionExists((yyvsp[-3])->names[0])){
			errorUndefFunc(yylineno, (yyvsp[-3])->names[0]);
			exit(1);
		}

		
		string rettype = symbolTable.getFunctionRetType((yyvsp[-3])->names[0]);
		std::vector<string> args = symbolTable.getFunctionArgs((yyvsp[-3])->names[0]);

		vector<string> args_s = argsTypesToStr(symbolTable.getFunctionArgs((yyvsp[-3])->names[0]));
		//check all arguments
		if (args.size() != 0){
			// error
			errorPrototypeMismatch(yylineno, (yyvsp[-3])->value, args_s);
			exit(1);
		}

		registerPool.jumpAndLink((yyvsp[-3])->names[0]);
		// CodeBuffer::instance().emit("addu $sp, $sp, "+intToString($4->types.size()*4));
		registerPool.restoreReturnAddressFramePointer();
		registerPool.restoreRegsInUse();

		(yyval) = new Node();

		if (rettype == "VOID"){
			// do nothing
		}
		else{
			(yyval)->types.push_back(rettype);
		}
		
		(yyval)->reg = registerPool.allocateRegister();
		CodeBuffer::instance().emit("addu $"+intToString((yyval)->reg)+", $v0, 0");

		if((yyval)->types.size() > 0 && (yyval)->types[0] ==  "BOOL")
		{
			(yyval)->falselist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("beq $"+intToString((yyval)->reg)+",0, ")));
			(yyval)->truelist =  new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));

			registerPool.deallocateRegister((yyval)->reg);
		}


		(yyval)->nonterminal = "call";
		(yyval)->line_num = yylineno;
	}
#line 2345 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 880 "parser.ypp" /* yacc.c:1646  */
    { 
		(yyval) = (yyvsp[0]);
		
		if((yyvsp[0])->types[0] == "INT" || (yyvsp[0])->types[0]=="BYTE")
		{
			CodeBuffer::instance().emit("subu $sp, $sp, 4");
			CodeBuffer::instance().emit("sw $"+intToString((yyvsp[0])->reg)+", ($sp)");
            //regs.deallocReg($1.reg);			
		}
		else if ((yyvsp[0])->types[0]=="BOOL")
		{
 			(yyvsp[0])->reg = registerPool.allocateRegister();

 			string f_label = CodeBuffer::instance().genLabel();
			CodeBuffer::instance().emit("li $"+intToString((yyvsp[0])->reg)+", 0");
	        std::vector<int> next_bp = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
 			string t_label = CodeBuffer::instance().genLabel();
	        CodeBuffer::instance().emit("li $"+intToString((yyvsp[0])->reg)+", 1"); 
 			string next_label = CodeBuffer::instance().genLabel();
 			CodeBuffer::instance().bpatch((*(yyvsp[0])->truelist), t_label);
 			CodeBuffer::instance().bpatch((*(yyvsp[0])->falselist), f_label);
 			CodeBuffer::instance().bpatch(next_bp, next_label);

 			CodeBuffer::instance().emit("subu $sp, $sp, 4");
 			CodeBuffer::instance().emit("sw $"+ intToString((yyvsp[0])->reg)+", ($sp)"); 			
    		registerPool.deallocateRegister((yyvsp[0])->reg);
		}
		else if ((yyvsp[0])->types[0]=="STRING")
		{

			int reg = registerPool.allocateRegister();
 			string label = CodeBuffer::instance().genLabel();
	        string label_str =  label + "_msg:    .asciiz    " + (yyvsp[0])->value;
			CodeBuffer::instance().emitData(label_str);
			//la rdest, mem - why used label?
			CodeBuffer::instance().emit("la $"+intToString(reg)+", "+label + "_msg");
			CodeBuffer::instance().emit("subu $sp, $sp, 4");
		    CodeBuffer::instance().emit("sw $"+intToString(reg)+", ($sp)");
		    
		    registerPool.deallocateRegister(reg);


		}
		//noamha>
	}
#line 2395 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 926 "parser.ypp" /* yacc.c:1646  */
    {


			if ((yyvsp[0])->types[0] ==  "BOOL")
			{
				
				(yyvsp[0])->reg = registerPool.allocateRegister();

				string f_label = CodeBuffer::instance().genLabel();
				CodeBuffer::instance().emit("li $"+intToString((yyvsp[0])->reg)+", 0");
				std::vector<int> next_bp = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
				string t_label = CodeBuffer::instance().genLabel();
				CodeBuffer::instance().emit("li $"+intToString((yyvsp[0])->reg)+", 1"); 
				string next_label = CodeBuffer::instance().genLabel();
				CodeBuffer::instance().bpatch((*(yyvsp[0])->truelist), t_label);
				CodeBuffer::instance().bpatch((*(yyvsp[0])->falselist), f_label);
				CodeBuffer::instance().bpatch(next_bp, next_label);
			}
		}
#line 2419 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 946 "parser.ypp" /* yacc.c:1646  */
    {
			if((yyvsp[-3])->types[0]=="INT" || (yyvsp[-3])->types[0]=="BYTE" || (yyvsp[-3])->types[0] == "BOOL")
			{
				// noamka what about BOOL ? they don;t have any register, the compiler will fault.
				CodeBuffer::instance().emit("subu $sp, $sp, 4");
				CodeBuffer::instance().emit("sw $"+intToString((yyvsp[-3])->reg) + ", 0($sp)");
				registerPool.deallocateRegister((yyvsp[-3])->reg);
			}
			else if((yyvsp[-3])->types[0]=="STRING")
			{
				int reg = registerPool.allocateRegister();
 				string label = CodeBuffer::instance().genLabel();
	        	string label_str =  label + "_msg:    .asciiz    " + (yyvsp[-3])->value;
				CodeBuffer::instance().emitData(label_str);
				//la rdest, mem - why used label?
				CodeBuffer::instance().emit("la $"+intToString(reg)+", "+label_str);
				CodeBuffer::instance().emit("subu $sp, $sp, 4");
		    	CodeBuffer::instance().emit("sw $"+intToString(reg)+", ($sp)");
		    	registerPool.deallocateRegister((yyvsp[-3])->reg);
			}

			// else if ($1->types[0] ==  "BOOL")
			// {
			// 	$1->reg = registerPool.allocateRegister();

			// 	string f_label = CodeBuffer::instance().genLabel();
			// 	CodeBuffer::instance().emit("li $"+intToString($1->reg)+", 0");
			// 	std::vector<int> next_bp = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
			// 	string t_label = CodeBuffer::instance().genLabel();
			// 	CodeBuffer::instance().emit("li $"+intToString($1->reg)+", 1"); 
			// 	string next_label = CodeBuffer::instance().genLabel();
			// 	CodeBuffer::instance().bpatch((*$1->truelist), t_label);
			// 	CodeBuffer::instance().bpatch((*$1->falselist), f_label);
			// 	CodeBuffer::instance().bpatch(next_bp, next_label);

			// 	CodeBuffer::instance().emit("subu $sp, $sp, 4");
			// 	CodeBuffer::instance().emit("sw $"+intToString($1->reg)+", ($sp)");
			// 	registerPool.deallocateRegister($1->reg);
			// }
			//<noamha
			(yyval) = new Node();
			(yyval)->types.push_back((yyvsp[-3])->types[0]);

			for (int i=0; i< (yyvsp[0])->types.size(); ++i){
				(yyval)->types.push_back((yyvsp[0])->types[i]);
			}
			(yyval)->line_num = (yyvsp[-3])->line_num;
		}
#line 2472 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 995 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); (yyval)->line_num = yylineno;}
#line 2478 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 996 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); (yyval)->line_num = yylineno;}
#line 2484 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 997 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); (yyval)->line_num = yylineno;}
#line 2490 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 1000 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]);}
#line 2496 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 1001 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new BinOp((yyvsp[-2]), (yyvsp[0]), "PLUS", yylineno);
		(yyval)->reg = (yyvsp[-2])->reg;
		registerPool.deallocateRegister((yyvsp[0])->reg);
	    CodeBuffer::instance().emit("addu $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg));
	        
	    // if (strcmp($$->types[0],"BYTE") == 0) {
	    if ((yyval)->types[0] == "BYTE") {
	        CodeBuffer::instance().emit("and $"+intToString((yyval)->reg)+", $"+intToString((yyval)->reg)+", 255");
	    }

	}
#line 2513 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 1013 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new BinOp((yyvsp[-2]), (yyvsp[0]), "MINUS", yylineno);

		(yyval)->reg = (yyvsp[-2])->reg;
		registerPool.deallocateRegister((yyvsp[0])->reg);
		CodeBuffer::instance().emit("subu $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg));
		if((yyval)->types[0]=="BYTE"){
			CodeBuffer::instance().emit("and $"+intToString((yyval)->reg)+", $"+intToString((yyval)->reg)+", 255");
		}

		// CodeBuffer::instance().emit("subu $"+its($1.reg)+", $"+its($1.reg)+", $"+its($3.reg));

	}
#line 2531 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 1026 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new BinOp((yyvsp[-2]), (yyvsp[0]), "MULT", yylineno);

		(yyval)->reg = (yyvsp[-2])->reg;
		registerPool.deallocateRegister((yyvsp[0])->reg);
		CodeBuffer::instance().emit("mul $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg));
		if((yyval)->types[0]=="BYTE"){
			CodeBuffer::instance().emit("and $"+intToString((yyval)->reg)+", $"+intToString((yyval)->reg)+", 255");
		}
	}
#line 2546 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 1036 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new BinOp((yyvsp[-2]), (yyvsp[0]), "DIV", yylineno);

		(yyval)->reg = (yyvsp[-2])->reg;
		registerPool.deallocateRegister((yyvsp[0])->reg);
		CodeBuffer::instance().emit("beq $"+intToString((yyvsp[0])->reg)+", 0, devided_by_zero");
		CodeBuffer::instance().emit("div $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg));
		if((yyval)->types[0]=="BYTE"){
			CodeBuffer::instance().emit("and $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[-2])->reg)+", 255");
		}
	}
#line 2562 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 1047 "parser.ypp" /* yacc.c:1646  */
    {
		//noamha: need to check that it exsits in all scopes
		if (!symbolTable.checkIfVariableExists((yyvsp[0])->names[0])){
			errorUndef(yylineno, (yyvsp[0])->names[0]);
			exit(1);
		}
		string type = symbolTable.getIdType((yyvsp[0])->names[0]);
		(yyvsp[0])->types.push_back(type);
		(yyval) = (yyvsp[0]);
		//noamha: hw 5:
		//alocate reg only if it's not boolean
		(yyval)->line_num = yylineno;
		if(type == "INT" || type == "BYTE" || type == "STRING" || type == "BOOL"){
			(yyval)->reg = registerPool.allocateRegister();
			//noamha: when it finds the var it gets in offset
			int offset = symbolTable.getIdOffset((yyvsp[0])->names[0]);
			// cout << "offset " << offset << endl;
			offset = (-4) * offset - 4;
			
			// CodeBuffer::instance().emit("#"+intToString(offset));
			CodeBuffer::instance().emit("lw $"+intToString((yyval)->reg)+", "+intToString(offset)+"($fp)");
			if(type ==  "BOOL")
			{
				(yyval)->falselist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("beq $"+intToString((yyval)->reg)+",0, ")));
				(yyval)->truelist =  new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));

				registerPool.deallocateRegister((yyval)->reg);
			}
		}
		
	}
#line 2598 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 1078 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]);
		(yyval)->line_num = yylineno;
		(yyval)->falselist = (yyvsp[0])->falselist;
		(yyval)->truelist = (yyvsp[0])->truelist;
		(yyval)->reg = (yyvsp[0])->reg;
	}
#line 2610 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 1085 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]);
		(yyval)->line_num = yylineno;
		(yyval)->reg = registerPool.allocateRegister();
      	
        CodeBuffer::instance().emit("li $"+ intToString((yyval)->reg) + ", " + (yyvsp[0])->value);
	}
#line 2622 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 1092 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new NumByte((yyvsp[-1])->value, yylineno);

	  	int res =  (yyvsp[-1])->value_t % 256;
	  	
	    (yyval)->value = intToString(res);
	    (yyval)->value_t = res;
	    (yyval)->reg = registerPool.allocateRegister();
	    std::stringstream buff;
	    buff <<"li $"<<(yyval)->reg<<", "<<(yyvsp[-1]);
	    CodeBuffer::instance().emit("li $" + intToString((yyval)->reg) + ", " + (yyval)->value);
	}
#line 2639 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 1104 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[0]); 
		(yyval)->line_num = yylineno;
	}
#line 2648 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 1108 "parser.ypp" /* yacc.c:1646  */
    {
		// cout << "true" << endl;
		(yyval) = (yyvsp[0]); 
		(yyval)->line_num = yylineno;
		(yyval)->falselist= new vector<int>();
		(yyval)->truelist = new vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
	}
#line 2660 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 1115 "parser.ypp" /* yacc.c:1646  */
    {

		// cout << yylineno <<"false" << endl;

		(yyval) = (yyvsp[0]); 
		(yyval)->line_num = yylineno;
		(yyval)->truelist= new vector<int>();
		(yyval)->falselist = new vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
	}
#line 2674 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 1124 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new Not((yyvsp[0]), yylineno);
		(yyval)->truelist = (yyvsp[0])->falselist;
        (yyval)->falselist = (yyvsp[0])->truelist;
	}
#line 2684 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 1130 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new BoolOp((yyvsp[-3]), (yyvsp[0]), (yyvsp[-2])->value, yylineno);
		CodeBuffer::instance().bpatch(*((yyvsp[-3])->truelist), (yyvsp[-1])->quad);
		(yyval)->truelist = (yyvsp[0])->truelist;
		(yyval)->falselist = new vector<int>(CodeBuffer::instance().merge(*((yyvsp[-3])->falselist),*((yyvsp[0])->falselist)));
	}
#line 2695 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 1137 "parser.ypp" /* yacc.c:1646  */
    {
		// cout << yylineno << "or " << endl;
		(yyval) = new BoolOp((yyvsp[-3]), (yyvsp[0]), (yyvsp[-2])->value, yylineno);

		CodeBuffer::instance().bpatch(*((yyvsp[-3])->falselist), (yyvsp[-1])->quad);
		(yyval)->truelist = new vector<int>(CodeBuffer::instance().merge(*((yyvsp[-3])->truelist),*((yyvsp[0])->truelist)));
		(yyval)->falselist = (yyvsp[0])->falselist;

	}
#line 2709 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 1147 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new Relop((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])->value, yylineno);
		if ((yyvsp[-1])->value == "=="){
			(yyval)->truelist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("beq $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg)+", ")));
		}
		else if ((yyvsp[-1])->value == "!="){
			(yyval)->truelist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("bne $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg)+", ")));
		}
		(yyval)->falselist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
		registerPool.deallocateRegister((yyvsp[-2])->reg);
		registerPool.deallocateRegister((yyvsp[0])->reg);
	}
#line 2726 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 1160 "parser.ypp" /* yacc.c:1646  */
    {
		(yyval) = new Relop((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])->value, yylineno);
		if ((yyvsp[-1])->value == ">="){
			(yyval)->truelist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("bge $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg)+", ")));
		}
		else if ((yyvsp[-1])->value == ">"){
			(yyval)->truelist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("bgt $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg)+", ")));
		}
		else if ((yyvsp[-1])->value == "<="){
			(yyval)->truelist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("ble $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg)+", ")));
		}
		else if ((yyvsp[-1])->value == "<"){
			(yyval)->truelist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("blt $"+intToString((yyvsp[-2])->reg)+", $"+intToString((yyvsp[0])->reg)+", ")));
		}
		(yyval)->falselist = new std::vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
		registerPool.deallocateRegister((yyvsp[-2])->reg);
		registerPool.deallocateRegister((yyvsp[0])->reg);
	}
#line 2749 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 1181 "parser.ypp" /* yacc.c:1646  */
    { 
		(yyval) = new Node();
		(yyval)->nextlist = new vector<int>(CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "))); 
	}
#line 2758 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 1187 "parser.ypp" /* yacc.c:1646  */
    { 
		(yyval) = new Node();
		// $$->label = strdup(CodeBuffer::instance().genLabel().c_str()); 
		(yyval)->quad = CodeBuffer::instance().genLabel();
		// std::cout << $$->quad << endl;
	}
#line 2769 "parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 2773 "parser.tab.cpp" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1195 "parser.ypp" /* yacc.c:1906  */


int main() 
{
	return yyparse();
}

void yyerror(const char*) 
{
	errorSyn(yylineno);
}


void emitPrintIandPrint(){
	//printi
	CodeBuffer::instance().emit("print:");
	CodeBuffer::instance().emit("lw $a0, 0($sp)");
	CodeBuffer::instance().emit("li $v0,4");
	CodeBuffer::instance().emit("syscall");
	CodeBuffer::instance().emit("jr $ra");

 	// print
 	CodeBuffer::instance().emit("printi:");
 	CodeBuffer::instance().emit("lw $a0, 0($sp)");
	CodeBuffer::instance().emit("li $v0, 1");
	CodeBuffer::instance().emit("syscall");
	CodeBuffer::instance().emit("jr $ra");

	// divided by zero
	CodeBuffer::instance().emit("devided_by_zero:");
  	CodeBuffer::instance().emit("la $a0, devided_by_zero_msg");
	CodeBuffer::instance().emit("li $v0, 4");
	CodeBuffer::instance().emit("syscall");
	CodeBuffer::instance().emit("li $v0, 10");
	CodeBuffer::instance().emit("syscall");
  	CodeBuffer::instance().emitData("devided_by_zero_msg: \t .asciiz \t \"Error division by zero\n\"");


  	// Precondition hasn't been satisfied for function <function_name>\n
	CodeBuffer::instance().emitData("new_line: \t .asciiz \t \"\n\"");
	CodeBuffer::instance().emitData("prcond_false_msg: \t .asciiz \t \"Precondition hasn't been satisfied for function \"");
}

void emitPreCondError(string function_name){
	// CodeBuffer::instance().emit("prcond_false:");
  	CodeBuffer::instance().emit("la $a0, prcond_false_msg");
	CodeBuffer::instance().emit("li $v0, 4");
	CodeBuffer::instance().emit("syscall");

	CodeBuffer::instance().emit("la $a0, "+function_name);
	CodeBuffer::instance().emit("li $v0, 4");
	CodeBuffer::instance().emit("syscall");


	CodeBuffer::instance().emit("la $a0, new_line");
	CodeBuffer::instance().emit("li $v0, 4");
	CodeBuffer::instance().emit("syscall");

	CodeBuffer::instance().emit("li $v0, 10"); // terminate
	CodeBuffer::instance().emit("syscall");
}
 
 
