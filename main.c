#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "processos/src/fifo/FIFO.h"
#include "processos/RoundRobin/ROUND_ROBIN.h"
#include "processos/FCFS/FCFS.h"


// Metodo para criar os processos para texte
void criarProcessos(FILA *f)
{

    for (int i = 0; i < 10; i++)
    {
        Processo p;
        p.id_processo = i + 1;
        p.tempo_restante = ((rand() % 301) + 50) / 100.0; // Simular de 0.5 a 3.5 segundos
        enfileirar(f, p);
    }
}


// Metodo para copiar as filas, a fim de testar o tempo de
// execução dos metodos fielmente
void copiarFila(FILA* f, FILA* c)
{
    inicializarFila(c);
    for (int i = 0; i < f->quantidade; i++)
    {
        int pos = (f->inicio + i) % MAX;
        c->elementos[pos] = f->elementos[pos];
    }

    c->fim        = f->fim;
    c->inicio     = f->inicio;
    c->quantidade = f->quantidade;
}


int main()
{

    FILA f;
    criarProcessos(&f);

    FILA r;
    copiarFila(&f, &r);

    FILA c;
    copiarFila(&f, &c);

    printf("Programa comaca aqui!\n");

    // RoundRobin
    simularRoundRobin(&r);

    // FCFS
    FCFS_FirstComeFirstServer(&c);
    return 0;
}
