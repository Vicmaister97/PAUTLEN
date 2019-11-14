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

int line = 1;

%}

/** Para procesar 1 solo fichero
*** La siguiente directiva indica que no se va a implementar la función ’yywrap’
*** evita que se tenga que enlazar con -lf, o que se tenga que implementar ’yywrap’
**/
%option noyywrap

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
"\{"                                         return LEFT_KEY;
"\}"                                         return RIGHT_KEY;
"\["                                         return LEFT_BRACKET;
"\]"                                         return RIGHT_BRACKET;
";"                                          return SEMICOLON;
"\("                                         return LEFT_PARENTHESIS;
"\)"                                         return RIGHT_PARENTHESIS;
","                                          return COMA;
"="                                          return ASSIGN;
"if"                                         return IF;
"then"                                       return THEN;
"else"                                       return ELSE;
"while"                                      return WHILE;
"return"                                     return RETURN;
"for"                                        return FOR;
":="                                         return ASSIGN_FOR;
"to"                                         return TO;
"do"                                         return DO;
"out"                                        return OUT;
"in"                                         return IN;
"initVar"                                    return INITVAR;
"endVar"                                     return ENDVAR;
"\+\+"                                       return PLUSPLUS;
"@"                                          return AT;
"\$"                                         return DOLLAR;
!                                            {return NEG;}
#                                            return COUNT;
\?                                           return QUEST;
\+                                           {return SYMBOL_OP;}
\-                                           {return SYMBOL_OP;}
"--"                                         return MINUSMINUS;
\*                                           {return BINARY_OP;}
\/                                           {return BINARY_OP;}
%                                            return BINARY_LIST_OP_I;
\*\*                                         return BINARY_LIST_OP_L;
">"                                          {return RELATION_OP;}
"<="                                         {return RELATION_OP;}
"<"                                          {return RELATION_OP;}
">="                                         {return RELATION_OP;}
"=="                                         {return EQUALS_OP;}
"<>"                                         {return EQUALS_OP;}
"and"                                        return AND_OP;
"or"                                         return OR_OP;
"xor"                                        return XOR_OP;
"<<"                                         return LIST_OP;
">>"                                         return LIST_OP;
"list_of"                                    return LIST_OF;
"int"                                        {return BASIC_TYPES;}
"double"                                     {return BASIC_TYPES;}
"boolean"                                    {return BASIC_TYPES;}
"char"                                       {return BASIC_TYPES;}
"true"                                       {return CONST_BOOLEAN;}
"false"                                      {return CONST_BOOLEAN;}
[0-9]+                                       {return CONST_INT;}
[0-9]*\.[0-9]+                               {return CONST_DOUBLE;}
\"[^\"]\"                                    {return CONST_CHAR;}
\"[^\"]*\"                                   {return CADENA;}
[_a-zA-Z][_a-zA-Z0-9]*                       {return ID;}

\n                                           { /** LLevamos cuenta de la linea leida **/	line++; }
[ \t\n"//"]+                                 { /** accion vacia: se ignoran los espacios y tabuladores **/ }
.                                            { /** REPRESENTA CUALQUIER CARACTER MENOS SALTO DE LINEA: token desconocido, se produce un mensaje de error **/
						if (yyleng<100){ strcpy(buffer, "****Error en [lin %d, col %d]: simbolo no permitido (%s)", line, yyleng, yytext); }
						else{ strcpy(buffer, "****Error en [lin %d, col %d]: identificador demasiado largo (%s)", line, yyleng, yytext); }
						yyerror(buffer); }

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
				fprintf(yyout, "%s\t%d\t%s", yytext, tok, yyext);
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