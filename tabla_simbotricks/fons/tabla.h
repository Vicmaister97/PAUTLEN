/*********************************************************
**
** Fichero: tabla.h
** Autores: Víctor García, Alfonso Carvajal
** Contenido: Definiciones de la tabla de símbolos y su funcionalidad
**            para el compilador a realizar en la asignatura de 
**            Proyecto de Autómatas y Lenguajes
**
*********************************************************/
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

extern int ambito;                 // Indica si el ambito del programa es global (= 0) o local&global (= 1)
extern int inic_global;            // Controla que el ambito no cambie al crear la tabla global


SIMBOLO *newSimbolo(char *identificador, int valor);
void setCategoriaSimbolo(SIMBOLO *s, CATEGORIA_SIMBOLO c);
void setTipo(SIMBOLO *s, TIPO t);
void setCategoria(SIMBOLO *s, CATEGORIA c);
void setValor(SIMBOLO *s, int v);
void setLongitud(SIMBOLO *s, int l);
void setNum_parametros(SIMBOLO *s, int n);
void setPosicion(SIMBOLO *s, int p);
void setNum_var_locales(SIMBOLO *s, int n);

char *getIdentificador(SIMBOLO *s);
CATEGORIA_SIMBOLO CategoriaSimbolo(SIMBOLO *s);
TIPO getTipo(SIMBOLO *s);
CATEGORIA getCategoria(SIMBOLO *s);
int getValor(SIMBOLO *s);
int getLongitud(SIMBOLO *s);
int getNum_parametros(SIMBOLO *s);
int getPosicion(SIMBOLO *s);
int getNum_var_locales(SIMBOLO *s);

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


/******************************************
** TABLA SIMBOLOS
******************************************/

int DeclararGlobal(HASH_TABLE *TGLOBAL, char *id, int desc_id);
int DeclararLocal(HASH_TABLE *TLOCAL, char *id, int desc_id);
SIMBOLO *UsoGlobal(HASH_TABLE *TGLOBAL, char *id);
SIMBOLO *UsoLocal(HASH_TABLE *TGLOBAL, HASH_TABLE *TLOCAL,  char *id);
int DeclararFuncion(HASH_TABLE *TGLOBAL, HASH_TABLE *TLOCAL, char *id, int desc_id);


#endif