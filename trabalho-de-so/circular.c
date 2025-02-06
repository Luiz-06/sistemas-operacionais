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

void round_robin(Processo processos[], int num_processos, int quantum, int troca_contexto) {
    Processo fila[num_processos]; 

    int tempo_espera[num_processos];  
    int tempo_vida[num_processos];

    for (int i = 0; i < num_processos; i++) {
        fila[i] = processos[i];
        fila[i].tempo_inicio = -1;  
        tempo_espera[i] = 0;
        tempo_vida[i] = 0; 
    }

    int tempo_total = 0;
    int fila_inicio = 0;
    int fila_fim = num_processos;
    int total_trocas = 0;

    while (fila_inicio < fila_fim) {
        Processo* processo = &fila[fila_inicio];

        if (tempo_total < processo->tempo_chegada) {
            tempo_total = processo->tempo_chegada;
        }

        if (processo->tempo_inicio == -1) {
            processo->tempo_inicio = tempo_total;
        }

        if (processo->tempo_restante > quantum) {
            tempo_total += quantum;
            processo->tempo_restante -= quantum;
            fila_inicio++;
            fila[fila_fim++] = *processo;
            tempo_total += troca_contexto;
            total_trocas++;
        } else {
            tempo_total += processo->tempo_restante;
            processo->tempo_restante = 0;
            processo->tempo_termino = tempo_total;

            tempo_vida[processo->id - 1] = processo->tempo_termino - processo->tempo_chegada;

            printf("Processo %d terminou | Tempo de vida: %d | Tempo de espera: ??\n",
                processo->id, tempo_vida[processo->id - 1]);

            fila_inicio++;
            tempo_total += troca_contexto;
            total_trocas++;
        }
    }

    printf("Tempo total: %d\n", tempo_total - troca_contexto);
    printf("Total de trocas de contexto: %d\n", total_trocas);
    
    int soma_tempo_vida = 0;

    for (int i = 0; i < num_processos; i++) {
        soma_tempo_vida += tempo_vida[i];
    }

    float tempo_medio_vida = (float)soma_tempo_vida / num_processos;

    printf("Tempo médio de vida: %.2f\n", tempo_medio_vida);
}

int main() {
    Processo processos[] = {
        {1, 10, 10, -1, 0, 3},  
        {2, 10, 10, -1, 0, 1}   
    };

    int num_processos = sizeof(processos) / sizeof(processos[0]);
    int quantum = 5;
    int troca_contexto = 4;

    ordenar_por_chegada(processos, num_processos);

    round_robin(processos, num_processos, quantum, troca_contexto);

    return 0;
}
