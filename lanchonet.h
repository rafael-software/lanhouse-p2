#ifndef LANCHONETE_H
#define LANCHONETE_H

#include <stdio.h>
#include <string.h>

// lanchonete.h - Integrante C
// Autor: Luiz Otavio Azevedo Rocha (RGM: 49939921)

struct Produto {
    int idProduto;
    char nomeProduto[40];
    float precoVenda;
    int quantidadeEstoque;
    int disponivel;        // 1 = no cardapio, 0 = removido
};
struct Produto estoqueLanchonete[50];
int totalProdutos = 0;

// Autor: Luiz Otavio Azevedo Rocha
void salvarProdutosCSV() {
    FILE *arq;
    int i;

    arq = fopen("produtos.csv", "w");
    if (arq == NULL) {
        printf("Erro ao salvar produtos.csv\n");
        return;
    }
    for (i = 0; i < totalProdutos; i++) {
        fprintf(arq, "%d;%s;%.2f;%d;%d\n",
                estoqueLanchonete[i].idProduto,
                estoqueLanchonete[i].nomeProduto,
                estoqueLanchonete[i].precoVenda,
                estoqueLanchonete[i].quantidadeEstoque,
                estoqueLanchonete[i].disponivel);
    }
    fclose(arq);
}

// Autor: Luiz Otavio Azevedo Rocha
void carregarProdutosCSV() {
    FILE *arq;

    arq = fopen("produtos.csv", "r");
    if (arq == NULL) {
        return;
    }
    totalProdutos = 0;
    // fscanf devolve quantos campos leu (5 = linha completa)
    while (totalProdutos < 50 &&
           fscanf(arq, "%d;%39[^;];%f;%d;%d\n",
                  &estoqueLanchonete[totalProdutos].idProduto,
                  estoqueLanchonete[totalProdutos].nomeProduto,
                  &estoqueLanchonete[totalProdutos].precoVenda,
                  &estoqueLanchonete[totalProdutos].quantidadeEstoque,
                  &estoqueLanchonete[totalProdutos].disponivel) == 5) {
        totalProdutos++;
    }
    fclose(arq);
}

#endif
