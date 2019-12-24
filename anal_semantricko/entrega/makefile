all:
	flex alfa.l
	bison -d -y -v alfa.y

	#Compile all the code.
	gcc -Wall -o pruebaSemantico lex.yy.c y.tab.c TS/tabla.c gen_codigo/generacion.c y.tab.h

clean:
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
	rm pruebaSemantico
	rm y.output
