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
// Autor: Daniel Eduardo Iaramenco Chagas
void cadastrarComputador() {
    int pos = totalComputadores;

    if (pos >= 50) {
        printf("\n[ERRO] Limite de 50 computadores atingido!\n");
        return;
    }

    printf("\nNome da maquina (ex: PC-01): ");
    scanf(" %19[^\n]", listaComputadores[pos].nomeMaquina);
    printf("Jogo principal: ");
    scanf(" %39[^\n]", listaComputadores[pos].jogoPrincipal);
    printf("Preco da hora (R$): ");
    scanf("%f", &listaComputadores[pos].precoHora);

    if (listaComputadores[pos].precoHora <= 0) {
        printf("\n[ERRO] O preco deve ser maior que zero.\n");
        return;
    }

    listaComputadores[pos].idComputador = pos + 1;
    listaComputadores[pos].ativo = 1;
    totalComputadores++;
    salvarComputadoresCSV();

    printf("\nComputador cadastrado! ID: %d\n", pos + 1);
}

// Autor: Daniel Eduardo Iaramenco Chagas
void listarOuBuscarComputadores() {
    char palavra[40];
    int i;
    int encontrou = 0;

    printf("\nParte do nome da maquina ou do jogo (ou 'todos'): ");
    scanf(" %39[^\n]", palavra);

    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].ativo == 1 &&
            (strcmp(palavra, "todos") == 0 ||
             strstr(listaComputadores[i].nomeMaquina, palavra) != NULL ||
             strstr(listaComputadores[i].jogoPrincipal, palavra) != NULL)) {
            printf("ID %d | %s | %s | R$ %.2f/h\n",
                   listaComputadores[i].idComputador,
                   listaComputadores[i].nomeMaquina,
                   listaComputadores[i].jogoPrincipal,
                   listaComputadores[i].precoHora);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum computador encontrado.\n");
    }
}
// Autor: Daniel Eduardo Iaramenco Chagas
void editarComputador() {
    int id, i;
    int pos = -1;
    float novoPreco;

    printf("\nID do computador a editar: ");
    scanf("%d", &id);
    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].idComputador == id && listaComputadores[i].ativo == 1) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Computador nao encontrado.\n");
        return;
    }

    printf("Novo preco da hora (R$): ");
    scanf("%f", &novoPreco);
    if (novoPreco <= 0) {
        printf("[ERRO] O preco deve ser maior que zero.\n");
        return;
    }
    printf("Novo jogo principal: ");
    scanf(" %39[^\n]", listaComputadores[pos].jogoPrincipal);

    listaComputadores[pos].precoHora = novoPreco;
    salvarComputadoresCSV();
    printf("Computador atualizado!\n");
}

// Autor: Daniel Eduardo Iaramenco Chagas
void removerComputador() {
    int id, i;
    int pos = -1;

    printf("\nID do computador para manutencao: ");
    scanf("%d", &id);
    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].idComputador == id && listaComputadores[i].ativo == 1) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Computador nao encontrado.\n");
        return;
    }

    listaComputadores[pos].ativo = 0;
    salvarComputadoresCSV();
    printf("Computador removido!\n");
}

// Autor: Daniel Eduardo Iaramenco Chagas
void moduloComputadores() {
    int opcao;
    do {
        printf("\n--- [MODULO 2: COMPUTADORES E BAIAS (Integrante B)] ---\n");
        printf("1. Cadastrar Novo Computador\n");
        printf("2. Listar / Buscar Computadores\n");
        printf("3. Editar Preco e Jogo\n");
        printf("4. Remover Computador (manutencao)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarComputador();
                break;
            case 2:
                listarOuBuscarComputadores();
                break;
            case 3:
                editarComputador();
                break;
            case 4:
                removerComputador();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

#endif
