/*********************************************************
**
** Fichero: TOKENS.L
** Autores: Manuel Orantes Taboada, Víctor Bricio Blázquez, Víctor García Carrera.
** Función: Implementar el analizador léxico para el compilador
**	    a realizar en las prácticas de Procesadores de Lenguajes
**
*********************************************************/

/*----- Sección de Declaraciones --------------*/
%{

/**
 Buffer usado para almacenamiento temporal de cadenas de texto
**/

#define MAXLONBUFFER 200
char buffer[MAXLONBUFFER] ;

/*int line = 1;*/
%}

/** La siguiente declaración indica que no se va a escribir la función ’yywrap’
*** evita que se tenga que enlazar con -lfl, o que se tenga que escribir ’yywrap’
**/

%option noyywrap


%%
	/*----- Sección de Reglas ----------------*/
"main"                                       return MAIN;
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
\+                                           {yylval.attr = 0; return SYMBOL_OP;}
\-                                           {yylval.attr = 1; return SYMBOL_OP;}
"--"                                         return MINUSMINUS;
\*                                           {yylval.attr = 0; return BINARY_OP;}
\/                                           {yylval.attr = 1; return BINARY_OP;}
%                                            return BINARY_LIST_OP_I;
\*\*                                         return BINARY_LIST_OP_L;
">"                                          {yylval.attr = 0; return RELATION_OP;}
"<="                                         {yylval.attr = 1; return RELATION_OP;}
"<"                                          {yylval.attr = 2; return RELATION_OP;}
">="                                         {yylval.attr = 3; return RELATION_OP;}
"=="                                         {yylval.attr = 0; return EQUALS_OP;}
"<>"                                         {yylval.attr = 1; return EQUALS_OP;}
"and"                                        return AND_OP;
"or"                                         return OR_OP;
"xor"                                        return XOR_OP;
"<<"                                         return LIST_OP;
">>"                                         return LIST_OP;
"list_of"                                    return LIST_OF;
"int"                                        {yylval.type = INT; return BASIC_TYPES;}
"double"                                     {yylval.type = DOUBLE; return BASIC_TYPES;}
"boolean"                                    {yylval.type = BOOLEAN; return BASIC_TYPES;}
"char"                                       {yylval.type = CHAR; return BASIC_TYPES;}
"true"                                       {yylval.attr = 0; yylval.name = strdup(yytext) ;return CONST_BOOLEAN;}
"false"                                      {yylval.attr = 1; yylval.name = strdup(yytext) ;return CONST_BOOLEAN;}
[0-9]+                                       {yylval.name = strdup(yytext); yylval.attr = 0; return CONST_INT;}
[0-9]*\.[0-9]+                               {yylval.name = strdup(yytext); yylval.attr = 1; return CONST_DOUBLE;}
\"[^\"]\"                                    {yylval.name = strdup(yytext); yylval.attr = 2; return CONST_CHAR;}
\"[^\"]*\"                                   {yylval.name = strdup(yytext); yylval.attr = 3; return CADENA;}
[_a-zA-Z][_a-zA-Z0-9]*                       {yylval.name = strdup(yytext); yylval.attr = 4; return ID;}
\n                                           { /** lleva la cuenta de las líneas **/
						line++; }
[ \t]+	                                     { /** accion vacia: se ignoran los espacios y tabuladores **/ }
.                                            { /** token desconocido, se produce un mensaje de error **/
						snprintf(buffer, MAXLONBUFFER, "el(los) caracter(es) ’%s’ no forma(n) ningun token conocido", yytext);
						yyerror(buffer); }


%%
/*----- Sección de Procedimientos --------*/
