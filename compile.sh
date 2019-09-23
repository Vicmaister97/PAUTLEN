nasm -g -o $1.o -f elf32 $1.asm
gcc -m32 -o $1 $1.o alfalib.o
