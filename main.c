#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

int main () {
int Soma = 0; 
int NumTeste = 0;

FILE *Resposta = fopen("Resultado.txt", "w");

Estrada *T1 = getEstrada("Teste01.txt");

if (T1->T == 10) Soma++;
NumTeste++;

if (T1->N == 2) Soma++;
NumTeste++;

fprintf(Resposta, "\n\nATENÇÃO: Você acertou %d de %d itens. Logo, em 1.50 pontos, sua nota foi %.2f.\n", Soma, NumTeste, 2.0 * (float)Soma/(float)NumTeste);


}


