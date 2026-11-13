#ifndef SESSOES_H
#define SESSOES_H

#include <stdio.h>
#include <string.h>
#include "clientes.h"
#include "computadores.h"

// sessoes.h - Integrante D
// Autor: Rafael Almeida Araujo (RGM: 884737167)

struct Sessao {
    int idSessao;
    int idCliente;         // liga com clientes.h
    int idComputador;      // liga com computadores.h
    int minutosUsados;
    int turno;             // 1 = Manha, 2 = Tarde, 3 = Noite
    float valorTotal;
    char formaPagamento[20];
    int ativa;             // 1 = valida, 0 = estornada
};
struct Sessao historicoSessoes[50];
int totalSessoes = 0;
char nomeTurno[3][10] = {"Manha", "Tarde", "Noite"};

// Autor: Rafael Almeida Araujo
void salvarSessoesCSV() {
    FILE *arq;
    int i;

    arq = fopen("sessoes.csv", "w");
    if (arq == NULL) {
        printf("Erro ao salvar sessoes.csv\n");
        return;
    }
    for (i = 0; i < totalSessoes; i++) {
        fprintf(arq, "%d;%d;%d;%d;%d;%.2f;%s;%d\n",
                historicoSessoes[i].idSessao,
                historicoSessoes[i].idCliente,
                historicoSessoes[i].idComputador,
                historicoSessoes[i].minutosUsados,
                historicoSessoes[i].turno,
                historicoSessoes[i].valorTotal,
                historicoSessoes[i].formaPagamento,
                historicoSessoes[i].ativa);
    }
    fclose(arq);
}

// Autor: Rafael Almeida Araujo
void carregarSessoesCSV() {
    FILE *arq;

    arq = fopen("sessoes.csv", "r");
    if (arq == NULL) {
        return;
    }
    totalSessoes = 0;
    // fscanf devolve quantos campos leu (8 = linha completa)
    while (totalSessoes < 50 &&
           fscanf(arq, "%d;%d;%d;%d;%d;%f;%19[^;];%d\n",
                  &historicoSessoes[totalSessoes].idSessao,
                  &historicoSessoes[totalSessoes].idCliente,
                  &historicoSessoes[totalSessoes].idComputador,
                  &historicoSessoes[totalSessoes].minutosUsados,
                  &historicoSessoes[totalSessoes].turno,
                  &historicoSessoes[totalSessoes].valorTotal,
                  historicoSessoes[totalSessoes].formaPagamento,
                  &historicoSessoes[totalSessoes].ativa) == 8) {
        totalSessoes++;
    }
    fclose(arq);
}

#endif
