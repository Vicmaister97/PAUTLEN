#ifndef ALFA_H
#define ALFA_H

#include <stdio.h>

//Tipos
#define BOOLEAN			1
#define INT 			0

//Clase
#define ESCALAR         1
#define VECTOR          0

//Categoria
#define PARAMETRO       0
#define FUNCION 		1
#define VARIABLE 		2

//Macros tamanio
#define MAX_ETIQUETAS   32768
#define MAX_TAMANIO_VECTOR 64

typedef struct atributos{
    char lexema[101];
    int tipo;
    int valor_entero;
    int es_direccion;
    int etiqueta;
    int clase;
} tipo_atributos;



void escribir_subseccion_data(FILE* fpasm);
void escribir_cabecera_bss(FILE* fpasm);
void escribir_inicio_main(FILE* fpasm);
void escribir_fin(FILE* fpasm);
void escribir_segmento_codigo(FILE* fpasm);
void uno_si_mayor_de_10(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta);

#endif
