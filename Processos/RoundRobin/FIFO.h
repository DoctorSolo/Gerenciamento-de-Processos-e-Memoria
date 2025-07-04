#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

#define MAX 5

typedef struct {
    int id_processo;
    float tempo_restante;
} Processo;





// Essa ser� nossa fila, ela � circular e trabalharemos
// com ponteiros. Variavel inicio e final recebera os
// valores do inicio e final da fila circular, e quantidade
// ira ser o que vai controlar se a fila esta cheia ou n�o.
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

#endif // FIFO_H_INCLUDED
