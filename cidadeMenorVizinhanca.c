#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("ERRO ao abrir o arquivo\n");
        return NULL;
    }

    int T, N; // T = comprimento total; N = número de cidades
    fscanf(arq, "%d", &T);
    fscanf(arq, "%d", &N);

    int *pos = (int*) malloc(N * sizeof(int));
    char (*nomes)[256] = malloc(N * sizeof(*nomes)); // guarda o nome de cada cidade
    if (!pos || !nomes) {
        fclose(arq);
        free(pos);
        free(nomes);
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        fscanf(arq, "%d %[^\n]", &pos[i], nomes[i]);
        while (nomes[i][0] == ' ') // remove espaço inicial, se houver
            memmove(nomes[i], nomes[i] + 1, strlen(nomes[i]));
    }

    // Ordena as cidades por posição (mesmo código da sua amiga)
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (pos[j] < pos[i]) {
                int temp = pos[i];
                pos[i] = pos[j];
                pos[j] = temp;

                char tempNome[256];
                strcpy(tempNome, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], tempNome);
            }
        }
    }

    // Mantém a estrutura do código dela, só com cálculo ajustado
    double menorViz = 999999.0;
    double vizinhoAnterior = 0.0;
    int idxMenor = 0;

    for (int i = 1; i <= N; i++) {
        double vizinhanca = 0.0;
        double dif = 0.0;

        if (i < N) {
            vizinhanca = pos[i-1] + ((pos[i] - pos[(i - 1)]) / 2.0);
            dif = vizinhanca - vizinhoAnterior;
        } else {
            vizinhanca = (T - vizinhoAnterior) / 1.0;
            dif = T - vizinhoAnterior;
        }

        if (dif < menorViz) {
            menorViz = dif;
            idxMenor = i - 1; // 👈 guarda o índice da cidade
        }

        vizinhoAnterior = vizinhanca;
    }

    fclose(arq);

    // Cria a string pra retornar o nome da cidade
    char *resultado = malloc(strlen(nomes[idxMenor]) + 1);
    if (resultado != NULL)
        strcpy(resultado, nomes[idxMenor]);

    free(pos);
    free(nomes);

    return resultado;
}