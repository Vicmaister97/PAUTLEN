#Clean old files.
rm lex.yy.c
rm y.tab.c

#Generate C source code from the analyzer frameworks.
flex $1.l
bison -d -y -v $1.y

#Compile all the code.
gcc -Wall -o pruebaSemantico lex.yy.c y.tab.c TS/tabla.c y.tab.h

#Execute the compiler.
./pruebaSemantico main$2.alfa misalida_sem_$2.txt

#Verify if we have done it well.
#diff -bB salida_sem_$2.txt misalida_sem_$2.txt
