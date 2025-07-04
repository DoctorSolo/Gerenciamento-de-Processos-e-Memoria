#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "processos/src/fifo/FIFO.h"
#include "processos/RoundRobin/ROUND_ROBIN.h"

int main()
{
    FILA f;
    inicializarFila(&f);
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        Processo p;
        p.id_processo = i + 1;
        p.tempo_restante = ((rand() % 301) + 50) / 100.0; // Simular de 0.5 a 3.5 segundos
        enfileirar(&f, p);
    }

    simularRoundRobin(&f);
    return 0;
}
