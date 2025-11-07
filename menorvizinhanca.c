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
    
    
    double menor=9999999;
    for (int i = 0; i < N; i++) {
        fscanf(arq, "%d %[^\n]", &pos[i], &nome);
       
        if(pos[i]<menor){
            menor=pos[i];
        }
        
       

    }
    printf("Menor vizinhanca de estrada: %.2lf", menor);
    
    fclose(arq);

    
    
    return menor;
}
