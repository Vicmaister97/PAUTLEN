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
