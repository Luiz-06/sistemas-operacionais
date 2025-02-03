#include <stdio.h>

typedef struct Processo {
    int id;
    int tempo_execucao;
    int tempo_restante;
} Processo;

void round_robin(Processo processos[], int num_processos, int quantum) {
    Processo fila[num_processos];
    for (int i = 0; i < num_processos; i++) {
        fila[i] = processos[i];
    }

    int tempo_total = 0;
    int fila_inicio = 0;
    int fila_fim = num_processos;

    while (fila_inicio < fila_fim) {
        Processo* processo = &fila[fila_inicio];

        if (processo->tempo_restante > quantum) {
            tempo_total += quantum;
            processo->tempo_restante -= quantum;
            fila_inicio++; 
            fila[fila_fim++] = *processo;  
        } else {
            tempo_total += processo->tempo_restante; 
            processo->tempo_restante = 0;
            printf("Processo %d terminou\n", processo->id);
            fila_inicio++;  
        }
    }

    printf("Tempo total: %d\n", tempo_total); 
}

int main() {
    Processo processos[] = {
        {1, 5, 5},
        {2, 3, 3},
    };
    int num_processos = sizeof(processos) / sizeof(processos[0]);
    int quantum = 3;

    round_robin(processos, num_processos, quantum);

    return 0;
}
