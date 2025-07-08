#ifndef FITS_H_INCLUDED
#define FITS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TAM_MEMORIA 100
#define NUM_PROCESSOS 5

// Estruturas para Particionamento Cont�guo
typedef struct {
    int inicio;
    int tamanho;
    int livre;
    int processo;
} Particao;

typedef struct {
    int id;
    int tamanho;
} ProcessoMemoria;

// Estruturas para Pagina��o
typedef struct {
    int id_processo;
    int pagina;
} Quadro;

void simularParticionamento();

// Fun��es para Particionamento Cont�guo
void inicializar_particoes(Particao particoes[], int tamanho_memoria);
void imprimir_mapa_memoria(Particao particoes[], int num_particoes);
int first_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo);
int best_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo);
int worst_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo);

// Fun��es para Pagina��o
void inicializar_quadros(Quadro quadros[], int num_quadros);
void imprimir_tabela_paginas(Quadro quadros[], int num_quadros);
void alocar_paginas(Quadro quadros[], int num_quadros, int id_processo, int num_paginas);

#endif // FITS_H_INCLUDED
