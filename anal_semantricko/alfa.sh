#Clean old files.
rm lex.yy.c
rm y.tab.c

#Generate C source code from the analyzer frameworks.
flex alfa.l
bison -d -y -v alfa.y

#Compile all the code.
gcc -Wall -o pruebaSemantico lex.yy.c y.tab.c TS/tabla.c gen_codigo/generacion.c y.tab.h

#Execute the compiler.
./pruebaSemantico $1 $1.asm

nasm -g -o $1.o -f elf32 $1.asm

gcc -m32 -o $2 $1.o alfalib.o



#Verify if we have done it well.
#diff -bB salida_sem_$2.txt misalida_sem_$2.txt


#
# #!/bin/sh
# gcc *.c alfa.h -o generacion
# ./generacion $1.asm
# nasm -g -o $1.o -f elf32 $1.asm
# gcc -m32 -o $1 $1.o alfalib.o
# rm $1.o generacion
