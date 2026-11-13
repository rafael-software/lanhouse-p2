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

// Autor: Luiz Otavio Azevedo Rocha
void cadastrarProduto() {
    int pos = totalProdutos;

    if (pos >= 50) {
        printf("\n[ERRO] Limite de 50 produtos atingido!\n");
        return;
    }

    printf("\nNome do produto: ");
    scanf(" %39[^\n]", estoqueLanchonete[pos].nomeProduto);
    printf("Preco de venda (R$): ");
    scanf("%f", &estoqueLanchonete[pos].precoVenda);
    printf("Quantidade em estoque: ");
    scanf("%d", &estoqueLanchonete[pos].quantidadeEstoque);

    if (estoqueLanchonete[pos].precoVenda <= 0 || estoqueLanchonete[pos].quantidadeEstoque < 0) {
        printf("\n[ERRO] Preco ou quantidade invalidos.\n");
        return;
    }

    estoqueLanchonete[pos].idProduto = pos + 1;
    estoqueLanchonete[pos].disponivel = 1;
    totalProdutos++;
    salvarProdutosCSV();

    printf("\nProduto cadastrado! ID: %d\n", pos + 1);
}

// Autor: Luiz Otavio Azevedo Rocha
void listarOuBuscarProdutos() {
    char palavra[40];
    int i;
    int encontrou = 0;

    printf("\nParte do nome do produto (ou 'todos'): ");
    scanf(" %39[^\n]", palavra);

    for (i = 0; i < totalProdutos; i++) {
        if (estoqueLanchonete[i].disponivel == 1 &&
            (strcmp(palavra, "todos") == 0 ||
             strstr(estoqueLanchonete[i].nomeProduto, palavra) != NULL)) {
            printf("ID %d | %s | R$ %.2f | Qtd: %d\n",
                   estoqueLanchonete[i].idProduto,
                   estoqueLanchonete[i].nomeProduto,
                   estoqueLanchonete[i].precoVenda,
                   estoqueLanchonete[i].quantidadeEstoque);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto encontrado.\n");
    }
}

#endif
