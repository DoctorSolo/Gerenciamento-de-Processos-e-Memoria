#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include "../src/fifo/FIFO.h"
#include "../src/processos/PROCESSOS.h"


// Função basica da estrutura FCFS
void FCFS_FirstComeFirstServer(FILA *f)
{
    // O algoritmo ira parar se a fila esvaziar
    while (!estaVazia(f))
    {
        // p recebe o processo desenfileirado e executa ele
        Processo p = desenfileirar(f);
        printf("Processo [%d] executando por %.2fs (finalizado)\n", p.id_processo, p.tempo_restante);
        Sleep(p.tempo_restante * 1000);
    }
    printf("FCFS finalizado!\n");
}
