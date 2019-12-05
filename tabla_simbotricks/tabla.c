/*********************************************************
**
** Fichero: tabla.c
** Autores: Víctor García, Alfonso Carvajal
** Contenido: Implementa la tabla de símbolos y su funcionalidad
**            para el compilador a realizar en la asignatura de 
**            Proyecto de Autómatas y Lenguajes
**
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla.h"


/*******************************************************
* METODOS DE LA TABLA HASH *
*******************************************************/

struct _SIMBOLO{
    char *identificador;                /* identificador */
    CATEGORIA_SIMBOLO cat_simbolo;      /* categoría del simbolo */
    TIPO tipo;                          /* tipo */
    CATEGORIA categoria;                /* categoria de la variable */
    int valor;                          /* valor si escalar */
    int longitud;                       /* longitud si vector */
    int num_parametros;                 /* número de parámetros si función */
    int posicion;                       /* posición en llamada a función si parámetro, posición de declaración si variable local de función */
    int num_var_locales;                /* número de variables locales si función */
};

struct _listaSimbolo{
  SIMBOLO **lista;
  int len;
};

struct _HASH_TABLE{
  listaSimbolo **hash_array;
  int num_items;
};

SIMBOLO *newSimbolo(char *identificador, int valor){
  SIMBOLO *s;
  s = (SIMBOLO *)malloc(sizeof(SIMBOLO));
  if(s == NULL)
    return NULL;
  s->identificador = (char *)malloc(sizeof(identificador));
  strcpy(s->identificador, identificador);
  s->valor = valor;
  return s;
}

void setCategoriaSimbolo(SIMBOLO *s, CATEGORIA_SIMBOLO c){
  if(s)
    s->cat_simbolo = c;
}

void setTipo(SIMBOLO *s, TIPO t){
  if(s)
    s->tipo = t;
}

void setCategoria(SIMBOLO *s, CATEGORIA c){
  if(s)
    s->categoria = c;
}

void setValor(SIMBOLO *s, int v){
  if(s != NULL)
    s->valor = v;
}

void setLongitud(SIMBOLO *s, int l){
  if(s != NULL)
    s->longitud = l;
}

void setNum_parametros(SIMBOLO *s, int n){
  if(s != NULL)
    s->num_parametros = n;
}

void setPosicion(SIMBOLO *s, int p){
  if(s != NULL)
    s->posicion = p;
}

void setNum_var_locales(SIMBOLO *s, int n){
  if(s != NULL)
    s->num_var_locales = n;
}

void freeSimbolo(SIMBOLO *s){
  if(s){
    if(s->identificador)
      free(s->identificador);
    free(s);
  }
}

char *getIdentificador(SIMBOLO *s){
  if(s)
    return s->identificador;
}

CATEGORIA_SIMBOLO CategoriaSimbolo(SIMBOLO *s){
  if(s)
    return s->cat_simbolo;
}

TIPO getTipo(SIMBOLO *s){
  if(s)
    return s->tipo;
}

CATEGORIA getCategoria(SIMBOLO *s){
  if(s)
    return s->categoria;
}

int getValor(SIMBOLO *s){
  if(s)
    return s->valor;
}

int getLongitud(SIMBOLO *s){
  if(s)
    return s->longitud;
}

int getNum_parametros(SIMBOLO *s){
  if(s)
    return s->num_parametros;
}

int getPosicion(SIMBOLO *s){
  if(s)
    return s->posicion;
}

int getNum_var_locales(SIMBOLO *s){
  if(s)
    return s->num_var_locales;
}


listaSimbolo *newListaSimbolo(){
  listaSimbolo *l;
  l = (listaSimbolo *)malloc(sizeof(listaSimbolo));
  if(l == NULL)
    return NULL;
  l->lista = NULL;
  l->len = 0;
}
void insertaSimboloLista(listaSimbolo *l, SIMBOLO *s){
  if(l == NULL || s == NULL)
    return;
  l->lista = (SIMBOLO **)realloc(l->lista, (l->len + 1) * sizeof(SIMBOLO *));
  *(l->lista + l->len) = s;
  l->len++;
}

int isSimboloEnLista(listaSimbolo *l, char *s){
  int i;
  if(l == NULL || s == NULL)
    return ERR;
  for(i=0; i<l->len; i++)
    if(strcmp(s, (*(l->lista + i))->identificador) == 0)
      return i;

  return FALSE;
}

void freeListaSimbolo(listaSimbolo *l){
  int i;
  if(l != NULL){
    if(l->lista != NULL){
      for(i=0; i<l->len; i++)
        freeSimbolo(*(l->lista + i));
      free(l->lista);
    }
    free(l);
  }
}


HASH_TABLE *newHashTable(){
  HASH_TABLE *h;
  int i;
  h = (HASH_TABLE *)malloc(sizeof(HASH_TABLE));
  if(h == NULL)
    return NULL;
  h->hash_array = (listaSimbolo **)malloc(MAX_HASH*sizeof(listaSimbolo *));
  if(h->hash_array == NULL){
    free(h);
    return NULL;
  }
  for(i=0; i<MAX_HASH; i++)
    *(h->hash_array + i) = newListaSimbolo();

  h->num_items = 0;
  return h;
}

void freeHashTable(HASH_TABLE *h){
  int i;
  if(h){
    if(h->hash_array){
      for(i=0; i<MAX_HASH; i++)
        freeListaSimbolo(*(h->hash_array + i));
      free(h->hash_array);
    }
    free(h);
  }
}

int hashCode(char *s){
  int len, code, i;
  if(s){
    len = strlen(s);
    code = 1;
    for(i=0; i<len; i++){
      code = code**(s + i);
      code = code%MAX_HASH;
    }
    return code;
  }
  return ERR;
}

int insertarSimbolo(HASH_TABLE *h, SIMBOLO *s){
  int i, hash;
  listaSimbolo *hash_item;
  if(h == NULL || s == NULL)
    return ERR;

  hash = hashCode(s->identificador);
  hash_item = *(h->hash_array + hash);
  /*Si tiene un item hay que ver si el que vamos a meter ya existe*/
  if(0 < hash_item->len)
    if(isSimboloEnLista(hash_item, s->identificador) != FALSE)
      return ERR;

  insertaSimboloLista(hash_item, s);
  return TRUE;
}

SIMBOLO *buscarSimbolo(HASH_TABLE *h, char *s){
  int hash, pos;
  listaSimbolo *hash_item;
  if(h == NULL || s == NULL)
    return NULL;


  hash = hashCode(s);
  hash_item = *(h->hash_array + hash);
  pos = isSimboloEnLista(hash_item, s);
  if(pos != FALSE)
    return *(hash_item->lista + pos);

  return NULL;
}

void printSimbolo(SIMBOLO *s){
  if(s){
    printf("SIMBOLO: %s", s->identificador);
  }
}
void printLista(listaSimbolo *l){
  int i, len;
  if(l){
    len = l->len;
    if(len <= 0)
      printf("VACIA");
    else{
      printf("ITEM: ");
      for(i=0; i<len; i++){
        printf(" %d--> ", i);
        printSimbolo(*(l->lista + i));
      }
    }
  }
}

void printHashTable(HASH_TABLE *h){
  int i;
  if(h){
    printf("HASH TABLE:\n");
    for(i=0; i<MAX_HASH; i++){
      printLista(*(h->hash_array + i));
      printf("\n");
    }
  }
}


/*******************************************************
* METODOS DE MODIFICACIÓN DE LA TABLA DE SÍMBOLOS (TS) *
*******************************************************/

// Declarar una variable de ámbito global
int DeclararGlobal(HASH_TABLE *TGLOBAL, char *id, int desc_id){
    SIMBOLO *newS;
    newS = newSimbolo(id, desc_id);

    return insertarSimbolo(TGLOBAL, newS);         // Devuelve TRUE si no es una redeclaración de una variable global
                                                    // y ha podido insertarlo o FALSE en caso contrario
    
    /*if (buscarSimbolo(TGLOBAL, id) == NULL){        // Si no es una redeclaración de una variable global
        SIMBOLO *newS;
        newS = newSimbolo(id, desc_id);
        return TRUE;
    }
    else return FALSE;*/
}

// Declarar una variable o parámetro(de una función) de ámbito local
int DeclararLocal(HASH_TABLE *TLOCAL, char *id, int desc_id){
    SIMBOLO *newS;
    newS = newSimbolo(id, desc_id);

    return insertarSimbolo(TLOCAL, newS);          // Devuelve TRUE si no es una redeclaración de una variable local
                                                    // y ha podido insertarlo o FALSE en caso contrario
}

// Comprueba si se puede usar la variable en un ámbito global
SIMBOLO *UsoGlobal(HASH_TABLE *TGLOBAL, char *id){

    SIMBOLO *simbol;
    simbol = buscarSimbolo(TGLOBAL, id);
    if (simbol == NULL){                         // Si el símbolo no pertenece al ámbito global
        return NULL;
    }
    else return simbol;
}

// Comprueba si se puede usar la variable en un ámbito local
SIMBOLO *UsoLocal(HASH_TABLE *TGLOBAL, HASH_TABLE *TLOCAL,  char *id){
    SIMBOLO *simbol;
    simbol = buscarSimbolo(TLOCAL, id);
    if (simbol == NULL){                        // Si el símbolo no pertenece al ámbito local
        simbol = buscarSimbolo(TGLOBAL, id);
        if (simbol == NULL) return NULL;        // Si el símbolo no pertenece tampoco al ámbito global
        else return simbol;
    }
    else return simbol;
}

// Declara una función con su correspondiente cambio de ámbito
int DeclararFuncion(HASH_TABLE *TGLOBAL, HASH_TABLE *TLOCAL, char *id, int desc_id){
    if (buscarSimbolo(TGLOBAL, id) != NULL) {   // Si ya existe esa función
        return FALSE;
    }
    else{
        SIMBOLO *newS;
        newS = newSimbolo(id, desc_id);

        // Insertamos la funcion en la tabla global
        if (insertarSimbolo(TGLOBAL, newS) == FALSE) return FALSE;      // NO deberia fallar

        // Inicializamos la tabla local para el ámbito de esta función
        TLOCAL = newHashTable():

        // Insertamos la funcion en la tabla local
        if (insertarSimbolo(TLOCAL, newS) == FALSE) return FALSE;      // NO deberia fallar

        return TRUE;
    }
}
