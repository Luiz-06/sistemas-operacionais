#include <stdio.h>

typedef struct {
    int recursosProcesso1[4];
    int recursosProcesso2[4];
    int recursosProcesso3[4];
} AlocacaoRequisicao;

int main() {
    int recursosTotais[] = {4, 2, 3, 1};
    int recursosDisponiveis[4];

    AlocacaoRequisicao alocacoes = {
        {0, 0, 1, 0},
        {2, 0, 0, 1}, 
        {0, 1, 2, 0}  
    };

    AlocacaoRequisicao requisicoes = {
        {2, 0, 0, 1},
        {1, 0, 1, 0}, 
        {2, 1, 0, 0}  
    };

    int processosFinalizados[3] = {0, 0, 0};
    int quantidadeProcessosFinalizados = 0;

    for (int i = 0; i < 4; i++) {
        recursosDisponiveis[i] = recursosTotais[i] - (alocacoes.recursosProcesso1[i] + alocacoes.recursosProcesso2[i] + alocacoes.recursosProcesso3[i]);
    }

    while (quantidadeProcessosFinalizados < 3) {
        int processoExecutado = 0;

        for (int p = 0; p < 3; p++) {
            if (processosFinalizados[p] == 0) {
                int podeExecutar = 1;

                for (int r = 0; r < 4; r++) {
                    if ((p == 0 && requisicoes.recursosProcesso1[r] > recursosDisponiveis[r]) ||
                        (p == 1 && requisicoes.recursosProcesso2[r] > recursosDisponiveis[r]) ||
                        (p == 2 && requisicoes.recursosProcesso3[r] > recursosDisponiveis[r])) {
                        podeExecutar = 0;
                        break;
                    }
                }

                if (podeExecutar) {
                    for (int r = 0; r < 4; r++) {
                        if (p == 0)
                            recursosDisponiveis[r] += alocacoes.recursosProcesso1[r];
                        if (p == 1)
                            recursosDisponiveis[r] += alocacoes.recursosProcesso2[r];
                        if (p == 2)
                            recursosDisponiveis[r] += alocacoes.recursosProcesso3[r];
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
