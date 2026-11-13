#include <stdio.h>

// Projeto P2 - Lan House Anos 2000 (Baias e Consumo)
// Checkpoint 1: structs, menu principal e submenus

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

struct Computador {
    int idComputador;
    char nomeMaquina[20];
    char jogoPrincipal[40];
    float precoHora;
    int ativo;             // 1 = ativo, 0 = removido (manutencao)
};
struct Computador listaComputadores[50];
int totalComputadores = 0;

struct Produto {
    int idProduto;
    char nomeProduto[40];
    float precoVenda;
    int quantidadeEstoque;
    int disponivel;        // 1 = no cardapio, 0 = removido
};
struct Produto estoqueLanchonete[50];
int totalProdutos = 0;

struct Sessao {
    int idSessao;
    int idCliente;         // liga com o Modulo A
    int idComputador;      // liga com o Modulo B
    int minutosUsados;
    float valorTotal;
    char formaPagamento[20];
    int ativa;             // 1 = valida, 0 = estornada
};
struct Sessao historicoSessoes[50];
int totalSessoes = 0;
float precoPorHora = 5.00;   // preco fixo por enquanto


// ---- Modulo 1: Clientes ----
// Autor: Ytallo Naldi Marteli Nakayama (RGM: 49282557)

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

    printf("\nCliente cadastrado! ID: %d\n", pos + 1);
}

// Autor: Ytallo Naldi Marteli Nakayama
void listarOuBuscarClientes() {
    int id, i;
    int encontrou = 0;

    printf("\nID (cliente) - 0 para listar todos: ");
    scanf("%d", &id);

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1 && (id == 0 || listaClientes[i].idCliente == id)) {
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

// Autor: Ytallo Naldi Marteli Nakayama
void editarCliente() {
    int id, i;
    int pos = -1;
    float credito;

    printf("\nID do cliente a editar: ");
    scanf("%d", &id);
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id && listaClientes[i].ativo == 1) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Credito a adicionar (R$, 0 para nenhum): ");
    scanf("%f", &credito);
    if (credito < 0) {
        printf("[ERRO] Credito invalido.\n");
        return;
    }
    printf("Novo apelido: ");
    scanf(" %29[^\n]", listaClientes[pos].apelido);

    listaClientes[pos].saldoCredito = listaClientes[pos].saldoCredito + credito;
    printf("Cliente atualizado! Saldo: R$ %.2f\n", listaClientes[pos].saldoCredito);
}

// Autor: Ytallo Naldi Marteli Nakayama
void removerCliente() {
    int id, i;
    int pos = -1;

    printf("\nID do cliente a remover: ");
    scanf("%d", &id);
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id && listaClientes[i].ativo == 1) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    listaClientes[pos].ativo = 0;
    printf("Cliente removido!\n");
}

// Autor: Ytallo Naldi Marteli Nakayama
void moduloClientes() {
    int opcao;
    do {
        printf("\n--- [MODULO 1: GESTAO DE CLIENTES (Integrante A)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar / Buscar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarOuBuscarClientes();
                break;
            case 3:
                editarCliente();
                break;
            case 4:
                removerCliente();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);
}


// ---- Modulo 2: Computadores ----
// Autor: Daniel Eduardo Iaramenco Chagas (RGM: 46825622)

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

    printf("\nComputador cadastrado! ID: %d\n", pos + 1);
}

// Autor: Daniel Eduardo Iaramenco Chagas
void listarOuBuscarComputadores() {
    int id, i;
    int encontrou = 0;

    printf("\nID (computador) - 0 para listar todos: ");
    scanf("%d", &id);

    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].ativo == 1 && (id == 0 || listaComputadores[i].idComputador == id)) {
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


// ---- Modulo 3: Lanchonete ----
// Autor: Luiz Otavio Azevedo Rocha (RGM: 49939921)

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

    printf("\nProduto cadastrado! ID: %d\n", pos + 1);
}

// Autor: Luiz Otavio Azevedo Rocha
void listarOuBuscarProdutos() {
    int id, i;
    int encontrou = 0;

    printf("\nID (produto) - 0 para listar todos: ");
    scanf("%d", &id);

    for (i = 0; i < totalProdutos; i++) {
        if (estoqueLanchonete[i].disponivel == 1 && (id == 0 || estoqueLanchonete[i].idProduto == id)) {
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

// Autor: Luiz Otavio Azevedo Rocha
void editarProduto() {
    int id, i, novaQtd;
    int pos = -1;
    float novoPreco;

    printf("\nID do produto a editar: ");
    scanf("%d", &id);
    for (i = 0; i < totalProdutos; i++) {
        if (estoqueLanchonete[i].idProduto == id && estoqueLanchonete[i].disponivel == 1) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Novo preco (R$): ");
    scanf("%f", &novoPreco);
    printf("Nova quantidade: ");
    scanf("%d", &novaQtd);
    if (novoPreco <= 0 || novaQtd < 0) {
        printf("[ERRO] Preco ou quantidade invalidos.\n");
        return;
    }

    estoqueLanchonete[pos].precoVenda = novoPreco;
    estoqueLanchonete[pos].quantidadeEstoque = novaQtd;
    printf("Produto atualizado!\n");
}

// Autor: Luiz Otavio Azevedo Rocha
void removerProduto() {
    int id, i;
    int pos = -1;

    printf("\nID do produto a remover: ");
    scanf("%d", &id);
    for (i = 0; i < totalProdutos; i++) {
        if (estoqueLanchonete[i].idProduto == id && estoqueLanchonete[i].disponivel == 1) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    estoqueLanchonete[pos].disponivel = 0;
    printf("Produto removido!\n");
}

// Autor: Luiz Otavio Azevedo Rocha
void moduloLanchonete() {
    int opcao;
    do {
        printf("\n--- [MODULO 3: LANCHONETE E ESTOQUE (Integrante C)] ---\n");
        printf("1. Cadastrar Novo Produto\n");
        printf("2. Listar / Buscar Estoque\n");
        printf("3. Editar Preco e Quantidade\n");
        printf("4. Remover Produto\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarOuBuscarProdutos();
                break;
            case 3:
                editarProduto();
                break;
            case 4:
                removerProduto();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);
}


// ---- Modulo 4: Sessoes e Relatorios ----
// Autor: Rafael Almeida Araujo (RGM: 884737167)

// Autor: Rafael Almeida Araujo
void registrarSessao() {
    int pos = totalSessoes;

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
    printf("Forma de pagamento (Dinheiro, Pix ou Cartao): ");
    scanf(" %19[^\n]", historicoSessoes[pos].formaPagamento);

    if (historicoSessoes[pos].idCliente <= 0 || historicoSessoes[pos].idComputador <= 0 ||
        historicoSessoes[pos].minutosUsados <= 0) {
        printf("\n[ERRO] IDs e minutos precisam ser maiores que zero.\n");
        return;
    }

    historicoSessoes[pos].idSessao = pos + 1;
    historicoSessoes[pos].valorTotal = (historicoSessoes[pos].minutosUsados / 60.0) * precoPorHora;
    historicoSessoes[pos].ativa = 1;
    totalSessoes++;

    printf("\nSessao %d registrada! Valor: R$ %.2f\n", pos + 1, historicoSessoes[pos].valorTotal);
}

// Autor: Rafael Almeida Araujo
void listarOuBuscarSessoes() {
    int id, i;
    int encontrou = 0;

    printf("\nID (sessao) - 0 para listar todos: ");
    scanf("%d", &id);

    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].ativa == 1 && (id == 0 || historicoSessoes[i].idSessao == id)) {
            printf("Sessao %d | Cliente %d | PC %d | %d min | R$ %.2f | %s\n",
                   historicoSessoes[i].idSessao,
                   historicoSessoes[i].idCliente,
                   historicoSessoes[i].idComputador,
                   historicoSessoes[i].minutosUsados,
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
    int id, i, minutos;
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
    if (minutos <= 0) {
        printf("[ERRO] Os minutos precisam ser maiores que zero.\n");
        return;
    }

    historicoSessoes[pos].minutosUsados = minutos;
    historicoSessoes[pos].valorTotal = (minutos / 60.0) * precoPorHora;
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
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);
}


// Autor: Equipe (todos os integrantes)
int main() {
    int opcao;

    do {
        printf("\n======================================================\n");
        printf("   LAN HOUSE ANOS 2000 - CONTROLE DE BAIAS E CONSUMO  \n");
        printf("======================================================\n");
        printf("1. Modulo de Clientes (Integrante A)\n");
        printf("2. Modulo de Computadores (Integrante B)\n");
        printf("3. Modulo da Lanchonete (Integrante C)\n");
        printf("4. Modulo de Sessoes e Relatorios (Integrante D)\n");
        printf("0. Encerrar\n");
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
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida! Digite de 0 a 4.\n");
        }
    } while (opcao != 0);

    return 0;
}
