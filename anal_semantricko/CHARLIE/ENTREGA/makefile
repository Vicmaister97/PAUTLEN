all:
	flex alfa.l
	bison -d -y -v alfa.y

	#Compile all the code.
	gcc -g -c  tablasimbolos.c
	gcc -g -c  lex.yy.c
	gcc -g -c  generacion.c


	gcc -g -o ./alfa y.tab.c generacion.o tablasimbolos.o lex.yy.o 

clean:
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
	rm pruebaSemantico
	rm y.output
	rm out*



