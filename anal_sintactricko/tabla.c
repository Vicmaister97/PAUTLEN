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

struct HASH_TABLE *TGLOBAL;       // Tabla hash que almacena los símbolos de ámbito global
struct HASH_TABLE *TLOCAL;       // Tabla hash que almacena los símbolos de ámbito local

// newHashTable

int ambito = 0;                 // Indica si el ambito del programa es global (= 0) o local&global (= 1)


/*********************
* METODOS DE MODIFICACIÓN DE LA TABLA DE SÍMBOLOS (TS) *
**********************/

int DeclararGlobal(char *id, int desc_id){
    struct SIMBOLO *newS;
    newS = newSimbolo(id, desc_id);

    return insertarSimbolo (TGLOBAL, newS)          // Devuelve TRUE si no es una redeclaración de una variable global
                                                    // y ha podido insertarlo o FALSE en caso contrario
    
    /*if (buscarSimbolo(TGLOBAL, id) == NULL){        // Si no es una redeclaración de una variable global
        struct SIMBOLO *newS;
        newS = newSimbolo(id, desc_id);
        return TRUE;
    }
    else return FALSE;*/
}

int DeclararLocal(char *id, int desc_id){
    struct SIMBOLO *newS;
    newS = newSimbolo(id, desc_id);

    return insertarSimbolo (TLOCAL, newS)          // Devuelve TRUE si no es una redeclaración de una variable global
                                                    // y ha podido insertarlo o FALSE en caso contrario
}

/* Inserta una entrada en la tabla de símbolos (TS). Devuelve 1 si funciona correctamente, -1 en caso de error */
int TS_AddEntry(entradaTS entrada){

    // Si aun quedan entradas en la tabla de símbolos
    if(TOPE < MAX_TS) {

        TS[TOPE].entry=entrada.entry;
        TS[TOPE].name=entrada.name;
        TS[TOPE].type=entrada.type;
        TS[TOPE].nParams=entrada.nParams;

        //printf("New Entry: %s TipoEntrada=%d TipoDato=%d numParams=%d \n", TS[TOPE].name, TS[TOPE].entry, TS[TOPE].type, TS[TOPE].nParams);

        // Actualizamos el número de entradas
        TOPE++;

        return 1;
    }

    else{   // Si está completa

        printf("MAX_ENTRIES ERR[line %d]: SYMBOL TABLE (TS) OVERFLOW", line);
        return -1;

    }
}

/* Elimina una entrada en la tabla de símbolos (TS). Devuelve 1 si funciona correctamente, -1 en caso de error */
int TS_DelEntry(){

    // Si hay alguna entrada en la tabla de símbolos
    if(TOPE > 0){

        TOPE--;
        return 1;
    }

    else{

        printf("NO_ENTRIES ERR[line %d]: EMPTY SYMBOL TABLE (TS)", line);
        return -1;
    }
}

/* Elimina todas las entradas de la tabla de símbolos del bloque actual y la cabecera del mismo si el bloque la tiene. Debe ser llamada al final de cada bloque. Devuelve 1 si funciona correctamente, -1 en caso de error */
int TS_CleanBlock(){

    int ret = -1;           // para el valor de return de la función que indica su comportamiento
    int actualTOPE = -1;    // para almacenar el valor del TOPE antes de actualizar la función actual

    if (TOPE == 0)          // Si la TS está vacía
        return 1;

    while(TOPE > 0){                 // Mientras que no llegue a la base de la pila(TS) buscamos el inicio del bloque en el que estamos
        TOPE--;                      // Nos desplazamos desde la entrada más reciente a las anteriores para leer las entradas del bloque
        //printf("Del Entry: %s \n", TS[TOPE].name);

        if (TS[TOPE].entry == MARK){ // Si encuentra una entrada con la marca de inicio de bloque
            ret = 1;
            break;
        }
        //if (TOPE == 0)
    }

    if (TOPE == 0){
        printf("ANALISIS FINALIZADO\n");
        return ret;
    }
    // Dejamos TOPE donde estaría la marca de bloque para comenzar a insertar ahí: todo lo anterior en la TS se conserva (params formales, funcion)
    actualTOPE = TOPE;
    actualTOPE--;
    if (TS[actualTOPE].entry == FORM_PARAM ) {          // Si el bloque es una función, actualizamos la currentFunction o la función actual
        while (TS[actualTOPE].entry == FORM_PARAM){
            actualTOPE--;
        }
    }
    if (TS[actualTOPE].entry == FUNCTION) {             // Busca en la TS la última función definida no finalizada por declarar para convertirla en la actual (es su ámbito ahora)
        TS[actualTOPE].finished = 1;                    // Señalamos que esta función ha finalizado, pues era el cuerpo de esta función lo que hemos eliminado
        updateCurrentFunction(actualTOPE);

    }

    return ret;
}

void updateCurrentFunction(int lastFunc){
    lastFunc--;
    while (TS[lastFunc].entry != FUNCTION && lastFunc > 0){
            lastFunc--;
    }
    if (lastFunc == 0){
        currentFunction = -1;
    }
    else{
        if (TS[lastFunc].finished == 0){        // si la función encontrada todavía no ha terminado de definirse
            currentFunction = lastFunc;
        }
        else updateCurrentFunction(lastFunc);
    }
}

// Busca una entrada en la TS de una VARIABLE por su identificador o nombre. Devuelve el índice de la entrada encontrada o -1 en caso de no encontrarla
int TS_FindByID(atributos e){

    int i = TOPE - 1;
    int found = 0;

    if (TOPE == 0)
        return -1;

    while (i > 0 && found == 0) {   /*&& ts[i].entry != MARK*/
        if (TS[i].entry == VAR && strcmp(e.name, TS[i].name) == 0){
            found = 1;
            break;
        }

        i--;
    }

    if(found == 0) {
        //printf("Semantic Error(%d): Ident not declared: %s\n", line, e.name);
        return -1;
    } else {
        return i;
    }

}

// Busca una entrada en la TS de una FUNCIÓN por su identificador o nombre. Devuelve el índice de la entrada encontrada o -1 en caso de no encontrarla
int TS_FindByName(atributos e){

    int i = TOPE - 1;
    int found = 0;

    if (TOPE == 0)
        return -1;

    while (i > 0 && found == 0) {
        if (TS[i].entry == FUNCTION && strcmp(e.name, TS[i].name) == 0){
            found = 1;
            break;
        }

        i--;
    }

    if(found == 0) {
        //printf("Semantic Error(%d): Ident not declared: %s\n", line, e.name);
        return -1;
    } else {
        return i;
    }

}

// Inserta una entrada en la tabla de símbolos de una función o un bloque
void TS_AddMark(){

    entradaTS initBlock;
    initBlock.entry = MARK;
    initBlock.name = "{";
    initBlock.type = NO_ASSIG;
    initBlock.nParams = 0;

    TS_AddEntry(initBlock);

    /* Si es el cuerpo de una función, se añaden a la tabla de símbolos los parámetros/argumentos de la función como
       variables locales de ese bloque al fin de poder ser utilizadas  */
    if(esFunc == 1){
        int j = TOPE - 2;       // TOPE-2 para leer los parámetros formales de antes de la llave
        while(j > 0 && TS[j].entry == FORM_PARAM){      // Mientras leamos parámetros formales los aniadimos como variables locales al nuevo bloque
            entradaTS Param;
            Param.entry = VAR;
            Param.name = TS[j].name;
            Param.type = TS[j].type;
            Param.nParams = TS[j].nParams;
            TS_AddEntry(Param);
            j--;
        }
    }

}

/*
// Añade una entrada en la tabla de símbolos de una variable local
void TS_AddVar(atributos e){
    int j = TOPE-1;
    int found = 0;
    //Debemos permitir redeclarar variables en bloques distintos, por lo que al aniadir una nuera variable hacemos la comprobación
    //  de la redeclaración de forma local, en el mismo bloque únicamente
    if(j >= 0 && decVar == 1){                                  // Caso de declaración de la variable
        while( TS[j].entry != MARK && j >= 0 && found == 0){    // Busco si es una redeclaración dentro de ese bloque. Busca el mismo nombre dentro del bloque
            if(strcmp(TS[j].name, e.name) == 0){
                found = 1;
                printf("DECLARATION ERR[line %d]: ID already exists: %s\n", line, e.name);
            }
        }
        if(found == 0) {
            entradaTS newIn;
            newIn.entry = VAR;
            newIn.name = e.name;
            newIn.type = TipoTmp;
            newIn.nParams = 0;
            TS_AddEntry(newIn);
        }
    }
}*/

// Añade una entrada en la tabla de símbolos de una variable local
void TS_AddVar(atributos e){
    int j = TOPE-1;
    int found = 0;
    int index;

    int numparams = TS[currentFunction].nParams;

    // Comprobamos que la variable a añadir no es una redeclaración de un argumento de la función en la que se encuentra
    if (index != -1){
        for (index = currentFunction+1; index < currentFunction+1 + numparams; index++){        // Comparamos con los parametros formales de la fución actual
            if (strcmp(TS[index].name, e.name) == 0){       // Su nombre es el de un argumento de la función
                printf("DECLARATION ERR[line %d]: ID already exists: %s\n", line, e.name);
                return;
            }
        }
    }
            

    if(j >= 0 && decVar == 1){                                  // Caso de declaración de la variable
        while( TS[j].entry != MARK && j >= 0 && found == 0){    // Busca una entrada con el mismo nombre dentro del bloque
            if(strcmp(TS[j].name, e.name) != 0){
                j--;
            }
            else{
                found = 1;
                printf("DECLARATION ERR[line %d]: ID already exists: %s\n", line, e.name);
                return;
            }
        }

        if(found == 0) {
            entradaTS newIn;
            newIn.entry = VAR;
            newIn.name = e.name;
            newIn.type = TipoTmp;
            newIn.nParams = 0;
            TS_AddEntry(newIn);
        }
    }
}

// Inserta una entrada en la tabla de símbolos de una función
void TS_AddFunction(atributos e){

    entradaTS inFunct;
    inFunct.entry = FUNCTION;
    inFunct.name = e.name;
    inFunct.nParams = 0;        // Luego se actualizará el número de parámetros
    inFunct.type = TipoTmp;
    inFunct.finished = 0;

    currentFunction = TOPE;     // Actualizamos la función actual
    TS_AddEntry(inFunct);
}

// Inserta una entrada en la tabla de símbolos de un parámetro formal
void TS_AddParam(atributos e){
  int j = TOPE - 1, found = 0;
    while( j != currentFunction && found == 0 ){        // Comprobamos si ya existe un argumento de esa función con el mismo nombre
        if(strcmp(TS[j].name, e.name) != 0) {
            j--;
        }
        else{
            found = 1;
            printf("DECLARATION ERR[line %d]: Param already exists: %s\n", line, e.name);
        }
    }

    if(found == 0) {
        entradaTS newIn;
        newIn.entry = FORM_PARAM;
        newIn.name = e.name;
        newIn.type = TipoTmp;
        newIn.nParams = 0;
        TS_AddEntry(newIn);

        if (currentFunction > -1)   // si NO son los parametros de entrada del programa
            // Actualiza el número de parámetros de la función
            TS[currentFunction].nParams += 1;
    }
}

/*********************
* METODOS PARA EN ANALIZADOR SINTÁCTICO *
**********************/

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
}