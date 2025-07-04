#include "../processos/PROCESSOS.h"


#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED


#define MAX 10

// Essa será nossa fila, ela é circular e trabalharemos
// com ponteiros. Variavel inicio e final recebera os
// valores do inicio e final da fila circular, e quantidade
// ira ser o que vai controlar se a fila esta cheia ou não.
typedef struct {
    Processo elementos[MAX];
    int inicio, fim, quantidade;
} FILA;


void inicializarFila(FILA *f);
int estaCheia(FILA *f);
int estaVazia(FILA *f);
void enfileirar(FILA *f, Processo p);
Processo desenfileirar(FILA *f);

#endif // FIFO_H_INCLUDED
