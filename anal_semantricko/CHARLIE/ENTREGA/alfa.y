%{
#include "alfa.h"
#include <stdio.h>
#include "y.tab.h"
#include "tablasimbolos.h"
#include "generacion.h"
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;
extern int row;
extern int col;

/* Variables Globales */
int tipo_actual = -1; 
int clase_actual = -1; 
int tamanio_vector_actual=1;
int en_explist = 0;
int etiqueta = 1;
int pos_variable_local_actual;
int num_parametros_llamada_actual;
int num_variables_locales_actual;
int num_parametros_actual;
int pos_parametro_actual;


char id_funcion_actual[100];
%}

%union
	{
		tipo_atributos atributos;
	}

%token <atributos> TOK_IDENTIFICADOR
%token <atributos> TOK_CONSTANTE_ENTERA

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
%token TOK_ERROR


%token TOK_TRUE
%token TOK_FALSE


%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL




%start programa
%left TOK_MENORIGUAL TOK_MAYORIGUAL TOK_DISTINTO TOK_IGUAL
%left TOK_AND TOK_OR
%left '+' '-'
%left '*' '/'
%right TOK_NOT

/* semántico                     */


%type <atributos> exp
%type <atributos> comparacion
%type <atributos> constante
%type <atributos> funcion
%type <atributos> fn_name
%type <atributos> fn_declaration
%type <atributos> clase_vector
%type <atributos> asignacion
%type <atributos> elemento_vector
%type <atributos> if_exp
%type <atributos> while_exp
%type <atributos> lectura
%type <atributos> escritura
%type <atributos> idf_llamada_funcion
%type <atributos> constante_logica
%type <atributos> constante_entera
%type <atributos> identificador
%type <atributos> idpf
%type <atributos> if_exp_sentencias
%type <atributos> condicional
%type <atributos> while


%%
programa:  inicioTabla TOK_MAIN   '{' declaraciones escritura_TS funciones escritura_main sentencias   '}' 
	{escribir_fin(yyout);DestruirTablaGlobal();}
;

inicioTabla: {
	elemento *el;
	Crear_TablaGlobal();
};

escritura_TS: { //Escritura de las cabeceras
	escribir_cabecera_bss(yyout);
	escribirTabla(yyout, getGlobal());
	escribir_subseccion_data(yyout);
	escribir_segmento_codigo(yyout); 

};

escritura_main: { escribir_inicio_main(yyout);}
;

declaraciones: declaracion
    | declaracion declaraciones
;

declaracion: clase identificadores ';'
;

clase: clase_escalar {clase_actual = ESCALAR;}
    | clase_vector {clase_actual = VECTOR;}
;

clase_escalar: tipo 
;

tipo: TOK_INT {tipo_actual = INT;}
	| TOK_BOOLEAN {tipo_actual = BOOLEAN;}
;

clase_vector:   TOK_ARRAY tipo '[' TOK_CONSTANTE_ENTERA ']' {
	tamanio_vector_actual = $4.valor_entero;
	if ((1 > tamanio_vector_actual ) || (tamanio_vector_actual > MAX_TAMANIO_VECTOR)) {
    	fprintf(stderr, "****Error semantico en lin %d: El tamanyo del vector <nombre_vector> excede los limites permitidos (1,64).", row);
  	}
};



identificadores: identificador 
				 |identificador ',' identificadores 
;

funciones: funcion funciones 
		| /*vacio*/
;

fn_name: TOK_FUNCTION tipo TOK_IDENTIFICADOR {
	elemento *el = NULL;
  elemento *aux = NULL;
	if (UsoGlobal($3.lexema) != NULL) {
		fprintf(stderr, "****Error semantico en lin %d: Declaracion duplicada.", row);
	}
	/*Actualizamos variables globales*/
	num_variables_locales_actual = 0;
	pos_variable_local_actual = 1;
	num_parametros_actual = 0;
	pos_parametro_actual = 0;
	el = crearElemento($3.lexema, FUNCION, tipo_actual, clase_actual, tamanio_vector_actual, $3.valor_entero, 0, 0, 1);
  
	DeclararFuncion($3.lexema, el);
  aux = UsoGlobal($3.lexema);

	strcpy($$.lexema, $3.lexema);
	strcpy(id_funcion_actual, $3.lexema);
};

fn_declaration: fn_name '(' parametros_funcion ')' '{' declaraciones_funcion {
	  int pos;
    elemento *el = UsoGlobal($1.lexema);
    if (el != NULL){
      el->n_params = num_parametros_actual;
    }
    el = UsoLocal($1.lexema);
    el->n_params = num_parametros_actual;
    strcpy($$.lexema, $1.lexema);
    declararFuncion(yyout, $1.lexema, num_variables_locales_actual); 

  };

funcion: fn_declaration sentencias '}' {
  //Cuando acaba la funcion destruimos la tabla local
  DestruirTablaLocal();
}
;

parametros_funcion: parametro_funcion resto_parametros_funcion {num_parametros_actual += 1;}
					| /*vacio*/ 
;

resto_parametros_funcion: ';'parametro_funcion resto_parametros_funcion  {num_parametros_actual += 1;}
						| /*vacio*/ 
;

parametro_funcion: tipo idpf 
;

declaraciones_funcion: declaraciones 
						| /*vacio*/ 
;

sentencias: sentencia 
			| sentencia sentencias 
;

sentencia: sentencia_simple ';' 
			| bloque 
;

sentencia_simple: asignacion 
					| lectura 
					| escritura 
					| retorno_funcion 
;

bloque: condicional {etiqueta += 1;}
			| bucle 
;

asignacion: TOK_IDENTIFICADOR '=' exp {
	elemento *el = Uso($1.lexema);
	if (el == NULL) {
		fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", row, $1.lexema);
		}
	else if (el->tipo != $3.tipo) {
		fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible. %d %d\n", row, el->tipo, $3.tipo);
		}
	else if(el->categoria == FUNCION) {
		fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", row);
		}
	else if (el->clase == VECTOR) {
		fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", row);
		}
	/*Cuidado aqui con las variables locales, estas se meten en la pila*/
	if(existelocal()){
    	escribirVariableLocal(yyout, el->posicion_local);
      asignarDestinoEnPila(yyout, $1.es_direccion);
  	}
  	else {
		asignar(yyout, $1.lexema, $1.es_direccion);
	}
	}
	| elemento_vector '=' exp {
    if ($1.tipo != $3.tipo) {
      fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", row);
    }
    /*DIAPO 49*/
    asignarDestinoEnPila2(yyout, $3.es_direccion);
  }
;

elemento_vector: TOK_IDENTIFICADOR '[' exp ']' 
{
  elemento *el = Uso($1.lexema);
  if (el == NULL) {
    fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", row, $1.lexema);
  }
  else if ($3.tipo != INT) {
    fprintf(stderr, "****Error semantico en lin %d: El indice en una operacion de indexacion tiene que ser de tipo entero.\n", row);
  }
  else if (el->clase != VECTOR) {
    fprintf(stderr, "****Error semantico en lin %d: Intento de indexacion de una variable que no es de tipo vector.\n", row);
  }
  $$.tipo = el->tipo;
  $$.es_direccion = 1;
  escribir_elemento_vector(yyout, $1.lexema, el->tamanio, $3.es_direccion);

  if(en_explist){
    operandoEnPilaAArgumento(yyout, $$.es_direccion);
  }
};


if_exp: TOK_IF '(' exp ')' '{' {
  if ($3.tipo != BOOLEAN) {
    fprintf(stderr, "****Error semantico en lin %d: Condicional con condicion de tipo int.\n", row);
  }
  $$.etiqueta = etiqueta + 1;
  ifthen_inicio(yyout, $3.es_direccion, $$.etiqueta);
};

if_exp_sentencias:  if_exp sentencias '}' {
  $$.etiqueta = $1.etiqueta;
  ifthenelse_fin_then(yyout, $$.etiqueta);
};

condicional: if_exp sentencias '}' { ifthen_fin(yyout, $1.etiqueta);}
  | if_exp_sentencias TOK_ELSE '{' sentencias '}' { ifthenelse_fin(yyout, $1.etiqueta);}
;

while: TOK_WHILE '(' {
  $$.etiqueta = etiqueta + 1;
  while_inicio(yyout, $$.etiqueta);
} ;

while_exp: while exp ')' '{' {
  if ($2.tipo != BOOLEAN) {
    fprintf(stderr, "****Error semantico en lin %d: Condicional con condicion de tipo int.\n", row);
  }
  $$.etiqueta = $1.etiqueta;
  while_exp_pila(yyout, $2.es_direccion, $$.etiqueta);
};

bucle: while_exp sentencias '}' { while_fin(yyout, $1.etiqueta);}
;

lectura: TOK_SCANF TOK_IDENTIFICADOR {
  	elemento *el = Uso($2.lexema);
  	if (el == NULL) {
    	fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", row, $2.lexema);
  	}
  	else {
	    if (el->categoria == FUNCION) {
	  		fprintf(stderr, "****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones.\n", row);
	    }
	    else if (el->clase == VECTOR) {
	  		fprintf(stderr, "****Error semantico en lin %d: Variable local de tipo no escalar.\n", row);
	    }
	    else {
	  		if (UsoLocal($2.lexema) == NULL) {
			    leer(yyout, $2.lexema, $2.tipo);
	      	}
	      	else{/*Si es local su dirección se expresa en función deebp y la posición del  parámetro o variable local */
		      	leer(yyout, $2.lexema, $2.tipo);
	      	}
	    }
  	}
};
escritura:  TOK_PRINTF exp {
  escribir(yyout, $2.es_direccion, $2.tipo);
};
retorno_funcion:  TOK_RETURN exp {
  retornarFuncion(yyout, $2.es_direccion);
};

idf_llamada_funcion: TOK_IDENTIFICADOR {
  if (UsoGlobal($1.lexema) == NULL) {
    if (existelocal()) {
      fprintf(stderr, "****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones\n", row);  
    }
    else {
      fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada ().\n", row);  
    }
  }
  else if (UsoGlobal($1.lexema)->categoria == FUNCION) {
    /*fprintf(stderr, "****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones. %s\n", fila, $1.lexema);
    */
  }
  else if (en_explist == 1) {
    fprintf(stderr, "****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones.\n", row);
  }
  strcpy($$.lexema, $1.lexema);
  strcpy(id_funcion_actual, $1.lexema);
  /*Inicializamos variables*/
  en_explist = 1;
  num_parametros_llamada_actual = 0;
};


constante_entera: TOK_CONSTANTE_ENTERA {
	/*Declaramos su tipo, si es una direccion y le asignamos el valor*/
	$$.valor_entero=$1.valor_entero;
	$$.tipo = INT;
	$$.es_direccion = 0;
	fprintf(yyout, "; numero_linea %d\n", row);
	fprintf(yyout, "\tpush dword %d\n", $1.valor_entero);
};


exp: exp '+' exp {
	if ($1.tipo != INT || $3.tipo != INT) {
        fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", row);
     }
	/* Declaramos tipo y escribimos su codigo ensamblador*/
	$$.tipo = INT;
	$$.es_direccion = 0;
	sumar(yyout, $1.es_direccion, $3.es_direccion);
    }
	| exp '-' exp {
    if ($1.tipo != INT || $3.tipo != INT) {
      fprintf(stderr,"****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", row);
    }
    /* Declaramos tipo y escribimos su codigo ensamblador*/
    $$.tipo = INT;
    $$.es_direccion = 0;
    restar(yyout, $1.es_direccion, $3.es_direccion);
  	}
	| exp '/' exp {
    if ($1.tipo != INT || $3.tipo != INT) {
    	fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", row);
    }
    /* Declaramos tipo y escribimos su codigo ensamblador*/
    $$.tipo = INT;
    $$.es_direccion = 0;
    dividir(yyout, $1.es_direccion, $3.es_direccion);
    }
	| exp '*' exp {
    if ($1.tipo != INT || $3.tipo != INT) {
    	fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", row);
    }
    /* Declaramos tipo y escribimos su codigo ensamblador*/
    $$.tipo = INT;
    $$.es_direccion = 0;
    multiplicar(yyout, $1.es_direccion, $3.es_direccion);
    }
	| '-' exp {
    if ($2.tipo != INT) {
    	fprintf(stderr,"****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", row);
    }
    /* Declaramos tipo y escribimos su codigo ensamblador*/
    $$.tipo = INT;
    $$.es_direccion = 0;
    cambiar_signo(yyout, $2.es_direccion);
  	}
	| exp TOK_AND exp {
    if ($1.tipo != BOOLEAN || $3.tipo != BOOLEAN) {
    	fprintf(stderr, "****Error semantico en lin %d: Operacion logica con operandos int.\n", row);
    }
    /* Declaramos tipo y escribimos su codigo ensamblador*/
    $$.tipo= BOOLEAN;
    $$.es_direccion = 0;
    y(yyout, $1.es_direccion, $3.es_direccion);
    }
	| exp TOK_OR exp {
    if ($1.tipo != BOOLEAN || $3.tipo != BOOLEAN) {
    	fprintf(stderr, "****Error semantico en lin %d: Operacion logica con operandos int.", row);
    }
    /* Declaramos tipo y escribimos su codigo ensamblador*/
    $$.tipo= BOOLEAN;
    $$.es_direccion = 0;
    o(yyout, $1.es_direccion, $3.es_direccion);
    }
	| TOK_NOT exp {
    if ($2.tipo != BOOLEAN) {
      fprintf(stderr, "****Error semantico en lin %d: Operacion logica con operandos int.\n", row);
    }
    /* Declaramos tipo y escribimos su codigo ensamblador*/
    $$.tipo= BOOLEAN;
    $$.es_direccion = 0;
    no(yyout, $2.es_direccion, etiqueta);
    /*Incrementamos la etiqueta*/
    etiqueta += 1;
    }
	| TOK_IDENTIFICADOR  {
    elemento *el = Uso($1.lexema);
    if (el == NULL) {
    	fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", row, $1.lexema);
    }
    else if (el->clase != ESCALAR) {
    	fprintf(stderr, "****Error semantico en lin %d: Variable local de tipo no escalar.\n", row);
    }
    else if (el->categoria == FUNCION) {
    	fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", row, $1.lexema);
    }
    /* Declaramos tipo y escribimos su codigo ensamblador*/
    $$.tipo = el->tipo;
    $$.es_direccion = 1;
    /* Parametro, VarLocal o Operando*/
    if(existelocal()){
    	if(el->categoria==PARAMETRO){
    		escribirParametro(yyout, el->posicion_param, Uso(id_funcion_actual)->n_params);}
    	else {
    		escribirVariableLocal(yyout, el->posicion_local);
    	}
    }
    else{
    	escribir_operando(yyout, el->lexema, $$.es_direccion);
      if (en_explist){
        operandoEnPilaAArgumento(yyout, $$.es_direccion);
      }
    }
    }
	| constante {
    $$.tipo = $1.tipo;
    $$.es_direccion = $1.es_direccion;
    $$.valor_entero = $1.valor_entero;
 	 }
	| '(' exp ')' {
    $$.tipo = $2.tipo;
    $$.es_direccion = $2.es_direccion;
  	}
	| '(' comparacion ')' {
    $$.tipo = $2.tipo;
    $$.es_direccion = $2.es_direccion;
  	}
	| elemento_vector {
    $$.tipo = $1.tipo;
    $$.es_direccion = $1.es_direccion;
  	}
	| idf_llamada_funcion '(' lista_expresiones ')' {
    elemento *el = UsoGlobal($1.lexema);
    if (el->n_params != num_parametros_llamada_actual) {
    	fprintf(stderr, "****Error semantico en lin %d: Numero incorrecto de parametros en llamada a funcion. %d, %d\n", row, num_parametros_llamada_actual, el->n_params);
    }
    if (el->categoria != FUNCION){
    	fprintf(stderr, "****Error semantico en lin %d: Intento de indexacion de una variable que no es de tipo vector.\n", row);
    }
    llamarFuncion(yyout, el->lexema, el->n_params);
    $$.tipo = el->tipo;
    $$.es_direccion = 0;
    /*Reseteamos variables*/
    num_parametros_llamada_actual=0;
    en_explist = 0;
    ;};


lista_expresiones: exp resto_lista_expresiones {
	num_parametros_llamada_actual++;
}
			| /*vacio*/ {;};
;

resto_lista_expresiones: ',' exp resto_lista_expresiones {
	num_parametros_llamada_actual++;
}
			| /*vacio*/ {;};
;

comparacion: exp TOK_IGUAL exp {
  if ($1.tipo != INT || $3.tipo != INT) {
      fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", row);
    }
    $$.tipo = BOOLEAN;
    $$.es_direccion = 0;
    igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;
}
  | exp TOK_DISTINTO exp {
    if ($1.tipo != INT || $3.tipo != INT) {
      fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", row);
    }
    $$.tipo = BOOLEAN;
    $$.es_direccion = 0;
    distinto(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;
  }
  | exp TOK_MENORIGUAL exp {
    if ($1.tipo != INT || $3.tipo != INT) {
      fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", row);
    }
    $$.tipo = BOOLEAN;
    $$.es_direccion = 0;
    menor_igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;
  }
  | exp TOK_MAYORIGUAL exp {
    if ($1.tipo != INT || $3.tipo != INT) {
      fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", row);
    }
    $$.tipo = BOOLEAN;
    $$.es_direccion = 0;
    mayor_igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;
  }
  | exp '<' exp {
    if ($1.tipo != INT || $3.tipo != INT) {
      fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", row);
    }
    $$.tipo = BOOLEAN;
    $$.es_direccion = 0;
    menor(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;
  }
  | exp '>' exp {
    if ($1.tipo != INT || $3.tipo != INT) {
      fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", row);
    }
    $$.tipo = BOOLEAN;
    $$.es_direccion = 0;
    mayor(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;
  };

constante: constante_logica {
  $$.tipo = $1.tipo;
  $$.es_direccion = $1.es_direccion;
  $$.valor_entero = $1.valor_entero;
}
  | constante_entera {
    $$.tipo = $1.tipo;
    $$.valor_entero = $1.valor_entero;
    $$.es_direccion = $1.es_direccion;
  };

constante_logica: TOK_TRUE {
  $$.tipo = BOOLEAN;
  $$.valor_entero = 1;
  $$.es_direccion = 0;
  fprintf(yyout, "; numero_linea %d\n", row);
  fprintf(yyout, "\tpush dword 1\n");
}
  | TOK_FALSE {
    $$.tipo = BOOLEAN;
    $$.valor_entero = 0;
    $$.es_direccion = 0;
    fprintf(yyout, "; numero_linea %d\n", row);
    fprintf(yyout, "\tpush dword 0\n");
  };


identificador: TOK_IDENTIFICADOR {
	elemento * el;
	if (existelocal()) {
    	if (UsoLocal($1.lexema) != NULL) {
        	fprintf(stderr, "****Error semantico en lin %d: Declaracion duplicada.\n", row);
      	}
      	else if (clase_actual == VECTOR) {
        	fprintf(stderr, "****Error semantico en lin %d: Variable local de tipo no escalar.\n", row);
      	}
    	else {
	        el = crearElemento($1.lexema, VARIABLE, tipo_actual, clase_actual, tamanio_vector_actual, $1.valor_entero, num_parametros_actual, pos_parametro_actual, pos_variable_local_actual);
	        Declarar($1.lexema, el);
	       	pos_variable_local_actual++;
	        num_variables_locales_actual++;
      	}
  	}
  	else {
    	if (Uso($1.lexema) != NULL) {
        	fprintf(stderr, "****Error semantico en lin %d: Declaracion duplicada. %s\n", row, $1.lexema);    
    	}
    	else {
	        el = crearElemento($1.lexema, VARIABLE, tipo_actual, clase_actual, tamanio_vector_actual, $1.valor_entero, num_parametros_actual, pos_parametro_actual, pos_variable_local_actual);
	        Declarar($1.lexema, el);
	    }
  	}
};

idpf: TOK_IDENTIFICADOR {
	elemento * el;
	if (Uso($1.lexema) != NULL) {
    	fprintf(stderr, "****Error semantico en lin %d: Declaracion duplicada.\n", row);
  	}
  	else {
	    el = crearElemento($1.lexema, PARAMETRO, tipo_actual, ESCALAR, tamanio_vector_actual, $1.valor_entero, num_parametros_actual, pos_parametro_actual, pos_variable_local_actual);
	    Declarar($1.lexema, el);
	    pos_parametro_actual++;
  	}
}
%%

int yyerror(char *s) {
  fprintf(stderr, "****Error sintactico en [lin %d col %d]\n", row, col);
  return -1;
}


int main(int argc, char** argv) {
  if (argc!=3){
		printf("Uso correcto: ./pruebaSintactico <entrada> <salida>\n");
		return -1;
  }
  yyin = fopen(argv[1], "r");
  yyout = fopen(argv[2], "w");

  
  yyparse();
  
  fclose(yyin);
  fclose(yyout);
  return 1;
}

