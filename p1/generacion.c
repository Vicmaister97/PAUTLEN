/*Práctica1 PAUTLEN
Autores:  Alfonso Carvajal
          Victor Garcia
Grupo:    1401*/

#include "generacion.h"

void escribir_subseccion_data(FILE* fpasm){
  fprintf(fpasm, "segment .data\n");
  fprintf(fpasm, "\t;declaracion de variables inicializadas\n\t;\n");
  fprintf(fpasm, "\tmensaje_1 db \"División por cero\", 0");
}
void escribir_cabecera_bss(FILE* fpasm){
  fprintf(fpasm, "segment .bss\n");
  /*Escribir variables de las tablas de simbolos*/
  fprintf(fpasm, "\t__esp resd 1\n");
  fprintf(fpasm, "\t;declaracion de variables sin inicializar\n\t;\n");
}
void escribir_inicio_main(FILE* fpasm){
  fprintf(fpasm, "main:\n");
  /*guardamos el actual valor del puntero de pila para restaurarlo al final del programa*/
  fprintf(fpasm, "\tmov dword __esp, [esp]\n");
}
void escribir_fin(FILE* fpasm){
  fprintf(fpasm, "\tmov dword esp, [__esp]\n");

  /*fprintf(fpasm, "\n\tmov ebx, 0\n");
  fprintf(fpasm, "\tmov eax, 1\n");
  fprintf(fpasm, "\tint 80h\n");*/

  fprintf(fpasm, "\tret\n");
}

void escribir_segmento_codigo(FILE* fpasm){
  fprintf(fpasm, "segment .text\n");
  fprintf(fpasm, "\tglobal main\n");
  /*Habilitar llamadas a funciones de alfalib*/
  fprintf(fpasm, "\t;habilitar funciones de alfalib\n");
  fprintf(fpasm, "\textern scan_int, scan_boolean\n");
  fprintf(fpasm, "\textern print_int, print_boolean, print_string, print_blank, print_endofline\n");
}


void uno_si_mayor_de_10(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta){
  /*Cargar contenido de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Comparacion*/
  /*Suma: [eax] = [eax] + [ebx]*/
  fprintf(fpasm, "\tadd eax, ebx\n");

  /*La suma de las dos variables es menor que 10 => escribe un 0*/
  fprintf(fpasm, "\tmov ecx, 0\n");

  /*Comparamos [eax] con 10*/
  fprintf(fpasm, "\tcmp eax, 10\n");
  fprintf(fpasm, "\tjle fin_if_%d\n", etiqueta);
  /*La suma de las dos variables es mayor que 10 => escribe un 1*/
  fprintf(fpasm, "\tmov ecx, 1\n");
  // fprint(fpasm, "\tjmp ENDCMP\n");

  fprintf(fpasm, "fin_if_%d:", etiqueta);
  /*Insertamos el valor de la comparacion: 1 si mayor, 0 si no*/
  fprintf(fpasm, "\t\tpush dword ecx\n");
  /*Imprime por pantalla el numero que hemos metido a la pila*/
  fprintf(fpasm, "\t\tcall print_int\n");
  fprintf(fpasm, "\t\tadd esp, 4\n");
  fprintf(fpasm, "\t\tcall print_endofline\n");

}

/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */

/* es_variable_x = 0  valor   = 1   referencia */
void sumar(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Comparacion*/
  /*Suma: [eax] = [eax] + [ebx]*/
  fprintf(fpasm, "\tadd eax, ebx\n");

}