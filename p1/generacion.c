#include <stdio.h>
#include "generacion.h"


void escribir_cabecera_bss(FILE* fpasm){
  fprintf(fpasm, "segment .bss\n");
  fprintf(fpasm, "\t__esp resd 1\n");
}


void escribir_subseccion_data(FILE* fpasm){
  fprintf(fpasm, "segment .data\n");
  fprintf(fpasm, "\terr_div0 db \"Error: dividing by 0\",0\n");
  fprintf(fpasm, "\terr_ioutrange db\"Error: index out of bounds\",0\n");
}

void declarar_variable(FILE* fpasm, char * nombre, int tipo, int tamano){
  if(tipo==0 || tipo==1){
    fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);
  }
}

void escribir_segmento_codigo(FILE* fpasm){
  fprintf(fpasm, "segment .text\n");
  fprintf(fpasm, "\tglobal main\n");
  fprintf(fpasm, "\textern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean\n");
  fprintf(fpasm, "\textern print_endofline, print_blank, print_string\n");
  fprintf(fpasm, "\textern alfa_malloc, alfa_free, ld_float\n");
}

void escribir_inicio_main(FILE* fpasm){
  fprintf(fpasm, "main:\n");
  fprintf(fpasm, "\tmov dword [__esp], dword esp\n");
}

void escribir_fin(FILE* fpasm){
  fprintf(fpasm, "\tjmp endofcode\n" );
  fprintf(fpasm, "etiq_div0:\n");
  fprintf(fpasm, "\tpush dword err_div0\n");
  fprintf(fpasm, "\tcall print_string\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");
  fprintf(fpasm, "etiq_ibounds:\n");
  fprintf(fpasm, "\tpush dword err_ioutrange\n");
  fprintf(fpasm, "\tcall print_string\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");
  fprintf(fpasm, "endofcode:\n");
  fprintf(fpasm, "\tmov dword esp, [__esp]\n");
  fprintf(fpasm, "\tret\n");

}

void escribir_operando(FILE* fpasm, char* nombre, int es_variable){
  if(es_variable) {
    fprintf(fpasm, "\tmov dword eax, _%s\n", nombre);
  }
  else {
    fprintf(fpasm, "\tmov dword eax, %s\n", nombre);
  }

  fprintf(fpasm, "\tpush dword eax\n");
}

void asignar(FILE* fpasm, char* nombre, int es_variable){
  fprintf(fpasm, "\tpop dword eax\n");
  if(es_variable){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre);
}
void sumar(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    if(es_variable_1){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    fprintf(fpasm, "\tadd eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
    return;
}
void restar(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    if(es_variable_1){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    fprintf(fpasm, "\tsub ebx, eax\n");
    fprintf(fpasm, "\tpush dword ebx\n");
    return;
}
void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    if(es_variable_1){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    fprintf(fpasm, "\timul ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
    return;
}
void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(es_variable_2){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }

    if(es_variable_1){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    
    fprintf(fpasm, "\tmov dword edx, 0\n");
    fprintf(fpasm, "\tcmp ebx, edx\n");
    fprintf(fpasm, "\tje etiq_div0\n");
    fprintf(fpasm, "\tidiv ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
    return;
}
void o(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    if(es_variable_1){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    fprintf(fpasm, "\tor eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
    return;
}
void y(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    if(es_variable_1){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    fprintf(fpasm, "\tand eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
    return;
}
void cambiar_signo(FILE* fpasm, int es_variable){
  if(es_variable){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    fprintf(fpasm, "\timul eax, -1\n");
    fprintf(fpasm, "\tpush dword eax\n");
    return;
}
/*HAY QUE ANADIR CONTROL ERRORES PARA DISTINTO DE BOOLEANO 
  O
  EXPLICACION DE 0 A 1 Y CUALQUIER VALOR A 0 <----ACTUALMENTE IMPLEMENTADA 
  ADEMAS QUEDA POR ANADIR EL CUANTOSNO*/
void no(FILE* fpasm, int es_variable, int cuantos_no){
  if(es_variable){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    fprintf(fpasm, "\tmov dword edx, 0\n");
    fprintf(fpasm, "\tcmp eax, edx\n");
    fprintf(fpasm, "\tje etiq_%d\n", cuantos_no);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp near fin%d\n", cuantos_no);
    fprintf(fpasm, "\tetiq_%d:\n", cuantos_no);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tfin%d:\n", cuantos_no);
    return;
}


/* FUNCIONES COMPARATIVAS */

void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(es_variable2){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    if(es_variable1){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tje etiq_%d\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp near fin%d\n", etiqueta);
    fprintf(fpasm, "\tetiq_%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tfin%d:\n", etiqueta);
    return;
}
void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(es_variable2){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    if(es_variable1){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tje etiq_%d\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tjmp near fin%d\n", etiqueta);
    fprintf(fpasm, "\tetiq_%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tfin%d:\n", etiqueta);
    return;
}
void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(es_variable2){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    if(es_variable1){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjle etiq_%d\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp near fin%d\n", etiqueta);
    fprintf(fpasm, "\tetiq_%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tfin%d:\n", etiqueta);
    return;
}
void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
   if(es_variable2){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
   if(es_variable1){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjge etiq_%d\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp near fin%d\n", etiqueta);
    fprintf(fpasm, "\tetiq_%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tfin%d:\n", etiqueta);
    return;
}
void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
   if(es_variable2){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
     if(es_variable1){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjl etiq_%d\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp near fin%d\n", etiqueta);
    fprintf(fpasm, "\tetiq_%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tfin%d:\n", etiqueta);
    return;
}
void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(es_variable2){
      fprintf(fpasm, "\tpop dword ebx\n");
      fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword ebx\n");
    }
    if(es_variable1){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjg etiq_%d\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp near fin%d\n", etiqueta);
    fprintf(fpasm, "\tetiq_%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tfin%d:\n", etiqueta);
    return;
}

/* FUNCIONES DE ESCRITURA Y LECTURA */
/*De momento entendemos que si el tipo no es booleano va a ser entero siempre*/
void leer(FILE* fpasm, char* nombre, int tipo){
  fprintf(fpasm, "\tpush dword _%s\n", nombre);
  if (tipo == BOOLEANO){
    fprintf(fpasm, "\tcall scan_boolean\n");
  }
  else{
    fprintf(fpasm, "\tcall scan_int\n");
  }
  fprintf(fpasm, "\tadd esp, 4\n");
  return;

}
void escribir(FILE* fpasm, int es_variable, int tipo){
  if(es_variable){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    else {
      fprintf(fpasm, "\tpop dword eax\n");
    }
  fprintf(fpasm, "\tpush dword eax\n");
  if (tipo == BOOLEANO){
    fprintf(fpasm, "\tcall print_boolean\n");
  }
  else{
    fprintf(fpasm, "\tcall print_int\n");
  }
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");

  return;
}



void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
  /*SE SACA DE LA PILA EL VALOR DE LA EXPRESIÓN*/
  fprintf(fpasm, "\tpop eax\n");
  if(exp_es_variable == 1)
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  fprintf(fpasm, "\tcmp eax, 0\n");
/*SI ES CERO SE SALTA AL FINAL DE LA RAMA THEN*/
  fprintf(fpasm, "\tje near fin_then_%d\n", etiqueta);
}
void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
  /*SE SACA DE LA PILA EL VALOR DE LA EXPRESIÓN*/
  fprintf(fpasm, "\tpop eax\n");
  if(exp_es_variable == 1){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm, "\tcmp eax,0\n");
/*SI ES CERO SE SALTA AL FINAL DE LA RAMA THEN*/
  fprintf(fpasm, "\tje near fin_then_%d\n", etiqueta);
}
void ifthen_fin(FILE * fpasm, int etiqueta){
  fprintf(fpasm, "\tfin_then_%d:\n", etiqueta);
}
void ifthenelse_fin_then( FILE * fpasm, int etiqueta){
  fprintf(fpasm, "\tjmp near fin_ifelse_%d\n", etiqueta);
  fprintf(fpasm, "\tfin_then_%d:\n", etiqueta);
}
void ifthenelse_fin( FILE * fpasm, int etiqueta){
  fprintf(fpasm, "\tfin_ifelse_%d:\n", etiqueta);
}


void while_inicio(FILE * fpasm, int etiqueta){
  fprintf(fpasm, "\tinicio_while_%d:\n", etiqueta);
}
void while_exp_pila(FILE * fpasm, int exp_es_variable, int etiqueta){
  fprintf(fpasm, "\tpop eax\n");
  if (exp_es_variable > 0){
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm, "\tcmp eax, 0\n");
  fprintf(fpasm, "\tje near fin_while_%d\n", etiqueta);
}
void while_fin( FILE * fpasm, int etiqueta){
  fprintf(fpasm, "\tjmp near inicio_while_%d\n", etiqueta);
  fprintf(fpasm, "\tfin_while_%d:\n", etiqueta);
}