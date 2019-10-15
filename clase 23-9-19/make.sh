#!/bin/sh
gcc *.c alfa.h -o ej1
./ej1 nasm.asm
nasm -g -o nasm.o -f elf32 nasm.asm
gcc -m32 -o nasm nasm.o alfalib.o
rm nasm.o ej1