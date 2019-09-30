#ifndef ALFA_H
#define ALFA_H

#include <stdio.h>

#define ENTERO          0
#define BOOLEANO        1
#define MAX_ETIQUETAS   32768

void escribir_subseccion_data(FILE* fpasm);
void escribir_cabecera_bss(FILE* fpasm);
void escribir_inicio_main(FILE* fpasm);
void escribir_fin(FILE* fpasm);
void escribir_segmento_codigo(FILE* fpasm);
void uno_si_mayor_de_10(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta);

#endif
