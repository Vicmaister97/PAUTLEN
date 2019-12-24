/*********************************************************
**
** Fichero: ALFA.Y
** Autores: Alfonso Carvajal, Víctor García.
** Función: Archivo YACC para implementar el compilador de la
**          asignatura Proyecto de Procesadores de Lenguajes.
**
*********************************************************/

%{
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

%}

%code requires {
  #include "alfa.h"

}
%union
{
  tipo_atributos atributos;
}

%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN

%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_MAS TOK_MENOS
%token TOK_ASTERISCO TOK_DIVISION
%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR

/* Tokens con valor semántico */

%token <atributos> TOK_IDENTIFICADOR
%token <atributos> TOK_CONSTANTE_ENTERA

%token TOK_TRUE
%token TOK_FALSE

%left TOK_IGUAL TOK_DISTINTO TOK_MENORIGUAL TOK_MAYORIGUAL TOK_MENOR TOK_MAYOR
%left TOK_AND TOK_OR
%left TOK_MAS TOK_MENOS
%left TOK_ASTERISCO TOK_DIVISION

%right TOK_NOT


/* Simbolos no terminales con valor semántico */

%type <atributos> identificadores
%type <atributos> identificador
%type <atributos> tipo

%type <atributos> exp
%type <atributos> comparacion
%type <atributos> constante
%type <atributos> constante_logica
%type <atributos> constante_entera
%type <atributos> elemento_vector

%type <atributos> funcion
%type <atributos> fn_name
%type <atributos> fn_declaration
%type <atributos> idf_llamada_funcion
%type <atributos> if_exp
%type <atributos> if_else_exp
%type <atributos> while
%type <atributos> bucle_exp
%type <atributos> bucle


%%


programa: inicioTabla TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones escritura_TS funciones end_funciones sentencias TOK_LLAVEDERECHA { escribir_fin(yyout);
        }
        ;

inicioTabla:{
              /* Acciones de inicialización de la tabla de símbolos */
              TGLOBAL = newHashTable();       // Tabla hash que almacena los símbolos de ámbito global
            }

escritura_TS:{
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

end_funciones:{
                escribir_inicio_main(yyout);
              }


declaraciones:  declaracion {fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion>\n");}
             |  declaracion declaraciones {fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");}
             ;
declaracion:  clase identificadores TOK_PUNTOYCOMA
              {
                if (errorVector == 1){
                  errorVector = 0;
                  char err[MAX_ERR_LEN];
                  sprintf(err, "El tamanyo del vector <%s> excede los limites permitidos (1,64)", $2.lexema);
                  errorSemantico(err);
                  return -1;
                }
                fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");
              }
            ;
clase:  clase_escalar {clase_actual=ESCALAR; fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar>\n");}
     |  clase_vector {clase_actual=VECTOR; fprintf(yyout, ";R7:\t<clase> ::= <clase_vector>\n");}
     ;
clase_escalar:  tipo {fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo>\n");}
             ;
tipo:  TOK_INT {tipo_actual=INT; fprintf(yyout, ";R10:\t<tipo> ::= int\n");}
    |  TOK_BOOLEAN {tipo_actual=BOOLEAN; fprintf(yyout, ";R11:\t<tipo> ::= boolean\n");}
    ;
clase_vector:  TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO
                {
                  tamanio_vector_actual = $4.valor_entero;
                  if ( (tamanio_vector_actual < 1) || (tamanio_vector_actual > MAX_TAMANIO_VECTOR) ){
                    errorVector = 1;
                  }
                  fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ constante_entera ]\n");
                }
            ;
identificadores:  identificador {fprintf(yyout, ";R18:\t<identificadores> ::= <identificador>\n");}
               |  identificador TOK_COMA identificadores {fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");}
               ;
funciones:  funcion funciones {fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones>\n");}
         |  {fprintf(yyout, ";R21:\t<funciones> ::= \n");}
         ;
funcion:  fn_declaration sentencias TOK_LLAVEDERECHA
          {
            // CHECKKKKK !!!!!!!!

            simbol = UsoGlobal(TGLOBAL, $1.lexema);
              if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                char err[MAX_ERR_LEN];
                sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
                errorSemantico(err);
                return -1;
              }

            if (hayReturn == 0){
              char err[MAX_ERR_LEN];
              sprintf(err, "Función %s sin sentencia de retorno", $1.lexema);
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

            strcpy($$.lexema, $1.lexema);

            freeHashTable(TLOCAL);

            fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");
          }
       ;
fn_name:  TOK_FUNCTION tipo TOK_IDENTIFICADOR
          {
            TLOCAL = newHashTable();    // Inicializamos la tabla local
            if (DeclararFuncion(TGLOBAL, TLOCAL, $3.lexema, FUNCION, tipo_actual, $3.valor_entero, FALSE, FALSE) == FALSE){
              char err[MAX_ERR_LEN];
              sprintf(err, "Declaracion (%s) duplicada", $3.lexema);
              errorSemantico(err);
              return -1;
            }
            // Inicializamos variables para la funcion
            num_variables_locales_actual = 0;
            pos_variable_local_actual = 1;      // Hemos insertado la funcion
            num_parametros_actual = 0;
            pos_parametro_actual = 0;

            strcpy($$.lexema, $3.lexema);
            strcpy(nombre_funcion_actual, $3.lexema);
          }
        ;
fn_declaration:  fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion
                  {
                    simbol = UsoLocal(TGLOBAL, TLOCAL, $1.lexema);
                    if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                        char err[MAX_ERR_LEN];
                        sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
                        errorSemantico(err);
                        return -1;
                    }

                    setNum_parametros(simbol, num_parametros_actual);
                    setNum_var_locales(simbol, num_variables_locales_actual);
                    strcpy($$.lexema, $1.lexema);
                    printf("\nDeclarar funcion: %s con %d varLoc", $1.lexema, num_variables_locales_actual);
                    declararFuncion(yyout, $1.lexema, num_variables_locales_actual);
                  }
              ;
parametros_funcion:  parametro_funcion resto_parametros_funcion {fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
                  |  {fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n");}
                  ;
resto_parametros_funcion:  TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion
                            {fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
                        |  {fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n");}
                        ;
parametro_funcion:  clase idpf {fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <idpf>\n");}
                 ;
idpf:  TOK_IDENTIFICADOR
        {
          if (DeclararLocal(TLOCAL, $1.lexema, PARAMETRO, tipo_actual, clase_actual,
                                        $1.valor_entero, FALSE, FALSE, pos_parametro_actual) == FALSE){     // redeclaración variable local
            char err[MAX_ERR_LEN];
            sprintf(err, "Declaracion (%s) duplicada", $1.lexema);
            errorSemantico(err);
            return -1;
          }
          else{
            pos_parametro_actual++;
            num_parametros_actual++;
          }
        }
declaraciones_funcion:  declaraciones {fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}
                     |  {fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");}
                     ;
sentencias:  sentencia {fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia>\n");}
          |  sentencia sentencias {fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}
          ;
sentencia:  sentencia_simple TOK_PUNTOYCOMA {fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
         |  bloque {fprintf(yyout, ";R33:\t<sentencia> ::= <bloque>\n");}
         ;
sentencia_simple:  asignacion {fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}
                |  lectura {fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura>\n");}
                |  escritura {fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura>\n");}
                |  retorno_funcion {fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}
                ;
bloque:  condicional {fprintf(yyout, ";R40:\t<bloque> ::= <condicional>\n");}
      |  bucle {fprintf(yyout, ";R41:\t<bloque> ::= <bucle>\n");}
      ;
asignacion:  TOK_IDENTIFICADOR TOK_ASIGNACION exp
             {
                if (ambito == 0){
                  simbol = UsoGlobal(TGLOBAL, $1.lexema);
                  if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                    char err[MAX_ERR_LEN];
                    sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
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
                        if (getTipo(simbol) != $3.tipo){
                          errorSemantico("Asignación incompatible");
                          return -1;
                        }
                    }
                    printf("\nAsignando a %s el valor %d, es DIR: %d", $1.lexema, $3.valor_entero, $3.es_direccion);
                    asignar(yyout, $1.lexema, $3.es_direccion);
                }
                else{                                           // Búsqueda en local
                    simbol = UsoLocal(TGLOBAL, TLOCAL, $1.lexema);
                    if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                        char err[MAX_ERR_LEN];
                        sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
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
                        if (getTipo(simbol) != $3.tipo){
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
                    asignarDestinoEnPila(yyout, $3.es_direccion);
                }
                fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
             }
          |  elemento_vector TOK_ASIGNACION exp
              {
                if ($1.tipo != $3.tipo){
                  errorSemantico("Asignación incompatible");
                  return -1;
                }
                asignarDestinoEnPilaINV(yyout, 0);

                fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");
              }
          ;
elemento_vector:  TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO
                  {
                    if (ambito == 0){
                      simbol = UsoGlobal(TGLOBAL, $1.lexema);
                      if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                        char err[MAX_ERR_LEN];
                        sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
                        errorSemantico(err);
                        return -1;
                      }
                      else{                                       // Si lo busca en global y lo encuentra
                        if (getCategoria(simbol) != VECTOR){
                          errorSemantico("Intento de indexacion de una variable que no es de tipo vector");
                          return -1;
                        }
                        if ($3.tipo != INT){
                          errorSemantico("El indice en una operacion de indexacion tiene que ser de tipo entero");
                          return -1;
                        }
                        $$.tipo = getTipo(simbol);
                        $$.es_direccion = 1;
                      }
                    }

                    else{                                           // Búsqueda en local
                      simbol = UsoLocal(TGLOBAL, TLOCAL, $1.lexema);
                      if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                        char err[MAX_ERR_LEN];
                        sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
                        errorSemantico(err);
                        return -1;
                      }

                      else{                                       // Si lo busca en global y lo encuentra
                        if (getCategoria(simbol) != VECTOR){
                          errorSemantico("Intento de indexacion de una variable que no es de tipo vector");
                          return -1;
                        }
                        if ($3.tipo != INT){
                          errorSemantico("El indice en una operacion de indexacion tiene que ser de tipo entero");
                          return -1;
                        }
                        $$.tipo = getTipo(simbol);
                        $$.es_direccion = 1;
                      }
                    }
                    fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");
                    escribir_elemento_vector(yyout, $1.lexema, getLongitud(simbol), $3.es_direccion);

                  }
               ;
condicional:  if_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA
              {
                ////printf("\nFIN GLOBAL = %d\nETIQUETA SEM = %d\n", etiqueta, $1.etiqueta);
                ifthen_fin(yyout, $1.etiqueta);
                fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");
              }
           |   if_else_exp TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA
              {
                ifthenelse_fin(yyout, $1.etiqueta);
                fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");
              }
           ;
if_exp:  TOK_IF TOK_PARENTESISIZQUIERDO exp
          {
            if ($3.tipo != BOOLEAN){
              errorSemantico("Condicional con condicion de tipo int");
              return -1;
            }
            $$.etiqueta = etiqueta;
            ifthen_inicio(yyout, $3.es_direccion, etiqueta);
            ////printf("\nINI GLOBAL = %d\nETIQUETA SEM = %d\n", etiqueta, $$.etiqueta);
          }
      ;
if_else_exp: if_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA
          {
            $$.etiqueta = $1.etiqueta;
            ifthenelse_fin_then(yyout, $1.etiqueta);
          }
      ;
bucle:  bucle_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA
      {
        while_fin(yyout, $1.etiqueta);
        fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
      }
     ;
bucle_exp:  while exp
            {
              if ($2.tipo != BOOLEAN){
                ////printf("\nPETA AQUI");
                errorSemantico("Bucle con condicion de tipo int");
                return -1;
              }
              $$.etiqueta = $1.etiqueta;
              while_exp_pila(yyout, $2.es_direccion, $1.etiqueta);
            }
         ;

while: TOK_WHILE TOK_PARENTESISIZQUIERDO
      {
        $$.etiqueta = etiqueta;
        while_inicio(yyout, etiqueta);
      }
    ;
lectura:  TOK_SCANF TOK_IDENTIFICADOR
          {
            if (ambito == 0){
              simbol = UsoGlobal(TGLOBAL, $2.lexema);
              if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                char err[MAX_ERR_LEN];
                sprintf(err, "Acceso a variable no declarada (%s)", $2.lexema);
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
              simbol = UsoLocal(TGLOBAL, TLOCAL, $2.lexema);
              if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                char err[MAX_ERR_LEN];
                sprintf(err, "Acceso a variable no declarada (%s)", $2.lexema);
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
            leer(yyout, $2.lexema, $2.tipo);
            fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador>\n");
          }
       ;
escritura:  TOK_PRINTF exp {
                              escribir(yyout, $2.es_direccion, $2.tipo);
                              fprintf(yyout, ";R56:\t<escritura> ::= printf <exp>\n");}
        ;
retorno_funcion:  TOK_RETURN exp
                  {
                    if (ambito == 0){
                      errorSemantico("Sentencia de retorno fuera del cuerpo de una función");
                      return -1;
                    }

                    hayReturn = 1;
                    tipoReturn = $2.tipo;
                    //printf("\nTRICK 7");
                    retornarFuncion(yyout, $2.es_direccion);
                    fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp>\n");
                  }
               ;
exp:  exp TOK_MAS exp
      {
        if ( ($1.tipo != INT) || ($3.tipo != INT) ){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        sumar(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp>\n");
      }
   |  exp TOK_MENOS exp
      {
        if ( ($1.tipo != INT) || ($3.tipo != INT) ){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        restar(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp>\n");
      }
   |  exp TOK_DIVISION exp
      {
        if ( ($1.tipo != INT) || ($3.tipo != INT) ){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        dividir(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp>\n");
      }
   |  exp TOK_ASTERISCO exp
      {
        if ( ($1.tipo != INT) || ($3.tipo != INT) ){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        multiplicar(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp>\n");
      }
   |  TOK_MENOS exp
      {
        if ($2.tipo != INT){
          errorSemantico("Operacion aritmetica con operandos boolean");
          return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        cambiar_signo(yyout, $2.es_direccion);
        fprintf(yyout, ";R76:\t<exp> ::= - <exp>\n");
      }


   |  exp TOK_AND exp
      {
        if ( ($1.tipo != BOOLEAN) || ($3.tipo != BOOLEAN) ){
          errorSemantico("Operacion logica con operandos int");
          return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        y(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp>\n");
      }
   |  exp TOK_OR exp
      {
        if ( ($1.tipo != BOOLEAN) || ($3.tipo != BOOLEAN) ){
          errorSemantico("Operacion logica con operandos int");
          return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        o(yyout, $1.es_direccion, $3.es_direccion);
        fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp>\n");
      }
   |  TOK_NOT exp
      {
        if ($2.tipo != BOOLEAN){
          errorSemantico("Operacion logica con operandos boolean");
          return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        no(yyout, $2.es_direccion, 1);
        fprintf(yyout, ";R79:\t<exp> ::= ! <exp>\n");
      }

   |  TOK_IDENTIFICADOR
      {
        if (ambito == 0){
          simbol = UsoGlobal(TGLOBAL, $1.lexema);
          if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
            char err[MAX_ERR_LEN];
            sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
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

            $$.tipo = getTipo(simbol);
            $$.es_direccion = 1;
          }
          printf("\nESCRIBIR Normal %s, valor %d\n", $1.lexema, $1.valor_entero);
          if(en_explist){
            char val[MAX_INT_LEN];
            sprintf(val, "%d", $1.valor_entero);
            escribir_operando(yyout, val, CTE);
            printf("\nOperando %s con pos %d y con valor %d a pila", getIdentificador(simbol), getPosicion(simbol), $1.valor_entero);
            operandoEnPilaAArgumento(yyout, getPosicion(simbol));
          }
          else{
            escribir_operando(yyout, $1.lexema, VAR);
          }
        }
        else{                                           // Búsqueda en local
          simbol = UsoLocal(TGLOBAL, TLOCAL, $1.lexema);
          if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
            char err[MAX_ERR_LEN];
            sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
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
            $$.tipo = getTipo(simbol);
            $$.es_direccion = 1;
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
   |  constante {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion; $$.valor_entero = $1.valor_entero;
                     fprintf(yyout, ";R81:\t<exp> ::= <constante>\n");}
   |  TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {$$.tipo = $2.tipo; $$.es_direccion = $2.es_direccion;
                                                        fprintf(yyout, ";R82:\t<exp> ::= ( <exp> )\n");}
   |  TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {
                                                                $$.tipo = $2.tipo; $$.es_direccion = $2.es_direccion;
                                                                fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> )\n");}
   |  elemento_vector {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion; fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector>\n");}
   |  idf_llamada_funcion TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO
      {
        if (ambito == 0){
          simbol = UsoGlobal(TGLOBAL, $1.lexema);
          if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
            char err[MAX_ERR_LEN];
            sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
            errorSemantico(err);
            return -1;
          }
          printf("\nLLamando a funcion %s con %d params\n", getIdentificador(simbol), getNum_parametros(simbol));
          llamarFuncion(yyout, getIdentificador(simbol), getNum_parametros(simbol));
        }

        else{                                           // Búsqueda en local
          simbol = UsoLocal(TGLOBAL, TLOCAL, $1.lexema);
          if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
            char err[MAX_ERR_LEN];
            sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
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

        $$.tipo = getTipo(simbol);
        $$.es_direccion = 0;

        fprintf(yyout, ";R88:\t<exp> ::= id_llamada_funcion ( <lista_expresiones> )\n");
      }
   ;

idf_llamada_funcion:  TOK_IDENTIFICADOR
                    {
                      if (ambito == 0){
                        simbol = UsoGlobal(TGLOBAL, $1.lexema);
                        if (simbol == NULL){                        // Si se busca en global pero no lo encuentra
                          char err[MAX_ERR_LEN];
                          sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
                          errorSemantico(err);
                          return -1;
                        }

                        else{                                       // Si lo busca en global y lo encuentra
                          if (CategoriaSimbolo(simbol) != FUNCION){
                            char err[MAX_ERR_LEN];
                            sprintf(err, "Llamada a funcion %s que no tiene categoria de funcion", $1.lexema);
                            errorSemantico(err);
                            return -1;
                          }

                        }
                      }
                      else{                                           // Búsqueda en local
                          simbol = UsoLocal(TGLOBAL, TLOCAL, $1.lexema);
                          if (simbol == NULL){                           // Si se busca en su ambito pero NO lo encuentra
                              char err[MAX_ERR_LEN];
                              sprintf(err, "Acceso a variable no declarada (%s)", $1.lexema);
                              errorSemantico(err);
                              return -1;
                          }
                          else{                                       // Si lo busca en local y lo encuentra
                              if (CategoriaSimbolo(simbol) != FUNCION){
                                char err[MAX_ERR_LEN];
                                sprintf(err, "Llamada a funcion %s que no tiene categoria de funcion", $1.lexema);
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
                      strcpy($$.lexema, getIdentificador(simbol) );
                      strcpy(nombre_funcion_actual,  getIdentificador(simbol));
                    }
                  ;
lista_expresiones:  exp resto_lista_expresiones
                    {
                      num_parametros_llamada_actual++;

                      fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");}
                 |  {fprintf(yyout, ";R90:\t<lista_expresiones> ::= \n");}
                 ;
resto_lista_expresiones:  TOK_COMA exp resto_lista_expresiones
                          {
                            num_parametros_llamada_actual++;

                            fprintf(yyout, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");}
                       |  {fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::= \n");}
                       ;
comparacion:  exp TOK_IGUAL exp
              {
              if ( ($1.tipo != INT) || ($3.tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              $$.tipo = BOOLEAN;
              $$.es_direccion = 0;
              ////printf("\nIGUAL: %d == %d", $1.valor_entero, $3.valor_entero);
              cmpOp(yyout, $1, $3, CMP_IGUAL);
              fprintf(yyout, ";R93:\t<comparacion> ::= <exp> == <exp>\n");
              }
           |  exp TOK_DISTINTO exp
              {
              if ( ($1.tipo != INT) || ($3.tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              $$.tipo = BOOLEAN;
              $$.es_direccion = 0;
              cmpOp(yyout, $1, $3, CMP_DIST);
              fprintf(yyout, ";R94:\t<comparacion> ::= <exp> != <exp>\n");
              }
           |  exp TOK_MENORIGUAL exp
              {
              if ( ($1.tipo != INT) || ($3.tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              $$.tipo = BOOLEAN;
              $$.es_direccion = 0;
              cmpOp(yyout, $1, $3, CMP_MEN_IG);
              fprintf(yyout, ";R95:\t<comparacion> ::= <exp> <= <exp>\n");
              }
           |  exp TOK_MAYORIGUAL exp
              {
              if ( ($1.tipo != INT) || ($3.tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              $$.tipo = BOOLEAN;
              $$.es_direccion = 0;
              cmpOp(yyout, $1, $3, CMP_MAY_IG);
              fprintf(yyout, ";R96:\t<comparacion> ::= <exp> >= <exp>\n");
              }
           |  exp TOK_MENOR exp
              {
              if ( ($1.tipo != INT) || ($3.tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              $$.tipo = BOOLEAN;
              $$.es_direccion = 0;
              cmpOp(yyout, $1, $3, CMP_MEN);
              fprintf(yyout, ";R97:\t<comparacion> ::= <exp> < <exp>\n");
              }
           |  exp TOK_MAYOR exp
              {
              if ( ($1.tipo != INT) || ($3.tipo != INT) ){
                errorSemantico("Comparacion con operandos boolean");
                return -1;
              }
              $$.tipo = BOOLEAN;
              $$.es_direccion = 0;
              cmpOp(yyout, $1, $3, CMP_MAY);
              fprintf(yyout, ";R98:\t<comparacion> ::= <exp> > <exp>\n");
              }
           ;
constante:  constante_logica
            {
              $$.tipo = $1.tipo;
              $$.es_direccion = $1.es_direccion;
              $$.valor_entero = $1.valor_entero;
              fprintf(yyout, ";R99:\t<constante> ::= <constante_logica>\n");
            }
          | constante_entera
            {
              $$.tipo = INT;
              $$.es_direccion = $1.es_direccion;
              fprintf(yyout, ";R100:\t<constante> ::= <constante_entera>\n");
            }
          ;
constante_logica:  TOK_TRUE
                  {
                    $$.tipo = BOOLEAN;
                    $$.es_direccion = 0;
                    $$.valor_entero = 1;
                    ////printf("\nTRICK 6 writing operando %s\n", STR_TRUE);
                    escribir_operando(yyout,STR_TRUE,CTE);
                    fprintf(yyout, ";R102:\t<constante_logica> ::= true\n");
                  }
                |  TOK_FALSE
                    {
                      $$.tipo = BOOLEAN;
                      $$.es_direccion = 0;
                      $$.valor_entero = 0;
                      ////printf("\nTRICK 7 writing operando %s\n", STR_FALSE);
                      escribir_operando(yyout,STR_FALSE,CTE);

                      fprintf(yyout, ";R103:\t<constante_logica> ::= false\n");
                    }
                ;
constante_entera:  TOK_CONSTANTE_ENTERA
                    {
                      $$.tipo = INT;
                      $$.es_direccion = 0;
                      $$.valor_entero = $1.valor_entero;

                      char val[MAX_INT_LEN];
                      sprintf(val, "%d", $1.valor_entero);
                      ////printf("\nTRICK 8 writing operando %s\n", val);
                      //printf("\nTrick 5");
                      escribir_operando(yyout,val,CTE);
                      fprintf(yyout, ";R105:\t<constante_entera> ::= <numero>\n");
                    }
                ;


identificador:  TOK_IDENTIFICADOR {
                            if (ambito == 0){
                                if (clase_actual == VECTOR){      // Estamos declarando un array
                                      sprintf(nombre_vector, "%s", $1.lexema);  // Guardamos el nombre del array

                                      if (DeclararGlobal(TGLOBAL, $1.lexema, VARIABLE, tipo_actual, clase_actual, $1.valor_entero, FALSE, tamanio_vector_actual) == FALSE){     // redeclaración variable global
                                        char err[MAX_ERR_LEN];
                                        sprintf(err, "Declaracion (%s) duplicada", $1.lexema);
                                        errorSemantico(err);
                                        return -1;
                                      }
                                }
                                else{
                                  if (DeclararGlobal(TGLOBAL, $1.lexema, VARIABLE, tipo_actual, clase_actual, $1.valor_entero, FALSE, FALSE) == FALSE){     // redeclaración variable global
                                      char err[MAX_ERR_LEN];
                                      sprintf(err, "Declaracion (%s) duplicada", $1.lexema);
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

                                  if (DeclararLocal(TLOCAL, $1.lexema, VARIABLE, tipo_actual, clase_actual,
                                        $1.valor_entero, FALSE, FALSE, pos_variable_local_actual) == FALSE){     // redeclaración variable local
                                    char err[MAX_ERR_LEN];
                                    sprintf(err, "Declaracion (%s) duplicada", $1.lexema);
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
             ;

%%

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
