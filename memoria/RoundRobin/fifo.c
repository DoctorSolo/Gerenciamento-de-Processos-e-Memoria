#include <stdio.h>
#include <windows.h>
#include "fifo.h"

void inicializarFila(FILA *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade;
}

int estaCheia(FILA *f) {
    return f->quantidade == MAX;
}

int estaVazia(FILA *f) {
    return f->quantidade == 0;
}

void enfileirar(FILA *f, Processo p) {
    while(estaCheia(f)){
        Sleep(10);// Evita a perda do processo fazendo com que entre em espera
    }

    f->elementos[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->quantidade++;

    printf("Processo [%d] re-enfileirado com tempo restante: %.2fs\n", p.id_processo, p.tempo_restante);
    return 1;
}

Processo desenfileirar(FILA *f) {
    Processo p = f->elementos[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;
    return p;
}

void simularRoundRobin(FILA *f) {
    while (!estaVazia(f)) {
        Processo p = desenfileirar(f);

        if (p.tempo_restante <= QUANTUM) {
            printf("Processo [%d] executando por %.2fs (finalizado)\n", p.id_processo, p.tempo_restante);
            Sleep((int)(p.tempo_restante * 1000));
        } else {
            printf("Processo [%d] executando por %.2fs (resta %.2fs)\n", p.id_processo, QUANTUM, p.tempo_restante - QUANTUM);
            Sleep((int)(QUANTUM * 1000));
            p.tempo_restante -= QUANTUM;

            enfileirar(f, p);  // sempre tentará reaproveitar o espaço circular
        }
    }

    printf("Todos os processos foram finalizados!\n");
}

