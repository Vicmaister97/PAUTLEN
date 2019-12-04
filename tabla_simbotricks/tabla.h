/******************************************************
Nombre: tabla.h
Descripcion: Definicion de simbolos para la tabla de simbolos
******************************************************/
#ifndef _TABLA_H
#define _TABLA_H

/* Categoría de un símbolo: variable, parámetro de función o función */
typedef enum { VARIABLE, PARAMETRO, FUNCION } CATEGORIA_SIMBOLO;

/* Tipo de un símbolo: sólo se trabajará con enteros y booleanos */
typedef enum { ENTERO, BOOLEANO } TIPO;

/* Categoría de la variable: puede ser variable atómicas (escalar) o lista/array (vector) */
typedef enum { ESCALAR, VECTOR } CATEGORIA;

/* Información de un símbolo */
typedef struct {
    char *identificador;                /* identificador */
    CATEGORIA_SIMBOLO cat_simbolo;      /* categoría del simbolo */
    TIPO tipo;                          /* tipo */
    CATEGORIA categoria;                /* categoria de la variable */
    int valor;                          /* valor si escalar */
    int longitud;                       /* longitud si vector */
    int num_parametros;                 /* número de parámetros si función */
    int posicion;                       /* posición en llamada a función si parámetro, posición de declaración si variable local de función */
    int num_var_locales;                /* número de variables locales si función */
} SIMBOLO;

struct SIMBOLO *newSimbolo(char *identificador, TIPO t, CATEGORIA c);
void setValor(struct SIMBOLO *s, int v);
void setLongitud(struct SIMBOLO *s, int l);
void setNum_parametros(struct SIMBOLO *s, int n);
void setPosicion(struct SIMBOLO *s, int p);
void setNum_var_locales(struct SIMBOLO *s, int n);

void freeSimbolo(struct SIMBOLO *s);

/* Aclaración: como los campos valor, longitud, num_parametros, posicion y num_var_locales
son opcionales dependiendo de si el símbolo es variable (escalar o vector), parámetro o función,
se pueden concentrar todos estos campos en sólo dos campos de tipo int (por ejemplo, info1 e info2)
y gestionar en cada caso al guardar y recuperar los valores el dato que corresponde */

typedef struct {
  struct SIMBOLO **hash_array;
  int num_items;
  int max_items;
} HASH_TABLE;

struct HASH_TABLE *newHashTable(int max_items);

void freeHashTable(struct HASH_TABLE *h);

int insertarSimbolo(struct HASH_TABLE *h, struct SIMBOLO s);

struct SIMBOLO *buscarSimbolo(struct HASH_TABLE *h, char *identificador);


#endif
