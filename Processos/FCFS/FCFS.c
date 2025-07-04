#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../src/fifo/FIFO.h"
#include "../src/processos/PROCESSOS.h"


void FCFS_FirstComeFirstServer(FILA *f)
{
    inicializarFila(f);
    while (!estaVazia(f))
    {
        printf("programa entrou aqui!\n");
        desenfileirar(f);
    }
    printf("FCFS finalizado!\n");
}













