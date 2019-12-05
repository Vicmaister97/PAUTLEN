/*********************************************************
**
** Fichero: prueba_tabla.c
** Autores: Víctor García, Alfonso Carvajal
** Contenido: Implementa el programa de prueba para la tabla de símbolos
**            y su funcionalidad del compilador a realizar en la asignatura
**            de Proyecto de Autómatas y Lenguajes
**
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla.h"

#define MAX_LINE 101

int main (int argc, char *argv[]){
    HASH_TABLE *TGLOBAL = newHashTable();       // Tabla hash que almacena los símbolos de ámbito global
    HASH_TABLE *TLOCAL = NULL;                  // Tabla hash que almacena los símbolos de ámbito local

    char linea[MAX_LINE];
    FILE *yyin;
    FILE *yyout;
    int i, j;

  if (argc == 3){
    yyin = fopen(argv[1], "r");
    if (yyin == NULL){
      fprintf (stderr, "El fichero '%s' no se puede abrir\n", argv[1]);
      exit(-1);
    }

    yyout = fopen(argv[2], "w");
    if (yyout == NULL){
      fprintf (stderr, "El fichero '%s' no se puede abrir\n", argv[1]);
      fclose(yyin);
      exit(-1);
    }

    // Procesamos linea a linea el fichero de entrada
    while (fgets(linea, MAX_LINE, (FILE*) yyin)) {
        char cadena[MAX_LINE];
        
        for (i=0; i<MAX_LINE; i++){

            if ( (linea[i] == '\t') || (linea[i] == ' ') ){        // Hemos llegado al separador entre el identificador y el entero opcional

                memset(cadena, 0, MAX_LINE);
                strncpy (cadena, linea, i);           // Copiamos el identificador
                //cadena[i+1]="\0";

                if (strcmp(cadena, "cierre") == 0){     // Si es el cierre de un ámbito
                    freeHashTable(TLOCAL);              // Borramos la tabla local
                    fprintf(yyout, "%s\n", "cierre");
                    break;
                }
                else{                                   // Si no, tiene el entero opcional
                    int jump = i+1;
                    for(j=0; j<MAX_LINE; j++){
                        if ( (linea[jump] != '\t') || (linea[jump] != ' ') ){       // Leemos hasta el primer caracter del numero
                            break;
                        }
                        else{
                            jump++;
                        }
                    }

                    char *ps = linea + jump;   // Nos situamos después del tabulador
                    
                    int num = atoi(ps);
                    if (num == 0){
                        linea[i] = '\0';
                        continue;   // Sobran espacios al final, está tratando de buscar el identificador
                    }

                    else{
                        if (num<=-1){                         // Si es negativo, comienza un nuevo ámbito 
                            TLOCAL = newHashTable();
                            if (DeclararFuncion(TGLOBAL, TLOCAL, cadena, num) == TRUE){   // Exito, devolvemos el id de la funcion 
                                fprintf(yyout, "%s\n", cadena);
                                break;
                            }
                        }
                        else{                               // Declaracion de variable, inserta el símbolo
                            if (ambito == 0){
                                if (DeclararGlobal(TGLOBAL, cadena, num) == FALSE){     // redeclaración variable global
                                    fprintf(yyout, "%d %s\n", -1, cadena);
                                    break;
                                }
                                else{
                                    fprintf(yyout, "%s\n", cadena);
                                    break;
                                }
                            }
                            else{                           // Ambito local
                                if (DeclararLocal(TLOCAL, cadena, num) == FALSE){     // redeclaración variable local
                                    
                                    fprintf(yyout, "%d %s\n", -1, cadena);
                                    break;
                                }
                                else{
                                    fprintf(yyout, "%s\n", cadena);
                                    break;
                                }
                            }
                        }
                    }

                }

            }

            if (linea[i] == '\0'){       // Si encontramos antes del tabulador el final de linea, se trata de una busqueda del identificador

                memset(cadena, 0, MAX_LINE);
                strncpy (cadena, linea, i-1);         // Copiamos el identificador
                if (ambito == 0){
                    //printHashTable(TGLOBAL);
                    SIMBOLO *ret = UsoGlobal(TGLOBAL, cadena);
                    if (ret == NULL){                           // Si se busca en global pero no lo encuentra
                        fprintf(yyout, "%s %d\n", cadena, -1);
                        break;
                    }
                    else{                                       // Si lo busca en global y lo encuentra
                        fprintf(yyout, "%s %d\n", cadena, getValor(ret));
                        break;
                    }
                }
                else{                               // Búsqueda en local
                    SIMBOLO *ret = UsoLocal(TGLOBAL, TLOCAL, cadena);
                    if (ret == NULL){                           // Si se busca en local pero no lo encuentra
                        fprintf(yyout, "%s %d\n", cadena, -1);
                        break;
                    }
                    else{                                       // Si lo busca en local y lo encuentra
                        fprintf(yyout, "%s %d\n", cadena, getValor(ret));
                        break;
                    }
                }
            }

        }
    }

    fclose(yyin);
    fclose(yyout);
    // BORRAMOS TABLAS??
    exit(1);
    
  }

  else{
    printf("Error en los parámetros de entrada\t./alfa FILE_IN FILE_OUT\n");
  }

}