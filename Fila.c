#include <stdlib.h>
#include <stdio.h>
#include "Fila.h"

/* Esse arquivo implementa uma fila circular */

TFila * InitFila( int N ){
	TFila *novaFila;

	novaFila = (TFila *) calloc( 1, sizeof(TFila));
	novaFila->elementos = (int *) calloc(N, sizeof(int));
	novaFila->first = novaFila->last = 0;
	novaFila->N = N;
	return novaFila;
}

void insere(TFila *F, int elemento){
	if( !cheia( F )){
		F->elementos[F->last] = elemento;
		F->last = (F->last + 1)%F->N;
	}
	else{
		printf("fila cheia\n");
		exit(1);
	}
}
int retira(TFila *F){
	int elemento;
	elemento = F->elementos[F->first];
	F->first = (F->first + 1)%F->N;
	return elemento;
}
int vazia(TFila *F){
	return F->first == F->last;
}
int cheia(TFila *F){
	return (F->last+1 == F->N && F->first == 0 ) ||
		   (F->last+1 == F->first);
	//return (F->last + 1)%N==F->first;
}
int primeiro(TFila *F){
	if(vazia(F)){
		printf("Fila está vazia!");
		exit(2);
	}
	else
		return(F->elementos[F->first]);
}
