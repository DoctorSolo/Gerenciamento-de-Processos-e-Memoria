#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

#define MAX 5
#define QUANTUM 0.8

typedef struct {
    int id_processo;
    float tempo_restante;
} Processo;

typedef struct {
    Processo elementos[MAX];
    int inicio;
    int fim;
    int quantidade;
} FILA;

void inicializarFila(FILA *f);
int estaCheia(FILA *f);
int estaVazia(FILA *f);
void enfileirar(FILA *f, Processo p);
Processo desenfileirar(FILA *f);
void simularRoundRobin(FILA *f);

#endif // FIFO_H_INCLUDED
