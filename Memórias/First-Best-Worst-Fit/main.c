#include <stdio.h>
#include <stdlib.h>
#include "FITS.h"

int main() {
    // ==============================================
    // SIMULAÇÃO DE PARTICIONAMENTO CONTÍGUO
    // ==============================================
    printf("----- SIMULACAO DE PARTICIONAMENTO CONTIGUO -----\n");

    // Cria array de partições com espaço extra para possível fragmentação
    Particao particoes[TAM_MEMORIA * 2];
    int num_particoes = 1; // Começa com apenas 1 partição (toda a memória)

    // Inicializa a memória como um único bloco livre
    inicializar_particoes(particoes, TAM_MEMORIA);

    // Define os processos que serão alocados (ID e tamanho)
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
    // Mostra o estado da memória após alocações
    imprimir_mapa_memoria(particoes, num_particoes);

    // ==============================================
    // TESTE DO ALGORITMO BEST FIT
    // ==============================================
    // Reinicia a memória para novo teste
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
    // Reinicia a memória para novo teste
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
    // SIMULAÇÃO DE PAGINAÇÃO
    // ==============================================
    printf("\n\n----- SIMULACAO DE PAGINACAO -----\n");
    Quadro quadros[TAM_MEMORIA]; // Cria array de quadros de página

    // Inicializa todos os quadros como livres
    inicializar_quadros(quadros, TAM_MEMORIA);

    // Aloca páginas para 3 processos diferentes:
    alocar_paginas(quadros, TAM_MEMORIA, 1, 15); // Processo 1, 15 páginas
    alocar_paginas(quadros, TAM_MEMORIA, 2, 8);  // Processo 2, 8 páginas
    alocar_paginas(quadros, TAM_MEMORIA, 3, 20); // Processo 3, 20 páginas

    // Mostra apenas os primeiros 30 quadros para facilitar visualização
    imprimir_tabela_paginas(quadros, 30);

    return 0;
}

// ==============================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ==============================================

/**
 * Inicializa a memória como um único bloco livre
 * @param particoes Array de partições
 * @param tamanho_memoria Tamanho total da memória
 */
void inicializar_particoes(Particao particoes[], int tamanho_memoria) {
    particoes[0].inicio = 0;               // Começa no endereço 0
    particoes[0].tamanho = tamanho_memoria; // Ocupa toda a memória
    particoes[0].livre = 1;                // Está livre
    particoes[0].processo = -1;            // Nenhum processo associado
}

/**
 * Imprime o mapa atual da memória
 * @param particoes Array de partições
 * @param num_particoes Número atual de partições
 */
void imprimir_mapa_memoria(Particao particoes[], int num_particoes) {
    printf("\nMapa da Memoria:\n");
    for (int i = 0; i < num_particoes; i++) {
        // Mostra intervalo de endereços [início-fim]
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
 * Algoritmo First Fit para alocação de memória
 * @param particoes Array de partições
 * @param num_particoes Ponteiro para número de partições (pode ser modificado)
 * @param tamanho Tamanho do processo a ser alocado
 * @param id_processo ID do processo
 * @return 1 se alocou com sucesso, 0 caso contrário
 */
int first_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo) {
    // Percorre todas as partições existentes
    for (int i = 0; i < *num_particoes; i++) {
        // Verifica se a partição está livre e cabe o processo
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {

            // Se a partição for maior que o necessário, divide em duas
            if (particoes[i].tamanho > tamanho) {
                // Desloca as partições posteriores para abrir espaço
                for (int j = *num_particoes; j > i + 1; j--) {
                    particoes[j] = particoes[j - 1];
                }

                // Cria nova partição com o espaço restante
                particoes[i + 1].inicio = particoes[i].inicio + tamanho;
                particoes[i + 1].tamanho = particoes[i].tamanho - tamanho;
                particoes[i + 1].livre = 1;
                particoes[i + 1].processo = -1;
                (*num_particoes)++; // Incrementa contador de partições
            }

            // Aloca o processo na partição atual
            particoes[i].tamanho = tamanho;
            particoes[i].livre = 0;
            particoes[i].processo = id_processo;
            return 1; // Sucesso
        }
    }
    return 0; // Falha (não encontrou partição adequada)
}

/**
 * Algoritmo Best Fit para alocação de memória
 * @param particoes Array de partições
 * @param num_particoes Ponteiro para número de partições
 * @param tamanho Tamanho do processo a ser alocado
 * @param id_processo ID do processo
 * @return 1 se alocou com sucesso, 0 caso contrário
 */
int best_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo) {
    int melhor_idx = -1;          // Índice da melhor partição
    int menor_espaco = INT_MAX;   // Menor espaço residual encontrado

    // Procura a partição que deixa o menor espaço residual
    for (int i = 0; i < *num_particoes; i++) {
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {
            // Calcula espaço que sobraria após alocação
            int espaco_residual = particoes[i].tamanho - tamanho;

            // Verifica se é a melhor opção até agora
            if (espaco_residual < menor_espaco) {
                menor_espaco = espaco_residual;
                melhor_idx = i;
            }
        }
    }

    // Se encontrou uma partição adequada
    if (melhor_idx != -1) {
        // Se a partição for maior que o necessário, divide
        if (particoes[melhor_idx].tamanho > tamanho) {
            // Desloca partições para abrir espaço
            for (int j = *num_particoes; j > melhor_idx + 1; j--) {
                particoes[j] = particoes[j - 1];
            }

            // Cria nova partição com espaço restante
            particoes[melhor_idx + 1].inicio = particoes[melhor_idx].inicio + tamanho;
            particoes[melhor_idx + 1].tamanho = particoes[melhor_idx].tamanho - tamanho;
            particoes[melhor_idx + 1].livre = 1;
            particoes[melhor_idx + 1].processo = -1;
            (*num_particoes)++;
        }

        // Aloca o processo na partição selecionada
        particoes[melhor_idx].tamanho = tamanho;
        particoes[melhor_idx].livre = 0;
        particoes[melhor_idx].processo = id_processo;
        return 1; // Sucesso
    }
    return 0; // Falha
}

/**
 * Algoritmo Worst Fit para alocação de memória
 * @param particoes Array de partições
 * @param num_particoes Ponteiro para número de partições
 * @param tamanho Tamanho do processo a ser alocado
 * @param id_processo ID do processo
 * @return 1 se alocou com sucesso, 0 caso contrário
 */
int worst_fit(Particao particoes[], int *num_particoes, int tamanho, int id_processo) {
    int melhor_idx = -1;      // Índice da melhor partição
    int maior_espaco = -1;    // Maior espaço encontrado

    // Procura a maior partição disponível
    for (int i = 0; i < *num_particoes; i++) {
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {
            // Verifica se é a maior partição até agora
            if (particoes[i].tamanho > maior_espaco) {
                maior_espaco = particoes[i].tamanho;
                melhor_idx = i;
            }
        }
    }

    // Se encontrou uma partição adequada
    if (melhor_idx != -1) {
        // Se a partição for maior que o necessário, divide
        if (particoes[melhor_idx].tamanho > tamanho) {
            // Desloca partições para abrir espaço
            for (int j = *num_particoes; j > melhor_idx + 1; j--) {
                particoes[j] = particoes[j - 1];
            }

            // Cria nova partição com espaço restante
            particoes[melhor_idx + 1].inicio = particoes[melhor_idx].inicio + tamanho;
            particoes[melhor_idx + 1].tamanho = particoes[melhor_idx].tamanho - tamanho;
            particoes[melhor_idx + 1].livre = 1;
            particoes[melhor_idx + 1].processo = -1;
            (*num_particoes)++;
        }

        // Aloca o processo na partição selecionada
        particoes[melhor_idx].tamanho = tamanho;
        particoes[melhor_idx].livre = 0;
        particoes[melhor_idx].processo = id_processo;
        return 1; // Sucesso
    }
    return 0; // Falha
}

/**
 * Inicializa todos os quadros de página como livres
 * @param quadros Array de quadros
 * @param num_quadros Número total de quadros
 */
void inicializar_quadros(Quadro quadros[], int num_quadros) {
    for (int i = 0; i < num_quadros; i++) {
        quadros[i].id_processo = -1;  // -1 indica quadro livre
        quadros[i].pagina = -1;       // Nenhuma página associada
    }
}

/**
 * Imprime a tabela de páginas
 * @param quadros Array de quadros
 * @param num_quadros Número de quadros a exibir
 */
void imprimir_tabela_paginas(Quadro quadros[], int num_quadros) {
    printf("\nTabela de Paginas:\n");
    printf("Quadro\tProcesso\tPagina\n");

    for (int i = 0; i < num_quadros; i++) {
        printf("%d\t", i); // Número do quadro

        if (quadros[i].id_processo == -1) {
            printf("Livre\t\t-\n"); // Quadro livre
        } else {
            printf("%d\t\t%d\n",     // Quadro ocupado
                  quadros[i].id_processo, quadros[i].pagina);
        }
    }
}

/**
 * Aloca páginas para um processo
 * @param quadros Array de quadros
 * @param num_quadros Número total de quadros
 * @param id_processo ID do processo
 * @param num_paginas Número de páginas necessárias
 */
void alocar_paginas(Quadro quadros[], int num_quadros, int id_processo, int num_paginas) {
    int paginas_alocadas = 0; // Contador de páginas alocadas

    // Percorre os quadros até alocar todas as páginas ou acabar a memória
    for (int i = 0; i < num_quadros && paginas_alocadas < num_paginas; i++) {
        if (quadros[i].id_processo == -1) { // Se quadro está livre
            quadros[i].id_processo = id_processo;
            quadros[i].pagina = paginas_alocadas; // Número da página (0 a n-1)
            paginas_alocadas++;
        }
    }

    // Verifica se conseguiu alocar todas as páginas necessárias
    if (paginas_alocadas < num_paginas) {
        printf("Processo %d: Memoria insuficiente (%d/%d paginas alocadas)\n",
               id_processo, paginas_alocadas, num_paginas);
    }
}
