#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"




double calcularMenorVizinhanca(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq==NULL){
        printf("ERRO ao abrir o arquivo\n");
        return 0;
    }

    int T, N; // T=comprimento total; N=numero de cidades
   
    fscanf(arq, "%d", &T);
    fscanf(arq, "%d", &N);

    int *pos = (int*) malloc(N * sizeof(int));
    char nome[256];
    
    for (int i = 0; i < N; i++) {
        fscanf(arq, "%d %[^\n]", &pos[i], &nome);
    }

     for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (pos[j] < pos[i]) {
                int temp = pos[i];
                pos[i] = pos[j];
                pos[j] = temp;
            }
        }
    }


    double menorViz = 999999.0;
    double vizinhoAnterior = 0.0;

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
        }
        vizinhoAnterior = vizinhanca;
    }

    
    printf("Menor vizinhanca de estrada: %.2lf\n", menorViz);
    
    fclose(arq);
    
    return menorViz;
}
