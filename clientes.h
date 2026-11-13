#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <string.h>

// clientes.h - Integrante A
// Autor: Ytallo Naldi Marteli Nakayama (RGM: 49282557)

struct Cliente {
    int idCliente;
    char nome[50];
    char apelido[30];
    int idade;
    float saldoCredito;
    int ativo;             // 1 = ativo, 0 = removido
};
struct Cliente listaClientes[50];
int totalClientes = 0;

// Autor: Ytallo Naldi Marteli Nakayama
void salvarClientesCSV() {
    FILE *arq;
    int i;

    arq = fopen("clientes.csv", "w");
    if (arq == NULL) {
        printf("Erro ao salvar clientes.csv\n");
        return;
    }
    for (i = 0; i < totalClientes; i++) {
        fprintf(arq, "%d;%s;%s;%d;%.2f;%d\n",
                listaClientes[i].idCliente,
                listaClientes[i].nome,
                listaClientes[i].apelido,
                listaClientes[i].idade,
                listaClientes[i].saldoCredito,
                listaClientes[i].ativo);
    }
    fclose(arq);
}

// Autor: Ytallo Naldi Marteli Nakayama
void carregarClientesCSV() {
    FILE *arq;

    arq = fopen("clientes.csv", "r");
    if (arq == NULL) {
        return;
    }
    totalClientes = 0;
    // fscanf devolve quantos campos leu (6 = linha completa)
    while (totalClientes < 50 &&
           fscanf(arq, "%d;%49[^;];%29[^;];%d;%f;%d\n",
                  &listaClientes[totalClientes].idCliente,
                  listaClientes[totalClientes].nome,
                  listaClientes[totalClientes].apelido,
                  &listaClientes[totalClientes].idade,
                  &listaClientes[totalClientes].saldoCredito,
                  &listaClientes[totalClientes].ativo) == 6) {
        totalClientes++;
    }
    fclose(arq);
}

#endif
