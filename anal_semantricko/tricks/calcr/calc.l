%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define YY_DECL int yylex()
#include "calc.tab.h"
#include "defs.h"

%}

%%

[ \t]	; // ignore all whitespace
[0-9]+		{
    //struct TIPO_ATRIBUTO attr = (struct TIPO_ATRIBUTO) yylval.atributo;
    yylval.atributo.tipo = NUMERO;
    yylval.atributo.valor = atoi(yytext);
    return T_INT;
}
\n		{return T_NEWLINE;}
"+"		{return T_PLUS;}
"-"		{return T_MINUS;}
"*"		{return T_MULTIPLY;}
"("		{return T_LEFT;}
")"		{return T_RIGHT;}
"="     {return T_EQUAL;}
"quit"	{return T_QUIT;}
[a-zA-Z] { 
    yylval.atributo.tipo = VARIABLE;
    yylval.atributo.nombre = yytext[0];
    return T_VAR;
}
.       { return T_ERROR;}
%%
