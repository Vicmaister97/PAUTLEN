/*********************************************************
**
** Fichero: tabla.c
** Autores: Víctor García, Alfonso Carvajal
** Contenido: Implementa la tabla de símbolos y su funcionalidad
**            para el compilador a realizar en la asignatura de 
**            Proyecto de Autómatas y Lenguajes
**
*********************************************************/


#include "tabla.h"


/*********************
* METODOS DE MODIFICACIÓN DE LA TABLA DE SÍMBOLOS (TS) *
**********************/

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



/*********************
* METODOS PARA EN ANALIZADOR SINTÁCTICO *
**********************/

/*
// Comprueba si el tipo de la expresión coincide con el tipo de retorno de la función
void TS_CheckReturn(atributos expr, atributos* res){
    int index = currentFunction;

    if (index > -1) {
        if (expr.type != TS[index].type) {
            printf("RETURN ERR[line %d]: Return type not equal to function type. %d\n", line, expr.type);
            return;
        }
        res->type = expr.type;
        return;
    }
    else {
        printf("RETURN ERR[line %d]: Result not declared into function.\n", line);
        return;
    }

}

// Devuelve en res la variable en la tabla de símbolos TS del identificador id si lo encuentra definido
void TS_GetId(atributos id, atributos* res){
    int index = TS_FindByID(id);
    if(index == -1) {       // No es ninguna variable guardada en la TS
        //if(TS[index].entry != FUNCTION)
        printf("\nSEARCH ERR[line %d]: Id not found %s.\n", line, id.name);
    }
    else {
        res->name = strdup(TS[index].name);
        res->type = TS[index].type;
    }
}

int TSGetId(atributos id){
    int index = TS_FindByID(id);
    if(index == -1) {       // No es ninguna variable guardada en la TS
        printf("%s %i\n", id.name, id.type);
        //if(id.type > 9){     // Si no tiene un tipo asignado, no es ni una constante, es una variable no declarada
            printf("\nSEARCH ERR[line %d]: Id not found %s.\n", line, id.name);
            return -1;
        //}
    }
    else {
        return TS[index].type;
    }
}

// Realiza la comprobación de la llamada a una función
void TS_FunctionCall(atributos* res){
    if(checkFunct == -1) {
        //currentFunction = -1;
    }
    else {
        if (checkparam != TS[checkFunct].nParams) {
            printf("ARGS ERR[line %d]: Number of params not valid.\n", line);
        }
        else {
            res->name = strdup(TS[checkFunct].name);
            res->type = TS[checkFunct].type;
        }
    }
}

// Realiza la comprobación de cada parámetro de una función
void TS_CheckParam(atributos param){

    checkparam += 1;
    int formalparam = checkFunct + checkparam;

    if(param.type != TS[formalparam].type) {
        printf("ARGS ERR[line %d]: Param type of %s not valid (type %d).\n", line, param.name, param.type);
        return;
    }
}*/