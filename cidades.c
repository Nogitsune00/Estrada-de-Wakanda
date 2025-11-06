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
