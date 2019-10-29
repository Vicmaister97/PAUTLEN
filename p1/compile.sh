#!/bin/sh
gcc *.c alfa.h -o generacion
./generacion $1.asm
nasm -g -o $1.o -f elf32 $1.asm
gcc -m32 -o $1 $1.o alfalib.o
rm $1.o generacion
