%{
	#include <stdio.h>
	#include <string.h>
	#include "alfa.h"
	#include "y.tab.h"
	int col=1;
	int row=1;
%}

%option noyywrap

/*Aqui se declaran los tokens*/
%%

" "+ {col+=yyleng;}
"\t"+ {col+=yyleng;}
"//"(.)* {col+=yyleng;}
"\n" {col=0; row+=1;}

main { col+=yyleng;    return TOK_MAIN;}
int { col+=yyleng;    return TOK_INT;}
boolean { col+=yyleng;    return TOK_BOOLEAN; }
array { col+=yyleng;    return TOK_ARRAY; }
function { col+=yyleng;    return TOK_FUNCTION; }
if { col+=yyleng;    return TOK_IF; }
else { col+=yyleng;    return TOK_ELSE; }
while { col+=yyleng;    return TOK_WHILE; }
scanf { col+=yyleng;    return TOK_SCANF; }
printf { col+=yyleng;    return TOK_PRINTF; }
return { col+=yyleng;    return TOK_RETURN; }

";" { col+=yyleng;    return yytext[0]; }
"," { col+=yyleng;    return yytext[0]; }
"(" { col+=yyleng;    return yytext[0]; } 
")" { col+=yyleng;    return yytext[0]; }
"[" { col+=yyleng;    return yytext[0]; }
"]" { col+=yyleng;    return yytext[0]; }
"{" { col+=yyleng;    return yytext[0]; }
"}" { col+=yyleng;    return yytext[0]; }
"=" { col+=yyleng;    return yytext[0]; }
"+" { col+=yyleng;    return yytext[0]; }
"-" { col+=yyleng;    return yytext[0]; }
"/" { col+=yyleng;    return yytext[0]; }
"*" { col+=yyleng;    return yytext[0]; }
"&&" { col+=yyleng;    return TOK_AND; }
"||" { col+=yyleng;    return TOK_OR; }
"!" { col+=yyleng;    return TOK_NOT; }
"==" { col+=yyleng;    return TOK_IGUAL; }
"!=" { col+=yyleng;    return TOK_DISTINTO; }
"<=" { col+=yyleng;    return TOK_MENORIGUAL; }
">=" { col+=yyleng;    return TOK_MAYORIGUAL; }
"<" { col+=yyleng;    return yytext[0]; }
">" { col+=yyleng;    return yytext[0]; }

true { col+=yyleng;    return TOK_TRUE; }
false { col+=yyleng;    return TOK_FALSE; }
[0-9]+ { yylval.atributos.valor_entero=atoi(yytext); col+=yyleng; return TOK_CONSTANTE_ENTERA; }

[a-zA-Z][a-zA-Z0-9]* { if (yyleng<101){
						 
						strcpy(yylval.atributos.lexema,yytext);
						return TOK_IDENTIFICADOR;
					} else {
						fprintf(stderr, "Error en fila: %d, col:%d. Identificador %s demasiado largo\n", row, col, yytext);
						return TOK_ERROR;
					}
				}

. { fprintf(stderr, "Error en fila:%d, col:%d. Caracter prohibido: %s\n", row, col, yytext);
return TOK_ERROR; }

%%

