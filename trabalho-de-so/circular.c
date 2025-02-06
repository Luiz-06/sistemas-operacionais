#include <stdio.h>

typedef struct Processo {
    int id;
    int tempo_execucao;
    int tempo_restante;
    int tempo_inicio;
    int tempo_termino;
    int tempo_chegada;
} Processo;

void ordenar_por_chegada(Processo processos[], int num_processos) {
    for (int i = 0; i < num_processos - 1; i++) {
        for (int j = i + 1; j < num_processos; j++) {
            if (processos[i].tempo_chegada > processos[j].tempo_chegada) {
                Processo temp = processos[i];
                processos[i] = processos[j];
                processos[j] = temp;
            }
        }
    }
}

int verificar_e_adicionar_troca_contexto(Processo fila[], int fila_inicio, int fila_fim, int tempo_total, int troca_contexto) {
    if (fila_inicio + 1 < fila_fim) { 
        return troca_contexto;
    }
    return 0;
}

void round_robin(Processo processos[], int num_processos, int quantum, int troca_contexto) {
    int tempo_vida[num_processos];
    int tempo_espera[num_processos];

    for (int i = 0; i < num_processos; i++) {
        tempo_vida[i] = 0; 
        tempo_espera[i] = 0; 
    }

    int tempo_total = 0;
    int fila_inicio = 0;
    int fila_fim = num_processos;
    int total_trocas = 0;

    while (fila_inicio < fila_fim) {
        Processo* processo = &processos[fila_inicio];

        if (tempo_total < processo->tempo_chegada) {
            tempo_total = processo->tempo_chegada;
        }

        if (processo->tempo_inicio == -1) {
            processo->tempo_inicio = tempo_total;
        }

        if (processo->tempo_restante > quantum) {
            tempo_total += quantum;
            processo->tempo_restante -= quantum;
            
            tempo_total += verificar_e_adicionar_troca_contexto(processos, fila_inicio, fila_fim, tempo_total, troca_contexto);
            
            fila_inicio++;  
            total_trocas++;
            processos[fila_fim++] = *processo; 
        } else {
            tempo_total += processo->tempo_restante;
            processo->tempo_restante = 0;
            processo->tempo_termino = tempo_total;

            tempo_vida[processo->id - 1] = processo->tempo_termino - processo->tempo_chegada;
            tempo_espera[processo->id - 1] = tempo_vida[processo->id - 1] - processo->tempo_execucao;

            printf("\nT_vida(t%d): %d\n", processo->id, tempo_vida[processo->id - 1]);
            printf("T_espera(t%d): %d\n", processo->id, tempo_espera[processo->id - 1]);
            printf("__________________________________________________");

            tempo_total += verificar_e_adicionar_troca_contexto(processos, fila_inicio, fila_fim, tempo_total, troca_contexto);
            
            fila_inicio++;  
            total_trocas++;
        }
    }

    int somatorio_espera = 0;
    int somatorio_vida = 0;

    for (int i = 0; i < num_processos; i++) {
        somatorio_espera += tempo_espera[i];
        somatorio_vida += tempo_vida[i];
    }

    float tempoMedioDeVida = somatorio_vida / num_processos;
    float tempoMedioDeEspera = somatorio_espera / num_processos;

    printf("\nTm_espera: %.2f\n", tempoMedioDeEspera);
    printf("Tm_vida: %.2f\n", tempoMedioDeVida);
    printf("Tempo total: %d\n", tempo_total);
}

int main() {
    Processo processos[] = {
        {1, 10, 10, -1, 0, 5},  
        {2, 30, 30, -1, 0, 15},
        {3, 20, 20, -1, 0, 10},
        {4, 40, 40, -1, 0, 0} 
    };

    int num_processos = sizeof(processos) / sizeof(processos[0]);
    int quantum = 15;
    int troca_contexto = 4;

    ordenar_por_chegada(processos, num_processos);

    round_robin(processos, num_processos, quantum, troca_contexto);

    return 0;
}
