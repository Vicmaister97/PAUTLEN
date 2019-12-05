#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla.h"

void main (int argc, char** argv){
  HASH_TABLE *h;
  SIMBOLO *s, *s1, *s2, *temp;
  listaSimbolo *l;
  s = newSimbolo("lalal", 1, 1);
  s1 = newSimbolo("lalla", 1, 1);
  s2 = newSimbolo("jajaj", 1, 1);
  l = newListaSimbolo();
  h = newHashTable();

  printSimbolo(s);
  printSimbolo(s1);
  printSimbolo(s2);
  insertarSimbolo(h, s);
  insertarSimbolo(h, s1);
  insertarSimbolo(h, s2);
  printHashTable(h);

  temp = buscarSimbolo(h, "jajaj");
  printf("\n");
  if(temp)
    printSimbolo(temp);
  else printf("\nNOT FOUND\n");

  temp = buscarSimbolo(h, "xd");
  printf("\n");
  if(temp)
    printSimbolo(temp);
  else printf("\nGOOD NOT FOUND\n");

  if(insertarSimbolo(h, s) == TRUE){
    printf("\nMAL");
  }
  else{ printf("\nNO inserta 2 iguales");}



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
