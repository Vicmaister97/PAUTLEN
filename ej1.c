/*Ejercicio ej1.c opcional PAUTLEN 23/09/2019
Autores:  Alfonso Carvajal
          Victor Garcia
Grupo:    1401*/

// #include "alfa.h"

void escribir_subseccion_data(FILE* fpasm){
  fprintf(fpasm, "\tsegment .data\n");
  fprintf(fpasm, "\t;guardamos posicion pila\n\tpila resd 1\n");
}
void escribir_cabecera_bss(FILE* fpasm){
  fprintf(fpasm, "\tsegment .bss\n");
  /*Escribir variables de las tablas de simbolos*/
  fprintf(fpasm, "\tpila resd 1\n");
  fprintf(fpasm, "\t;declaracion de variables sin inicializar\n\t;\n");
}
void escribir_inicio_main(FILE* fpasm){
  fprintf(fpasm, "\tmain:\n");
  /*guardamos el actual valor del puntero de pila para restaurarlo al final del programa*/
  fprintf(fpasm, "\tmov dword[pila], esp\n");
}
void escribir_fin(FILE* fpasm){
  fprintf(fpasm, "\tmov dword esp, [pila]\n");
  fprintf(fpasm, "\tret\n");
}

void escribir_segmento_codigo(FILE* fpasm){
  fprintf(fpasm, "\tsegment .text\n");
  fprintf(fpasm, "\tglobal main\n");
  /*Habilitar llamadas a funciones de alfalib*/
  fprintf(fpasm, "\t;habilitar funciones de alfalib\n");
  fprintf(fpasm, "\textern scan_int, scan_boolean\n");
  fprintf(fpasm, "\textern print_int, print_boolean, print_string, print_blank, print_endofline\n");
}


void uno_si_mayor_de_10(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta){
  /*Cargar contenido de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword, eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword, ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Comparacion*/
  /*Suma: [eax] = [eax] + [ebx]*/
  fprintf(fpasm, "\tadd eax, ebx\n");

  /*Comparamos [eax] con 10*/
  fprintf(fpasm, "\tcmp eax, 10\n");
  fprintf(fpasm, "\tjle MENOR\n");
  /*La suma de las dos variables es mayor que 10 => escribe un 1*/
  fprintf(fpasm, "\tpush dword 1\n");
  // fprint(fpasm, "\tjmp ENDCMP\n");
  fprintf(fpasm, "\tjmp fin_if_%d\n", etiqueta);
  fprint(fpasm, "\tMENOR:\n");
  /*La suma de las dos variables es menor que 10 => escribe un 0*/
  fprintf(fpasm, "\tpush dword 0\n");
  fprintf(fpasm, "\tfin_if_%d:\n", etiqueta);
  /*Imprime por pantalla el numero que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}
