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
int col = 1;
/** Buffer usado para almacenamiento temporal de cadenas de texto **/
char* buffer;
%}

/** Para procesar 1 solo fichero
*** La siguiente directiva indica que no se va a implementar la función ’yywrap’
*** evita que se tenga que enlazar con -lf, o que se tenga que implementar ’yywrap’
**/
%option noyywrap

/** Obliga a mantener el número de línea analizada en la variable global yylineno **/
%option yylineno

DIGITO [0-9]
LETRA	[a-zA-Z]


%%


											/*----- Sección de Reglas ----------------*/
											/** Además de la accion asociada se guarda el token en yytext como char* y su longitud en yyleng **/
main                                         {col += yyleng; buffer = "TOK_MAIN"; return TOK_MAIN;}
"\{"                                         {col += yyleng; buffer = "TOK_LLAVEIZQUIERDA"; return TOK_LLAVEIZQUIERDA;}
"\}"                                         {col += yyleng; buffer = "TOK_LLAVEDERECHA"; return TOK_LLAVEDERECHA;}
"\["                                         {col += yyleng; buffer = "TOK_CORCHETEIZQUIERDO"; return TOK_CORCHETEIZQUIERDO;}
"\]"                                         {col += yyleng; buffer = "TOK_CORCHETEDERECHO"; return TOK_CORCHETEDERECHO;}
";"                                          {col += yyleng; buffer = "TOK_PUNTOYCOMA"; return TOK_PUNTOYCOMA;}
"\("                                         {col += yyleng; buffer = "TOK_PARENTESISIZQUIERDO"; return TOK_PARENTESISIZQUIERDO;}
"\)"                                         {col += yyleng; buffer = "TOK_PARENTESISDERECHO"; return TOK_PARENTESISDERECHO;}
","                                          {col += yyleng; buffer = "TOK_COMA"; return TOK_COMA;}
"="                                          {col += yyleng; buffer = "TOK_ASIGNACION"; return TOK_ASIGNACION;}
"if"                                         {col += yyleng; buffer = "TOK_IF"; return TOK_IF;}
"else"                                       {col += yyleng; buffer = "TOK_ELSE"; return TOK_ELSE;}
"while"                                      {col += yyleng; buffer = "TOK_WHILE"; return TOK_WHILE;}
"return"                                     {col += yyleng; buffer = "TOK_RETURN"; return TOK_RETURN;}
!                                            {col += yyleng; buffer = "TOK_NOT"; return TOK_NOT;}
\+                                           {col += yyleng; buffer = "TOK_MAS"; return TOK_MAS;}
\-                                           {col += yyleng; buffer = "TOK_MENOS"; return TOK_MENOS;}
\*                                           {col += yyleng; buffer = "TOK_ASTERISCO"; return TOK_ASTERISCO;}
\/                                           {col += yyleng; buffer = "TOK_DIVISION"; return TOK_DIVISION;}
">"                                          {col += yyleng; buffer = "TOK_MAYOR"; return TOK_MAYOR;}
"<="                                         {col += yyleng; buffer = "TOK_MENORIGUAL"; return TOK_MENORIGUAL;}
"<"                                          {col += yyleng; buffer = "TOK_MENOR"; return TOK_MENOR;}
">="                                         {col += yyleng; buffer = "TOK_MAYORIGUAL"; return TOK_MAYORIGUAL;}
"=="                                         {col += yyleng; buffer = "TOK_IGUAL"; return TOK_IGUAL;}
"!="                                         {col += yyleng; buffer = "TOK_DISTINTO"; return TOK_DISTINTO;}
"&&"                                         {col += yyleng; buffer = "TOK_AND"; return TOK_AND;}
"or"                                         {col += yyleng; buffer = "TOK_OR"; return TOK_OR;}
"int"                                        {col += yyleng; buffer = "TOK_INT"; return TOK_INT;}
"boolean"                                    {col += yyleng; buffer = "TOK_BOOLEAN"; return TOK_BOOLEAN;}
"true"                                       {col += yyleng; buffer = "TOK_TRUE"; return TOK_TRUE;}
"false"                                      {col += yyleng; buffer = "TOK_FALSE"; return TOK_FALSE;}
{DIGITO}+                                    {col += yyleng; buffer = "TOK_CONSTANTE_ENTERA"; return TOK_CONSTANTE_ENTERA;}
"scanf"                                      {col += yyleng; buffer = "TOK_SCANF"; return TOK_SCANF;}
"printf"                                     {col += yyleng; buffer = "TOK_PRINTF"; return TOK_PRINTF;}
"array"                                      {col += yyleng; buffer = "TOK_ARRAY"; return TOK_ARRAY;}
"function"                                   {col += yyleng; buffer = "TOK_FUNCTION"; return TOK_FUNCTION;}
{LETRA}({DIGITO}|{LETRA})*                   {if (yyleng > 100){ yyerror(" identificador demasiado largo"); return TOK_ERROR;} else{col += yyleng; buffer = "TOK_IDENTIFICADOR"; return TOK_IDENTIFICADOR;}}
[ \t]+                                 			 { /**se ignoran los espacios y tabuladores **/ col += yyleng;}
[\n]																				 {col = 1;}
"//".*																			{ /** accion vacia: ignoramos comentarios **/ }
.                                            { /** REPRESENTA CUALQUIER CARACTER MENOS SALTO DE LINEA: token desconocido, se produce un mensaje de error **/
																							 yyerror("simbolo no permitido"); return TOK_ERROR;}
%%


/*----- Sección de Procedimientos --------*/
void yyerror (char *msg)
{
  fprintf(stderr,"****Error en [lin %d, col %d]: %s (%s)\n", yylineno, col, msg, yytext);
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
				if(tok == TOK_ERROR)
					break;
				fprintf(yyout, "%s\t%d\t%s\n", buffer, tok, yytext);
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
