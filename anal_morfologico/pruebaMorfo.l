/*********************************************************
**
** Fichero: alfa.l
** Autores: Víctor García, Alfonso Carvajal
** Contenido: Implementa el analizador morfológico para el compilador
**      a realizar en la asignatura de Proyecto de Autómatas y Lenguajes
**
*********************************************************/

/*----- Sección de Declaraciones -----------*/
%{

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

#define MAXIDLENGTH 100

/** Ficheros de entrada y salida del analizador morfológico **/
/** extern?? **/
FILE* yyin;
FILE* yyout;

/** Buffer usado para almacenamiento temporal de cadenas de texto **/
char* buffer;

int line = 1;

%}

/** Para procesar 1 solo fichero
*** La siguiente directiva indica que no se va a implementar la función ’yywrap’
*** evita que se tenga que enlazar con -lf, o que se tenga que implementar ’yywrap’
**/
%option noyywrap

/** Obliga a mantener el número de línea analizada en la variable global yylineno **/
%option yylineno

DIGITO	[0-9]
LETRA	[a-zA-Z]


%%

	/*----- Sección de Reglas ----------------*/
	/** Además de la accion asociada se guarda el token en yytext como char* y su longitud en yyleng **/
main                                         {buffer = "TOK_MAIN"; return TOK_MAIN;}
"\{"                                         {buffer = "TOK_PARENTESISIZQUIERDO"; return TOK_PARENTESISIZQUIERDO;}

\n                                           { /** LLevamos cuenta de la linea leida **/	line++; }
[ \t\n//]+                                 { /** accion vacia: se ignoran los espacios y tabuladores **/ }
.                                            { /** REPRESENTA CUALQUIER CARACTER MENOS SALTO DE LINEA: token desconocido, se produce un mensaje de error **/
						if (yyleng<100){ fprintf(stderr, "****Error en [lin %d, col %d]: simbolo no permitido (%s)", line, yyleng, yytext); }
						else{ fprintf(stderr,  "****Error en [lin %d, col %d]: identificador demasiado largo (%s)", line, yyleng, yytext); }
						}

%%


/*----- Sección de Procedimientos --------*/


int main (int argc, char *argv[]){
	int tok;
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

		else{
			printf("Leyendo fichero '%s'\n",argv[1]);
			tok = yylex();
			while (tok != 0){	// Hasta que no llegue al final del fichero
				fprintf(yyout, "%s\t%d\t%s\n", buffer, tok, yytext);
				tok = yylex();
			}
			printf("FINALIZADO ANALISIS MORFOLÓGICO!!");
			fclose(yyin);
			fclose(yyout);
			exit(1);
		}
	}

	else{
		printf("Error en los parámetros de entrada\t./executable FILE_IN FILE_OUT\n");
	}

}