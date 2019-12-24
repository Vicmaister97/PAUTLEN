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
#line 10 "alfa.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TS/tabla.h"
#include "gen_codigo/generacion.h"
#include "alfa.h"


HASH_TABLE *TGLOBAL;
HASH_TABLE *TLOCAL = NULL;


//Para la negacion Logica
int global_no;
//Para generacion de etiquetas
int etiqueta;

void cmpOp(FILE *yyout, tipo_atributos op1, tipo_atributos op2, int tipo_op){
  if(tipo_op == CMP_IGUAL)
    igual(yyout, op1.es_direccion, op2.es_direccion, etiqueta++);
  else if(tipo_op == CMP_DIST)
    distinto(yyout, op1.es_direccion, op2.es_direccion, etiqueta++);
  else if(tipo_op == CMP_MEN_IG)
    menor_igual(yyout, op1.es_direccion, op2.es_direccion, etiqueta++);
  else if(tipo_op == CMP_MAY_IG)
    mayor_igual(yyout, op1.es_direccion, op2.es_direccion, etiqueta++);
  else if(tipo_op == CMP_MEN)
    menor(yyout, op1.es_direccion, op2.es_direccion, etiqueta++);
  else if(tipo_op == CMP_MAY)
    mayor(yyout, op1.es_direccion, op2.es_direccion, etiqueta++);

return;
}


extern void errorMorfo (char *msg);
void yyerror(char *msg);
void errorSemantico (char *msg);

extern FILE* yyin;
extern FILE* yyout;
extern int col;
extern int yylineno;
extern int yyleng;
extern int is_morpho;
int yylex();

/* Variables globales para acciones semanticas */
int tipo_actual;
int clase_actual;
int tamanio_vector_actual;
int num_parametros_llamada_actual;
int en_explist = 0;       // Vale 1 si es una llamada a funcion dentro de una llamada a funcion


/* INICIALIZAR EN DECLARAR FUNCION!!!!!!!!!!!!!!!!!!!!!!! */
int pos_variable_local_actual;       // Incrementamos esta variable cada vez que se declara una variable LOCAL
int num_variables_locales_actual;    // Incrementamos esta variable cada vez que se declara una variable LOCAL
int pos_parametro_actual;
int num_parametros_actual;
int hayReturn = 0;                   // Indica si la funcion tiene una sentencia return (=1) o no (=0)
int tipoReturn;

char nombre_funcion_actual[MAX_LONG_ID];
char nombre_vector[MAX_LONG_ID];
int errorVector = 0;                 // Indica si hay un error al declarar un vector (=1) o no (=0)

SIMBOLO *simbol;


#line 138 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 82 "alfa.y" /* yacc.c:355  */

  #include "alfa.h"


#line 173 "y.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_MAIN = 258,
    TOK_INT = 259,
    TOK_BOOLEAN = 260,
    TOK_ARRAY = 261,
    TOK_FUNCTION = 262,
    TOK_IF = 263,
    TOK_ELSE = 264,
    TOK_WHILE = 265,
    TOK_SCANF = 266,
    TOK_PRINTF = 267,
    TOK_RETURN = 268,
    TOK_PUNTOYCOMA = 269,
    TOK_COMA = 270,
    TOK_PARENTESISIZQUIERDO = 271,
    TOK_PARENTESISDERECHO = 272,
    TOK_CORCHETEIZQUIERDO = 273,
    TOK_CORCHETEDERECHO = 274,
    TOK_LLAVEIZQUIERDA = 275,
    TOK_LLAVEDERECHA = 276,
    TOK_ASIGNACION = 277,
    TOK_MAS = 278,
    TOK_MENOS = 279,
    TOK_ASTERISCO = 280,
    TOK_DIVISION = 281,
    TOK_AND = 282,
    TOK_OR = 283,
    TOK_NOT = 284,
    TOK_IGUAL = 285,
    TOK_DISTINTO = 286,
    TOK_MENORIGUAL = 287,
    TOK_MAYORIGUAL = 288,
    TOK_MENOR = 289,
    TOK_MAYOR = 290,
    TOK_IDENTIFICADOR = 291,
    TOK_CONSTANTE_ENTERA = 292,
    TOK_TRUE = 293,
    TOK_FALSE = 294
  };
#endif
/* Tokens.  */
#define TOK_MAIN 258
#define TOK_INT 259
#define TOK_BOOLEAN 260
#define TOK_ARRAY 261
#define TOK_FUNCTION 262
#define TOK_IF 263
#define TOK_ELSE 264
#define TOK_WHILE 265
#define TOK_SCANF 266
#define TOK_PRINTF 267
#define TOK_RETURN 268
#define TOK_PUNTOYCOMA 269
#define TOK_COMA 270
#define TOK_PARENTESISIZQUIERDO 271
#define TOK_PARENTESISDERECHO 272
#define TOK_CORCHETEIZQUIERDO 273
#define TOK_CORCHETEDERECHO 274
#define TOK_LLAVEIZQUIERDA 275
#define TOK_LLAVEDERECHA 276
#define TOK_ASIGNACION 277
#define TOK_MAS 278
#define TOK_MENOS 279
#define TOK_ASTERISCO 280
#define TOK_DIVISION 281
#define TOK_AND 282
#define TOK_OR 283
#define TOK_NOT 284
#define TOK_IGUAL 285
#define TOK_DISTINTO 286
#define TOK_MENORIGUAL 287
#define TOK_MAYORIGUAL 288
#define TOK_MENOR 289
#define TOK_MAYOR 290
#define TOK_IDENTIFICADOR 291
#define TOK_CONSTANTE_ENTERA 292
#define TOK_TRUE 293
#define TOK_FALSE 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 87 "alfa.y" /* yacc.c:355  */

  tipo_atributos atributos;

#line 267 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 284 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   141

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   171,   176,   198,   203,   204,   206,   218,
     219,   221,   223,   224,   226,   235,   236,   238,   239,   241,
     276,   295,   312,   313,   315,   317,   319,   321,   335,   336,
     338,   339,   341,   342,   344,   345,   346,   347,   349,   350,
     352,   412,   423,   474,   480,   486,   497,   503,   509,   521,
     527,   571,   575,   589,   600,   611,   622,   633,   646,   657,
     668,   680,   753,   755,   757,   760,   761,   800,   852,   857,
     859,   864,   866,   878,   889,   900,   911,   922,   934,   941,
     948,   957,   968,   984
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_MAIN", "TOK_INT", "TOK_BOOLEAN",
  "TOK_ARRAY", "TOK_FUNCTION", "TOK_IF", "TOK_ELSE", "TOK_WHILE",
  "TOK_SCANF", "TOK_PRINTF", "TOK_RETURN", "TOK_PUNTOYCOMA", "TOK_COMA",
  "TOK_PARENTESISIZQUIERDO", "TOK_PARENTESISDERECHO",
  "TOK_CORCHETEIZQUIERDO", "TOK_CORCHETEDERECHO", "TOK_LLAVEIZQUIERDA",
  "TOK_LLAVEDERECHA", "TOK_ASIGNACION", "TOK_MAS", "TOK_MENOS",
  "TOK_ASTERISCO", "TOK_DIVISION", "TOK_AND", "TOK_OR", "TOK_NOT",
  "TOK_IGUAL", "TOK_DISTINTO", "TOK_MENORIGUAL", "TOK_MAYORIGUAL",
  "TOK_MENOR", "TOK_MAYOR", "TOK_IDENTIFICADOR", "TOK_CONSTANTE_ENTERA",
  "TOK_TRUE", "TOK_FALSE", "$accept", "programa", "inicioTabla",
  "escritura_TS", "end_funciones", "declaraciones", "declaracion", "clase",
  "clase_escalar", "tipo", "clase_vector", "identificadores", "funciones",
  "funcion", "fn_name", "fn_declaration", "parametros_funcion",
  "resto_parametros_funcion", "parametro_funcion", "idpf",
  "declaraciones_funcion", "sentencias", "sentencia", "sentencia_simple",
  "bloque", "asignacion", "elemento_vector", "condicional", "if_exp",
  "if_else_exp", "bucle", "bucle_exp", "while", "lectura", "escritura",
  "retorno_funcion", "exp", "idf_llamada_funcion", "lista_expresiones",
  "resto_lista_expresiones", "comparacion", "constante",
  "constante_logica", "constante_entera", "identificador", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF -39

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-39)))

#define YYTABLE_NINF -68

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -39,     3,     9,   -39,    -1,    10,   -39,   -39,    17,   -39,
      10,     1,   -39,   -39,   -39,     5,    29,   -39,   -39,    26,
      23,     6,    17,   -39,    29,    39,    22,   -39,     1,    37,
      21,    22,   -39,    10,    43,    44,    25,    15,    15,   -13,
      48,    22,    31,   -39,   -39,    63,   -39,    53,    89,   -39,
      82,    15,   -39,   -39,   -39,   -39,   -39,   -39,    79,    66,
      86,    91,    15,   -39,   -39,    15,    15,    15,   -10,   -39,
     -39,   -39,   -39,    49,    97,   -39,   -39,   -39,    49,    15,
      15,   -39,   -39,   -39,    15,   102,   103,   110,    49,   -39,
     -39,   -39,   111,    10,   -39,    49,    84,   104,     0,   -39,
      15,    15,    15,    15,    15,    15,    15,   101,    49,    49,
      22,    22,    22,    10,    91,   -39,    15,    15,    15,    15,
      15,    15,   -39,     0,     0,   -39,   -39,    24,    24,    69,
     115,   -39,   112,   113,   114,   -39,   -39,   -39,    49,    49,
      49,    49,    49,    49,    15,   -39,   -39,   127,   -39,   -39,
      69,   -39
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,    12,    13,     0,     4,
       6,     0,     9,    11,    10,     0,    18,     7,    83,     0,
      15,     0,     0,     5,    18,     0,     0,     8,     0,     0,
       0,     0,    17,    23,     0,     0,     0,     0,     0,     0,
       0,    30,     0,    33,    34,     0,    38,     0,     0,    39,
       0,     0,    35,    36,    37,    16,    14,    20,     0,     0,
       0,    25,     0,    49,    50,     0,     0,     0,    61,    82,
      80,    81,    65,    51,     0,    62,    78,    79,    52,     0,
       0,    19,    31,    32,     0,     0,     0,     0,    48,     2,
      27,    26,     0,     0,    22,    45,     0,     0,    57,    60,
       0,     0,     0,     0,     0,     0,    69,     0,    40,    41,
       0,     0,     0,    29,    25,    63,     0,     0,     0,     0,
       0,     0,    64,    53,    54,    56,    55,    58,    59,    71,
       0,    42,     0,     0,     0,    28,    21,    24,    72,    73,
      74,    75,    76,    77,     0,    68,    66,    43,    44,    47,
      71,    70
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,   -39,   -39,   -39,    -9,   -39,   -22,   -39,    -4,
     -39,   109,   116,   -39,   -39,   -39,   -39,    27,    45,   -39,
     -39,   -21,   -39,   -39,   -39,   -39,   -24,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -38,   -39,   -39,   -11,
     -39,   -39,   -39,   -39,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    16,    31,     9,    10,    11,    12,    13,
      14,    19,    23,    24,    25,    26,    60,    94,    61,    91,
     136,    40,    41,    42,    43,    44,    72,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    73,    74,   130,   145,
      97,    75,    76,    77,    20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,    17,    45,     3,    15,    79,   -67,    45,    79,    80,
      58,    59,     4,    88,     6,     7,     8,    45,    30,     5,
      82,     6,     7,    21,    95,   102,   103,    96,    98,    99,
      34,    65,    35,    36,    37,    38,    22,    18,    28,    66,
      27,   107,   108,    29,    67,    83,   109,   100,   101,   102,
     103,    68,    69,    70,    71,    33,    56,    57,    39,    62,
      63,    64,   123,   124,   125,   126,   127,   128,   129,    81,
      85,    59,   100,   101,   102,   103,   104,   105,   138,   139,
     140,   141,   142,   143,   144,    84,    45,    45,    45,   132,
     133,   134,   100,   101,   102,   103,   104,   105,    86,    87,
      89,   115,    90,    92,   135,    93,   150,   100,   101,   102,
     103,   104,   105,   106,   116,   117,   118,   119,   120,   121,
     131,   122,   110,   111,   100,   101,   102,   103,   104,   105,
     112,   113,   146,   147,   148,   149,   -46,    55,   114,   151,
      32,   137
};

static const yytype_uint8 yycheck[] =
{
      38,    10,    26,     0,     8,    18,    16,    31,    18,    22,
      31,    33,     3,    51,     4,     5,     6,    41,    22,    20,
      41,     4,     5,    18,    62,    25,    26,    65,    66,    67,
       8,    16,    10,    11,    12,    13,     7,    36,    15,    24,
      14,    79,    80,    37,    29,    14,    84,    23,    24,    25,
      26,    36,    37,    38,    39,    16,    19,    36,    36,    16,
      16,    36,   100,   101,   102,   103,   104,   105,   106,    21,
      17,    93,    23,    24,    25,    26,    27,    28,   116,   117,
     118,   119,   120,   121,    15,    22,   110,   111,   112,   110,
     111,   112,    23,    24,    25,    26,    27,    28,     9,    17,
      21,    17,    36,    17,   113,    14,   144,    23,    24,    25,
      26,    27,    28,    16,    30,    31,    32,    33,    34,    35,
      19,    17,    20,    20,    23,    24,    25,    26,    27,    28,
      20,    20,    17,    21,    21,    21,     9,    28,    93,   150,
      24,   114
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,    42,     0,     3,    20,     4,     5,     6,    45,
      46,    47,    48,    49,    50,    49,    43,    45,    36,    51,
      84,    18,     7,    52,    53,    54,    55,    14,    15,    37,
      49,    44,    52,    16,     8,    10,    11,    12,    13,    36,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    51,    19,    36,    61,    47,
      56,    58,    16,    16,    36,    16,    24,    29,    36,    37,
      38,    39,    66,    76,    77,    81,    82,    83,    76,    18,
      22,    21,    61,    14,    22,    17,     9,    17,    76,    21,
      36,    59,    17,    14,    57,    76,    76,    80,    76,    76,
      23,    24,    25,    26,    27,    28,    16,    76,    76,    76,
      20,    20,    20,    20,    58,    17,    30,    31,    32,    33,
      34,    35,    17,    76,    76,    76,    76,    76,    76,    76,
      78,    19,    61,    61,    61,    45,    60,    57,    76,    76,
      76,    76,    76,    76,    15,    79,    17,    21,    21,    21,
      76,    79
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    43,    44,    45,    45,    46,    47,
      47,    48,    49,    49,    50,    51,    51,    52,    52,    53,
      54,    55,    56,    56,    57,    57,    58,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    63,    63,    64,    64,
      65,    65,    66,    67,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    77,    78,    78,
      79,    79,    80,    80,    80,    80,    80,    80,    81,    81,
      82,    82,    83,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     9,     0,     0,     0,     1,     2,     3,     1,
       1,     1,     1,     1,     5,     1,     3,     2,     0,     3,
       3,     6,     2,     0,     3,     0,     2,     1,     1,     0,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     4,     5,     5,     3,     5,     5,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     2,     3,     3,
       2,     1,     1,     3,     3,     1,     4,     1,     2,     0,
       3,     0,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1
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
#line 167 "alfa.y" /* yacc.c:1646  */
    { escribir_fin(yyout);
        }
#line 1480 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 171 "alfa.y" /* yacc.c:1646  */
    {
              /* Acciones de inicialización de la tabla de símbolos */
              TGLOBAL = newHashTable();       // Tabla hash que almacena los símbolos de ámbito global
            }
#line 1489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 176 "alfa.y" /* yacc.c:1646  */
    {
              listaSimbolo *temp_list_symbols;
              int i, total, len;
              SIMBOLO *tempSymbol;

              escribir_subseccion_data(yyout);
              escribir_cabecera_bss(yyout);
              temp_list_symbols = DumpHashTable(TGLOBAL);
              total = getLenListaSimbolo(temp_list_symbols);
              for(i=0; i<total; i++){
                tempSymbol = *(getListaSimbolo(temp_list_symbols) + i);
                if(getCategoria(tempSymbol) == VECTOR)
                  len = getLongitud(tempSymbol);
                if(len <= 0)
                  len = 1;
                declarar_variable(yyout, getIdentificador(tempSymbol), getTipo(tempSymbol), len);
                }

                freeListaSimbolo(temp_list_symbols);
                escribir_segmento_codigo(yyout);
              }
#line 1515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 198 "alfa.y" /* yacc.c:1646  */
    {
                escribir_inicio_main(yyout);
              }
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 203 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion>\n");}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 204 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");}
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 207 "alfa.y" /* yacc.c:1646  */
    {
                if (errorVector == 1){
                  errorVector = 0;
                  char err[MAX_ERR_LEN];
                  sprintf(err, "El tamanyo del vector <%s> excede los limites permitidos (1,64)", (yyvsp[-1].atributos).lexema);
                  errorSemantico(err);
                  return -1;
                }
                fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");
              }
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 218 "alfa.y" /* yacc.c:1646  */
    {clase_actual=ESCALAR; fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar>\n");}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 219 "alfa.y" /* yacc.c:1646  */
    {clase_actual=VECTOR; fprintf(yyout, ";R7:\t<clase> ::= <clase_vector>\n");}
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 221 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo>\n");}
#line 1568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 223 "alfa.y" /* yacc.c:1646  */
    {tipo_actual=INT; fprintf(yyout, ";R10:\t<tipo> ::= int\n");}
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 224 "alfa.y" /* yacc.c:1646  */
    {tipo_actual=BOOLEAN; fprintf(yyout, ";R11:\t<tipo> ::= boolean\n");}
#line 1580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 227 "alfa.y" /* yacc.c:1646  */
    {
                  tamanio_vector_actual = (yyvsp[-1].atributos).valor_entero;
                  if ( (tamanio_vector_actual < 1) || (tamanio_vector_actual > MAX_TAMANIO_VECTOR) ){
                    errorVector = 1;
                  }
                  fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ constante_entera ]\n");
                }
#line 1592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 235 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R18:\t<identificadores> ::= <identificador>\n");}
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 236 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");}
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 238 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones>\n");}
#line 1610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 239 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R21:\t<funciones> ::= \n");}
#line 1616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 242 "alfa.y" /* yacc.c:1646  */
    {
            // CHECKKKKK !!!!!!!!

            simbol = UsoGlobal(TGLOBAL, (yyvsp[-2].atributos).lexema);
              if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                char err[MAX_ERR_LEN];
                sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[-2].atributos).lexema);
                errorSemantico(err);
                return -1;
              }

            if (hayReturn == 0){
              char err[MAX_ERR_LEN];
              sprintf(err, "Función %s sin sentencia de retorno", (yyvsp[-2].atributos).lexema);
              errorSemantico(err);
              return -1;
            }
            if (getTipo(simbol) != tipoReturn){
              char err[MAX_ERR_LEN];
              sprintf(err, "El tipo de la función (%d) no coincide con el tipo de retorno (%d)", getTipo(simbol), tipoReturn);
              errorSemantico(err);
              return -1;
            }

            setNum_parametros(simbol, num_parametros_actual);
            setNum_var_locales(simbol, num_variables_locales_actual);

            strcpy((yyval.atributos).lexema, (yyvsp[-2].atributos).lexema);

            freeHashTable(TLOCAL);

            fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");
          }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 277 "alfa.y" /* yacc.c:1646  */
    {
            TLOCAL = newHashTable();    // Inicializamos la tabla local
            if (DeclararFuncion(TGLOBAL, TLOCAL, (yyvsp[0].atributos).lexema, FUNCION, tipo_actual, (yyvsp[0].atributos).valor_entero, FALSE, FALSE) == FALSE){
              char err[MAX_ERR_LEN];
              sprintf(err, "Declaracion (%s) duplicada", (yyvsp[0].atributos).lexema);
              errorSemantico(err);
              return -1;
            }
            // Inicializamos variables para la funcion
            num_variables_locales_actual = 0;
            pos_variable_local_actual = 1;      // Hemos insertado la funcion
            num_parametros_actual = 0;
            pos_parametro_actual = 0;

            strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);
            strcpy(nombre_funcion_actual, (yyvsp[0].atributos).lexema);
          }
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 296 "alfa.y" /* yacc.c:1646  */
    {
                    simbol = UsoLocal(TGLOBAL, TLOCAL, (yyvsp[-5].atributos).lexema);
                    if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                        char err[MAX_ERR_LEN];
                        sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[-5].atributos).lexema);
                        errorSemantico(err);
                        return -1;
                    }

                    setNum_parametros(simbol, num_parametros_actual);
                    setNum_var_locales(simbol, num_variables_locales_actual);
                    strcpy((yyval.atributos).lexema, (yyvsp[-5].atributos).lexema);
                    printf("\nDeclarar funcion: %s con %d varLoc", (yyvsp[-5].atributos).lexema, num_variables_locales_actual);
                    declararFuncion(yyout, (yyvsp[-5].atributos).lexema, num_variables_locales_actual);
                  }
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 312 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 313 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n");}
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 316 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 317 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n");}
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 319 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <idpf>\n");}
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 322 "alfa.y" /* yacc.c:1646  */
    {
          if (DeclararLocal(TLOCAL, (yyvsp[0].atributos).lexema, PARAMETRO, tipo_actual, clase_actual,
                                        (yyvsp[0].atributos).valor_entero, FALSE, FALSE, pos_parametro_actual) == FALSE){     // redeclaración variable local
            char err[MAX_ERR_LEN];
            sprintf(err, "Declaracion (%s) duplicada", (yyvsp[0].atributos).lexema);
            errorSemantico(err);
            return -1;
          }
          else{
            pos_parametro_actual++;
            num_parametros_actual++;
          }
        }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 335 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 336 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");}
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 338 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia>\n");}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 339 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 341 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 342 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R33:\t<sentencia> ::= <bloque>\n");}
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 344 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 345 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura>\n");}
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 346 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura>\n");}
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 347 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 349 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R40:\t<bloque> ::= <condicional>\n");}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 350 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R41:\t<bloque> ::= <bucle>\n");}
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 353 "alfa.y" /* yacc.c:1646  */
    {
                if (ambito == 0){
                  simbol = UsoGlobal(TGLOBAL, (yyvsp[-2].atributos).lexema);
                  if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                    char err[MAX_ERR_LEN];
                    sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[-2].atributos).lexema);
                    errorSemantico(err);
                    return -1;
                  }

                  else{                                       // Si lo busca en global y lo encuentra
                        if (CategoriaSimbolo(simbol) == FUNCION){
                          errorSemantico("Asignación incompatible");
                          return -1;
                        }
                        if (getCategoria(simbol) == VECTOR){
                          errorSemantico("Asignación incompatible");
                          return -1;
                        }
                        if (getTipo(simbol) != (yyvsp[0].atributos).tipo){
                          errorSemantico("Asignación incompatible");
                          return -1;
                        }
                    }
                    printf("\nAsignando a %s el valor %d, es DIR: %d", (yyvsp[-2].atributos).lexema, (yyvsp[0].atributos).valor_entero, (yyvsp[0].atributos).es_direccion);
                    asignar(yyout, (yyvsp[-2].atributos).lexema, (yyvsp[0].atributos).es_direccion);
                }
                else{                                           // Búsqueda en local
                    simbol = UsoLocal(TGLOBAL, TLOCAL, (yyvsp[-2].atributos).lexema);
                    if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                        char err[MAX_ERR_LEN];
                        sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[-2].atributos).lexema);
                        errorSemantico(err);
                        return -1;
                    }
                    else{                                       // Si lo busca en local y lo encuentra
                        if (CategoriaSimbolo(simbol) == FUNCION){
                          errorSemantico("Asignación incompatible");
                          return -1;
                        }
                        if (getCategoria(simbol) == VECTOR){
                          errorSemantico("Asignación incompatible");
                          return -1;
                        }
                        if (getTipo(simbol) != (yyvsp[0].atributos).tipo){
                          errorSemantico("Asignación incompatible");
                          return -1;
                        }
                    }
                    ////printf("\nTrick var local pos: %d\nDir: %d",getPosicion(simbol), $1.es_direccion);
                    //printf("\nTrick 3");
                    printf("\nEscribir VLoc %s con pos %d", getIdentificador(simbol), getPosicion(simbol));
                    escribirVariableLocal(yyout, getPosicion(simbol));
                    //printf("\nTrick 4");
                    printf("\nAsignar dst en pila");
                    asignarDestinoEnPila(yyout, (yyvsp[0].atributos).es_direccion);
                }
                fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
             }
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 413 "alfa.y" /* yacc.c:1646  */
    {
                if ((yyvsp[-2].atributos).tipo != (yyvsp[0].atributos).tipo){
                  errorSemantico("Asignación incompatible");
                  return -1;
                }
                asignarDestinoEnPilaINV(yyout, 0);

                fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");
              }
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 424 "alfa.y" /* yacc.c:1646  */
    {
                    if (ambito == 0){
                      simbol = UsoGlobal(TGLOBAL, (yyvsp[-3].atributos).lexema);
                      if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                        char err[MAX_ERR_LEN];
                        sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[-3].atributos).lexema);
                        errorSemantico(err);
                        return -1;
                      }
                      else{                                       // Si lo busca en global y lo encuentra
                        if (getCategoria(simbol) != VECTOR){
                          errorSemantico("Intento de indexacion de una variable que no es de tipo vector");
                          return -1;
                        }
                        if ((yyvsp[-1].atributos).tipo != INT){
                          errorSemantico("El indice en una operacion de indexacion tiene que ser de tipo entero");
                          return -1;
                        }
                        (yyval.atributos).tipo = getTipo(simbol);
                        (yyval.atributos).es_direccion = 1;
                      }
                    }

                    else{                                           // Búsqueda en local
                      simbol = UsoLocal(TGLOBAL, TLOCAL, (yyvsp[-3].atributos).lexema);
                      if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                        char err[MAX_ERR_LEN];
                        sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[-3].atributos).lexema);
                        errorSemantico(err);
                        return -1;
                      }

                      else{                                       // Si lo busca en global y lo encuentra
                        if (getCategoria(simbol) != VECTOR){
                          errorSemantico("Intento de indexacion de una variable que no es de tipo vector");
                          return -1;
                        }
                        if ((yyvsp[-1].atributos).tipo != INT){
                          errorSemantico("El indice en una operacion de indexacion tiene que ser de tipo entero");
                          return -1;
                        }
                        (yyval.atributos).tipo = getTipo(simbol);
                        (yyval.atributos).es_direccion = 1;
                      }
                    }
                    fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");
                    escribir_elemento_vector(yyout, (yyvsp[-3].atributos).lexema, getLongitud(simbol), (yyvsp[-1].atributos).es_direccion);

                  }
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 475 "alfa.y" /* yacc.c:1646  */
    {
                ////printf("\nFIN GLOBAL = %d\nETIQUETA SEM = %d\n", etiqueta, $1.etiqueta);
                ifthen_fin(yyout, (yyvsp[-4].atributos).etiqueta);
                fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");
              }
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 481 "alfa.y" /* yacc.c:1646  */
    {
                ifthenelse_fin(yyout, (yyvsp[-4].atributos).etiqueta);
                fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");
              }
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 487 "alfa.y" /* yacc.c:1646  */
    {
            if ((yyvsp[0].atributos).tipo != BOOLEAN){
              errorSemantico("Condicional con condicion de tipo int");
              return -1;
            }
            (yyval.atributos).etiqueta = etiqueta;
            ifthen_inicio(yyout, (yyvsp[0].atributos).es_direccion, etiqueta);
            ////printf("\nINI GLOBAL = %d\nETIQUETA SEM = %d\n", etiqueta, $$.etiqueta);
          }
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 498 "alfa.y" /* yacc.c:1646  */
    {
            (yyval.atributos).etiqueta = (yyvsp[-4].atributos).etiqueta;
            ifthenelse_fin_then(yyout, (yyvsp[-4].atributos).etiqueta);
          }
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 504 "alfa.y" /* yacc.c:1646  */
    {
        while_fin(yyout, (yyvsp[-4].atributos).etiqueta);
        fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
      }
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 510 "alfa.y" /* yacc.c:1646  */
    {
              if ((yyvsp[0].atributos).tipo != BOOLEAN){
                ////printf("\nPETA AQUI");
                errorSemantico("Bucle con condicion de tipo int");
                return -1;
              }
              (yyval.atributos).etiqueta = (yyvsp[-1].atributos).etiqueta;
              while_exp_pila(yyout, (yyvsp[0].atributos).es_direccion, (yyvsp[-1].atributos).etiqueta);
            }
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 522 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).etiqueta = etiqueta;
        while_inicio(yyout, etiqueta);
      }
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 528 "alfa.y" /* yacc.c:1646  */
    {
            if (ambito == 0){
              simbol = UsoGlobal(TGLOBAL, (yyvsp[0].atributos).lexema);
              if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                char err[MAX_ERR_LEN];
                sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[0].atributos).lexema);
                errorSemantico(err);
                return -1;
              }
              else{                                       // Si lo busca en global y lo encuentra
                if (CategoriaSimbolo(simbol) == FUNCION){
                  errorSemantico("Lectura incompatible");
                  return -1;
                }
                if (getCategoria(simbol) == VECTOR){
                  errorSemantico("Lectura incompatible");
                  return -1;
                }
              }
            }
            else{                                           // Búsqueda en local
              simbol = UsoLocal(TGLOBAL, TLOCAL, (yyvsp[0].atributos).lexema);
              if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                char err[MAX_ERR_LEN];
                sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[0].atributos).lexema);
                errorSemantico(err);
                return -1;
              }
              else{                                       // Si lo busca en local y lo encuentra
                if (CategoriaSimbolo(simbol) == FUNCION){
                  errorSemantico("Lectura incompatible");
                  return -1;
                }
                if (getCategoria(simbol) == VECTOR){
                  errorSemantico("Lectura incompatible");
                  return -1;
                }
              }
            }
            leer(yyout, (yyvsp[0].atributos).lexema, (yyvsp[0].atributos).tipo);
            fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador>\n");
          }
#line 2069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 571 "alfa.y" /* yacc.c:1646  */
    {
                              escribir(yyout, (yyvsp[0].atributos).es_direccion, (yyvsp[0].atributos).tipo);
                              fprintf(yyout, ";R56:\t<escritura> ::= printf <exp>\n");}
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 576 "alfa.y" /* yacc.c:1646  */
    {
                    if (ambito == 0){
                      errorSemantico("Sentencia de retorno fuera del cuerpo de una función");
                      return -1;
                    }

                    hayReturn = 1;
                    tipoReturn = (yyvsp[0].atributos).tipo;
                    //printf("\nTRICK 7");
                    retornarFuncion(yyout, (yyvsp[0].atributos).es_direccion);
                    fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp>\n");
                  }
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 590 "alfa.y" /* yacc.c:1646  */
    {
        if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        sumar(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp>\n");
      }
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 601 "alfa.y" /* yacc.c:1646  */
    {
        if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        restar(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp>\n");
      }
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 612 "alfa.y" /* yacc.c:1646  */
    {
        if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        dividir(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp>\n");
      }
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 623 "alfa.y" /* yacc.c:1646  */
    {
        if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        multiplicar(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp>\n");
      }
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 634 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].atributos).tipo != INT){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        cambiar_signo(yyout, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R76:\t<exp> ::= - <exp>\n");
      }
#line 2169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 647 "alfa.y" /* yacc.c:1646  */
    {
        if ( ((yyvsp[-2].atributos).tipo != BOOLEAN) || ((yyvsp[0].atributos).tipo != BOOLEAN) ){
          errorSemantico("Operacion logica con operandos int");
          return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        y(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp>\n");
      }
#line 2184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 658 "alfa.y" /* yacc.c:1646  */
    {
        if ( ((yyvsp[-2].atributos).tipo != BOOLEAN) || ((yyvsp[0].atributos).tipo != BOOLEAN) ){
          errorSemantico("Operacion logica con operandos int");
          return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        o(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp>\n");
      }
#line 2199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 669 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].atributos).tipo != BOOLEAN){
          errorSemantico("Operacion logica con operandos boolean");
          return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        no(yyout, (yyvsp[0].atributos).es_direccion, 1);
        fprintf(yyout, ";R79:\t<exp> ::= ! <exp>\n");
      }
#line 2214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 681 "alfa.y" /* yacc.c:1646  */
    {
        if (ambito == 0){
          simbol = UsoGlobal(TGLOBAL, (yyvsp[0].atributos).lexema);
          if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
            char err[MAX_ERR_LEN];
            sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[0].atributos).lexema);
            errorSemantico(err);
            return -1;
          }
          else{                                       // Si lo busca en global y lo encuentra
            if (CategoriaSimbolo(simbol) == FUNCION){
              errorSemantico("Expresion incompatible");
              return -1;
            }
            if (getCategoria(simbol) == VECTOR){
              errorSemantico("Expresion incompatible");
              return -1;
            }

            (yyval.atributos).tipo = getTipo(simbol);
            (yyval.atributos).es_direccion = 1;
          }
          printf("\nESCRIBIR Normal %s, valor %d\n", (yyvsp[0].atributos).lexema, (yyvsp[0].atributos).valor_entero);
          if(en_explist){
            char val[MAX_INT_LEN];
            sprintf(val, "%d", (yyvsp[0].atributos).valor_entero);
            escribir_operando(yyout, val, CTE);
            printf("\nOperando %s con pos %d y con valor %d a pila", getIdentificador(simbol), getPosicion(simbol), (yyvsp[0].atributos).valor_entero);
            operandoEnPilaAArgumento(yyout, getPosicion(simbol));
          }
          else{
            escribir_operando(yyout, (yyvsp[0].atributos).lexema, VAR);
          }
        }
        else{                                           // Búsqueda en local
          simbol = UsoLocal(TGLOBAL, TLOCAL, (yyvsp[0].atributos).lexema);
          if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
            char err[MAX_ERR_LEN];
            sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[0].atributos).lexema);
            errorSemantico(err);
            return -1;
          }
          else{                                       // Si lo busca en local y lo encuentra
            if (CategoriaSimbolo(simbol) == FUNCION){
              errorSemantico("Expresion incompatible");
              return -1;
            }
            if (getCategoria(simbol) == VECTOR){
              errorSemantico("Expresion incompatible");
              return -1;
            }
            (yyval.atributos).tipo = getTipo(simbol);
            (yyval.atributos).es_direccion = 1;
          }
          int pos;
          pos = getPosicion(simbol); //Posicion tanto si Parametro como var Local
          ////printf("\nPOS == %d\n", pos);
          if(CategoriaSimbolo(simbol) == PARAMETRO){
            ////printf("\nTRICK 1 escribiendo parametro de pos = %d\n", pos);
            //printf("\nTrick 2");
            printf("\nEscribir parametro %s con pos %d y valor %d", getIdentificador(simbol), pos, getValor(simbol));
            escribirParametro(yyout, pos, getNum_parametros(UsoLocal(TGLOBAL, TLOCAL, nombre_funcion_actual) ));
          }
          else{
            //printf("\nTrick 3.5");
            escribirVariableLocal(yyout, pos);
            }
        }
        ////printf("\nTRICK 1 writing operando %s\n", $1.lexema);

        fprintf(yyout, ";R80:\t<exp> ::= <identificador>\n");
      }
#line 2291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 753 "alfa.y" /* yacc.c:1646  */
    {(yyval.atributos).tipo = (yyvsp[0].atributos).tipo; (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion; (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
                     fprintf(yyout, ";R81:\t<exp> ::= <constante>\n");}
#line 2298 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 755 "alfa.y" /* yacc.c:1646  */
    {(yyval.atributos).tipo = (yyvsp[-1].atributos).tipo; (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
                                                        fprintf(yyout, ";R82:\t<exp> ::= ( <exp> )\n");}
#line 2305 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 757 "alfa.y" /* yacc.c:1646  */
    {
                                                                (yyval.atributos).tipo = (yyvsp[-1].atributos).tipo; (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
                                                                fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> )\n");}
#line 2313 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 760 "alfa.y" /* yacc.c:1646  */
    {(yyval.atributos).tipo = (yyvsp[0].atributos).tipo; (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion; fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector>\n");}
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 762 "alfa.y" /* yacc.c:1646  */
    {
        if (ambito == 0){
          simbol = UsoGlobal(TGLOBAL, (yyvsp[-3].atributos).lexema);
          if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
            char err[MAX_ERR_LEN];
            sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[-3].atributos).lexema);
            errorSemantico(err);
            return -1;
          }
          printf("\nLLamando a funcion %s con %d params\n", getIdentificador(simbol), getNum_parametros(simbol));
          llamarFuncion(yyout, getIdentificador(simbol), getNum_parametros(simbol));
        }

        else{                                           // Búsqueda en local
          simbol = UsoLocal(TGLOBAL, TLOCAL, (yyvsp[-3].atributos).lexema);
          if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
            char err[MAX_ERR_LEN];
            sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[-3].atributos).lexema);
            errorSemantico(err);
            return -1;
          }
        }

        if (num_parametros_llamada_actual != getNum_parametros(simbol)){
            errorSemantico("Numero incorrecto de parametros en llamada a funcion");
            return -1;
        }

        // Reseteamos variable para controlar llamada a func desde una llamada
        en_explist = 0;

        (yyval.atributos).tipo = getTipo(simbol);
        (yyval.atributos).es_direccion = 0;

        fprintf(yyout, ";R88:\t<exp> ::= id_llamada_funcion ( <lista_expresiones> )\n");
      }
#line 2360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 801 "alfa.y" /* yacc.c:1646  */
    {
                      if (ambito == 0){
                        simbol = UsoGlobal(TGLOBAL, (yyvsp[0].atributos).lexema);
                        if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                          char err[MAX_ERR_LEN];
                          sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[0].atributos).lexema);
                          errorSemantico(err);
                          return -1;
                        }

                        else{                                       // Si lo busca en global y lo encuentra
                          if (CategoriaSimbolo(simbol) != FUNCION){
                            char err[MAX_ERR_LEN];
                            sprintf(err, "Llamada a funcion %s que no tiene categoria de funcion", (yyvsp[0].atributos).lexema);
                            errorSemantico(err);
                            return -1;
                          }

                        }
                      }
                      else{                                           // Búsqueda en local
                          simbol = UsoLocal(TGLOBAL, TLOCAL, (yyvsp[0].atributos).lexema);
                          if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                              char err[MAX_ERR_LEN];
                              sprintf(err, "Acceso a variable no declarada (%s)", (yyvsp[0].atributos).lexema);
                              errorSemantico(err);
                              return -1;
                          }
                          else{                                       // Si lo busca en local y lo encuentra
                              if (CategoriaSimbolo(simbol) != FUNCION){
                                char err[MAX_ERR_LEN];
                                sprintf(err, "Llamada a funcion %s que no tiene categoria de funcion", (yyvsp[0].atributos).lexema);
                                errorSemantico(err);
                                return -1;
                              }
                          }
                      }

                      if (en_explist == 0){
                        en_explist = 1;
                      }
                      else{
                        errorSemantico("No esta permitido el uso de llamadas a funciones como parametros de otras funciones");
                        return -1;
                      }

                      num_parametros_llamada_actual = 0;
                      strcpy((yyval.atributos).lexema, getIdentificador(simbol) );
                      strcpy(nombre_funcion_actual,  getIdentificador(simbol));
                    }
#line 2415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 853 "alfa.y" /* yacc.c:1646  */
    {
                      num_parametros_llamada_actual++;

                      fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");}
#line 2424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 857 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R90:\t<lista_expresiones> ::= \n");}
#line 2430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 860 "alfa.y" /* yacc.c:1646  */
    {
                            num_parametros_llamada_actual++;

                            fprintf(yyout, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");}
#line 2439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 864 "alfa.y" /* yacc.c:1646  */
    {fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::= \n");}
#line 2445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 867 "alfa.y" /* yacc.c:1646  */
    {
              if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              (yyval.atributos).tipo = BOOLEAN;
              (yyval.atributos).es_direccion = 0;
              ////printf("\nIGUAL: %d == %d", $1.valor_entero, $3.valor_entero);
              cmpOp(yyout, (yyvsp[-2].atributos), (yyvsp[0].atributos), CMP_IGUAL);
              fprintf(yyout, ";R93:\t<comparacion> ::= <exp> == <exp>\n");
              }
#line 2461 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 879 "alfa.y" /* yacc.c:1646  */
    {
              if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              (yyval.atributos).tipo = BOOLEAN;
              (yyval.atributos).es_direccion = 0;
              cmpOp(yyout, (yyvsp[-2].atributos), (yyvsp[0].atributos), CMP_DIST);
              fprintf(yyout, ";R94:\t<comparacion> ::= <exp> != <exp>\n");
              }
#line 2476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 890 "alfa.y" /* yacc.c:1646  */
    {
              if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              (yyval.atributos).tipo = BOOLEAN;
              (yyval.atributos).es_direccion = 0;
              cmpOp(yyout, (yyvsp[-2].atributos), (yyvsp[0].atributos), CMP_MEN_IG);
              fprintf(yyout, ";R95:\t<comparacion> ::= <exp> <= <exp>\n");
              }
#line 2491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 901 "alfa.y" /* yacc.c:1646  */
    {
              if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              (yyval.atributos).tipo = BOOLEAN;
              (yyval.atributos).es_direccion = 0;
              cmpOp(yyout, (yyvsp[-2].atributos), (yyvsp[0].atributos), CMP_MAY_IG);
              fprintf(yyout, ";R96:\t<comparacion> ::= <exp> >= <exp>\n");
              }
#line 2506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 912 "alfa.y" /* yacc.c:1646  */
    {
              if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              (yyval.atributos).tipo = BOOLEAN;
              (yyval.atributos).es_direccion = 0;
              cmpOp(yyout, (yyvsp[-2].atributos), (yyvsp[0].atributos), CMP_MEN);
              fprintf(yyout, ";R97:\t<comparacion> ::= <exp> < <exp>\n");
              }
#line 2521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 923 "alfa.y" /* yacc.c:1646  */
    {
              if ( ((yyvsp[-2].atributos).tipo != INT) || ((yyvsp[0].atributos).tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              (yyval.atributos).tipo = BOOLEAN;
              (yyval.atributos).es_direccion = 0;
              cmpOp(yyout, (yyvsp[-2].atributos), (yyvsp[0].atributos), CMP_MAY);
              fprintf(yyout, ";R98:\t<comparacion> ::= <exp> > <exp>\n");
              }
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 935 "alfa.y" /* yacc.c:1646  */
    {
              (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
              (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
              (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
              fprintf(yyout, ";R99:\t<constante> ::= <constante_logica>\n");
            }
#line 2547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 942 "alfa.y" /* yacc.c:1646  */
    {
              (yyval.atributos).tipo = INT;
              (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
              fprintf(yyout, ";R100:\t<constante> ::= <constante_entera>\n");
            }
#line 2557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 949 "alfa.y" /* yacc.c:1646  */
    {
                    (yyval.atributos).tipo = BOOLEAN;
                    (yyval.atributos).es_direccion = 0;
                    (yyval.atributos).valor_entero = 1;
                    ////printf("\nTRICK 6 writing operando %s\n", STR_TRUE);
                    escribir_operando(yyout,STR_TRUE,CTE);
                    fprintf(yyout, ";R102:\t<constante_logica> ::= true\n");
                  }
#line 2570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 958 "alfa.y" /* yacc.c:1646  */
    {
                      (yyval.atributos).tipo = BOOLEAN;
                      (yyval.atributos).es_direccion = 0;
                      (yyval.atributos).valor_entero = 0;
                      ////printf("\nTRICK 7 writing operando %s\n", STR_FALSE);
                      escribir_operando(yyout,STR_FALSE,CTE);

                      fprintf(yyout, ";R103:\t<constante_logica> ::= false\n");
                    }
#line 2584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 969 "alfa.y" /* yacc.c:1646  */
    {
                      (yyval.atributos).tipo = INT;
                      (yyval.atributos).es_direccion = 0;
                      (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;

                      char val[MAX_INT_LEN];
                      sprintf(val, "%d", (yyvsp[0].atributos).valor_entero);
                      ////printf("\nTRICK 8 writing operando %s\n", val);
                      //printf("\nTrick 5");
                      escribir_operando(yyout,val,CTE);
                      fprintf(yyout, ";R105:\t<constante_entera> ::= <numero>\n");
                    }
#line 2601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 984 "alfa.y" /* yacc.c:1646  */
    {
                            if (ambito == 0){
                                if (clase_actual == VECTOR){      // Estamos declarando un array
                                      sprintf(nombre_vector, "%s", (yyvsp[0].atributos).lexema);  // Guardamos el nombre del array

                                      if (DeclararGlobal(TGLOBAL, (yyvsp[0].atributos).lexema, VARIABLE, tipo_actual, clase_actual, (yyvsp[0].atributos).valor_entero, FALSE, tamanio_vector_actual) == FALSE){     // redeclaración variable global
                                        char err[MAX_ERR_LEN];
                                        sprintf(err, "Declaracion (%s) duplicada", (yyvsp[0].atributos).lexema);
                                        errorSemantico(err);
                                        return -1;
                                      }
                                }
                                else{
                                  if (DeclararGlobal(TGLOBAL, (yyvsp[0].atributos).lexema, VARIABLE, tipo_actual, clase_actual, (yyvsp[0].atributos).valor_entero, FALSE, FALSE) == FALSE){     // redeclaración variable global
                                      char err[MAX_ERR_LEN];
                                      sprintf(err, "Declaracion (%s) duplicada", (yyvsp[0].atributos).lexema);
                                      errorSemantico(err);
                                      return -1;
                                   }
                                  else{
                                        fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
                                        // AQUI VA GENERACION DE CODIGO JEJEJE
                                  }
                                }
                              }

                              else{                           // Ambito local
                                  if (clase_actual != ESCALAR){
                                    errorSemantico("Variable local de tipo no escalar");
                                    return -1;
                                  }

                                  if (DeclararLocal(TLOCAL, (yyvsp[0].atributos).lexema, VARIABLE, tipo_actual, clase_actual,
                                        (yyvsp[0].atributos).valor_entero, FALSE, FALSE, pos_variable_local_actual) == FALSE){     // redeclaración variable local
                                    char err[MAX_ERR_LEN];
                                    sprintf(err, "Declaracion (%s) duplicada", (yyvsp[0].atributos).lexema);
                                    errorSemantico(err);
                                    return -1;
                                  }
                                  else{
                                    pos_variable_local_actual++;
                                    num_variables_locales_actual++;

                                    fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
                                    }
                                }

                                //fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
                            }
#line 2655 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2659 "y.tab.c" /* yacc.c:1646  */
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
#line 1035 "alfa.y" /* yacc.c:1906  */


void yyerror (char *msg)
{
  if(is_morpho == 0) {
    int col2 = col-yyleng;
    fprintf(stderr,"****Error sintactico en [lin %d, col %d]\n", yylineno, col2);
  }

  else{               /** Si hubo un error morfologico, restaura el valor de la variable de control **/
    is_morpho = 0;
  }
}

void errorSemantico (char *msg)
{
  fprintf(stderr,"****Error semantico en lin %d: %s\n", yylineno, msg);
}

int main (int argc, char *argv[]){
  if (argc == 3){
    yyin = fopen(argv[1], "r");
    if (yyin == NULL){
      fprintf (stderr, "El fichero '%s' no se puede abrir\n", argv[1]);
      exit(-1);
    }

    yyout = fopen(argv[2], "w");
    if (yyout == NULL){
      fprintf (stderr, "El fichero '%s' no se puede abrir\n", argv[1]);
      fclose(yyin);
      exit(-1);
    }

    yyparse();

    fclose(yyin);
    fclose(yyout);

    freeHashTable(TGLOBAL);
    exit(1);
  }

  else{
    printf("Error en los parámetros de entrada\t./alfa FILE_IN FILE_OUT\n");
  }

}
