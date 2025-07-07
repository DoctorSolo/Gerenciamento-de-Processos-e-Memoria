#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>

#include "../src/fifo/FIFO.h"
#include "ROUND_ROBIN.h"


// Essa funcao � o RoundRobin
void simularRoundRobin(FILA *f) {
    // Essa fun��o ira se encerrar se a fila esvaziar
    while (!estaVazia(f)) {
        // Recebe o processo desenfileirado
        Processo p = desenfileirar(f);

        // Se o tempo restante for menor ou igual o Quantum do roundrobin,
        //ent�o executa o processo direto.
        if (p.tempo_restante <= QUANTUM) {
            printf("Processo [%d] executando por %.2fs (finalizado)\n", p.id_processo, p.tempo_restante);
            Sleep((int)(p.tempo_restante * 1000));
        // Se n�o, ent�o fragmenta o tempo restante e, coloca o processo na fila de novo.
        } else {
            printf("Processo [%d] executando por %.2fs (resta %.2fs)\n", p.id_processo, QUANTUM, p.tempo_restante - QUANTUM);
            Sleep((int)(QUANTUM * 1000));
            p.tempo_restante -= QUANTUM;

            enfileirar(f, p);  // sempre tentar� reaproveitar o espa�o circular
        }
    }

    printf("Todos os processos foram finalizados!\n");
}
