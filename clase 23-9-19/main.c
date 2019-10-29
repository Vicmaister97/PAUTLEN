#include <stdio.h>
#include "alfa.h"

int main(int argc, char ** argv)
{
	FILE * fd_asm;
        int etiqueta = 0;

	fd_asm = fopen(argv[1],"w");

	escribir_subseccion_data(fd_asm);
    escribir_cabecera_bss(fd_asm);
	escribir_segmento_codigo(fd_asm);
	escribir_inicio_main(fd_asm);


	fprintf(fd_asm, "\tpush dword 6\n");
	fprintf(fd_asm, "\tpush dword 5\n");

	//Debe imprimir 1 y devolver un 1.
	uno_si_mayor_de_10(fd_asm,0,0,etiqueta);
	etiqueta++;

	//fprintf(fd_asm, "\tadd esp, 4\n");
	fprintf(fd_asm, "\tpush dword 11\n");
    fprintf(fd_asm, "\tpush dword 3\n");

	//Debe imprimir 0 y devolver un 0.
    sumar(fd_asm,0,0);

	fprintf(fd_asm, "\tpush dword 5\n");
    fprintf(fd_asm, "\tpush dword 3\n");
	restar(fd_asm, 0,0);

	fprintf(fd_asm, "\tpush dword 2\n");
    fprintf(fd_asm, "\tpush dword 7\n");
	multiplicar(fd_asm, 0,0);


	fprintf(fd_asm, "\tpush dword 8\n");
    fprintf(fd_asm, "\tpush dword 2\n");
	dividir(fd_asm, 0,0);

	fprintf(fd_asm, "\tpush dword 5\n");
    fprintf(fd_asm, "\tpush dword 2\n");
	dividir(fd_asm, 0,0);

	fprintf(fd_asm, "\tpush dword 5\n");
    fprintf(fd_asm, "\tpush dword 0\n");
	dividir(fd_asm, 0,0);


	//fprintf(fd_asm, "\tadd esp, 4\n");

	escribir_fin(fd_asm);
    fclose(fd_asm);

    return 0;
}
