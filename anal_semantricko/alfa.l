/*********************************************************
**
** Fichero: ALFA.L
** Autores: Víctor García, Alfonso Carvajal
** Contenido: Implementa el analizador sintáctico para el compilador
**      a realizar en la asignatura de Proyecto de Autómatas y Lenguajes
**
*********************************************************/

/*----- Sección de Declaraciones -----------*/
%{

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TS/tabla.h"
#include "y.tab.h"

#define MAXIDLENGTH 100
void errorMorfo(char *msg);

/** Ficheros de entrada y salida del analizador morfológico **/
/** extern?? **/
FILE* yyin;
FILE* yyout;

int col = 1;
int is_morpho = 0;

%}
/**
*** La siguiente directiva indica que no se va a implementar la función ’yywrap’
*** evita que se tenga que enlazar con -lf, o que se tenga que implementar ’yywrap’
**/
%option noyywrap

/** Opciones para quitar los warnings de bison **/
%option noinput
%option nounput

/** Obliga a mantener el número de línea analizada en la variable global yylineno **/
%option yylineno

DIGITO	[0-9]
LETRA	[a-zA-Z]


%%

											/*----- Sección de Reglas ----------------*/
											/** Además de la accion asociada se guarda el token en yytext como char* y su longitud en yyleng **/
main                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAIN;}
"\{"                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_LLAVEIZQUIERDA;}
"\}"                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_LLAVEDERECHA;}
"\["                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CORCHETEIZQUIERDO;}
"\]"                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CORCHETEDERECHO;}
";"                                          {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PUNTOYCOMA;}
"\("                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PARENTESISIZQUIERDO;}
"\)"                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PARENTESISDERECHO;}
","                                          {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_COMA;}
"="                                          {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ASIGNACION;}
"if"                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IF;}
"else"                                       {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ELSE;}
"while"                                      {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_WHILE;}
"return"                                     {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_RETURN;}
!                                            {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_NOT;}
\+                                           {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAS;}
\-                                           {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENOS;}
\*                                           {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ASTERISCO;}
\/                                           {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_DIVISION;}
">"                                          {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAYOR;}
"<="                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENORIGUAL;}
"<"                                          {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENOR;}
">="                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAYORIGUAL;}
"=="                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IGUAL;}
"!="                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_DISTINTO;}
"&&"                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_AND;}
"or"                                         {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_OR;}
"int"                                        {yylval.atributos.tipo = INT; col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_INT;}
"boolean"                                    {yylval.atributos.tipo = BOOLEAN; col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_BOOLEAN;}
"true"                                       {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_TRUE;}
"false"                                      {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_FALSE;}
{DIGITO}+                                    {yylval.atributos.valor_entero = atoi(yytext); col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CONSTANTE_ENTERA;}
"scanf"									 	 {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_SCANF;}
"printf"                                     {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PRINTF;}
"array"                                      {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ARRAY;}
"function"                                   {col += yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_FUNCTION;}
{LETRA}({DIGITO}|{LETRA})*                   {if (yyleng > 100){ errorMorfo(" identificador demasiado largo"); return 0;}	else{col += yyleng; strcpy(yylval.atributos.lexema,yytext); fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IDENTIFICADOR;}}
[ \t]+                                       { /**se ignoran los espacios y tabuladores **/ col += yyleng;}
[\n]                                         {col = 1;}
"//".*                                       { /** accion vacia: ignoramos comentarios **/ }
.                                            { /** REPRESENTA CUALQUIER CARACTER MENOS SALTO DE LINEA: token desconocido, se produce un mensaje de error **/
                                                   errorMorfo("simbolo no permitido"); return 0;}
%%


/*----- Sección de Procedimientos --------*/
void errorMorfo (char *msg)
{
	is_morpho = 1;
	fprintf(stderr,"****Error morfologico en [lin %d, col %d]: %s (%s)\n", yylineno, col, msg, yytext);
}
