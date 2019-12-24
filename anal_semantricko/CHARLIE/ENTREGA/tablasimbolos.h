#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>



/***************************** ESTRUCTURA ******************************/

typedef struct _element {
	char* lexema;
    int categoria;
    int tipo;
    int clase;
    int tamanio;
    int valor;
    int n_params;	
    int posicion_param;
    int posicion_local;
} elemento;

elemento * crearElemento(char* lexema, int categoria, int tipo, int clase, int tamanio, int valor, int num_params, int posicion_param, int posicion_local);
void destruirElemento(elemento *e);
void insertarnum_parametros_actual(elemento *e , int npa);
/******************** DECLARACIÓN DE TIPOS DE DATOS ********************/

typedef enum {VACIO, OCUPADO, BORRADO} status_t;
typedef struct hash hash_t;
typedef struct hash_iter hash_iter_t;

//La funcion hash_destruirElemento_t será aplicada no sólo al momento de
//destruir la tabla de hash, sino también al reemplazar datos previamente
//agregados a la tabla                                           
typedef void (*hash_destruir_dato_t)(void *);

/********************** DECLARACIÓN DE PRIMITIVAS **********************/

//Crea una tabla de hash.
//Post: Se creó una tabla de hash.
hash_t *hash_crear(hash_destruir_dato_t destruir_dato);

//Almacena una tupla clave-dato en la tabla de hash.
//Pre: la tabla de hash fue creada
//Post: Almacena la tupla clave-dato en una posición de la tabla que
//está determinada por la función de hash utilizada. Devuelve true si
//logra almacenarla, false si la tupla ya estaba
bool hash_guardar(hash_t *hash, const char *clave, elemento *e);

//Elimina el dato correspondiente a la clave
//Pre: La tabla de hash fue creada
//Post: Elimina el dato asociado a la clave y lo devuelve. 
elemento *hash_borrar(hash_t *hash, const char *clave);

//Obtiene el dato asociado a la clave
//Pre: La tabla de hash fue creada
//Post: devuelve el dato asociado a la clave.
elemento *hash_obtener(const hash_t *hash, const char *clave);

//Determina si una clave tiene dato asociado en la tabla
//Pre: la tabla de hash fue creada
//Post: devuelve true si la clave tiene dato asociado en la tabla, false
//si no lo tiene
bool hash_pertenece(const hash_t *hash, const char *clave);

//Determina la cantidad de tuplas clave-dato que tiene la tabla
//Pre: la tabla de hash fue creada
//Post: Devuelve la cantidad de tuplas en la tabla.
size_t hash_cantidad(const hash_t *hash);

//Destruye la tabla hash
//Pre: La tabla de hash fue creada
//Post: La tabla de hash es destruida
void hash_destruir(hash_t *hash);

/*************** DECLARACIÓN DE PRIMITIVAS (ITERADORES) ****************/

//Crea un iterador sobre la tabla de hash
//Pre: La tabla de hash fue creada
//Post: Devuelve un iterador que apunta al primer elemento válido de la
//tabla
hash_iter_t *hash_iter_crear(const hash_t *hash);

//Avanza sobre la tabla
//Pre: El iterador fue creado
//Post: Devuelve true si logra avanzar al siguiente elemento de la tabla
//false si no hay más elementos para iterar
bool hash_iter_avanzar(hash_iter_t *iter);

//Muestra la clave asociada a la posición en la que se encuentra el iterador
//Pre: El iterador fue creado
//Post: Devuelve la clave de la posición actual del iterador.
const char *hash_iter_ver_actual(const hash_iter_t *iter);

//Determina si el iterador está al final de la tabla de hash
//Pre: el iterador fue creado
//Post: Devuelve true si el iterador está al final, false en caso contrario.
bool hash_iter_al_final(const hash_iter_t *iter);

//Destruye el iterador de hash
//Pre: El iterador fue creado
//Post: El iterador es destruido
void hash_iter_destruir(hash_iter_t* iter);


bool DeclararGlobal(char* id, elemento *e);
bool DeclararLocal(char* id, elemento *e);
bool Declarar(char* id, elemento *e);
elemento *UsoGlobal(char* id);
elemento *UsoLocal(char* id);
bool DeclararFuncion(char* id, elemento *e);
void DestruirTablaLocal();
void DestruirTablaGlobal();
void Crear_TablaGlobal();
bool existelocal();
elemento *Uso(char* id);
hash_t *getGlobal();
hash_t *getLocal();
/*hash_destruir(hash);*/
#endif
