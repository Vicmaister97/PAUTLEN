#Clean old files.
rm lex.yy.c
rm y.tab.c

#Generate C source code from the analyzer frameworks.
flex $1.l
bison -d -y -v $1.y 

#Compile all the code.
gcc -Wall -o pruebaSintactico lex.yy.c y.tab.c y.tab.h

#Execute the compiler.
./pruebaSintactico entrada_sin_$2.txt misalida_sin_$2.txt

#Verify if we have done it well.
diff -bB salida_sin_$2.txt misalida_sin_$2.txt
