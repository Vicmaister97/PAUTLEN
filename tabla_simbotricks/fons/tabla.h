/******************************************************
Nombre: tabla.h
Descripcion: Definicion de simbolos para la tabla de simbolos
******************************************************/
#ifndef _TABLA_H
#define _TABLA_H


#define TRUE 1
#define FALSE -1
#define OK 1
#define ERR -1
#define MAX_HASH 20

/* Categoría de un símbolo: variable, parámetro de función o función */
typedef enum { VARIABLE, PARAMETRO, FUNCION } CATEGORIA_SIMBOLO;

/* Tipo de un símbolo: sólo se trabajará con enteros y booleanos */
typedef enum { ENTERO, BOOLEANO } TIPO;

/* Categoría de la variable: puede ser variable atómicas (escalar) o lista/array (vector) */
typedef enum { ESCALAR, VECTOR } CATEGORIA;

/* Información de un símbolo */
typedef struct _SIMBOLO SIMBOLO;
typedef struct _listaSimbolo listaSimbolo;
typedef struct _HASH_TABLE HASH_TABLE;

SIMBOLO *newSimbolo(char *identificador, TIPO t, CATEGORIA c);
void setValor(SIMBOLO *s, int v);
void setLongitud(SIMBOLO *s, int l);
void setNum_parametros(SIMBOLO *s, int n);
void setPosicion(SIMBOLO *s, int p);
void setNum_var_locales(SIMBOLO *s, int n);

void freeSimbolo(SIMBOLO *s);

/* Aclaración: como los campos valor, longitud, num_parametros, posicion y num_var_locales
son opcionales dependiendo de si el símbolo es variable (escalar o vector), parámetro o función,
se pueden concentrar todos estos campos en sólo dos campos de tipo int (por ejemplo, info1 e info2)
y gestionar en cada caso al guardar y recuperar los valores el dato que corresponde */





listaSimbolo *newListaSimbolo();
void freeListaSimbolo(listaSimbolo *l);
void insertaSimboloLista(listaSimbolo *l, SIMBOLO *s);



HASH_TABLE *newHashTable();

void freeHashTable(HASH_TABLE *h);

int insertarSimbolo(HASH_TABLE *h, SIMBOLO *s);

SIMBOLO *buscarSimbolo(HASH_TABLE *h, char *identificador);

void printSimbolo(SIMBOLO *s);
void printLista(listaSimbolo *l);
void printHashTable(HASH_TABLE *h);


#endif
