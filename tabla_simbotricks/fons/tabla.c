#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla.h"

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

SIMBOLO *newSimbolo(char *identificador, TIPO t, CATEGORIA c){
  SIMBOLO *s;
  s = (SIMBOLO *)malloc(sizeof(SIMBOLO));
  if(s == NULL)
    return NULL;
  s->identificador = (char *)malloc(sizeof(identificador));
  strcpy(s->identificador, identificador);
  s->tipo = t;
  s->cat_simbolo = c;
  return s;
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
        printf("%d ", i);
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
