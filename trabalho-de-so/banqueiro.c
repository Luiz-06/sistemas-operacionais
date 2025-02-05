#include <stdio.h>

int main() {
    /*
    int quantidadeDeProcessos = 3;
    int quantidadeDeRecursos  = 4; 
    */
    
    int recursosTotais[] = {4, 2, 3, 1};
    
    int alocacoes[3][4] = {
        {0, 0, 1, 0}, 
        {2, 0, 0, 1},  
        {0, 1, 2, 0} 
    };
    
    int requisicoes[3][4] = {
        {2, 0, 0, 1},  
        {1, 0, 1, 0},
        {2, 1, 0, 0}  
    };

    int recursosDisponiveis[4];
    
    int processosFinalizados[3] = {0, 0, 0};
    int quantidadeProcessosFinalizados = 0;
    
    for (int i = 0; i < 4; i++) {
        recursosDisponiveis[i] = recursosTotais[i];
        for (int j = 0; j < 3; j++) {
            recursosDisponiveis[i] -= alocacoes[j][i];
        }
    }

    while (quantidadeProcessosFinalizados < 3) {
        int processoExecutado = 0;

        for (int p = 0; p < 3; p++) {
            if (processosFinalizados[p] == 0) {
                int podeExecutar = 1;

                for (int r = 0; r < 4; r++) {
                    if (requisicoes[p][r] > recursosDisponiveis[r]) {
                        podeExecutar = 0;
                        break;
                    }
                }

                if (podeExecutar) {
                    for (int r = 0; r < 4; r++) {
                        recursosDisponiveis[r] += alocacoes[p][r];
                    }
                    processosFinalizados[p] = 1;
                    quantidadeProcessosFinalizados++;
                    processoExecutado = 1;
                }
            }
        }

        if (!processoExecutado) {
            printf("Deadlock detectado! Não é possível continuar a execução.\n");
            return 1;
        }
    }

    printf("Nenhum deadlock detectado. O sistema está em um estado seguro.\n");
    return 0;
}
