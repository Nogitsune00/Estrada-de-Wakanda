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

    int T, N;
    if (fscanf(arq, "%d", &T) != 1 || fscanf(arq, "%d", &N) != 1) {
        fclose(arq);
        return NULL;
    }

    int *pos = malloc(N * sizeof(int));
    char (*nomes)[256] = malloc(N * sizeof(*nomes));
    if (!pos || !nomes) {
        fclose(arq);
        free(pos);
        free(nomes);
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        if (fscanf(arq, "%d", &pos[i]) != 1) {
            fclose(arq);
            free(pos);
            free(nomes);
            return NULL;
        }

        while (fgetc(arq) == ' ');

        fseek(arq, -1, SEEK_CUR);
        fgets(nomes[i], 256, arq);

        nomes[i][strcspn(nomes[i], "\r\n")] = 0;

        while (nomes[i][0] == ' ')
            memmove(nomes[i], nomes[i] + 1, strlen(nomes[i]));
    }
    fclose(arq);

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

    double menorViz = 1e9;
    int idxMenor = 0;

    for (int i = 0; i < N; i++) {
        double viz;
        if (i == 0)
            viz = (pos[i + 1] - 0) / 2.0;
        else if (i == N - 1)
            viz = (T - pos[i - 1]) / 2.0;
        else
            viz = (pos[i + 1] - pos[i - 1]) / 2.0;

        if (viz < menorViz) {
            menorViz = viz;
            idxMenor = i;
        }
    }

    char *resultado = malloc(strlen(nomes[idxMenor]) + 1);
    if (resultado)
        strcpy(resultado, nomes[idxMenor]);

    free(pos);
    free(nomes);
    return resultado;
}
