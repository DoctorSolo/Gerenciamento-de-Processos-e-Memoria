#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../src/fifo/FIFO.h"
#include "ROUND_ROBIN.h"


void simularRoundRobin(FILA *f) {
    while (!estaVazia(f)) {
        Processo p = desenfileirar(f);

        if (p.tempo_restante <= QUANTUM) {
            printf("Processo [%d] executando por %.2fs (finalizado)\n", p.id_processo, p.tempo_restante);
            sleep((int)(p.tempo_restante * 1000));
        } else {
            printf("Processo [%d] executando por %.2fs (resta %.2fs)\n", p.id_processo, QUANTUM, p.tempo_restante - QUANTUM);
            sleep((int)(QUANTUM * 1000));
            p.tempo_restante -= QUANTUM;

            enfileirar(f, p);  // sempre tentará reaproveitar o espaço circular
        }
    }

    printf("Todos os processos foram finalizados!\n");
}
