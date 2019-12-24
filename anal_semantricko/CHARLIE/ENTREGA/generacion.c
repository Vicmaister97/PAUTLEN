#include <stdio.h>
#include "generacion.h"
#include "tablasimbolos.h"

void escribir_cabecera_bss(FILE* fpasm){
  fprintf(fpasm, "segment .bss\n");
  fprintf(fpasm, "\t__esp resd 1\n");
}


void escribir_subseccion_data(FILE* fpasm){
  fprintf(fpasm, "segment .data\n");
  fprintf(fpasm, "\terr_div0 db \"Error: dividiendo por 0\",0\n");
  fprintf(fpasm, "\terr_ioutrange db\"Error: indice fuera de rango\",0\n");
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
	if (tipo == BOOLEAN){
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
	if (tipo == BOOLEAN){
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














void escribir_elemento_vector(FILE * fpasm,char* nombre_vector, int tam_max, int exp_es_direccion){
// SE SACA DE LA PILA A UN REGISTRO EL VALOR DEL ÍNDICE
  fprintf(fpasm, "\tpop dword eax\n");
// HACIENDO LO QUE PROCEDA EN EL CASO DE QUE SEA UNA DIRECCIÓN (VARIABLE O EQUIVALENTE)
if(exp_es_direccion== 1)     
  fprintf(fpasm, "\tmov dword eax, [eax]\n");
  // SE PROGRAMA EL CONTROL DE ERRORES EN TIEMPO DE EJECUCIÓN
  /* SI EL INDICE ES <0 SE TERMINA EL PROGRAMA, SI NO, CONTINUA*/
  fprintf(fpasm, "\tcmp eax, 0\n");
  // SE SUPONE QUE EN LA DIRECCIÓN fin_indice_fuera_rango SE PROCESA ESTE ERROR EN TIEMPO DE EJECUCIÓN
   fprintf(fpasm, "\tjl near etiq_ibounds\n");
   /* SI EL INDICE ES > MAXIMO PERMITIDO SE TERMINA EL PROGRAMA, SI NO, CONTINUA*/
   // EL TAMANO MÁXIMO SE PROPORCIONA COMO ARGUMENTO
   fprintf(fpasm, "\tcmp eax, %d\n", tam_max-1);
   fprintf(fpasm, "\tjg near etiq_ibounds\n");
   // UNA OPCIÓN ES CALCULAR CON lea LA DIRECCIÓN EFECTIVA DEL ELEMENTO INDEXADO TRAS CALCULARLA 
   // DESPLAZANDO DESDE EL INICIO DEL VECTOR EL VALOR DEL INDICE
   fprintf(fpasm, "\tmov dword edx, _%s\n", nombre_vector);
   fprintf(fpasm, "\tlea eax, [edx+ eax*4]\n");  /* DIRECCION ELEMENTO INDEXADO EN eax*/
   fprintf(fpasm, "\tpush dword eax\n"); /* DIRECCION ELEMENTO INDEXADO EN CIMA PILA*/
 }

 void asignarDestinoEnPila(FILE* fpasm, int es_variable){
    fprintf(fpasm, ";asignaciondestinoenpila\n" );
  fprintf(fpasm, "\tpop dword ebx\n");
  fprintf(fpasm, "\tpop dword eax\n");
  if (es_variable)
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  fprintf(fpasm, "\tmov dword [ebx], eax\n");
 }
  void asignarDestinoEnPila2(FILE* fpasm, int es_variable){
  fprintf(fpasm, "\tpop dword ebx\n");
  fprintf(fpasm, "\tpop dword eax\n");
  if (es_variable)
    fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
  fprintf(fpasm, "\tmov dword [eax], ebx\n");
 }


 void declararFuncion(FILE * fd_asm, char* nombre_funcion, int num_var_loc){
 fprintf(fd_asm, "%s:\n", nombre_funcion);   // ETIQUETA DE INICIO DE LA FUNCIÓN 
 fprintf(fd_asm, "\tpush dword ebp\n"); // PRESERVACIÓN DE ebp/ esp
 fprintf(fd_asm, "\tmov ebp, esp\n");
 fprintf(fd_asm, "\tsub esp, %d\n", 4*num_var_loc);// RESERVA DE ESPACIO PARA LAS VARIABLES LOCALES EN LA PILA
}
void retornarFuncion(FILE * fd_asm, int es_variable){
fprintf(fd_asm, "\tpop dword eax\n");// RETORNO DE LA FUNCIÓN (EL VALOR DE LA EXPRESIÓN ESTÁ EN LA PILA
if(es_variable== 1)// Y TIENE QUE DEJARSE EN eax
  fprintf(fd_asm, "\tmov dword eax, [eax]\n");
fprintf(fd_asm, "\tmov esp, ebp\n");/* restaurar el puntero de pila */
fprintf(fd_asm, "\tpop dword  ebp\n");/* sacar de la pila ebp*/
fprintf(fd_asm, "\tret\n");/* vuelve al programa llamante y saca de la pila la dirde retorno */
}

void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros){
int d_ebp;
d_ebp = 4*( 1 + (num_total_parametros-pos_parametro));
fprintf(fpasm, "\tlea eax,[ebp + %d]\n", d_ebp); // UNA ALTERNATIVA ES CALCULAR LA DIRECCIÓN EFECTIVA CON lea DESPLAZANDO DESDE ebp
fprintf(fpasm, "\tpush dword eax\n");
}

void escribirVariableLocal(FILE* fpasm, int posicion_variable_local){
  int d_ebp;
  d_ebp= 4*posicion_variable_local;
  fprintf(fpasm, "\tlea eax, [ebp - %d]\n", d_ebp);
  fprintf(fpasm, "\tpush dword eax\n");
}

void operandoEnPilaAArgumento(FILE * fd_asm, int es_variable){
  if(es_variable== 1){
    fprintf(fd_asm, "\tpop dword eax\n"); // EN EL CASO DE QUE EN LA PILA TENGAMOS UNA VARIABLE Y NO UN VALOR
    fprintf(fd_asm, "\tmov dword eax, [eax]\n"); // SE SACA, SE ACCEDE AL VALOR Y SE VUELVE A AINTRODUCIR EN LA PILA
    fprintf(fd_asm, "\tpush dword eax\n");
    }
}

void llamarFuncion(FILE * fd_asm, char* nombre_funcion, int num_argumentos){
 fprintf(fd_asm, "\tcall %s\n", nombre_funcion); // SE LLAMA A LA FUNCIÓN
 fprintf(fd_asm, "\tadd esp, %d\n", 4*num_argumentos );// SE LIMPIA LA PILA (DE LOS ARGUMENTOS USADOS EN LA LLAMADA)
 fprintf(fd_asm, "\tpush dword eax\n");// EN NUESTRO LENGUAJE LAS LLAMADAS A FUNCIONES SON EXPRESIONES
// POR LO QUE EL EFECTO DE SER LLAMADAS (SU RETORNO) DEBE SER DEJADO // LA PILA
}

void escribirTabla(FILE * fd_asm, hash_t * tSimbolos){
  hash_iter_t * h_it = hash_iter_crear(tSimbolos);
  elemento * elem;
  /*Recorremos el iterador por toda la tabla*/
  while (hash_iter_al_final(h_it) == false){
    /* Obtenemos el elemento */
    elem = hash_obtener(tSimbolos, hash_iter_ver_actual(h_it));
    /* Escribimos la variable */
    declarar_variable(fd_asm, hash_iter_ver_actual(h_it), elem->tipo, elem->tamanio);
    /*Avanzamos a la siguiente posicion*/
    hash_iter_avanzar(h_it);
  }
  hash_iter_destruir(h_it);
}
