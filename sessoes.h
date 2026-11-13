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

// devolve a posicao do cliente no vetor, ou -1 se nao achar
// Autor: Rafael Almeida Araujo
int acharCliente(int id) {
    int i;
    int pos = -1;

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id) {
            pos = i;
        }
    }
    return pos;
}

// devolve a posicao do computador no vetor, ou -1 se nao achar
// Autor: Rafael Almeida Araujo
int acharComputador(int id) {
    int i;
    int pos = -1;

    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].idComputador == id) {
            pos = i;
        }
    }
    return pos;
}

// Autor: Rafael Almeida Araujo
void registrarSessao() {
    int pos = totalSessoes;
    int posC, posP;

    if (pos >= 50) {
        printf("\n[ERRO] Limite de 50 sessoes atingido!\n");
        return;
    }

    printf("\nID do cliente: ");
    scanf("%d", &historicoSessoes[pos].idCliente);
    printf("ID do computador: ");
    scanf("%d", &historicoSessoes[pos].idComputador);
    printf("Minutos usados: ");
    scanf("%d", &historicoSessoes[pos].minutosUsados);
    printf("Turno (1-Manha  2-Tarde  3-Noite): ");
    scanf("%d", &historicoSessoes[pos].turno);
    printf("Forma de pagamento (Dinheiro, Pix ou Cartao): ");
    scanf(" %19[^\n]", historicoSessoes[pos].formaPagamento);

    posC = acharCliente(historicoSessoes[pos].idCliente);
    posP = acharComputador(historicoSessoes[pos].idComputador);
    if (posC == -1 || posP == -1 ||
        listaClientes[posC].ativo == 0 || listaComputadores[posP].ativo == 0) {
        printf("\n[ERRO] Cliente ou computador invalido.\n");
        return;
    }
    if (historicoSessoes[pos].minutosUsados <= 0 ||
        historicoSessoes[pos].turno < 1 || historicoSessoes[pos].turno > 3) {
        printf("\n[ERRO] Minutos ou turno invalido.\n");
        return;
    }

    historicoSessoes[pos].idSessao = pos + 1;
    historicoSessoes[pos].valorTotal =
        (historicoSessoes[pos].minutosUsados / 60.0) * listaComputadores[posP].precoHora;
    historicoSessoes[pos].ativa = 1;
    totalSessoes++;
    salvarSessoesCSV();

    printf("\nSessao %d registrada! Valor: R$ %.2f\n", pos + 1, historicoSessoes[pos].valorTotal);
}

// Autor: Rafael Almeida Araujo
void listarOuBuscarSessoes() {
    char palavra[50];
    int i, posC, posP;
    int encontrou = 0;

    printf("\nParte do nome do cliente (ou 'todos'): ");
    scanf(" %49[^\n]", palavra);

    for (i = 0; i < totalSessoes; i++) {
        posC = acharCliente(historicoSessoes[i].idCliente);
        posP = acharComputador(historicoSessoes[i].idComputador);
        if (historicoSessoes[i].ativa == 1 && posC != -1 && posP != -1 &&
            (strcmp(palavra, "todos") == 0 ||
             strstr(listaClientes[posC].nome, palavra) != NULL)) {
            printf("Sessao %d | %s | %s | %d min | %s | R$ %.2f | %s\n",
                   historicoSessoes[i].idSessao,
                   listaClientes[posC].nome,
                   listaComputadores[posP].nomeMaquina,
                   historicoSessoes[i].minutosUsados,
                   nomeTurno[historicoSessoes[i].turno - 1],
                   historicoSessoes[i].valorTotal,
                   historicoSessoes[i].formaPagamento);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhuma sessao encontrada.\n");
    }
}

// Autor: Rafael Almeida Araujo
void editarSessao() {
    int id, i, minutos, posP;
    int pos = -1;

    printf("\nID da sessao a editar: ");
    scanf("%d", &id);
    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].idSessao == id && historicoSessoes[i].ativa == 1) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Sessao nao encontrada.\n");
        return;
    }

    printf("Novos minutos: ");
    scanf("%d", &minutos);
    posP = acharComputador(historicoSessoes[pos].idComputador);
    if (minutos <= 0 || posP == -1) {
        printf("[ERRO] Dados invalidos.\n");
        return;
    }

    historicoSessoes[pos].minutosUsados = minutos;
    historicoSessoes[pos].valorTotal = (minutos / 60.0) * listaComputadores[posP].precoHora;
    salvarSessoesCSV();
    printf("Sessao atualizada! Novo valor: R$ %.2f\n", historicoSessoes[pos].valorTotal);
}

// Autor: Rafael Almeida Araujo
void removerSessao() {
    int id, i;
    int pos = -1;

    printf("\nID da sessao a estornar: ");
    scanf("%d", &id);
    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].idSessao == id && historicoSessoes[i].ativa == 1) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Sessao nao encontrada.\n");
        return;
    }

    historicoSessoes[pos].ativa = 0;
    salvarSessoesCSV();
    printf("Sessao estornada!\n");
}

// Autor: Rafael Almeida Araujo
void relatorioComputadorMaisUsado() {
    int i, j, soma;
    int maior = 0;
    int pos = -1;

    for (i = 0; i < totalComputadores; i++) {
        soma = 0;
        for (j = 0; j < totalSessoes; j++) {
            if (historicoSessoes[j].ativa == 1 &&
                historicoSessoes[j].idComputador == listaComputadores[i].idComputador) {
                soma = soma + historicoSessoes[j].minutosUsados;
            }
        }
        if (soma > maior) {
            maior = soma;
            pos = i;
        }
    }

    printf("\n--- RELATORIO: COMPUTADOR MAIS USADO ---\n");
    if (pos == -1) {
        printf("Nenhuma sessao registrada.\n");
    } else {
        printf("%s (%s) - %d minutos (%.1f horas)\n",
               listaComputadores[pos].nomeMaquina,
               listaComputadores[pos].jogoPrincipal,
               maior, maior / 60.0);
    }
}

// Autor: Rafael Almeida Araujo
void relatorioClienteVip() {
    int i, j, contador;
    int maior = 0;
    int pos = -1;
    float gasto;
    float gastoVip = 0;

    for (i = 0; i < totalClientes; i++) {
        contador = 0;
        gasto = 0;
        for (j = 0; j < totalSessoes; j++) {
            if (historicoSessoes[j].ativa == 1 &&
                historicoSessoes[j].idCliente == listaClientes[i].idCliente) {
                contador++;
                gasto = gasto + historicoSessoes[j].valorTotal;
            }
        }
        if (contador > maior) {
            maior = contador;
            pos = i;
            gastoVip = gasto;
        }
    }

    printf("\n--- RELATORIO: CLIENTE VIP ---\n");
    if (pos == -1) {
        printf("Nenhuma sessao registrada.\n");
    } else {
        printf("%s (%s) - %d sessoes, R$ %.2f gastos\n",
               listaClientes[pos].nome, listaClientes[pos].apelido, maior, gastoVip);
    }
}

// matriz: linha = computador, coluna = turno, valor = minutos de uso
// Autor: Rafael Almeida Araujo
void relatorioMatrizUso() {
    int mapa[50][3] = {0};
    int totalTurno[3] = {0, 0, 0};
    int i, j, t;
    int maior = 0;
    int turnoMaior = 0;

    for (j = 0; j < totalSessoes; j++) {
        i = acharComputador(historicoSessoes[j].idComputador);
        t = historicoSessoes[j].turno - 1;
        if (historicoSessoes[j].ativa == 1 && i != -1) {
            mapa[i][t] = mapa[i][t] + historicoSessoes[j].minutosUsados;
            totalTurno[t] = totalTurno[t] + historicoSessoes[j].minutosUsados;
        }
    }

    printf("\n--- RELATORIO: MINUTOS DE USO POR PC E TURNO ---\n");
    printf("%-12s%-8s%-8s%-8s\n", "PC", nomeTurno[0], nomeTurno[1], nomeTurno[2]);
    for (i = 0; i < totalComputadores; i++) {
        printf("%-12s", listaComputadores[i].nomeMaquina);
        for (t = 0; t < 3; t++) {
            printf("%-8d", mapa[i][t]);
        }
        printf("\n");
    }

    for (t = 0; t < 3; t++) {
        if (totalTurno[t] > maior) {
            maior = totalTurno[t];
            turnoMaior = t;
        }
    }
    if (maior > 0) {
        printf("Turno mais movimentado: %s (%d minutos)\n", nomeTurno[turnoMaior], maior);
    }
}

// Autor: Rafael Almeida Araujo
void moduloSessoesRelatorios() {
    int opcao;
    do {
        printf("\n--- [MODULO 4: SESSOES E RELATORIOS (Integrante D)] ---\n");
        printf("1. Registrar Nova Sessao\n");
        printf("2. Listar / Buscar Sessoes\n");
        printf("3. Editar Sessao\n");
        printf("4. Estornar Sessao\n");
        printf("5. [RELATORIO] Computador Mais Usado\n");
        printf("6. [RELATORIO] Cliente VIP\n");
        printf("7. [RELATORIO] Uso por PC e Turno (matriz)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrarSessao();
                break;
            case 2:
                listarOuBuscarSessoes();
                break;
            case 3:
                editarSessao();
                break;
            case 4:
                removerSessao();
                break;
            case 5:
                relatorioComputadorMaisUsado();
                break;
            case 6:
                relatorioClienteVip();
                break;
            case 7:
                relatorioMatrizUso();
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
