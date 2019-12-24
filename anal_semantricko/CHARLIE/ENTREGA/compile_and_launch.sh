#Clean old files.

#Generate C source code from the analyzer frameworks.
make all
#Execute the compiler.
./alfa $1.alfa out$1.asm

nasm -g -o out$1.o -f elf32 out$1.asm
gcc -m32 -o out$1 out$1.o alfalib.o

./out$1

