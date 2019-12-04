pruebaSintactico: lex.yy.c
	gcc -Wall -o pruebaSintactico lex.yy.c

lex.yy.c: alfa.l
	lex alfa.l

all:
	make pruebaSintactico

clean:
	rm -rf *.o lex.yy.c

