#ifndef PROCESSOS_H_INCLUDED
#define PROCESSOS_H_INCLUDED

// Estrutura basica dos processos
typedef struct {
    int id_processo;        // todo processo possui um ID
    float tempo_restante;   // todo processo possui um tempo de execução
} Processo;

#endif // PROCESSOS_H_INCLUDED
