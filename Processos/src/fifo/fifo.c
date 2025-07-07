#include <stdio.h>
#include <windows.h>
#include "FIFO.h"
#include "../processos/PROCESSOS.h"


// Funcao para retornar algo caso,
// a fila esteja vazia
Processo ProcessoNull() {
    Processo p = {-1, 0.0};
    return p;
}


// Metodo usado para iniciar os ponteiros
// da fila e a variavel de quantidade.
void inicializarFila(FILA *f) {
    f->inicio     = 0;
    f->fim        =-1;
    f->quantidade = 0;
}


// Verifica se a fila está cheia, se estiver
// retorna 1 caso contrario, vai retornar 0.
int estaCheia(FILA *f) {
    return f->quantidade == MAX;
}


// Verifica se a fila está vazia, caso esteja
// retorna 1, e o contrario retorna 0.
int estaVazia(FILA *f) {
    return f->quantidade == 0;
}


// Este metodo é o responsável por enfileirar os processos,
void enfileirar(FILA *f, Processo p) {

    // Este loop serve para evitar que o processo se perca,
    // então ele ira entrar em espera.
    while(estaCheia(f)){
        printf("A fila esta cheia!\n");
        Sleep(10);
        return;
    }

    // Verifica se está vazia para fazer o remanegamento
    // dos valores.
    if (estaVazia(f)){
        inicializarFila(f);
    }

    // Adiciona o elemento no final da fila
    // e mostra os resultados.
    f->fim = (f->fim + 1) % MAX;
    f->elementos[f->fim] = p;
    f->quantidade++;

    printf("Processo [%d] enfileirado com tempo restante: %.2fs\n", p.id_processo, p.tempo_restante);
}


// Este metodo é responsavel por tirar o primeiro da fila.
Processo desenfileirar(FILA *f) {

    // Este metodo é responsavel por impedir erro no codigo,
    // caso a fila estiver vazia.
    if (estaVazia(f)){
        inicializarFila(f);
        printf("A fila está vazia!\n");
        return ProcessoNull();
    }

    // inicio da fila caminha +1 na lista.
    Processo p = f->elementos[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;
    return p;
}
