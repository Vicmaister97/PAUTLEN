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
  fprintf(fpasm, "\tjmp fin\n");
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
  
  fprintf(fpasm, "fin:\n");
  fprintf(fpasm, "\tmov dword esp, [__esp]\n");

  /*fprintf(fpasm, "\n\tmov ebx, 0\n");
  fprintf(fpasm, "\tmov eax, 1\n");
  fprintf(fpasm, "\tint 80h\n");*/

  fprintf(fpasm, "\tret\n");
}


void escribir_operando(FILE* fpasm, char* nombre, int es_variable){
  /* Si el operando es un valor*/
  if (es_variable == 0){
    fprintf(fpasm, "\tmov dword eax, %s\n", nombre);
  }
  /* Si el operando es una variable*/
  else{
    fprintf(fpasm, "\tmov dword eax, _%s\n", nombre);
  }

  fprintf(fpasm, "\tpush dword eax\n");

}

void asignar(FILE* fpasm, char* nombre, int es_variable){
  /*Cargar contenido de la pila */
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /* Asignar a "nombre" el valor leido de la pila (contenido eax)*/
  fprintf(fpasm, "\tmov dword [_%s], eax \n", nombre);

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


/* FUNCIONES DE ESCRITURA Y LECTURA */
void leer(FILE* fpasm, char* nombre, int tipo){
  /* Guardamos en la pila el nombre de la variable a leer*/
  fprintf(fpasm, "\tpush dword _%s\n", nombre);
  /* Lee una variable de tipo ENTERO*/
  if (tipo == ENTERO){
    fprintf(fpasm, "\tcall scan_int\n");
  }
  /* Lee una variable de tipo BOOLEAN*/
  else{
    fprintf(fpasm, "\tcall scan_boolean\n");
  }

  fprintf(fpasm, "\tadd esp, 4\n");

}


void escribir(FILE* fpasm, int es_variable, int tipo){
  /*Cargar contenido a imprimir de la pila */
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /* Asignar a "nombre" el valor leido de la pila (contenido eax)*/
  fprintf(fpasm, "\tpush dword eax\n");
  /* Lee una variable de tipo ENTERO*/
  if (tipo == ENTERO){
    fprintf(fpasm, "\tcall print_int\n");
  }
  /* Lee ua variable de tipo BOOLEAN*/
  else{
    fprintf(fpasm, "\tcall print_boolean\n");
  }

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
    fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /*Suma: [eax] = [eax] + [ebx]*/
  fprintf(fpasm, "\tadd eax, ebx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");
}


/* Función que resta 2 operandos.  es_variable_x = 0 valor   = 1 referencia */
void restar(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Segunda variable, es la que se encuentra en el tope de la pila*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /*Resta: [eax] = [eax] - [ebx]*/
  fprintf(fpasm, "\tsub eax, ebx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");
}


/* Función que multiplica 2 operandos.  es_variable_x = 0 valor   = 1 referencia */
void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /*Mult: [eax] = [eax]*[ebx]*/
  fprintf(fpasm, "\timul ebx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");
}


/* Función que divide 2 operandos.  es_variable_x = 0 valor   = 1 referencia */
void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Divisor*/
  fprintf(fpasm, "\tpop dword ecx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov dword ecx, [ecx]\n");
  }
  fprintf(fpasm, "\tcmp ecx, 0\n");
  fprintf(fpasm, "\tje error_1\n");

  /*Dividendo*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /*Extendemos el dividendo para la división*/
  fprintf(fpasm, "\tcdq\n");
  /*Div: [eax] = [edx:eax]/[ecx]*/
  fprintf(fpasm, "\tidiv ecx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");
}


void o(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /*Mult: [eax] = [eax]or[ebx]*/
  fprintf(fpasm, "\tor eax, ebx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");
}


void y(FILE* fpasm, int es_variable_1, int es_variable_2){
  /*Cargamos los operandos de la pila */
  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/

  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
  }

  /*Primera variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /*Mult: [eax] = [eax]and[ebx]*/
  fprintf(fpasm, "\tand eax, ebx\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");
}


void cambiar_signo(FILE* fpasm, int es_variable){
  /*Cargamos el operando de la pila */
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }


  /*Mult: [eax] = -[eax]*/
  fprintf(fpasm, "\tneg eax\n");
  /*Guardamos resultado en pila*/
  fprintf(fpasm, "\tpush dword eax\n");
}

void no(FILE* fpasm, int es_variable, int cuantos_no){
  /* Cargamos el operando de la pila */
  fprintf(fpasm, "\tpop dword eax\n");
  /* Si es una variable */
  if (es_variable == 1){
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /* Comprobamos si vamos a negar un 0*/
  fprintf(fpasm, "\tcmp eax, 0\n");
  /* Si niega un 0, saltamos a la rutina de negar un 0*/
  fprintf(fpasm, "\tje negar_0_%d\n", cuantos_no);
  /* Si niega un 1, metemos en la pila un 0*/
  fprintf(fpasm, "\tmov dword ebx, 0\n");
  fprintf(fpasm, "\tjmp fin_neg_%d\n", cuantos_no);


  fprintf(fpasm, "negar_0_%d:\n", cuantos_no);
  fprintf(fpasm, "\tmov dword ebx, 1\n");

  fprintf(fpasm, "fin_neg_%d:\n", cuantos_no);

  fprintf(fpasm, "\tpush dword ebx\n");

}

/* FUNCIONES COMPARATIVAS */

void igual(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta){
  /*Cargar contenido de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Comparacion*/
  /* Guardamos un 1 en caso de que sean iguales*/
  fprintf(fpasm, "\tmov ecx, 1\n");
  /*Comparamos [eax] con [ebx]*/
  fprintf(fpasm, "\tcmp eax, ebx\n");
  fprintf(fpasm, "\tje fin_igual_%d\n", etiqueta);
  /*Si no son iguales, escribe un 0 en la pila*/
  fprintf(fpasm, "\tmov ecx, 0\n");

  fprintf(fpasm, "fin_igual_%d:", etiqueta);
  /*Insertamos el valor de la comparacion: 1 si iguales, 0 si no*/
  fprintf(fpasm, "\n\tpush dword ecx\n");

}

void distinto(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta){
  /*Cargar contenido de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Comparacion*/
  /* Guardamos un 1 en caso de que sean iguales*/
  fprintf(fpasm, "\tmov ecx, 1\n");
  /*Comparamos [eax] con [ebx]*/
  fprintf(fpasm, "\tcmp eax, ebx\n");

  fprintf(fpasm, "\tjne fin_dist_%d\n", etiqueta);
  /*Si no son distintos, escribe un 0 en la pila*/
  fprintf(fpasm, "\tmov ecx, 0\n");

  fprintf(fpasm, "fin_dist_%d:", etiqueta);
  /*Insertamos el valor de la comparacion: 1 si iguales, 0 si no*/
  fprintf(fpasm, "\n\tpush dword ecx\n");

}

void menor_igual(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta){
  /*Cargar contenido de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Comparacion*/
  /* Guardamos un 1 en caso de que sean iguales*/
  fprintf(fpasm, "\tmov ecx, 1\n");
  /*Comparamos [eax] con [ebx]*/
  fprintf(fpasm, "\tcmp eax, ebx\n");
  fprintf(fpasm, "\tjle fin_menorigual_%d\n", etiqueta);
  /*Si no es menorigual, escribe un 0 en la pila*/
  fprintf(fpasm, "\tmov ecx, 0\n");
  // fprint(fpasm, "\tjmp ENDCMP\n");

  fprintf(fpasm, "fin_menorigual_%d:", etiqueta);
  /*Insertamos el valor de la comparacion: 1 si iguales, 0 si no*/
  fprintf(fpasm, "\n\tpush dword ecx\n");

}

void mayor_igual(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta){
  /*Cargar contenido de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Comparacion*/
  /* Guardamos un 1 en caso de que sean iguales*/
  fprintf(fpasm, "\tmov ecx, 1\n");
  /*Comparamos [eax] con [ebx]*/
  fprintf(fpasm, "\tcmp eax, ebx\n");
  fprintf(fpasm, "\tjge fin_menorigual_%d\n", etiqueta);
  /*Si no es menorigual, escribe un 0 en la pila*/
  fprintf(fpasm, "\tmov ecx, 0\n");
  // fprint(fpasm, "\tjmp ENDCMP\n");

  fprintf(fpasm, "fin_menorigual_%d:", etiqueta);
  /*Insertamos el valor de la comparacion: 1 si iguales, 0 si no*/
  fprintf(fpasm, "\n\tpush dword ecx\n");
}

void menor(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta){
  /*Cargar contenido de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Comparacion*/
  /* Guardamos un 1 en caso de que sean iguales*/
  fprintf(fpasm, "\tmov ecx, 1\n");
  /*Comparamos [eax] con [ebx]*/
  fprintf(fpasm, "\tcmp eax, ebx\n");
  fprintf(fpasm, "\tjl fin_menorigual_%d\n", etiqueta);
  /*Si no es menorigual, escribe un 0 en la pila*/
  fprintf(fpasm, "\tmov ecx, 0\n");
  // fprint(fpasm, "\tjmp ENDCMP\n");

  fprintf(fpasm, "fin_menorigual_%d:", etiqueta);
  /*Insertamos el valor de la comparacion: 1 si iguales, 0 si no*/
  fprintf(fpasm, "\n\tpush dword ecx\n");
}


void mayor(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta){
  /*Cargar contenido de la pila */
  /*Primera variable*/
  fprintf(fpasm, "\tpop dword ebx\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_2 == 1){
    fprintf(fpasm, "\tmov ebx, [ebx]\n");
  }

  /*Segunda variable*/
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable_1 == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /*Comparacion*/
  /* Guardamos un 1 en caso de que sean iguales*/
  fprintf(fpasm, "\tmov ecx, 1\n");
  /*Comparamos [eax] con [ebx]*/
  fprintf(fpasm, "\tcmp eax, ebx\n");
  fprintf(fpasm, "\tjg fin_menorigual_%d\n", etiqueta);
  /*Si no es menorigual, escribe un 0 en la pila*/
  fprintf(fpasm, "\tmov ecx, 0\n");
  // fprint(fpasm, "\tjmp ENDCMP\n");

  fprintf(fpasm, "fin_menorigual_%d:", etiqueta);
  /*Insertamos el valor de la comparacion: 1 si iguales, 0 si no*/
  fprintf(fpasm, "\n\tpush dword ecx\n");
}


/*######################################################################
      SEGUNDA PARTE DE LA PRACTICA*/

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
  /* Extraemos de la pila la expresión del condicional*/
  fprintf(fpasm, "\tpop eax\n");
  /* Comprobamos si la expresión es similar a una variable o no*/
  if (exp_es_variable == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /* Si la expresion es 1, se cumple la condición del IF*/
  fprintf(fpasm, "\tcmp eax, 1\n");
  /* Si la expresion NO es 1, es decir NO se cumple, salta al final de la rama THEN, NO entra en el IF*/
  fprintf(fpasm, "\tjne fin_then_%d\n", etiqueta);
}

void ifthen_fin(FILE * fpasm, int etiqueta){
  fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}


void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
  /* Extraemos de la pila la expresión del condicional*/
  fprintf(fpasm, "\tpop eax\n");
  /* Comprobamos si la expresión es similar a una variable o no*/
  if (exp_es_variable == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /* Si la expresion es 1, se cumple la condición del IF*/
  fprintf(fpasm, "\tcmp eax, 1\n");
  /* Si la expresion NO es 1, es decir NO se cumple, salta al final de la rama THEN, comienzo del ELSE, NO entra en el IF*/
  fprintf(fpasm, "\tjne fin_then_%d\n", etiqueta);
}

void ifthenelse_fin_then( FILE * fpasm, int etiqueta){
  /* Ha terminado el bloque THEN, salta el bloque ELSE y va al final */
  fprintf(fpasm, "\tjmp fin_then_else_%d\n", etiqueta);
  /*  Etiqueta del fin del bloque */
  fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

void ifthenelse_fin( FILE * fpasm, int etiqueta){
  fprintf(fpasm, "fin_then_else_%d:\n", etiqueta);
}


void while_inicio(FILE * fpasm, int etiqueta){
  fprintf(fpasm, "\tinicio_while_%d:\n", etiqueta);
}

void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta){
  /* Extraemos de la pila la expresión del condicional*/
  fprintf(fpasm, "\tpop eax\n");
  /* Comprobamos si la expresión es similar a una variable o no*/
  if (exp_es_variable == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /* Si la expresion es 1, se cumple la condición del WHILE*/
  fprintf(fpasm, "\tcmp eax, 1\n");
  /* Si la expresion NO es 1, es decir NO se cumple, salta al final del cuerpo del WHILE, NO entra en el WHILE*/
  fprintf(fpasm, "\tjne fin_while_%d\n", etiqueta);
}

void while_fin( FILE * fpasm, int etiqueta){
  /* Ha terminado el bloque WHILE, salta al inicio de este mismo bloque de nuevo */
  fprintf(fpasm, "\tjmp inicio_while_%d\n", etiqueta);
  /*  Etiqueta del fin del bloque */
  fprintf(fpasm, "fin_while_%d:\n", etiqueta);
}


void escribir_elemento_vector(FILE * fpasm,char * nombre_vector, int tam_max, int exp_es_direccion){
  // sacamos de la pila la expresion que indexa al vector
  fprintf(fpasm, "\tpop dword eax\n");
  // si exp_es_direccion == 1 entonces la expresion es una variable o algo equivalente
  // y queremos el contenido de lo que esta guardado en esa direccion
  if(exp_es_direccion == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }
  // Si el indice es menor que 0, tiene que dar un error porque no es parte del vector
  fprintf(fpasm, "\tcmp eax, 0\n");
  fprintf(fpasm, "\tjl near error_2\n");

  // si el indice es mayor de lo permitido: (tam vector - 1) entonces
  // tiene que dar un error porque no es parte del vector
  fprintf(fpasm, "\tcmp eax, %d\n", tam_max);
  fprintf(fpasm, "\tjge near error_2\n");

  // Si hemos llegado aqui, el indice es correcto y esta en eax

  // La direccion del primer elemento del vector en memoria es a donde apunta el nombre_vector
  // cargamos esta direccion en edx
  fprintf(fpasm, "\tmov dword edx, _%s\n", nombre_vector);

  // ahora cargamos en eax la direccion del elemento indexado
  // esta direccion es el la direccion del inicio del vector + eax*4 (indice x 4 bytes)
  fprintf(fpasm, "\tlea eax, [edx + eax*4]\n");

  // ahora solo queda meter la direccion del elemento indexado en la pila
  fprintf(fpasm, "\tpush dword eax\n");
}
