#include <stdio.h>
#include <string.h>

// ============================================================================
// PROJETO INTEGRADOR P2 - TEMA 3: LAN HOUSE ANOS 2000 (BAIAS E CONSUMO)
// Checkpoint 1: structs, menu principal e submenus de cada integrante
// ============================================================================


// ============================================================================
// PARTE 1: MODELAGEM DE DADOS (ESCOPO GLOBAL - 1 STRUCT POR INTEGRANTE)
// ============================================================================

// 1. Perspectiva do Integrante A: Clientes (gamers cadastrados)
struct Cliente {
    int idCliente;
    char nome[50];
    char apelido[30];      // nick usado nos jogos
    int idade;
    float saldoCredito;    // credito pre-pago em reais
    int ativo;             // 1 = Ativo, 0 = Removido
};
struct Cliente listaClientes[50];
int totalClientes = 0;

// 2. Perspectiva do Integrante B: Computadores / Baias
struct Computador {
    int idComputador;
    char nomeMaquina[20];  // ex: PC-01
    char jogoPrincipal[40];// ex: Counter-Strike 1.6
    float precoHora;
    int ocupado;           // 1 = Ocupado, 0 = Livre
};
struct Computador listaComputadores[50];
int totalComputadores = 0;

// 3. Perspectiva do Integrante C: Lanchonete (consumo)
struct Produto {
    int idProduto;
    char nomeProduto[40];  // ex: Refrigerante lata
    float precoVenda;
    int quantidadeEstoque;
    int disponivel;        // 1 = Disponivel, 0 = Esgotado
};
struct Produto estoqueLanchonete[50];
int totalProdutos = 0;

// 4. Perspectiva do Integrante D: Sessoes de Uso e Relatorios
struct Sessao {
    int idSessao;
    int idCliente;         // quem usou (liga com o Modulo A)
    int idComputador;      // qual PC usou (liga com o Modulo B)
    int minutosUsados;
    float valorTotal;
    char formaPagamento[20];
    int ativa;             // 1 = Valida, 0 = Estornada
};
struct Sessao historicoSessoes[50];
int totalSessoes = 0;
float precoPorHora = 5.00; // preco fixo por enquanto (depois vem do Modulo B)


// ============================================================================
// PARTE 2: FUNCOES DE INTERFACE E MODULOS DE CADA INTEGRANTE
// ============================================================================

// Funcao Visual Comum da Equipe
// Autor: Equipe (todos os integrantes)
void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("   LAN HOUSE ANOS 2000 - CONTROLE DE BAIAS E CONSUMO  \n");
    printf("======================================================\n");
}

// ----------------------------------------------------------------------------
// MODULO 1: PERSPECTIVA DE CLIENTES
// Autor: Ytallo Naldi Marteli Nakayama (RGM: 49282557)
// ----------------------------------------------------------------------------

// Autor: Ytallo Naldi Marteli Nakayama
void cadastrarCliente() {
    int pos;            // posicao onde o cliente vai ser guardado
    int idade;          // guarda a idade digitada
    float saldo;        // guarda o saldo digitado

    if (totalClientes >= 50) {                       // vetor cheio?
        printf("\n[ERRO] Limite de 50 clientes atingido!\n");
        return;                                      // sai da funcao
    }

    pos = totalClientes;                             // proxima posicao livre

    printf("\n--- CADASTRO DE CLIENTE ---\n");
    printf("Nome: ");
    scanf(" %49[^\n]", listaClientes[pos].nome);     // le o nome com espacos
    printf("Apelido (nick): ");
    scanf(" %29[^\n]", listaClientes[pos].apelido);  // le o apelido com espacos
    printf("Idade: ");
    scanf("%d", &idade);
    printf("Saldo de credito (R$): ");
    scanf("%f", &saldo);

    if (idade <= 0 || saldo < 0) {                   // dados invalidos
        printf("\n[ERRO] Idade deve ser maior que zero e saldo nao pode ser negativo.\n");
        return;                                      // nao cadastra
    }

    listaClientes[pos].idCliente = pos + 1;          // ID automatico: 1, 2, 3...
    listaClientes[pos].idade = idade;
    listaClientes[pos].saldoCredito = saldo;
    listaClientes[pos].ativo = 1;                    // 1 = cliente ativo
    totalClientes++;                                 // agora tem 1 cliente a mais

    printf("\nCliente cadastrado! ID: %d\n", listaClientes[pos].idCliente);
}

// Autor: Ytallo Naldi Marteli Nakayama
void imprimirCliente(int i) {
    printf("ID %d | %s (%s) | %d anos | Saldo: R$ %.2f\n",
           listaClientes[i].idCliente,
           listaClientes[i].nome,
           listaClientes[i].apelido,
           listaClientes[i].idade,
           listaClientes[i].saldoCredito);
}

// Autor: Ytallo Naldi Marteli Nakayama
void listarClientes() {
    int i;                  // contador do for
    int encontrou = 0;      // 0 = ainda nao achou ninguem

    printf("\n--- LISTA DE CLIENTES ---\n");
    for (i = 0; i < totalClientes; i++) {      // passa por todos os cadastrados
        if (listaClientes[i].ativo == 1) {     // ignora os removidos
            imprimirCliente(i);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum cliente cadastrado.\n");
    }
}

// Autor: Ytallo Naldi Marteli Nakayama
void buscarCliente() {
    int id;
    int i;
    int encontrou = 0;

    printf("\nDigite o ID do cliente: ");
    scanf("%d", &id);

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id && listaClientes[i].ativo == 1) {
            imprimirCliente(i);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Cliente nao encontrado.\n");
    }
}

// Autor: Ytallo Naldi Marteli Nakayama
void listarOuBuscarClientes() {
    int opcao;

    printf("\n1. Listar todos\n");
    printf("2. Buscar por ID\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            listarClientes();
            break;
        case 2:
            buscarCliente();
            break;
        default:
            printf("\n[ERRO] Opcao invalida!\n");
    }
}

// Autor: Ytallo Naldi Marteli Nakayama
void removerCliente() {
    int id;
    int i;
    int pos = -1;           // -1 = ainda nao achou o cliente
    int confirmar;

    printf("\nID do cliente a remover: ");
    scanf("%d", &id);

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id && listaClientes[i].ativo == 1) {
            pos = i;        // guarda onde o cliente esta
        }
    }

    if (pos == -1) {        // ninguem foi encontrado
        printf("Cliente nao encontrado.\n");
        return;
    }

    imprimirCliente(pos);                        // mostra quem sera removido
    printf("Confirma a remocao? (1-Sim  2-Nao): ");
    scanf("%d", &confirmar);

    if (confirmar == 1) {
        listaClientes[pos].ativo = 0;            // remocao logica
        printf("Cliente removido!\n");
    } else {
        printf("Remocao cancelada.\n");
    }
}

// Autor: Ytallo Naldi Marteli Nakayama
void editarCliente() {
    int id;
    int i;
    int pos = -1;           // -1 = ainda nao achou o cliente
    int opcao;
    int idade;
    float valor;

    printf("\nID do cliente a editar: ");
    scanf("%d", &id);

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id && listaClientes[i].ativo == 1) {
            pos = i;        // guarda onde o cliente esta
        }
    }

    if (pos == -1) {        // ninguem foi encontrado
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("1. Nome\n");
    printf("2. Apelido\n");
    printf("3. Idade\n");
    printf("4. Adicionar credito\n");
    printf("O que deseja editar? ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Novo nome: ");
            scanf(" %49[^\n]", listaClientes[pos].nome);
            printf("Nome atualizado!\n");
            break;
        case 2:
            printf("Novo apelido: ");
            scanf(" %29[^\n]", listaClientes[pos].apelido);
            printf("Apelido atualizado!\n");
            break;
        case 3:
            printf("Nova idade: ");
            scanf("%d", &idade);
            if (idade <= 0) {
                printf("[ERRO] Idade invalida.\n");
            } else {
                listaClientes[pos].idade = idade;
                printf("Idade atualizada!\n");
            }
            break;
        case 4:
            printf("Valor a adicionar (R$): ");
            scanf("%f", &valor);
            if (valor <= 0) {
                printf("[ERRO] O valor deve ser maior que zero.\n");
            } else {
                listaClientes[pos].saldoCredito = listaClientes[pos].saldoCredito + valor;
                printf("Novo saldo: R$ %.2f\n", listaClientes[pos].saldoCredito);
            }
            break;
        default:
            printf("[ERRO] Opcao invalida!\n");
    }
}

// Autor: Ytallo Naldi Marteli Nakayama
void moduloClientes() {
    int opcaoCliente;
    do {
        printf("\n--- [MODULO 1: GESTAO DE CLIENTES (Integrante A)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar / Buscar Clientes\n");
        printf("3. Editar Dados ou Credito de Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCliente);

        switch (opcaoCliente) {
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
                printf("\n[ERRO] Opcao invalida no Modulo de Clientes!\n");
        }
    } while (opcaoCliente != 0);
}

// ----------------------------------------------------------------------------
// MODULO 2: PERSPECTIVA DE COMPUTADORES / BAIAS
// Autor: Daniel Eduardo Iaramenco Chagas (RGM: 46825622)
// ----------------------------------------------------------------------------

// Autor: Daniel Eduardo Iaramenco Chagas
void cadastrarComputador() {
    int i, idDigitado, existe;
    float preco;

    if (totalComputadores >= 50) {                   // vetor cheio?
        printf("\n[ERRO] Limite de 50 computadores atingido!\n");
        return;
    }

    printf("\nID do computador: ");
    scanf("%d", &idDigitado);

    if (idDigitado <= 0) {                           // ID precisa ser positivo
        printf("[ERRO] O ID deve ser maior que zero.\n");
        return;
    }

    existe = 0;                                      // 0 = ID ainda nao existe
    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].idComputador == idDigitado) {
            existe = 1;
        }
    }
    if (existe == 1) {
        printf("[ERRO] Ja existe um computador com esse ID!\n");
        return;
    }

    printf("Nome da maquina (ex: PC-01): ");
    scanf(" %19[^\n]", listaComputadores[totalComputadores].nomeMaquina);
    printf("Jogo principal: ");
    scanf(" %39[^\n]", listaComputadores[totalComputadores].jogoPrincipal);
    printf("Preco da hora (R$): ");
    scanf("%f", &preco);

    if (preco <= 0) {                                // preco invalido
        printf("[ERRO] O preco deve ser maior que zero.\n");
        return;
    }

    listaComputadores[totalComputadores].idComputador = idDigitado;
    listaComputadores[totalComputadores].precoHora = preco;
    listaComputadores[totalComputadores].ocupado = 0;    // 0 = livre
    totalComputadores++;                                 // agora tem 1 PC a mais

    printf("\nComputador cadastrado com sucesso!\n");
}

// Autor: Daniel Eduardo Iaramenco Chagas
void imprimirComputador(int i) {
    printf("ID %d | %s | %s | R$ %.2f/h | ",
           listaComputadores[i].idComputador,
           listaComputadores[i].nomeMaquina,
           listaComputadores[i].jogoPrincipal,
           listaComputadores[i].precoHora);
    if (listaComputadores[i].ocupado == 1) {
        printf("Ocupado\n");
    } else {
        printf("Livre\n");
    }
}

// Autor: Daniel Eduardo Iaramenco Chagas
void listarComputadores() {
    int i;

    printf("\n--- LISTA DE COMPUTADORES ---\n");
    if (totalComputadores == 0) {
        printf("Nenhum computador cadastrado.\n");
        return;
    }
    for (i = 0; i < totalComputadores; i++) {
        imprimirComputador(i);
    }
}

// Autor: Daniel Eduardo Iaramenco Chagas
void buscarComputador() {
    int id, i;
    int encontrou = 0;

    printf("\nDigite o ID do computador: ");
    scanf("%d", &id);

    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].idComputador == id) {
            imprimirComputador(i);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Computador nao encontrado.\n");
    }
}

// Autor: Daniel Eduardo Iaramenco Chagas
void listarOuBuscarComputadores() {
    int opcao;

    printf("\n1. Listar todos\n");
    printf("2. Buscar por ID\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            listarComputadores();
            break;
        case 2:
            buscarComputador();
            break;
        default:
            printf("\n[ERRO] Opcao invalida!\n");
    }
}

// Autor: Daniel Eduardo Iaramenco Chagas
void editarComputador() {
    int id, i, opcao;
    int pos = -1;           // -1 = ainda nao achou o computador
    float novoPreco;

    printf("\nID do computador a editar: ");
    scanf("%d", &id);

    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].idComputador == id) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Computador nao encontrado.\n");
        return;
    }

    printf("1. Preco da hora\n");
    printf("2. Jogo instalado\n");
    printf("O que deseja alterar? ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Novo preco da hora (R$): ");
            scanf("%f", &novoPreco);
            if (novoPreco <= 0) {
                printf("[ERRO] O preco deve ser maior que zero.\n");
            } else {
                listaComputadores[pos].precoHora = novoPreco;
                printf("Preco atualizado!\n");
            }
            break;
        case 2:
            printf("Novo jogo: ");
            scanf(" %39[^\n]", listaComputadores[pos].jogoPrincipal);
            printf("Jogo atualizado!\n");
            break;
        default:
            printf("[ERRO] Opcao invalida!\n");
    }
}

// Autor: Daniel Eduardo Iaramenco Chagas
void removerComputador() {
    int id, i;
    int pos = -1;

    printf("\nID do computador para manutencao: ");
    scanf("%d", &id);

    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].idComputador == id) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Computador nao encontrado.\n");
        return;
    }
    if (listaComputadores[pos].ocupado == 1) {       // nao remove PC em uso
        printf("[ERRO] Computador ocupado, nao pode ser removido.\n");
        return;
    }

    for (i = pos; i < totalComputadores - 1; i++) {  // puxa os proximos uma posicao
        listaComputadores[i] = listaComputadores[i + 1];
    }
    totalComputadores--;                             // vetor ficou com 1 a menos

    printf("Computador removido para manutencao.\n");
}

// Autor: Daniel Eduardo Iaramenco Chagas
void moduloComputadores() {
    int opcaoComputador;
    do {
        printf("\n--- [MODULO 2: COMPUTADORES E BAIAS (Integrante B)] ---\n");
        printf("1. Cadastrar Novo Computador\n");
        printf("2. Listar Computadores / Buscar Baia\n");
        printf("3. Alterar Preco da Hora ou Jogo Instalado\n");
        printf("4. Remover Computador (manutencao)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoComputador);

        switch (opcaoComputador) {
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
                printf("\n[ERRO] Opcao invalida no Modulo de Computadores!\n");
        }
    } while (opcaoComputador != 0);
}

// ----------------------------------------------------------------------------
// MODULO 3: PERSPECTIVA DA LANCHONETE (CONSUMO)
// Autor: Luiz Otavio Azevedo Rocha (RGM: 49939921)
// ----------------------------------------------------------------------------

// Autor: Luiz Otavio Azevedo Rocha
void cadastrarProduto() {
    int i, idDigitado, existe;

    if (totalProdutos >= 50) {
        printf("\nLimite de 50 produtos atingido!\n");
        return;
    }

    printf("\nID do produto: ");
    scanf("%d", &idDigitado);

    existe = 0;
    for (i = 0; i < totalProdutos; i++) {
        if (estoqueLanchonete[i].idProduto == idDigitado) {
            existe = 1;
        }
    }
    if (existe == 1) {
        printf("Ja existe um produto com esse ID!\n");
        return;
    }

    estoqueLanchonete[totalProdutos].idProduto = idDigitado;

    printf("Nome do produto: ");
    scanf(" %39[^\n]", estoqueLanchonete[totalProdutos].nomeProduto);

    estoqueLanchonete[totalProdutos].precoVenda = 0;
    while (estoqueLanchonete[totalProdutos].precoVenda <= 0) {
        printf("Preco de venda (maior que 0): ");
        scanf("%f", &estoqueLanchonete[totalProdutos].precoVenda);
        if (estoqueLanchonete[totalProdutos].precoVenda <= 0) {
            printf("Preco invalido!\n");
        }
    }

    estoqueLanchonete[totalProdutos].quantidadeEstoque = -1;
    while (estoqueLanchonete[totalProdutos].quantidadeEstoque < 0) {
        printf("Quantidade em estoque (0 ou mais): ");
        scanf("%d", &estoqueLanchonete[totalProdutos].quantidadeEstoque);
        if (estoqueLanchonete[totalProdutos].quantidadeEstoque < 0) {
            printf("Quantidade invalida!\n");
        }
    }

    if (estoqueLanchonete[totalProdutos].quantidadeEstoque > 0) {
        estoqueLanchonete[totalProdutos].disponivel = 1;
    } else {
        estoqueLanchonete[totalProdutos].disponivel = 0;
    }

    totalProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

// Autor: Luiz Otavio Azevedo Rocha
void listarEstoque() {
    int i;

    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n===== ESTOQUE DA LANCHONETE =====\n");
    for (i = 0; i < totalProdutos; i++) {
        printf("ID: %d | %s | R$ %.2f | Qtd: %d | ",
               estoqueLanchonete[i].idProduto,
               estoqueLanchonete[i].nomeProduto,
               estoqueLanchonete[i].precoVenda,
               estoqueLanchonete[i].quantidadeEstoque);
        if (estoqueLanchonete[i].disponivel == 1) {
            printf("Disponivel\n");
        } else {
            printf("Esgotado\n");
        }
    }
}

// Autor: Luiz Otavio Azevedo Rocha
void editarProduto() {
    int i, idBusca, posicao, opcao;
    float novoPreco;
    int novaQtd;

    printf("\nID do produto a editar: ");
    scanf("%d", &idBusca);

    posicao = -1;
    for (i = 0; i < totalProdutos; i++) {
        if (estoqueLanchonete[i].idProduto == idBusca) {
            posicao = i;
        }
    }
    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("1 - Editar preco\n2 - Editar quantidade\nEscolha: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Novo preco: ");
            scanf("%f", &novoPreco);
            if (novoPreco > 0) {
                estoqueLanchonete[posicao].precoVenda = novoPreco;
                printf("Preco atualizado!\n");
            } else {
                printf("Preco invalido!\n");
            }
            break;
        case 2:
            printf("Nova quantidade: ");
            scanf("%d", &novaQtd);
            if (novaQtd >= 0) {
                estoqueLanchonete[posicao].quantidadeEstoque = novaQtd;
                if (novaQtd > 0) {
                    estoqueLanchonete[posicao].disponivel = 1;
                } else {
                    estoqueLanchonete[posicao].disponivel = 0;
                }
                printf("Quantidade atualizada!\n");
            } else {
                printf("Quantidade invalida!\n");
            }
            break;
        default:
            printf("Opcao invalida!\n");
    }
}

// Autor: Luiz Otavio Azevedo Rocha
void darBaixaProduto() {
    int i, idBusca, posicao, qtdBaixa;

    printf("\nID do produto para dar baixa: ");
    scanf("%d", &idBusca);

    posicao = -1;
    for (i = 0; i < totalProdutos; i++) {
        if (estoqueLanchonete[i].idProduto == idBusca) {
            posicao = i;
        }
    }
    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    if (estoqueLanchonete[posicao].disponivel == 0) {
        printf("Produto esgotado, nao ha o que dar baixa!\n");
        return;
    }

    printf("Quantidade a dar baixa: ");
    scanf("%d", &qtdBaixa);

    if (qtdBaixa <= 0) {
        printf("Quantidade invalida!\n");
    } else if (qtdBaixa > estoqueLanchonete[posicao].quantidadeEstoque) {
        printf("Estoque insuficiente! Disponivel: %d\n",
               estoqueLanchonete[posicao].quantidadeEstoque);
    } else {
        estoqueLanchonete[posicao].quantidadeEstoque -= qtdBaixa;
        if (estoqueLanchonete[posicao].quantidadeEstoque == 0) {
            estoqueLanchonete[posicao].disponivel = 0;
            printf("Baixa realizada. Produto agora ESGOTADO.\n");
        } else {
            printf("Baixa realizada com sucesso!\n");
        }
    }
}

// Autor: Luiz Otavio Azevedo Rocha
void moduloLanchonete() {
    int opcaoProduto;
    do {
        printf("\n--- [MODULO 3: LANCHONETE E ESTOQUE (Integrante C)] ---\n");
        printf("1. Cadastrar Novo Produto (salgadinho, refri...)\n");
        printf("2. Consultar Estoque da Lanchonete\n");
        printf("3. Atualizar Preco ou Quantidade\n");
        printf("4. Dar Baixa / Remover Produto\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoProduto);

        switch (opcaoProduto) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarEstoque();
                break;
            case 3:
                editarProduto();
                break;
            case 4:
                darBaixaProduto();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo da Lanchonete!\n");
        }
    } while (opcaoProduto != 0);
}

// ----------------------------------------------------------------------------
// MODULO 4: PERSPECTIVA DE SESSOES DE USO E RELATORIOS ANALITICOS
// Autor: Rafael Almeida Araujo (RGM: 884737167)
// ----------------------------------------------------------------------------

// Grava a forma de pagamento escolhida na sessao da posicao informada.
// Autor: Rafael Almeida Araujo
void definirPagamento(int posicao, int opcaoPagamento) {
    switch (opcaoPagamento) {
        case 1:
            strcpy(historicoSessoes[posicao].formaPagamento, "Dinheiro");
            break;
        case 2:
            strcpy(historicoSessoes[posicao].formaPagamento, "Pix");
            break;
        case 3:
            strcpy(historicoSessoes[posicao].formaPagamento, "Cartao");
            break;
        default:
            strcpy(historicoSessoes[posicao].formaPagamento, "Nao informado");
    }
}

// Opcao 1: registra uma nova sessao (cruza Cliente + Computador)
// Autor: Rafael Almeida Araujo
void registrarSessao() {
    int idCliente, idComputador, minutos, opcaoPagamento;

    // Valida o limite do vetor (so cabem 50 sessoes)
    if (totalSessoes >= 50) {
        printf("\n[ERRO] Limite de 50 sessoes atingido!\n");
        return;
    }

    printf("\nID do cliente: ");
    scanf("%d", &idCliente);
    printf("ID do computador: ");
    scanf("%d", &idComputador);
    printf("Minutos usados: ");
    scanf("%d", &minutos);

    // Nao aceita valores zerados ou negativos
    if (idCliente <= 0 || idComputador <= 0 || minutos <= 0) {
        printf("\n[ERRO] Todos os valores precisam ser maiores que zero.\n");
        return;
    }

    printf("Forma de pagamento (1-Dinheiro  2-Pix  3-Cartao): ");
    scanf("%d", &opcaoPagamento);

    // Preenche a proxima posicao livre do vetor
    historicoSessoes[totalSessoes].idSessao = totalSessoes + 1;
    historicoSessoes[totalSessoes].idCliente = idCliente;
    historicoSessoes[totalSessoes].idComputador = idComputador;
    historicoSessoes[totalSessoes].minutosUsados = minutos;
    historicoSessoes[totalSessoes].valorTotal = (minutos / 60.0) * precoPorHora;
    definirPagamento(totalSessoes, opcaoPagamento);
    historicoSessoes[totalSessoes].ativa = 1;

    printf("\nSessao %d registrada! Valor a pagar: R$ %.2f\n",
           historicoSessoes[totalSessoes].idSessao,
           historicoSessoes[totalSessoes].valorTotal);

    totalSessoes++; // agora o vetor tem uma sessao a mais
}

// Opcao 2: lista todas as sessoes validas
// Autor: Rafael Almeida Araujo
void listarSessoes() {
    int i;
    int encontrou = 0;

    printf("\n--- HISTORICO DE SESSOES ---\n");
    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].ativa == 1) {
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
        printf("Nenhuma sessao registrada.\n");
    }
}

// Opcao 3: edita os minutos e a forma de pagamento de uma sessao
// Autor: Rafael Almeida Araujo
void editarSessao() {
    int id, i, novosMinutos, opcaoPagamento;
    int posicao = -1; // -1 significa "ainda nao encontrei"

    printf("\nID da sessao a editar: ");
    scanf("%d", &id);

    // Procura a sessao no vetor
    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].idSessao == id && historicoSessoes[i].ativa == 1) {
            posicao = i;
        }
    }

    if (posicao == -1) {
        printf("\n[ERRO] Sessao nao encontrada.\n");
        return;
    }

    printf("Minutos atuais: %d. Novos minutos: ", historicoSessoes[posicao].minutosUsados);
    scanf("%d", &novosMinutos);
    if (novosMinutos <= 0) {
        printf("\n[ERRO] Os minutos precisam ser maiores que zero.\n");
        return;
    }
    printf("Nova forma de pagamento (1-Dinheiro  2-Pix  3-Cartao): ");
    scanf("%d", &opcaoPagamento);

    historicoSessoes[posicao].minutosUsados = novosMinutos;
    historicoSessoes[posicao].valorTotal = (novosMinutos / 60.0) * precoPorHora;
    definirPagamento(posicao, opcaoPagamento);

    printf("\nSessao %d atualizada! Novo valor: R$ %.2f\n",
           id, historicoSessoes[posicao].valorTotal);
}

// Opcao 4: estorna (cancela) uma sessao. Nao apaga do vetor, so marca ativa = 0
// Autor: Rafael Almeida Araujo
void removerSessao() {
    int id, i;
    int posicao = -1;

    printf("\nID da sessao a estornar: ");
    scanf("%d", &id);

    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].idSessao == id && historicoSessoes[i].ativa == 1) {
            posicao = i;
        }
    }

    if (posicao == -1) {
        printf("\n[ERRO] Sessao nao encontrada.\n");
        return;
    }

    historicoSessoes[posicao].ativa = 0;
    printf("\nSessao %d estornada com sucesso.\n", id);
}

// Opcao 5 [RELATORIO]: computador com mais minutos de uso
// Autor: Rafael Almeida Araujo
void relatorioComputadorMaisUsado() {
    int i, j, somaMinutos;
    int maiorSoma = 0;
    int pcMaisUsado = 0; // 0 = nenhum encontrado ainda

    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].ativa == 1) {
            // Soma todos os minutos do mesmo PC da sessao i
            somaMinutos = 0;
            for (j = 0; j < totalSessoes; j++) {
                if (historicoSessoes[j].ativa == 1 &&
                    historicoSessoes[j].idComputador == historicoSessoes[i].idComputador) {
                    somaMinutos = somaMinutos + historicoSessoes[j].minutosUsados;
                }
            }
            // Guarda o PC se ele bateu o recorde
            if (somaMinutos > maiorSoma) {
                maiorSoma = somaMinutos;
                pcMaisUsado = historicoSessoes[i].idComputador;
            }
        }
    }

    printf("\n--- RELATORIO: COMPUTADOR MAIS USADO ---\n");
    if (pcMaisUsado == 0) {
        printf("Nenhuma sessao registrada ainda.\n");
    } else {
        printf("PC %d, com %d minutos de uso (%.1f horas).\n",
               pcMaisUsado, maiorSoma, maiorSoma / 60.0);
    }
}

// Opcao 6 [RELATORIO]: cliente com mais sessoes (Cliente VIP)
// Autor: Rafael Almeida Araujo
void relatorioClienteVip() {
    int i, j, contador;
    int maiorContador = 0;
    int clienteVip = 0;
    float gasto;
    float gastoVip = 0;

    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].ativa == 1) {
            // Conta as sessoes e soma o gasto do mesmo cliente da sessao i
            contador = 0;
            gasto = 0;
            for (j = 0; j < totalSessoes; j++) {
                if (historicoSessoes[j].ativa == 1 &&
                    historicoSessoes[j].idCliente == historicoSessoes[i].idCliente) {
                    contador++;
                    gasto = gasto + historicoSessoes[j].valorTotal;
                }
            }
            if (contador > maiorContador) {
                maiorContador = contador;
                clienteVip = historicoSessoes[i].idCliente;
                gastoVip = gasto;
            }
        }
    }

    printf("\n--- RELATORIO: CLIENTE VIP ---\n");
    if (clienteVip == 0) {
        printf("Nenhuma sessao registrada ainda.\n");
    } else {
        printf("Cliente %d, com %d sessoes e R$ %.2f gastos.\n",
               clienteVip, maiorContador, gastoVip);
    }
}

// Opcao 7 [RELATORIO]: todas as sessoes de um cliente especifico
// Autor: Rafael Almeida Araujo
void relatorioSessoesPorCliente() {
    int id, i;
    int quantidade = 0;
    int totalMinutos = 0;
    float totalGasto = 0;

    printf("\nID do cliente: ");
    scanf("%d", &id);

    printf("\n--- RELATORIO: SESSOES DO CLIENTE %d ---\n", id);
    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].ativa == 1 && historicoSessoes[i].idCliente == id) {
            printf("Sessao %d | PC %d | %d min | R$ %.2f\n",
                   historicoSessoes[i].idSessao,
                   historicoSessoes[i].idComputador,
                   historicoSessoes[i].minutosUsados,
                   historicoSessoes[i].valorTotal);
            quantidade++;
            totalMinutos = totalMinutos + historicoSessoes[i].minutosUsados;
            totalGasto = totalGasto + historicoSessoes[i].valorTotal;
        }
    }

    if (quantidade == 0) {
        printf("Nenhuma sessao encontrada para esse cliente.\n");
    } else {
        printf("Total: %d sessoes, %d minutos, R$ %.2f\n",
               quantidade, totalMinutos, totalGasto);
    }
}

// Submenu do Modulo 4 (chamado pelo menu principal)
// Autor: Rafael Almeida Araujo
void moduloSessoesRelatorios() {
    int opcaoSessao;
    do {
        printf("\n--- [MODULO 4: SESSOES E RELATORIOS ANALITICOS (Integrante D)] ---\n");
        printf("1. Registrar Nova Sessao (Cruza Cliente + Computador)\n");
        printf("2. Listar Historico de Sessoes\n");
        printf("3. Editar Sessao\n");
        printf("4. Cancelar / Estornar Sessao\n");
        printf("5. [RELATORIO] Computador Mais Usado\n");
        printf("6. [RELATORIO] Cliente VIP (Maior Numero de Sessoes)\n");
        printf("7. [RELATORIO] Sessoes de um Cliente Especifico\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoSessao);

        switch (opcaoSessao) {
            case 1:
                registrarSessao();
                break;
            case 2:
                listarSessoes();
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
                relatorioSessoesPorCliente();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Sessoes!\n");
        }
    } while (opcaoSessao != 0);
}


// ============================================================================
// PARTE 3: FUNCAO PRINCIPAL (MAIN) - DESPACHANTE DE MENUS
// ============================================================================
// Autor: Equipe (todos os integrantes)
int main() {
    int opcaoPrincipal;

    do {
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA DO SISTEMA:\n");
        printf("1. Modulo de Clientes (Integrante A)\n");
        printf("2. Modulo de Computadores / Baias (Integrante B)\n");
        printf("3. Modulo da Lanchonete / Consumo (Integrante C)\n");
        printf("4. Modulo de Sessoes e Relatorios (Integrante D)\n");
        printf("0. Encerrar o Sistema\n");
        printf("------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
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
                printf("\nEncerrando o sistema da Lan House... Ate logo!\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida! Digite um numero de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
