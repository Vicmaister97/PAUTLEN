/*********************************************************
**
** Procesadores de Lenguajes, 2018-2019
** Fichero: SEMANTICA.H
** Autores: Manuel Orantes Taboada, Víctor Bricio Blázquez, Víctor García Carrera.
** Función: Archivo de definición de la tabla de símbolos (TS) junto con sus constantes
** 	   		y procedimientos para las comprobaciones semánticas del traductor.
**
**
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{	// Enumeración para definir el tipo de entrada en la TS

	MARK = 0,		// Marca especial para referenciar los inicios de bloque
	FUNCTION,		// Indica que es una función
	VAR,			// Indica que es una variable local
	FORM_PARAM		// Indica que es un parámetro formal de una función

} tipoEntrada;

typedef enum {	// Enumeración para definir el tipo de dato de las entradas función, variable local o parámetro formal

	INT = 0,		// Entero
	DOUBLE,			// Real
	CHAR,			// Caracter
	BOOLEAN,		// Booleano
	LIST_INT,		// Lista
	LIST_DOUBLE,
	LIST_CHAR,
	LIST_BOOLEAN,
	SIZE,			// Tamanio o dimensión de una lista situada en la entrada anterior
	NO_ASSIG		// Aun no se ha asignado el tipo, para inicialización

	// Matriz???

} tipoDato;

#define YYSTYPE atributos	// A partir de ahora, cada símbolo tiene una estructura de tipo atributos

typedef struct {	// Los atributos usados son el tipo de los elementos y el lexema

	int attr;				// Atributo del símbolo (si tiene)
	char *name;				// Nombre del lexema
	tipoDato type;			// Tipo del símbolo
	/*unsigned int nDim;	// En el caso de una lista, indica su dimensión o tamanio

	// Tamaño de la dimensión 1
	int tDim1;

	// Tamaño de la dimensión 2
	int tDim2;*/

}atributos;
/*************************************************************
** DEFINICIÓN DE LOS ELEMENTOS DE LA TABLA DE SÍMBOLOS (TS) **
**************************************************************/
#define MAX_TS 1000	// Tamanio máximo de la tabla de símbolos

typedef struct {	// Entrada de la tabla de símbolos (TS)

	tipoEntrada entry;		// Tipo de entrada, valor del tipo enum tipoEntrada
	char *name;				// Nombre o caracteres que conforman el identificador, no utilizado en una marca de bloque
	tipoDato type;			// Tipo de dato para las funciones, variables o parámetros formales, valor del tipo enum tipoDato
	int nParams;			// En el caso de una función, indica el número de parámetros formales (COMO SE ACTUALIZA??)
	int finished;
	/*unsigned int nDim;	// En el caso de una lista, indica su dimensión o tamanio

	// Tamaño de la dimensión 1
	int tDim1;

	// Tamaño de la dimensión 2
	int tDim2;*/

}entradaTS;


extern long int TOPE ;			// Tope de la pila, indica en cada momento la siguiente posición en la pila TS para insertar una entrada
extern entradaTS TS[MAX_TS] ;		// Pila de la tabla de símbolos

// Línea del fichero que se está analizando
extern int line;

// Indica si las variables se están utilizando (decVar=0), si se están declarando (decVar=1)
// o si se llaman desde una expresión (decVar=2)
extern int decVar;

// Indica el inicio de una declaración de parámetros formales o argumentos de una función con 1 y el final con un 0(valor predeterminado)
extern int decParam;

// Indica el inicio del cuerpo de una función con 1 y el final con un 0(valor predeterminado)
extern int esFunc;

// Variable global que almacena el tipo de dato mas recientemente leido en las declaraciones
extern tipoDato TipoTmp;

// Cuenta el número de parámetros de una función
extern int nParams;

// Variable con el numero de parámetros de la función llamada para comprobarlos
extern int checkparam;

// Variable con el nombre de la función llamada que se quiere comprobar
extern int checkFunct;

// Índice en la tabla de símbolos de la función que se está utilizando
extern int currentFunction;

/*************************************************************
** LISTA DE FUNCIONES Y PROCEDIMIENTOS PARA MANEJO DE LA TS **
**************************************************************/

/* Guarda el type o tipo de dato del atributo leido en la variable TipoTmp */
void getType(atributos value);

/*************************************************************
** METODOS DE MODIFICACIÓN DE LA TABLA DE SÍMBOLOS (TS) **
**************************************************************/

/* Inserta una entrada en la tabla de símbolos (TS). Devuelve 1 si funciona correctamente, -1 en caso de error */
int TS_AddEntry(entradaTS entrada);

/* Elimina una entrada en la tabla de símbolos (TS). Devuelve 1 si funciona correctamente, -1 en caso de error */
int TS_DelEntry();

/* Elimina todas las entradas de la tabla de símbolos del bloque actual y la cabecera del mismo si la tiene. Debe ser llamada al final de cada bloque. Devuelve 1 si funciona correctamente, -1 en caso de error */
int TS_CleanBlock();

void updateCurrentFunction(int lastFunc);

// Busca una entrada en la TS de una VARIABLE por su identificador o nombre. Devuelve el índice de la entrada encontrada o -1 en caso de no encontrarla
int TS_FindByID(atributos e);

// Busca una entrada en la TS de una FUNCIÓN por su identificador o nombre. Devuelve el índice de la entrada encontrada o -1 en caso de no encontrarla
int TS_FindByName(atributos e);

// Inserta una entrada en la tabla de símbolos de una función o un bloque
void TS_AddMark();

// Añade una entrada en la tabla de símbolos de una variable local
void TS_AddVar(atributos e);

// Inserta una entrada en la tabla de símbolos de una función
void TS_AddFunction(atributos e);

// Inserta una entrada en la tabla de símbolos de un parámetro formal o argumento de función
void TS_AddParam(atributos e);

/*************************************************************
** METODOS PARA EN ANALIZADOR SINTÁCTICO **
**************************************************************/

// Comprueba si el type de la expresión coincide con lo que devuelve la función
void TS_CheckReturn(atributos expr, atributos* res);

// Devuelve el identificador
void TS_GetId(atributos id, atributos* res);
int TSGetId(atributos id);

// Realiza la comprobación de la llamada a una función
void TS_FunctionCall(atributos* res);

// Realiza la comprobación de cada parámetro de una función
void TS_CheckParam(atributos param);

// Muestra por pantalla las entradas de la tabla de símbolos
void printTS();

// Muestra por pantalla un atributo recibido
void printAttr(atributos e, char *msg);
