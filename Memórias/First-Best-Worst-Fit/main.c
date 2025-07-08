#include <stdio.h>
#include <stdlib.h>
#include "FITS.h"

int main() {
    // ==============================================
    // SIMULA��O DE PARTICIONAMENTO CONT�GUO
    // ==============================================
    printf("----- SIMULACAO DE PARTICIONAMENTO CONTIGUO -----\n");

    // Cria array de parti��es com espa�o extra para poss�vel fragmenta��o
    Particao particoes[TAM_MEMORIA * 2];
    int num_particoes = 1; // Come�a com apenas 1 parti��o (toda a mem�ria)

    // Inicializa a mem�ria como um �nico bloco livre
    inicializar_particoes(particoes, TAM_MEMORIA);

    // Define os processos que ser�o alocados (ID e tamanho)
    Processo processos[NUM_PROCESSOS] = {
        {1, 30}, // Processo 1 precisa de 30 blocos
        {2, 20}, // Processo 2 precisa de 20 blocos
        {3, 40}, // Processo 3 precisa de 40 blocos
        {4, 10}, // Processo 4 precisa de 10 blocos
        {5, 25}  // Processo 5 precisa de 25 blocos
    };

    // ==============================================
    // TESTE DO ALGORITMO FIRST FIT
    // ==============================================
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < NUM_PROCESSOS; i++) {
        if (first_fit(particoes, &num_particoes, processos[i].tamanho, processos[i].id)) {
            printf("Processo %d (%d blocos) alocado com sucesso\n",
                  processos[i].id, processos[i].tamanho);
        } else {
            printf("Falha ao alocar Processo %d (%d blocos)\n",
                  processos[i].id, processos[i].tamanho);
        }
    }
    // Mostra o estado da mem�ria ap�s aloca��es
    imprimir_mapa_memoria(particoes, num_particoes);

    // ==============================================
    // TESTE DO ALGORITMO BEST FIT
    // ==============================================
    // Reinicia a mem�ria para novo teste
    num_particoes = 1;
    inicializar_particoes(particoes, TAM_MEMORIA);

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < NUM_PROCESSOS; i++) {
        if (best_fit(particoes, &num_particoes, processos[i].tamanho, processos[i].id)) {
            printf("Processo %d (%d blocos) alocado com sucesso\n",
                  processos[i].id, processos[i].tamanho);
        } else {
            printf("Falha ao alocar Processo %d (%d blocos)\n",
                  processos[i].id, processos[i].tamanho);
        }
    }
    imprimir_mapa_memoria(particoes, num_particoes);

    // ==============================================
    // TESTE DO ALGORITMO WORST FIT
    // ==============================================
    // Reinicia a mem�ria para novo teste
    num_particoes = 1;
    inicializar_particoes(particoes, TAM_MEMORIA);

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < NUM_PROCESSOS; i++) {
        if (worst_fit(particoes, &num_particoes, processos[i].tamanho, processos[i].id)) {
            printf("Processo %d (%d blocos) alocado com sucesso\n",
                  processos[i].id, processos[i].tamanho);
        } else {
            printf("Falha ao alocar Processo %d (%d blocos)\n",
                  processos[i].id, processos[i].tamanho);
        }
    }
    imprimir_mapa_memoria(particoes, num_particoes);

    // ==============================================
    // SIMULA��O DE PAGINA��O
    // ==============================================
    printf("\n\n----- SIMULACAO DE PAGINACAO -----\n");
    Quadro quadros[TAM_MEMORIA]; // Cria array de quadros de p�gina

    // Inicializa todos os quadros como livres
    inicializar_quadros(quadros, TAM_MEMORIA);

    // Aloca p�ginas para 3 processos diferentes:
    alocar_paginas(quadros, TAM_MEMORIA, 1, 15); // Processo 1, 15 p�ginas
    alocar_paginas(quadros, TAM_MEMORIA, 2, 8);  // Processo 2, 8 p�ginas
    alocar_paginas(quadros, TAM_MEMORIA, 3, 20); // Processo 3, 20 p�ginas

    // Mostra apenas os primeiros 30 quadros para facilitar visualiza��o
    imprimir_tabela_paginas(quadros, 30);

    return 0;
}

// ==============================================
// IMPLEMENTA��O DAS FUN��ES
// ==============================================

/**
 * Inicializa a mem�ria como um �nico bloco livre
 * @param particoes Array de parti��es
 * @param tamanho_memoria Tamanho total da mem�ria
 */
void inicializar_particoes(Particao particoes[], int tamanho_memoria) {
    particoes[0].inicio = 0;               // Come�a no endere�o 0
    particoes[0].tamanho = tamanho_memoria; // Ocupa toda a mem�ria
    particoes[0].livre = 1;                // Est� livre
    particoes[0].processo = -1;            // Nenhum processo associado
}

/**
 * Imprime o mapa atual da mem�ria
 * @param particoes Array de parti��es
 * @param num_particoes N�mero atual de parti��es
 */
void imprimir_mapa_memoria(Particao particoes[], int num_particoes) {
    printf("\nMapa da Memoria:\n");
    for (int i = 0; i < num_particoes; i++) {
        // Mostra intervalo de endere�os [in�cio-fim]
        printf("Particao %d: [%d-%d] ", i, particoes[i].inicio,
               particoes[i].inicio + particoes[i].tamanho - 1);

        if (particoes[i].livre) {
            printf("Livre (%d blocos)\n", particoes[i].tamanho);
        } else {
            printf("Processo %d (%d blocos)\n",
                  particoes[i].processo, particoes[i].tamanho);
        }
    }
}

/**
 * Algoritmo First Fit para aloca��o de mem�ria
 * @param particoes Array de parti��es
 * @param num_particoes Ponteiro para n�mero de parti��es (pode ser modificado)
 * @param tamanho Tamanho do processo a ser alocado
 * @param id_processo ID do processo
 * @return 1 se alocou com sucesso, 0 caso contr�rio
 */
int first_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo) {
    // Percorre todas as parti��es existentes
    for (int i = 0; i < *num_particoes; i++) {
        // Verifica se a parti��o est� livre e cabe o processo
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {

            // Se a parti��o for maior que o necess�rio, divide em duas
            if (particoes[i].tamanho > tamanho) {
                // Desloca as parti��es posteriores para abrir espa�o
                for (int j = *num_particoes; j > i + 1; j--) {
                    particoes[j] = particoes[j - 1];
                }

                // Cria nova parti��o com o espa�o restante
                particoes[i + 1].inicio = particoes[i].inicio + tamanho;
                particoes[i + 1].tamanho = particoes[i].tamanho - tamanho;
                particoes[i + 1].livre = 1;
                particoes[i + 1].processo = -1;
                (*num_particoes)++; // Incrementa contador de parti��es
            }

            // Aloca o processo na parti��o atual
            particoes[i].tamanho = tamanho;
            particoes[i].livre = 0;
            particoes[i].processo = id_processo;
            return 1; // Sucesso
        }
    }
    return 0; // Falha (n�o encontrou parti��o adequada)
}

/**
 * Algoritmo Best Fit para aloca��o de mem�ria
 * @param particoes Array de parti��es
 * @param num_particoes Ponteiro para n�mero de parti��es
 * @param tamanho Tamanho do processo a ser alocado
 * @param id_processo ID do processo
 * @return 1 se alocou com sucesso, 0 caso contr�rio
 */
int best_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo) {
    int melhor_idx = -1;          // �ndice da melhor parti��o
    int menor_espaco = INT_MAX;   // Menor espa�o residual encontrado

    // Procura a parti��o que deixa o menor espa�o residual
    for (int i = 0; i < *num_particoes; i++) {
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {
            // Calcula espa�o que sobraria ap�s aloca��o
            int espaco_residual = particoes[i].tamanho - tamanho;

            // Verifica se � a melhor op��o at� agora
            if (espaco_residual < menor_espaco) {
                menor_espaco = espaco_residual;
                melhor_idx = i;
            }
        }
    }

    // Se encontrou uma parti��o adequada
    if (melhor_idx != -1) {
        // Se a parti��o for maior que o necess�rio, divide
        if (particoes[melhor_idx].tamanho > tamanho) {
            // Desloca parti��es para abrir espa�o
            for (int j = *num_particoes; j > melhor_idx + 1; j--) {
                particoes[j] = particoes[j - 1];
            }

            // Cria nova parti��o com espa�o restante
            particoes[melhor_idx + 1].inicio = particoes[melhor_idx].inicio + tamanho;
            particoes[melhor_idx + 1].tamanho = particoes[melhor_idx].tamanho - tamanho;
            particoes[melhor_idx + 1].livre = 1;
            particoes[melhor_idx + 1].processo = -1;
            (*num_particoes)++;
        }

        // Aloca o processo na parti��o selecionada
        particoes[melhor_idx].tamanho = tamanho;
        particoes[melhor_idx].livre = 0;
        particoes[melhor_idx].processo = id_processo;
        return 1; // Sucesso
    }
    return 0; // Falha
}

/**
 * Algoritmo Worst Fit para aloca��o de mem�ria
 * @param particoes Array de parti��es
 * @param num_particoes Ponteiro para n�mero de parti��es
 * @param tamanho Tamanho do processo a ser alocado
 * @param id_processo ID do processo
 * @return 1 se alocou com sucesso, 0 caso contr�rio
 */
int worst_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo) {
    int melhor_idx = -1;      // �ndice da melhor parti��o
    int maior_espaco = -1;    // Maior espa�o encontrado

    // Procura a maior parti��o dispon�vel
    for (int i = 0; i < *num_particoes; i++) {
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {
            // Verifica se � a maior parti��o at� agora
            if (particoes[i].tamanho > maior_espaco) {
                maior_espaco = particoes[i].tamanho;
                melhor_idx = i;
            }
        }
    }

    // Se encontrou uma parti��o adequada
    if (melhor_idx != -1) {
        // Se a parti��o for maior que o necess�rio, divide
        if (particoes[melhor_idx].tamanho > tamanho) {
            // Desloca parti��es para abrir espa�o
            for (int j = *num_particoes; j > melhor_idx + 1; j--) {
                particoes[j] = particoes[j - 1];
            }

            // Cria nova parti��o com espa�o restante
            particoes[melhor_idx + 1].inicio = particoes[melhor_idx].inicio + tamanho;
            particoes[melhor_idx + 1].tamanho = particoes[melhor_idx].tamanho - tamanho;
            particoes[melhor_idx + 1].livre = 1;
            particoes[melhor_idx + 1].processo = -1;
            (*num_particoes)++;
        }

        // Aloca o processo na parti��o selecionada
        particoes[melhor_idx].tamanho = tamanho;
        particoes[melhor_idx].livre = 0;
        particoes[melhor_idx].processo = id_processo;
        return 1; // Sucesso
    }
    return 0; // Falha
}

/**
 * Inicializa todos os quadros de p�gina como livres
 * @param quadros Array de quadros
 * @param num_quadros N�mero total de quadros
 */
void inicializar_quadros(Quadro quadros[], int num_quadros) {
    for (int i = 0; i < num_quadros; i++) {
        quadros[i].id_processo = -1;  // -1 indica quadro livre
        quadros[i].pagina = -1;       // Nenhuma p�gina associada
    }
}

/**
 * Imprime a tabela de p�ginas
 * @param quadros Array de quadros
 * @param num_quadros N�mero de quadros a exibir
 */
void imprimir_tabela_paginas(Quadro quadros[], int num_quadros) {
    printf("\nTabela de Paginas:\n");
    printf("Quadro\tProcesso\tPagina\n");

    for (int i = 0; i < num_quadros; i++) {
        printf("%d\t", i); // N�mero do quadro

        if (quadros[i].id_processo == -1) {
            printf("Livre\t\t-\n"); // Quadro livre
        } else {
            printf("%d\t\t%d\n",     // Quadro ocupado
                  quadros[i].id_processo, quadros[i].pagina);
        }
    }
}

/**
 * Aloca p�ginas para um processo
 * @param quadros Array de quadros
 * @param num_quadros N�mero total de quadros
 * @param id_processo ID do processo
 * @param num_paginas N�mero de p�ginas necess�rias
 */
void alocar_paginas(Quadro quadros[], int num_quadros, int id_processo, int num_paginas) {
    int paginas_alocadas = 0; // Contador de p�ginas alocadas

    // Percorre os quadros at� alocar todas as p�ginas ou acabar a mem�ria
    for (int i = 0; i < num_quadros && paginas_alocadas < num_paginas; i++) {
        if (quadros[i].id_processo == -1) { // Se quadro est� livre
            quadros[i].id_processo = id_processo;
            quadros[i].pagina = paginas_alocadas; // N�mero da p�gina (0 a n-1)
            paginas_alocadas++;
        }
    }

    // Verifica se conseguiu alocar todas as p�ginas necess�rias
    if (paginas_alocadas < num_paginas) {
        printf("Processo %d: Memoria insuficiente (%d/%d paginas alocadas)\n",
               id_processo, paginas_alocadas, num_paginas);
    }
}
