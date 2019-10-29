#include <stdio.h>
#include "generacion.h"

int main(int argc, char** argv)
{
	FILE* fd_asm;

    if (argc != 2) { fprintf(stdout, "ERROR POCOS ARGUMENTOS\n"); return -1; }


	fd_asm = fopen(argv[1],"w");

	escribir_subseccion_data(fd_asm);
    escribir_cabecera_bss(fd_asm);
	declarar_variable(fd_asm, "x", ENTERO, 1);
	declarar_variable(fd_asm, "y", ENTERO, 1);
	declarar_variable(fd_asm, "z", ENTERO, 1);

	escribir_segmento_codigo(fd_asm);
	escribir_inicio_main(fd_asm);

	/* x=8; */
	escribir_operando(fd_asm, "8", 0);
	asignar(fd_asm, "x", 0);
	/* scanf(&y); */
	leer(fd_asm, "y", ENTERO);

	/* z = x + y */
	escribir_operando(fd_asm, "x", 1);
	escribir_operando(fd_asm, "y", 1);
	sumar(fd_asm, 1, 1);
	escribir(fd_asm, 1, ENTERO);
	
	escribir_fin(fd_asm);
	fclose(fd_asm);
	return 0;

}
