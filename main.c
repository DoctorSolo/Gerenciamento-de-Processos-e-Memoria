#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "processos/src/fifo/FIFO.h"
#include "processos/RoundRobin/ROUND_ROBIN.h"
#include "processos/FCFS/FCFS.h"
#include "processos/SJF/SJF.h"


// Metodo para criar os processos para texte
void criarProcessos(FILA *f)
{
    // Usamos um loop para dar ID e um tempo de execução aleatorio
    for (int i = 0; i < 10; i++)
    {
        Processo p;
        p.id_processo = i + 1;  // ID inicial sempre será 1
        p.tempo_restante = ((rand() % 301) + 50) / 100.0; // Simular de 0.5 a 3.5 segundos
        enfileirar(f, p);       // Enfileira o processo
    }
}


// Metodo para copiar as filas, a fim de testar o tempo de
// execuчуo dos metodos fielmente
void copiarFila(FILA* f, FILA* c)
{
    // inicia a nova fila
    inicializarFila(c);

    // loop nescessario para copiar o array que simula a fila
    for (int i = 0; i < f->quantidade; i++)
    {
        int pos = (f->inicio + i) % MAX;
        c->elementos[pos] = f->elementos[pos];
    }
    // copia os valores de apontamento
    c->fim        = f->fim;
    c->inicio     = f->inicio;
    c->quantidade = f->quantidade;
}


// Metodo MAIN
int main()
{
    FILA f;
    criarProcessos(&f);

    FILA r;
    copiarFila(&f, &r);

    FILA c;
    copiarFila(&f, &c);

    // RoundRobin
    printf("\nPrograma comeca aqui!\n \nRoundRobin\n");
    simularRoundRobin(&f);

    // FCFS
    printf("\nFCFS\n");
    FCFS_FirstComeFirstServer(&r);

    // SJF
    printf("\nSJF\n");
    SJF_Shortest_Job_First(&c);

    return 0;
}
