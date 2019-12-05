#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla.h"

void main (int argc, char** argv){
  HASH_TABLE *h;
  SIMBOLO *s, *s1, *s2, *temp, *s3;
  listaSimbolo *l;
  char ar[200];
  printf("\nCrea Simbolo");
  s = newSimbolo("lalal", 1);
  printf("\nCrea Simbolo");
  s1 = newSimbolo("lalla", 2);
  printf("\nCrea Simbolo");
  s2 = newSimbolo("jajaj", 4);
  l = newListaSimbolo();
  h = newHashTable();

  printf("\nSimbolo 1");
  printSimbolo(s);
  printf("\nSimbolo 2");
  printSimbolo(s1);
  printf("\nSimbolo 3");
  printSimbolo(s2);
  printf("\nInserta Simbolo 1");
  insertarSimbolo(h, s);
  printf("\nInserta Simbolo 2");
  insertarSimbolo(h, s1);
  printf("\nInserta Simbolo 3");
  insertarSimbolo(h, s2);
  printf("\nTabla despues de inserciones:\n");
  printHashTable(h);

  printf("\nBusca jajaj");
  temp = buscarSimbolo(h, "jajaj");
  printf("\n");
  if(temp)
    printSimbolo(temp);
  else printf("\nNOT FOUND\n");

  temp = buscarSimbolo(h, "xd");
  printf("\n");
  printf("\nBusca xd");
  if(temp)
    printSimbolo(temp);
  else printf("\nGOOD NOT FOUND\n");

  printf("\nIntenta Insertar Simbolo 1 otra vez");
  if(insertarSimbolo(h, s) == TRUE){
    printf("\nMAL");
  }
  else{ printf("\nNO inserta 2 iguales");}

  // ar = "abc";
  strcpy(ar, "abc");
  s3 = newSimbolo(ar, 2);
  printf("\nInsertar Simbolo 4");
  if(insertarSimbolo(h, s3) == TRUE){
    printf("\nOk");
  }
  else{ printf("\nMAL\n");}

  printHashTable(h);




  // freeSimbolo(s);
  freeListaSimbolo(l);
  freeHashTable(h);
  printf("\nOK\n");






  // char *a;
  // int len, i, sum;
  // len = 20;
  // printf("C * 5 == %d\n", 'c'*5);
  // a = (char *)malloc(len*sizeof(char));
  // strcpy(a, "identifasdfasdfi");
  // len = strlen(a);
  // printf("A == %s", a);
  // sum = 1;
  // for(i=0; i<len; i++){
  //   printf("CHAR %d == %c\n", i, *(a + i));
  //   sum = sum * *(a + i);
  // }
  // printf("SUM === %d\n", sum);
  // printf("SUMMOD === %d\n", sum%200);
  // printf("LENN == %d\n", sizeof("identifi"));
  // printf("LENN == %d\n", sizeof(a));
  // free(a);

}
