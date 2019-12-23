/*********************************************************
**
** Fichero: alfa.h
** Autores: Víctor García, Alfonso Carvajal
** Contenido: Definiciones de la estructura de atributos semanticos
**            para el compilador a realizar en la asignatura de
**            Proyecto de Autómatas y Lenguajes
**
*********************************************************/
#ifndef _ALFA_H
#define _ALFA_H

#define MAX_LONG_ID 100
#define MAX_TAMANIO_VECTOR 64
#define ESCALAR 1
#define VECTOR 2
#define INT 1
#define BOOLEAN 2

#define CTE 0
#define VAR 1
#define MAX_INT_LEN 11
#define STR_TRUE "1"
#define STR_FALSE "0"

#define TIPO_SUMA 0
#define TIPO_RESTA 1
#define TIPO_DIV 2
#define TIPO_MUL 3
#define TIPO_MENOS 4
#define TIPO_AND 5
#define TIPO_OR 6
#define TIPO_NEG 7

#define CMP_IGUAL 7
#define CMP_DIST 8
#define CMP_MEN_IG 9
#define CMP_MAY_IG 10
#define CMP_MEN 11
#define CMP_MAY 12





//#define YYSTYPE atributos	// A partir de ahora, cada símbolo tiene una estructura de tipo atributos

typedef struct {
  char lexema[MAX_LONG_ID + 1];
  int tipo;
  int valor_entero;
  int es_direccion;
  int etiqueta;
}tipo_atributos;


#endif
