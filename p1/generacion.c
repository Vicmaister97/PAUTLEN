/*Práctica1 PAUTLEN
Autores:  Alfonso Carvajal
          Victor Garcia
Grupo:    1401*/

#include "generacion.h"
#include "alfa.h"


void escribir_cabecera_bss(FILE* fpasm){
  fprintf(fpasm, "segment .bss\n");
  fprintf(fpasm, "\t;declaracion de variables sin inicializar\n\t;\n");
  fprintf(fpasm, "\t__esp resd 1\n");
    /*FALTA escribir variables de las tablas de simbolos*/

}


void escribir_subseccion_data(FILE* fpasm){
  fprintf(fpasm, "segment .data\n");
  fprintf(fpasm, "\t;declaracion de variables inicializadas\n\t;\n");
  fprintf(fpasm, "\tmensaje_1 db \"División por cero\", 0\n");
  fprintf(fpasm, "\tmensaje_2 db \"Indice fuera de rango\", 0\n");
}


void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano){
  /* Si declaramos un ENTERO*/
  /*if (tipo == 0){

  }*/
  // Declaramos la variable "nombre" con resd "tamano"
  fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);

}


void escribir_segmento_codigo(FILE* fpasm){
  fprintf(fpasm, "segment .text\n");
  fprintf(fpasm, "\tglobal main\n");
  /*Habilitar llamadas a funciones de alfalib*/
  fprintf(fpasm, "\t;habilitar funciones de alfalib\n");
  fprintf(fpasm, "\textern scan_int, scan_boolean\n");
  fprintf(fpasm, "\textern print_int, print_boolean, print_string, print_blank, print_endofline\n");
}


void escribir_inicio_main(FILE* fpasm){
  fprintf(fpasm, "\t;codigo correspondiente a la compilacion del no terminal \"funciones\" \n\t;\n");
  fprintf(fpasm, "main:\n");
  /*guardamos el actual valor del puntero de pila para restaurarlo al final del programa*/
  fprintf(fpasm, "\tmov dword [__esp], esp\n");
}


void escribir_fin(FILE* fpasm){
  fprintf(fpasm, "error_1:\n");
  fprintf(fpasm, "\tpush dword mensaje_1\n");
  fprintf(fpasm, "\tcall print_string\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tmov dword esp, [__esp]\n");
  fprintf(fpasm, "\tcall print_endofline\n");
  fprintf(fpasm, "\tjmp fin\n");

  fprintf(fpasm, "error_2:\n");
  fprintf(fpasm, "\tpush dword mensaje_2\n");
  fprintf(fpasm, "\tcall print_string\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tmov dword esp, [__esp]\n");
  fprintf(fpasm, "\tcall print_endofline\n");
  fprintf(fpasm, "\tjmp fin\n");
  
  fprintf(fpasm, "fin:ret\n");

  /*fprintf(fpasm, "\n\tmov ebx, 0\n");
  fprintf(fpasm, "\tmov eax, 1\n");
  fprintf(fpasm, "\tint 80h\n");*/

}


void escribir_operando(FILE* fpasm, char* nombre, int es_variable){
  /* Si el operando es un valor*/
  if (es_variable == 0){
    fprintf(fpasm, "\tpush dword %s\n", nombre);
  }
  /* Si el operando es una variable*/
  else{
    fprintf(fpasm, "\tpush dword [_%s]\n", nombre);
  }

    //TRICK1
  /*Imprime por pantalla el resultado que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}

void asignar(FILE* fpasm, char* nombre, int es_variable){
  /*Cargar contenido de la pila */
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /* Asignar a "nombre" el valor leido de la pila (contenido eax)*/
  fprintf(fpasm, "\tmov dword [_%s] , eax \n", nombre);

  //TRICK1
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword [_%s]\n", nombre);
  /*Imprime por pantalla el resultado que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

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
  /*Si es menor de 10, escribe el 0*/
  fprintf(fpasm, "\tjle fin_if_%d\n", etiqueta);
  /*La suma de las dos variables es mayor que 10 => escribe un 1*/
  fprintf(fpasm, "\tmov ecx, 1\n");
  // fprint(fpasm, "\tjmp ENDCMP\n");

  fprintf(fpasm, "fin_if_%d:", etiqueta);
  /*Insertamos el valor de la comparacion: 1 si mayor, 0 si no*/
  fprintf(fpasm, "\n\tpush dword ecx\n");
  /*Imprime por pantalla el numero que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}

/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */

/* Función que suma 2 operandos.  es_variable_x = 0 valor   = 1 referencia */
void sumar(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Suma: [eax] = [eax] + [ebx]*/
  fprintf(fpasm, "\tadd eax, ebx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");

  /*Imprime por pantalla el resultado que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}

/* Función que resta 2 operandos.  es_variable_x = 0 valor   = 1 referencia */
void restar(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Segunda variable, es la que se encuentra en el tope de la pila*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Resta: [eax] = [eax] - [ebx]*/
  fprintf(fpasm, "\tsub eax, ebx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");

  /*Imprime por pantalla el resultado que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}

/* Función que multiplica 2 operandos.  es_variable_x = 0 valor   = 1 referencia */
void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Mult: [eax] = [eax]*[ebx]*/
  fprintf(fpasm, "\timul ebx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");

  /*Imprime por pantalla el resultado que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}

/* Función que divide 2 operandos.  es_variable_x = 0 valor   = 1 referencia */
void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Divisor*/
  fprintf(fpasm, "\tpop dword ecx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ecx, [ecx]\n");
  }
  fprintf(fpasm, "\tcmp ecx, 0\n");
  fprintf(fpasm, "\tje error_1\n");

  /*Dividendo*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Extendemos el dividendo para la división*/
  fprintf(fpasm, "\tcdq\n");
  /*Div: [eax] = [edx:eax]/[ecx]*/
  fprintf(fpasm, "\tidiv ecx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");

  /*Imprime por pantalla el resultado que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}


/* FUNCIONES DE ESCRITURA Y LECTURA */
void leer(FILE* fpasm, char* nombre, int tipo){
  /* Guardamos en la pila el nombre de la variable a leer*/
  fprintf(fpasm, "\tpush dword _%s\n", nombre);
  /* Lee una variable de tipo ENTERO*/
  if (tipo == 0){
    fprintf(fpasm, "\tcall scan_int\n");
  }
  /* Lee ua variable de tipo BOOLEAN*/
  else{
    fprintf(fpasm, "\tcall scan_boolean\n");
  }

  fprintf(fpasm, "\tadd esp, 4\n");

  //TRICK1
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword [_%s]\n", nombre);
  /*Imprime por pantalla el resultado que hemos metido a la pila*/
  fprintf(fpasm, "\tcall print_int\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}


void escribir(FILE* fpasm, int es_variable, int tipo){
  /*Cargar contenido a imprimir de la pila */
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /* Asignar a "nombre" el valor leido de la pila (contenido eax)*/
  fprintf(fpasm, "\tpush dword eax\n");
  /* Lee una variable de tipo ENTERO*/
  if (tipo == 0){
    fprintf(fpasm, "\tcall print_int\n");
  }
  /* Lee ua variable de tipo BOOLEAN*/
  else{
    fprintf(fpasm, "\tcall print_boolean\n");
  }

  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

}