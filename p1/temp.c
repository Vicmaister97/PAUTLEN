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
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

void declararFuncion(FILE * fd_asm, char * nombre_funcion, int num_var_loc){
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

void retornarFuncion(FILE * fd_asm, int es_variable){
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
