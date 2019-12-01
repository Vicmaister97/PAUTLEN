%{
#include <stdio.h>
...
%}

/* Palabras reservadas */
%token TOK_MAIN
%token TOK_INT
...
%%

programa: TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones funciones sentencias TOK_LLAVEDERECHA {fprintf(out, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");}
        ;

declaraciones:  declaracion {fprintf(out, ";R2:\t<declaraciones> ::= <declaracion>\n");}
              | declaracion declaraciones {fprintf(out, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");}

declaracion:  clase identificadores TOK_PUNTOYCOMA {fprintf(out, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");}

clase:  clase_escalar {fprintf(out, ";R5:\t<clase> ::= <clase_escalar>\n");}
      | clase_vector {fprintf(out, ";R7:\t<clase> ::= <clase_vector>\n");}

clase_escalar:  tipo {fprintf(out, ";R9:\t<clase_escalar> ::= <tipo>\n");}

tipo: TOK_INT {fprintf(out, ";R10:\t<tipo> ::= int\n");}
    | TOK_BOOLEAN {fprintf(out, ";R11:\t<tipo> ::= boolean\n");}

clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO constante_entera TOK_CORCHETEDERECHO {fprintf(out, ";R15:\tclase_vector ::= array tipo [ constante_entera ]\n");}

identificador:

...
%%

void yyerror(const char * s) {
    if(!is_morpho) {
        printf("****Error sintactico en [lin %ld, col %ld]\n", num_lin, num_col);
    }
}
