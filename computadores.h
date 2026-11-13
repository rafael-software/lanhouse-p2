#ifndef COMPUTADORES_H
#define COMPUTADORES_H

#include <stdio.h>
#include <string.h>

// computadores.h - Integrante B
// Autor: Daniel Eduardo Iaramenco Chagas (RGM: 46825622)

struct Computador {
    int idComputador;
    char nomeMaquina[20];
    char jogoPrincipal[40];
    float precoHora;
    int ativo;             // 1 = ativo, 0 = removido (manutencao)
};
struct Computador listaComputadores[50];
int totalComputadores = 0;

// Autor: Daniel Eduardo Iaramenco Chagas
void salvarComputadoresCSV() {
    FILE *arq;
    int i;

    arq = fopen("computadores.csv", "w");
    if (arq == NULL) {
        printf("Erro ao salvar computadores.csv\n");
        return;
    }
    for (i = 0; i < totalComputadores; i++) {
        fprintf(arq, "%d;%s;%s;%.2f;%d\n",
                listaComputadores[i].idComputador,
                listaComputadores[i].nomeMaquina,
                listaComputadores[i].jogoPrincipal,
                listaComputadores[i].precoHora,
                listaComputadores[i].ativo);
    }
    fclose(arq);
}

// Autor: Daniel Eduardo Iaramenco Chagas
void carregarComputadoresCSV() {
    FILE *arq;

    arq = fopen("computadores.csv", "r");
    if (arq == NULL) {
        return;
    }
    totalComputadores = 0;
    // fscanf devolve quantos campos leu (5 = linha completa)
    while (totalComputadores < 50 &&
           fscanf(arq, "%d;%19[^;];%39[^;];%f;%d\n",
                  &listaComputadores[totalComputadores].idComputador,
                  listaComputadores[totalComputadores].nomeMaquina,
                  listaComputadores[totalComputadores].jogoPrincipal,
                  &listaComputadores[totalComputadores].precoHora,
                  &listaComputadores[totalComputadores].ativo) == 5) {
        totalComputadores++;
    }
    fclose(arq);
}

#endif
