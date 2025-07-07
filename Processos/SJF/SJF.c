#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../src/processos/PROCESSOS.h"
#include "../src/fifo/FIFO.h"


// Um algoritmo BubbleSort sera usado para reordenar os valores
// para o menor tempo de execucao para o maior
void bubbleSort(FILA *f)
{
    for (int i = 0; i < f->quantidade; i++)
    {
        for (int j = 0; j < f->quantidade - i - 1; j++)
        {
            if (f->elementos[j].tempo_restante > f->elementos[j + 1].tempo_restante)
            {
                Processo temp = f->elementos[j];
                f->elementos[j] = f->elementos[j + 1];
                f->elementos[j + 1] = temp;
            }
        }
    }
}


// essa funcao é o SJF do projeto
void SJF_Shortest_Job_First(FILA *f)
{
    bubbleSort(f);  // Reordena a fila

    // O algoritmo ira parar se a fila esvaziar
    while (!estaVazia(f))
    {
        // p recebe o processo desenfileirado e executa ele
        Processo p = desenfileirar(f);
        printf("Processo [%d] executando por %.2fs (finalizado)\n", p.id_processo, p.tempo_restante);
        Sleep(p.tempo_restante * 1000);
    }
    printf("SJF finalizado!\n");
}
