/*Práctica1 PAUTLEN
Autores:  Alfonso Carvajal
          Victor Garcia
Grupo:    1401*/

#include "generacion.h"


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
  /* Si declaramos un INT*/
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
  fprintf(fpasm, "\t; inicio de la funcion escribir_fin\n");
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
  fprintf(fpasm, "\t; inicio de la funcion escribir_operando\n");
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
  fprintf(fpasm, "\t; inicio de la funcion asignar\n");
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

/* FUNCIONES DE ESCRITURA Y LECTURA */
void leer(FILE* fpasm, char* nombre, int tipo){
  fprintf(fpasm, "\t; inicio de la funcion leer\n");
  /* Guardamos en la pila el nombre de la variable a leer*/
  fprintf(fpasm, "\tpush dword _%s\n", nombre);
  /* Lee una variable de tipo INT*/
  if (tipo == INT){
    fprintf(fpasm, "\tcall scan_int\n");
  }
  /* Lee una variable de tipo BOOLEAN*/
  else{
    fprintf(fpasm, "\tcall scan_boolean\n");
  }

  fprintf(fpasm, "\tadd esp, 4\n");

}


void escribir(FILE* fpasm, int es_variable, int tipo){
  fprintf(fpasm, "\t; inicio de la funcion escribir\n");
  /*Cargar contenido a imprimir de la pila */
  fprintf(fpasm, "\tpop dword eax\n");
  /*Si es 0 entonces se ha pasado por valor en la pila
  si no, se ha pasado la direccion del registro*/
  if(es_variable == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  /* Asignar a "nombre" el valor leido de la pila (contenido eax)*/
  fprintf(fpasm, "\tpush dword eax\n");
  /* Lee una variable de tipo INT*/
  if (tipo == INT){
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
  fprintf(fpasm, "\t; inicio de la funcion sumar\n");
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
  fprintf(fpasm, "\t; inicio de la funcion restar\n");
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
  fprintf(fpasm, "\t; inicio de la funcion multiplicar\n");
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
  fprintf(fpasm, "\t; inicio de la funcion dividir\n");
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
  fprintf(fpasm, "\t; inicio de la funcion o\n");
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
  fprintf(fpasm, "\t; inicio de la funcion y\n");
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
  fprintf(fpasm, "\t; inicio de la funcion cambiar_signo\n");
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
  fprintf(fpasm, "\t; inicio de la funcion no\n");
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
  fprintf(fpasm, "\t; inicio de la funcion igual\n");
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
  fprintf(fpasm, "\t; inicio de la funcion distinto\n");
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
  fprintf(fpasm, "\t; inicio de la funcion menor_igual\n");
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
  fprintf(fpasm, "\t; inicio de la funcion mayor_igual\n");
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
  fprintf(fpasm, "\t; inicio de la funcion menor\n");
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
  fprintf(fpasm, "\t; inicio de la funcion mayor\n");
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
  ######################################################################
      SEGUNDA PARTE DE LA PRACTICA*/

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
  fprintf(fpasm, "\t; inicio de la funcion ifthen_inicio\n");
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
  fprintf(fpasm, "\t; inicio de la funcion ifthen_fin\n");
  fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}


void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
  fprintf(fpasm, "\t; inicio de la funcion ifthenelse_inicio\n");
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
  fprintf(fpasm, "\t; inicio de la funcion ifthenelse_fin_then\n");
  /* Ha terminado el bloque THEN, salta el bloque ELSE y va al final */
  fprintf(fpasm, "\tjmp fin_then_else_%d\n", etiqueta);
  /*  Etiqueta del fin del bloque */
  fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

void ifthenelse_fin( FILE * fpasm, int etiqueta){
  fprintf(fpasm, "\t; inicio de la funcion ifthenelse_fin\n");
  fprintf(fpasm, "fin_then_else_%d:\n", etiqueta);
}


void while_inicio(FILE * fpasm, int etiqueta){
  fprintf(fpasm, "\t; inicio de la funcion while_inicio\n");
  fprintf(fpasm, "\tinicio_while_%d:\n", etiqueta);
}

void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta){
  fprintf(fpasm, "\t; inicio de la funcion while_exp_pila\n");
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
  fprintf(fpasm, "\t; inicio de la funcion while_fin\n");
  /* Ha terminado el bloque WHILE, salta al inicio de este mismo bloque de nuevo */
  fprintf(fpasm, "\tjmp inicio_while_%d\n", etiqueta);
  /*  Etiqueta del fin del bloque */
  fprintf(fpasm, "fin_while_%d:\n", etiqueta);
}


void escribir_elemento_vector(FILE * fpasm,char * nombre_vector, int tam_max, int exp_es_direccion){
  fprintf(fpasm, "\t; inicio de la funcion escribir_elemento_vector\n");
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

/* FUNCIONES */
void declararFuncion(FILE * fpasm, char * nombre_funcion, int num_var_loc){
  fprintf(fpasm, "\t; inicio de la funcion declararFuncion\n");
  // etiqueta del inicio de la funcion es "_" seguido por el nombre de la funcion y ":"
  fprintf(fpasm, "\t_%s:\n", nombre_funcion);
  // guardar en la pila el registro ebp --> puntero base para localizar en la pila
  // los args y variables locales de la funcion
  fprintf(fpasm, "\tpush ebp\n");
  // copiamos en ebp el valor de puntero de pila (esp) para poder gestionar
  // acceso a los parametros y variables locales
  fprintf(fpasm, "\tmov ebp, esp\n");
  // reservamos espacio en la pila para las variables locales de la funcion
  // cada variable local son 4 bytes
  fprintf(fpasm, "\tsub esp, %d\n", 4*num_var_loc);

}

void retornarFuncion(FILE * fpasm, int es_variable){
  fprintf(fpasm, "\t; inicio de la funcion retornarFuncion\n");
  fprintf(fpasm, "\tpop dword eax\n");
  // si es_variable == 1 entonces lo que esta en la cima de la pila es una variable o algo equivalente
  // y queremos el contenido de lo que esta guardado en esa direccion
  // el valor de retorno de la funcion se deja en eax
  if(es_variable == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }
  // restauramos el puntero de la pila
  fprintf(fpasm, "\tmov esp, ebp\n");
  // sacamos ebp de la pila
  fprintf(fpasm, "\tpop dword ebp\n");
  // volvemos al programa llamante y saca de la pila la direccion de retorno
  fprintf(fpasm, "\tret\n");
}


void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros){
  fprintf(fpasm, "\t; inicio de la funcion escribirParametro\n");
  int aux_ebp;
  // cada argumento ocupa 4 bytes, por eso se multiplica por 4
  // 1er argumento se corresponde con la posicion 0
  aux_ebp = 4 * (1 + (num_total_parametros - pos_parametro));
  // calculamos la direccion efectiva del parametro y la cargamos en eax
  // al encontrarnos dentro de la funcion, ebp contiene el valor de puntero a pila (esp)
  // donde se encuentran todos los parametros
  fprintf(fpasm, "\tlea eax, [ebp + %d]\n", aux_ebp);
  // insertamos en la pila eax, que contiene la direccion efectiva del parametro
  fprintf(fpasm, "\tpush dword eax\n");
}

void escribirVariableLocal(FILE* fpasm, int posicion_variable_local){
  fprintf(fpasm, "\t; inicio de la funcion escribirVariableLocal\n");
  int aux_ebp;
  // cada argumento ocupa 4 bytes, por eso se multiplica por 4
  // 1er argumento se corresponde con la posicion 1
  aux_ebp = 4 * posicion_variable_local;
  // calculamos la direccion efectiva del parametro y la cargamos en eax
  // al encontrarnos dentro de la funcion, ebp contiene el valor de puntero a pila (esp)
  // donde se encuentran todos los argumentos
  fprintf(fpasm, "\tlea eax, [ebp - %d]\n", aux_ebp);
  // insertamos en la pila eax, que contiene la direccion efectiva del parametro
  fprintf(fpasm, "\tpush dword eax\n");
}

void asignarDestinoEnPila(FILE* fpasm, int es_variable){
  fprintf(fpasm, "\t; inicio de la funcion asignarDestinoEnPila\n");
  /* Comenzamos extrayendo de la pila el destino donde realizaremos la asignacion*/
  fprintf(fpasm,"\tpop dword ebx\n");
  /* Acto seguido, extraemos el valor a asignar*/
  fprintf(fpasm,"\tpop dword eax\n");
  /* Comprobamos si el valor leido es una variable*/
  if (es_variable == 1){
    fprintf(fpasm, "\tmov eax, [eax]\n");
  }

  /* Finalmente, guardamos el valor leido en el destino correspondiente
  [ebx] = eax*/
  fprintf(fpasm, "\tmov dword [ebx], eax\n");
}

void operandoEnPilaAArgumento(FILE * fpasm, int es_variable){
  fprintf(fpasm, "\t; inicio de la funcion operandoEnPilaAArgumento\n");
  /* Comprobamos si el valor leido es una variable*/
  if (es_variable == 1){
    /* Extramos de la pila el operando que está como variable*/
    fprintf(fpasm,"\tpop dword eax\n");
    /* Guardamos el valor de la variable */
    fprintf(fpasm, "\tmov eax, [eax]\n");
    /* Metemos en la pila el valor del operando */
    fprintf(fpasm,"\tpush dword eax\n");
  }

  /* EN CASO DE NO SER UNA VARIABLE, YA ESTÁ GUARDADO EL VALOR DEL OPERANDO*/
}


void limpiarPila(FILE * fpasm, int num_argumentos){
  fprintf(fpasm, "\t; inicio de la funcion limpiarPila\n");
  /* Movemos el puntero de la pila para descartar los argumentos introducidos al llamar a la función*/
  /* Puesto que todos nuestros datos ocupan 32bytes, guardamos y leemos los datos en la pila con add esp 4, moviendonos de 4 en 4.
      Por ello, avanzamos la pila 4*num_argumentos*/
  fprintf(fpasm, "\tadd esp, %d\n", 4*num_argumentos);
}

void llamarFuncion(FILE * fpasm, char * nombre_funcion, int num_argumentos){
  fprintf(fpasm, "\t; inicio de la funcion llamarFuncion\n");
  /* Asumimos que los argumentos de la función ya están en la pila según el convenio fijado en el material de la asignatura */
  /* Llamamos a la rutina correspondiente*/
  fprintf(fpasm, "\tcall %s\n", nombre_funcion);
  /* Después de finalizar la función, limpiamos de la pila sus argumentos */
  limpiarPila(fpasm, num_argumentos);
  /* Dejamos en la cima de la pila el retorno de la función (SIEMPRE EN EAX SEGÚN CONVENIO) tras haberla limpiado de sus argumentos*/
  fprintf(fpasm, "\tpush dword eax\n");
}
