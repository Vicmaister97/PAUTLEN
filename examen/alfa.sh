make all

#Execute the compiler.
./pruebaSemantico $1.alf $2.asm

nasm -g -o $2.o -f elf32 $2.asm

gcc -m32 -o alfa $2.o alfalib.o
./alfa


#Verify if we have done it well.
#diff -bB salida_sem_$2.txt misalida_sem_$2.txt


#
# #!/bin/sh
# gcc *.c alfa.h -o generacion
# ./generacion $1.asm
# nasm -g -o $1.o -f elf32 $1.asm
# gcc -m32 -o $1 $1.o alfalib.o
# rm $1.o generacion
