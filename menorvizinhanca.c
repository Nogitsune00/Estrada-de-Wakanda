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

    
    double menor = (double)T; // começa com o valor grande

    double viz = (pos[1] - pos[0]) / 2.0 + pos[0]; 

    printf("Menor vizinhanca de estrada: %.2lf\n", viz);
    
    fclose(arq);

    
    
    return viz;
}
