%{
//Sección de definiciones
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "defs.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);

int x, y, z; // Difinición de variables
int bx=0, by=0, bz=0; //Variables para determinar variables no están definidas 

//Manejo de variables
char VARS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int variables[MAX_VARS];
bool bvariables[MAX_VARS];
int pos(char var);

%}

%code requires {
	struct TIPO_ATRIBUTO { 
		char nombre; 
		int tipo; 
		int valor; 
	}; 
}
%union {
	struct TIPO_ATRIBUTO atributo;
}
%token<atributo> T_INT
%token<atributo> T_VAR
%token T_PLUS T_MINUS T_MULTIPLY T_LEFT T_RIGHT T_EQUAL
%token T_NEWLINE T_QUIT T_ERROR
%left T_PLUS T_MINUS
%left T_MULTIPLY
%type<atributo> expression
%start calculation

//Sección de reglas
%%
calculation:
	| calculation line
;
line: T_NEWLINE
  	| expression T_NEWLINE { printf("Result: %i\n", $1.valor); }
  	| T_QUIT T_NEWLINE { printf("Bye!\n"); exit(0); }
	| T_VAR T_EQUAL expression T_NEWLINE { 
		int i = pos($1.nombre);
		bvariables[i] = true;
		variables[i] = $3.valor; 
		// declarar_variable(salida, $1.nombre, ENTERO, 1);
		// escribir_operando(salida,$3.valor,0);
		// asignar(salida,$1.nombre,0);
	}
	| T_ERROR T_NEWLINE { yyerror("Error: simbolo no encontrado\n"); }
;
expression: T_INT  { 
		$$ = $1; 
		// escribir_operando(salida, $1.valor, $1.tipo);
	}
	| T_MINUS expression	{ $$.valor = $2.valor*(-1); }
	| expression T_PLUS expression	{ 
		if ($1.tipo==NUMERO && $3.tipo==NUMERO) {
			$$.valor = $1.valor + $3.valor;
			//sumar(salida, $1.tipo, $3.tipo);
		}
		else yyerror( "Error de tipo!\n"); 
	}
	| expression T_MINUS expression	{ 
		$$.valor = $1.valor - $3.valor; 
		//restar(salida, $1.tipo, $3.tipo);
	}
	| expression T_MULTIPLY expression	{ 
		$$.valor = $1.valor * $3.valor; 
		//multiplicar(salida, $1.tipo, $3.tipo);
	}
	| T_LEFT expression T_RIGHT		{ $$ = $2; }
	| T_VAR { 
		int i = pos($1.nombre);
		if (bvariables[i]) {
			$$.tipo = VARIABLE;
			$$.nombre = $1.nombre;
			$$.valor = variables[i];
			//escribir_operando(salida, $1.nombre, $1.tipo);
		}
		else yyerror( "Variable no definida!\n"); 
	}
;
%%

//Sección de funciones de usuario
int main() {
	yyin = stdin;
	do { 
		yyparse();
	} while(!feof(yyin));
	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

int pos(char var){
    for (int i=0;i<MAX_VARS;i++)
        if (VARS[i]==var) return i;
    return -1;
}

