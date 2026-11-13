#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Projeto P2 - Lan House Anos 2000 (Baias e Consumo)
// Checkpoint 2

#include "clientes.h"
#include "computadores.h"
#include "lanchonete.h"
#include "sessoes.h"

// cls no Windows, clear nos outros
// Autor: Equipe (todos os integrantes)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Autor: Equipe (todos os integrantes)
int main() {
    int opcao;

    setlocale(LC_CTYPE, "Portuguese");

    carregarClientesCSV();
    carregarComputadoresCSV();
    carregarProdutosCSV();
    carregarSessoesCSV();

    do {
        limparTela();
        printf("======================================================\n");
        printf("   LAN HOUSE ANOS 2000 - CONTROLE DE BAIAS E CONSUMO  \n");
        printf("======================================================\n");
        printf("1. Modulo de Clientes (clientes.h)\n");
        printf("2. Modulo de Computadores (computadores.h)\n");
        printf("3. Modulo da Lanchonete (lanchonete.h)\n");
        printf("4. Modulo de Sessoes e Relatorios (sessoes.h)\n");
        printf("0. Salvar Tudo e Encerrar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                moduloClientes();
                break;
            case 2:
                moduloComputadores();
                break;
            case 3:
                moduloLanchonete();
                break;
            case 4:
                moduloSessoesRelatorios();
                break;
            case 0:
                salvarClientesCSV();
                salvarComputadoresCSV();
                salvarProdutosCSV();
                salvarSessoesCSV();
                printf("\nDados salvos. Ate logo!\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida! Digite de 0 a 4.\n");
        }
    } while (opcao != 0);

    return 0;
}
