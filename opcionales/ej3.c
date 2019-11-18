#include "generacion.h"

int main (int argc, char ** argv)
{
  FILE * fd_asm;
  if (argc != 2) {
    fprintf (stdout, "ERROR POCOS ARGUMENTOS\n");
    return -1;
  }

  fd_asm = fopen(argv[1],"w");
  escribir_subseccion_data(fd_asm);
  escribir_cabecera_bss(fd_asm);
  //int x;
  declarar_variable(fd_asm, "x", ENTERO, 1);
  declarar_variable(fd_asm, "t", ENTERO, 1);
  declarar_variable(fd_asm, "m", ENTERO, 1);
  escribir_segmento_codigo(fd_asm);
  /* Declaracion de la funcion triple:
  function int triple(int a) {
    int tmp;
    tmp = a;
    return tmp * 3;
  }
  */
  /* Declaracion de la funcion mitad:
  function int mitad(int a) {
    int tmp;
    tmp = a;
    return tmp / 2;
  }
  */
  escribir_inicio_main(fd_asm);
  leer(fd_asm, "x", ENTERO);
  /* llamada a funcion con un argumento
   * y almacenamiento de retorno en variable
  t = triple(x);
  */
  
  /* llamada a funcion con un argumento
   * y almacenamiento de retorno en variable
  m = mitad(t);
  */
  escribir_operando(fd_asm,"t",1);
  escribir(fd_asm, 1, ENTERO);

  escribir_operando(fd_asm,"m",1);
  escribir(fd_asm, 1, ENTERO);

  escribir_operando(fd_asm, "t", 1);
  escribir_operando(fd_asm, "m", 1);
  multiplicar(fd_asm, 1, 1);

  escribir(fd_asm, 0, ENTERO);
  escribir_fin(fd_asm);
  fclose(fd_asm);
}
