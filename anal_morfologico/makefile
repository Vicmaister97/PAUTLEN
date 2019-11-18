pruebaMorfo: lex.yy.c
	gcc -Wall -o pruebaMorfo lex.yy.c

lex.yy.c: pruebaMorfo.l
	lex pruebaMorfo.l

all:
	make pruebaMorfo

clean:
	rm -rf *.o lex.yy.c

