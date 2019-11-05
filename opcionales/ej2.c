#include <stdio.h>
#include "generacion.h"
int main (int argc, char** argv)
{
  FILE * salida;
  int etiqueta = 0;
  int getiqueta = 0;
  int etiquetas[MAX_ETIQUETAS];
  int cima_etiquetas=-1;

  if (argc != 2) {
    fprintf (stdout, "ERROR POCOS ARGUMENTOS\n");
    return -1;
  }
  salida = fopen(argv[1],"w");
  escribir_subseccion_data(salida);
  escribir_cabecera_bss(salida);
  declarar_variable(salida, "b1", BOOLEANO, 1);
  declarar_variable(salida, "x", ENTERO, 1);
  escribir_segmento_codigo(salida);
  escribir_inicio_main(salida);
  /* b1 = true; */
  escribir_operando(salida, "1", 0);
  asignar(salida, "b1", 0);
  /* Incluye aqui el codigo necesario para
  while (b1) {
    scanf x;
    b1 = x > 4;
    if (b1) {
      printf x;
    }
    else {
      printf false;
    }
  }
  */
  escribir_fin(salida);
  fclose(salida);
  return 0;
}
