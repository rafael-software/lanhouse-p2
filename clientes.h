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

// Autor: Ytallo Naldi Marteli Nakayama
void cadastrarCliente() {
    int pos = totalClientes;

    if (pos >= 50) {
        printf("\n[ERRO] Limite de 50 clientes atingido!\n");
        return;
    }

    printf("\nNome: ");
    scanf(" %49[^\n]", listaClientes[pos].nome);
    printf("Apelido (nick): ");
    scanf(" %29[^\n]", listaClientes[pos].apelido);
    printf("Idade: ");
    scanf("%d", &listaClientes[pos].idade);
    printf("Saldo de credito (R$): ");
    scanf("%f", &listaClientes[pos].saldoCredito);

    if (listaClientes[pos].idade <= 0 || listaClientes[pos].saldoCredito < 0) {
        printf("\n[ERRO] Idade e saldo invalidos.\n");
        return;
    }

    listaClientes[pos].idCliente = pos + 1;
    listaClientes[pos].ativo = 1;
    totalClientes++;
    salvarClientesCSV();

    printf("\nCliente cadastrado! ID: %d\n", pos + 1);
}

// Autor: Ytallo Naldi Marteli Nakayama
void listarOuBuscarClientes() {
    char palavra[50];
    int i;
    int encontrou = 0;

    printf("\nParte do nome ou apelido (ou 'todos'): ");
    scanf(" %49[^\n]", palavra);

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1 &&
            (strcmp(palavra, "todos") == 0 ||
             strstr(listaClientes[i].nome, palavra) != NULL ||
             strstr(listaClientes[i].apelido, palavra) != NULL)) {
            printf("ID %d | %s (%s) | %d anos | R$ %.2f\n",
                   listaClientes[i].idCliente,
                   listaClientes[i].nome,
                   listaClientes[i].apelido,
                   listaClientes[i].idade,
                   listaClientes[i].saldoCredito);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum cliente encontrado.\n");
    }
}
#endif
