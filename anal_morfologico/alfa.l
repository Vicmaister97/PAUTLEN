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
void yyerror(char *msg);

/** Ficheros de entrada y salida del analizador morfológico **/
/** extern?? **/
FILE* yyin;
FILE* yyout;

/*int line = 1;*/

%}

/** Para procesar 1 solo fichero
*** La siguiente directiva indica que no se va a implementar la función ’yywrap’
*** evita que se tenga que enlazar con -lf, o que se tenga que implementar ’yywrap’
**/
%option noyywrap;

/** Obliga a mantener el número de línea analizada en la variable global yylineno **/
%option yylineno;

/** Buffer usado para almacenamiento temporal de cadenas de texto **/
char* buffer;

DIGITO	[0-9]
LETRA	[a-zA-Z]


%%


/*----- Sección de Reglas ----------------*/
/** Además de la accion asociada se guarda el token en yytext como char* y su longitud en yyleng **/
main                                         {buffer = "TOK_MAIN"; return TOK_MAIN;}
"\{"                                         {buffer = "TOK_LLAVEIZQUIERDA"; return TOK_LLAVEIZQUIERDA;}
"\}"                                         {buffer = "TOK_LLAVEDERECHA"; return TOK_LLAVEDERECHA;}
"\["                                         {buffer = "TOK_CORCHETEIZQUIERDO"; return TOK_CORCHETEIZQUIERDO;}
"\]"                                         {buffer = "TOK_CORCHETEDERECHO"; return TOK_CORCHETEDERECHO;}
";"                                          {buffer = "TOK_PUNTOYCOMA"; return TOK_PUNTOYCOMA;}
"\("                                         {buffer = "TOK_PARENTESISIZQUIERDO"; return TOK_PARENTESISIZQUIERDO;}
"\)"                                         {buffer = "TOK_PARENTESISDERECHO"; return TOK_PARENTESISDERECHO;}
","                                          {buffer = "TOK_COMA"; return TOK_COMA;}
"="                                          {buffer = "TOK_ASIGNACION"; return TOK_ASIGNACION;}
"if"                                         {buffer = "TOK_IF"; return TOK_IF;}
"else"                                       {buffer = "TOK_ELSE"; return TOK_ELSE;}
"while"                                      {buffer = "TOK_WHILE"; return TOK_WHILE;}
"return"                                     {buffer = "TOK_RETURN"; return TOK_RETURN;}
!                                            {buffer = "TOK_NOT"; return TOK_NOT;}
\+                                           {buffer = "TOK_MAS"; return TOK_MAS;}
\-                                           {buffer = "TOK_MENOS"; return TOK_MENOS;}
\*                                           {buffer = "TOK_ASTERISCO"; return TOK_ASTERISCO;}
\/                                           {buffer = "TOK_DIVISION"; return TOK_DIVISION;}
">"                                          {buffer = "TOK_MAYOR"; return TOK_MAYOR;}
"<="                                         {buffer = "TOK_MENORIGUAL"; return TOK_MENORIGUAL;}
"<"                                          {buffer = "TOK_MENOR"; return TOK_MENOR;}
">="                                         {buffer = "TOK_MAYORIGUAL"; return TOK_MAYORIGUAL;}
"=="                                         {buffer = "TOK_IGUAL"; return TOK_IGUAL;}
"!="                                         {buffer = "TOK_DISTINTO"; return TOK_DISTINTO;}
"&&"                                         {buffer = "TOK_AND"; return TOK_AND;}
"or"                                         {buffer = "TOK_OR"; return TOK_OR;}
"int"                                        {buffer = "TOK_INT"; return TOK_INT;}
"boolean"                                    {buffer = "TOK_BOOLEAN"; return TOK_BOOLEAN;}
"true"                                       {buffer = "TOK_TRUE"; return TOK_TRUE;}
"false"                                      {buffer = "TOK_FALSE"; return TOK_FALSE;}
{DIGITO}+                                    {buffer = "TOK_CONSTANTE_ENTERA"; return TOK_CONSTANTE_ENTERA;}
"scanf"                                      {buffer = "TOK_SCANF"; return TOK_SCANF;}
"printf"                                     {buffer = "TOK_PRINTF"; return TOK_PRINTF;}
"array"                                      {buffer = "TOK_ARRAY"; return TOK_ARRAY;}
"function"                                   {buffer = "TOK_FUNCTION"; return TOK_FUNCTION;}
{LETRA} ({DIGITO} |{LETRA})*                 {if (yyleng > 100){
																							yyerror(" identificador demasiado largo");
																							return TOK_ERROR;}
																							else{buffer = "TOK_IDENTIFICADOR";
																								return TOK_IDENTIFICADOR;}}


[ \t\n"//"]+                                 { /** accion vacia: se ignoran los espacios y tabuladores **/ }
.                                            { /** REPRESENTA CUALQUIER CARACTER MENOS SALTO DE LINEA: token desconocido, se produce un mensaje de error **/
																							 yyerror("simbolo no permitido"); return TOK_ERROR;}
%%


/*----- Sección de Procedimientos --------*/
void yyerror (char *msg)
{
  fprintf(stderr,"****Error en [lin %d, col %d]: %s (%s)\n", yylineno, yyleng, msg, yytext);
}

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
				fprintf(yyout, "%s\t%d\t%s", buffer, tok, yytext);
				tok=yylex();
			}
			printf("FINALIZADO ANALISIS MORFOLÓGICO!!");
			fclose(yyin);
			fclose(yyout);
			exit(1);
		}
	}

	else{
		printf("Error en los parámetros de entrada\t./alfa FILE_IN FILE_OUT\n");
	}

}
