#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return NULL;
    }

    Estrada *est = (Estrada *) malloc(sizeof(Estrada));
    if (!est) {
        fclose(arq);
        return NULL;
    }

    if (fscanf(arq, "%d", &est->T) != 1 || fscanf(arq, "%d", &est->N) != 1) {
        fclose(arq);
        free(est);
        return NULL;
    }

    if (est->T < 3 || est->T > 1000000 || est->N < 2 || est->N > 10000) {
        fclose(arq);
        free(est);
        return NULL;
    }

    int *pos = (int*) malloc(est->N * sizeof(int));
    if (!pos) {
        fclose(arq);
        free(est);
        return NULL;
    }

    Cidade *inicio = NULL;
    Cidade *fim = NULL;
    int usados = 0;

    for (int i = 0; i < est->N; i++) {
        Cidade *nova = (Cidade *) malloc(sizeof(Cidade));
        if (!nova) {
            fclose(arq);
            free(pos);
            free(est);
            return NULL;
        }

        if (fscanf(arq, "%d %[^\n]", &nova->Posicao, nova->Nome) != 2) {
            fclose(arq);
            free(pos);
            free(est);
            free(nova);
            return NULL;
        }

        if (nova->Posicao <= 0 || nova->Posicao >= est->T) {
            fclose(arq);
            free(pos);
            free(est);
            free(nova);
            return NULL;
        }

        for (int j = 0; j < usados; j++) {
            if (pos[j] == nova->Posicao) {
                fclose(arq);
                free(pos);
                free(est);
                free(nova);
                return NULL;
            }
        }

        pos[usados++] = nova->Posicao;

        nova->Proximo = NULL;
        if (inicio == NULL)
            inicio = nova;
        else
            fim->Proximo = nova;
        fim = nova;
    }

    est->Inicio = inicio;

    fclose(arq);
    free(pos);

    printf("Tamanho da estrada: %d | Cidades: %d\n", est->T, est->N);
    for (Cidade *c = est->Inicio; c != NULL; c = c->Proximo) {
        printf("Cidade: %s\tPosição: %d\n", c->Nome, c->Posicao);
    }

    return est;
}

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

    // Ordena as cidades por posição
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
            idxMenor = i - 1; // guarda o índice da cidade
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