/*********************************************************
**
** Fichero: SEMANTICA.Y
** Autores: Manuel Orantes Taboada, Víctor Bricio Blázquez, Víctor García Carrera.
** Función: Archivo YACC para implementar el traductor.
**
*********************************************************/

%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "semant.h"

/** La siguiente declaracion permite que ’yyerror’ se pueda invocar desde el
*** fuente de lex (tokens.l)
**/

void yyerror(const char *msg);
int yylex();

%}

/** Para uso de mensajes de error sintáctico con BISON.
*** La siguiente declaración provoca que ’bison’, ante un error sintáctico,
*** visualice mensajes de error con indicación de los tokens que se esperaban
*** en el lugar en el que produjo el error.
**/

%error-verbose

/** Declaramos la lista de nombres simbólicos de los tokens de nuestra gramática, junto con su asociatividad y precedencia
**/

%token MAIN RIGHT_PARENTHESIS LEFT_KEY RIGHT_KEY LEFT_BRACKET RIGHT_BRACKET SEMICOLON COMA ASSIGN IF THEN ELSE WHILE RETURN FOR ASSIGN_FOR TO DO OUT IN INITVAR ENDVAR LIST_OF BASIC_TYPES CADENA
%left OR_OP
%left AND_OP
%left XOR_OP
%left EQUALS_OP
%left RELATION_OP
%left SYMBOL_OP
%left BINARY_OP BINARY_LIST_OP_I BINARY_LIST_OP_L
%right NEG
%right COUNT
%right QUEST
%right MINUSMINUS
%right PLUSPLUS
%right DOLLAR LIST_OP
%right AT
%left CONST_INT CONST_DOUBLE CONST_BOOLEAN CONST_CHAR ID
%right LEFT_PARENTHESIS

%%

/** Declaramos el conjunto de reglas o producciones que definen nuestra gramática junto con una serie de acciones asociadas a las mismas
**/

Programa : Cabecera_programa bloque;
Cabecera_programa : MAIN LEFT_PARENTHESIS argumentos RIGHT_PARENTHESIS;
bloque	 : LEFT_KEY {TS_AddMark();} inbloque RIGHT_KEY
					{TS_CleanBlock();};
inbloque : Declar_de_variables_locales Declar_de_subprogs Sentencias
	 			 | Declar_de_variables_locales Declar_de_subprogs;
Declar_de_subprogs  : Declar_de_subprogs Declar_subprog
                    | ;
Declar_subprog      : Cabecera_subprograma {esFunc = 1;} bloque {esFunc = 0;};

Declar_de_variables_locales : INITVAR {decVar = 1;} Variables_locales ENDVAR { decVar = 0;}
			                | ;
Variables_locales	: Variables_locales Cuerpo_declar_variables
			| Cuerpo_declar_variables ;
Cuerpo_declar_variables : tipo {getType($1);} list_id SEMICOLON
						| error ;
Cabecera_subprograma : tipo ID {getType($1);} {decParam = 1;} {TS_AddFunction($2);} LEFT_PARENTHESIS argumentos RIGHT_PARENTHESIS {decParam = 0;};
argumentos  : argumentos COMA argumento
	        | argumento
	        |
			    | error ;
argumento : tipo ID {getType($1);} {TS_AddParam($2);};
Sentencias  : Sentencias {decVar = 2;} Sentencia
            | {decVar = 2;} Sentencia ;
Sentencia   : bloque
	    | sentencia_contador
            | sentencia_asignacion
            | sentencia_if
            | sentencia_while
            | sentencia_entrada
            | sentencia_salida
            | sentencia_return
            | sentencia_for
            | sentencia_list;

sentencia_contador	: PLUSPLUS expresion SEMICOLON
                    {if ($2.type == BOOLEAN || $2.type == CHAR  || $2.type == LIST_INT || $2.type == LIST_DOUBLE || $2.type == LIST_CHAR || $2.type == LIST_BOOLEAN)
                        printf("Semantic Error(%d): Type not increaseable.\n", line);
                    $$.type = $2.type;}
			              | MINUSMINUS expresion SEMICOLON
                    {if ($2.type == BOOLEAN || $2.type == CHAR || $2.type == LIST_INT || $2.type == LIST_DOUBLE || $2.type == LIST_CHAR || $2.type == LIST_BOOLEAN)
                        printf("Semantic Error(%d): Type not decrementacle.\n", line);
                    $$.type = $2.type;}
			              | expresion PLUSPLUS SEMICOLON
                    {if ($1.type == BOOLEAN || $1.type == CHAR || $1.type == LIST_INT || $2.type == LIST_DOUBLE || $2.type == LIST_CHAR || $2.type == LIST_BOOLEAN)
                        printf("Semantic Error(%d): Type not increaseable.\n", line);
                    $$.type = $1.type;}
			              | expresion MINUSMINUS SEMICOLON
                    {if ($1.type == BOOLEAN || $1.type == CHAR || $1.type == LIST_INT || $2.type == LIST_DOUBLE || $2.type == LIST_CHAR || $2.type == LIST_BOOLEAN)
                        printf("Semantic Error(%d): Type not decrementable.\n", line);
                    $$.type = $1.type;};
sentencia_asignacion  : ID ASSIGN expresion SEMICOLON
                      {if (TSGetId($1) != $3.type) printf("Semantic Error(%d): Types are not equal.\n",line );};
sentencia_if  : IF LEFT_PARENTHESIS expresion RIGHT_PARENTHESIS THEN Sentencia
              {if ($3.type != BOOLEAN)
                  printf("Semantic Error(%d): Expression are not logic.\n", line);}
              | IF LEFT_PARENTHESIS expresion RIGHT_PARENTHESIS THEN Sentencia ELSE Sentencia
              {if ($3.type != BOOLEAN)
                  printf("Semantic Error(%d): Expression are not logic.\n", line);};
sentencia_while : WHILE LEFT_PARENTHESIS expresion RIGHT_PARENTHESIS Sentencia
                {if ($3.type != BOOLEAN)
                    printf("Semantic Error(%d): Expression are not logic.\n", line);};
sentencia_entrada : IN CADENA list_id SEMICOLON
		          | IN list_id SEMICOLON;
sentencia_salida  : OUT list_expresiones_o_cadena SEMICOLON ;
sentencia_return  : RETURN expresion {TS_CheckReturn($2,&$$);} SEMICOLON ;
sentencia_for 	: FOR ID ASSIGN_FOR constante TO constante DO bloque;
sentencia_list  : expresion LIST_OP
                | DOLLAR expresion ;

expresion : NEG expresion
          {if ($2.type != BOOLEAN)
              printf("Semantic Error(%d): Expression are not logic.\n", line);
          $$.type = $2.type;}
          | COUNT expresion
          {if ($2.type != LIST_INT && $2.type != LIST_DOUBLE && $2.type != LIST_BOOLEAN && $2.type != LIST_CHAR)
              printf("Semantic Error(%d): Expression is not a list.\n", line);
          $$.type = INT;}
          | QUEST expresion
          {if ($2.type != LIST_INT && $2.type != LIST_DOUBLE && $2.type != LIST_BOOLEAN && $2.type != LIST_CHAR)
              printf("Semantic Error(%d): Types not operable.\n", line);
          if ($2.type == LIST_INT)
              $$.type = INT;
          else if ($2.type == LIST_DOUBLE)
              $$.type = DOUBLE;
          else if ($2.type == LIST_BOOLEAN)
              $$.type = BOOLEAN;
          else if ($2.type == LIST_CHAR)
              $$.type = CHAR;}
          | SYMBOL_OP expresion %prec NEG
          {if ($2.type == BOOLEAN || $2.type == CHAR || $2.type == LIST_INT || $2.type == LIST_DOUBLE || $2.type == LIST_CHAR || $2.type == LIST_BOOLEAN)
              printf("Semantic Error(%d): Type not signable.\n", line);
          $$.type = $2.type;}
          | expresion SYMBOL_OP expresion
          {int res = INT;
					if ($1.type == BOOLEAN || $3.type == BOOLEAN || $1.type == CHAR || $3.type == CHAR
					|| $1.type == LIST_CHAR || $3.type == LIST_CHAR || $1.type == LIST_BOOLEAN || $3.type == LIST_BOOLEAN)
              printf("Semantic Error(%d): Types not operable.\n", line);
          if ($3.type == LIST_INT || $3.type == LIST_DOUBLE)
              printf("Semantic Error(%d): Types not operable.\n", line);
          if ($1.type == DOUBLE || $3.type == DOUBLE)
            res = DOUBLE;
          if (($1.type == LIST_INT && $3.type == INT) ||($1.type == LIST_DOUBLE && $3.type == DOUBLE) )
            res = $1.type;
					$$.type = res;}
          | expresion BINARY_OP expresion
					{int res = INT;
                
					if ($1.type == BOOLEAN || $3.type == BOOLEAN || $1.type == CHAR  || $3.type == CHAR
					|| $1.type == LIST_BOOLEAN || $3.type == LIST_BOOLEAN || $1.type == LIST_CHAR || $3.type == LIST_CHAR)
              printf("Semantic Error(%d): Types not operable.\n", line);
           if (($1.type == LIST_INT || $1.type == LIST_DOUBLE || $1.type == LIST_BOOLEAN || $1.type == LIST_CHAR)
              && ($3.type == LIST_INT || $3.type == LIST_DOUBLE || $3.type == LIST_BOOLEAN || $3.type == LIST_CHAR))
              printf("Semantic Error(%d): Types not operable.\n", line);
          if ($1.type == DOUBLE || $3.type == DOUBLE)
            res = DOUBLE;
          if ($1.type == LIST_INT && $3.type == INT)
            res = $1.type;
          if ($3.type == LIST_DOUBLE && $3.type == DOUBLE)
            res = $3.type;
          if ($3.type == LIST_INT && $3.type == DOUBLE) printf("Semantic Error(%d): Types not operable.\n", line);
          if ($3.type == LIST_DOUBLE && $3.type == INT) printf("Semantic Error(%d): Types not operable.\n", line);
					$$.type = res;}
          | expresion BINARY_LIST_OP_I expresion
          {if (($1.type == LIST_INT && $3.type == INT) || ($1.type == LIST_DOUBLE && $3.type == DOUBLE)){}
					else
          	printf("Semantic Error(%d): Types not operable.\n", line);
          $$.type = $1.type;}
          | expresion BINARY_LIST_OP_L expresion
          {if ($1.type == $3.type){
							//printf("%d\n", $1.type);
              if ($1.type == LIST_INT || $1.type == LIST_DOUBLE || $1.type == LIST_BOOLEAN || $1.type == LIST_CHAR) {
                $$.type = $1.type;
								}
              else
                printf("Semantic Error(%d): Types not operable.\n", line);
                }
          else
            printf("Semantic Error(%d): Types not operable.\n", line);}
          | expresion AND_OP expresion
          {if ($1.type != BOOLEAN && $3.type != BOOLEAN)
              printf("Semantic Error(%d): Expression are not logic.\n", line);
          $$.type = BOOLEAN;}
          | expresion OR_OP expresion
          {if ($1.type != BOOLEAN && $3.type != BOOLEAN)
              printf("Semantic Error(%d): Expression are not logic.\n", line);
          $$.type = BOOLEAN;}
          | expresion XOR_OP expresion
          {if ($1.type != BOOLEAN && $3.type != BOOLEAN)
              printf("Semantic Error(%d): Expression are not logic.\n", line);
          $$.type = BOOLEAN;}
          | expresion RELATION_OP expresion
          {int tipoizq = $1.type;
					int tipodrch = $3.type;
					if (tipoizq == BOOLEAN || tipodrch == BOOLEAN || tipoizq == CHAR || tipodrch == CHAR
              || tipoizq == LIST_INT || tipoizq == LIST_DOUBLE || tipoizq == LIST_BOOLEAN || tipoizq == LIST_CHAR
              || tipodrch == LIST_INT || tipodrch == LIST_DOUBLE || tipodrch == LIST_BOOLEAN || tipodrch == LIST_CHAR)
              printf("Semantic Error(%d): Types not comparable, izquierda: %d, derecha %d.\n",line, $1.type, $3.type);
          $$.type = BOOLEAN;}
          | expresion EQUALS_OP expresion
          {if ($1.type != $3.type)
              printf("Semantic Error(%d): Types not comparable.\n", line);
          $$.type = BOOLEAN;}
          | expresion AT expresion
          {if ($1.type != LIST_INT && $1.type != LIST_DOUBLE && $1.type != LIST_BOOLEAN && $1.type != LIST_CHAR
              && $3.type != INT)
              printf("Semantic Error(%d): Types not operable.\n", line);
          if ($1.type == INT)
              $$.type = INT;
          else if ($1.type == DOUBLE)
              $$.type = DOUBLE;
          else if ($1.type == BOOLEAN)
              $$.type = BOOLEAN;
          else if ($1.type == CHAR)
              $$.type = CHAR;}
          | expresion MINUSMINUS expresion
          {if ($1.type != LIST_INT && $1.type != LIST_DOUBLE && $1.type != LIST_BOOLEAN && $1.type != LIST_CHAR
              && $3.type != INT)
              printf("Semantic Error(%d): Types not operable.\n", line);
          $$.type = $1.type;}
          | ID                {TS_GetId($1, &$$);}
          | constante         {$$.type = $1.type;}
          | funcion           {$$.type = $1.type;}
          | expresion PLUSPLUS expresion AT AT expresion
          {if ($1.type != LIST_INT && $1.type != LIST_DOUBLE && $1.type != LIST_BOOLEAN && $1.type != LIST_CHAR
                && $3.type != INT && $6.type != INT)
              printf("Semantic Error(%d): Types not operable.\n", line);
          $$.type = $1.type;}
	      | LEFT_PARENTHESIS expresion RIGHT_PARENTHESIS   {$$.type = $2.type;}
	      | error ;

funcion         : cabecera_func argumentos_func;
cabecera_func   : ID LEFT_PARENTHESIS {checkFunct = TS_FindByName($1);
                    if(checkFunct == -1) printf("Semantic Error(%d): Function %s not declared\n", line, $1.name);};
argumentos_func : list_expresiones RIGHT_PARENTHESIS { TS_FunctionCall(&$$);}
                | RIGHT_PARENTHESIS { TS_FunctionCall(&$$);};

list_expresiones_o_cadena : list_expresiones_o_cadena COMA exp_cad
                          | exp_cad;
exp_cad                   : expresion
                          | CADENA ;
constante                 : CONST_INT                       {$$.type = INT;}
                          | CONST_DOUBLE                    {$$.type = DOUBLE;}
                          | CONST_CHAR                      {$$.type = CHAR;}
                          | CONST_BOOLEAN                   {$$.type = BOOLEAN;}
                          | const_list_int
                          | const_list_double
                          | const_list_boolean
                          | const_list_char;
list_expresiones          : list_expresiones COMA expresion { TS_CheckParam($3);}
                          | expresion { checkparam = 0; TS_CheckParam($1);};
tipo                      : BASIC_TYPES
													{if ($1.type == INT)
															$$.type = INT;
													else if ($1.type == DOUBLE)
															$$.type = DOUBLE;
													else if ($1.type == CHAR)
															$$.type = CHAR;
													else if ($1.type == BOOLEAN)
															$$.type = BOOLEAN;}
                          | LIST_OF BASIC_TYPES
													{if ($2.type == INT)
															$$.type = LIST_INT;
													else if ($2.type == DOUBLE)
															$$.type = LIST_DOUBLE;
													else if ($2.type == CHAR)
															$$.type = LIST_CHAR;
													else if ($2.type == BOOLEAN)
															$$.type = LIST_BOOLEAN;};

const_list_int  : LEFT_BRACKET list_int RIGHT_BRACKET {$$.type = LIST_INT;};

list_int  : list_int COMA CONST_INT
          | CONST_INT ;

const_list_double  : LEFT_BRACKET list_double RIGHT_BRACKET {$$.type = LIST_DOUBLE;};
list_double  : list_double COMA CONST_DOUBLE
             | CONST_DOUBLE ;

const_list_boolean  : LEFT_BRACKET list_boolean RIGHT_BRACKET {$$.type = LIST_BOOLEAN;};
list_boolean  : list_boolean COMA CONST_BOOLEAN
              | CONST_BOOLEAN ;

const_list_char  : LEFT_BRACKET list_char RIGHT_BRACKET {$$.type = LIST_CHAR;};
list_char  : list_char COMA CONST_CHAR
           | CONST_CHAR ;

list_id   : list_id COMA ID
					{if (decVar == 1)
						TS_AddVar($3);
					else
						if (decParam == 0)
							TS_GetId($3, &$$);}
          | ID
					{if (decVar == 1)
						TS_AddVar($1);
					else
						if (decParam == 0)
							TS_GetId($1, &$$);}
          | list_id error ID;


%%


#ifdef DOSWINDOWS
#include "lexyy.c"
#else
#include "lex.yy.c"
#endif

/** Implementamos la función yyerror. En este caso
*** simplemente escribimos el mensaje de error en pantalla
**/

/** Utilizamos la variable ’yylineno’ que nos muestra la línea actual. Para ello es necesario
*** invocar a lex con la opción ’-l’.
**/

void yyerror (const char *msg)
{
  fprintf(stderr,"GRAMMAR ERR[Line %d]: %s\n", yylineno, msg);
}
