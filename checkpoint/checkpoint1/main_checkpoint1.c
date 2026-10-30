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
                printf("\n[Em construcao] Rotina de Cadastro de Cliente...\n");
                printf("Campos previstos: ID, Nome, Apelido, Idade e Saldo de Credito.\n");
                break;
            case 2:
                printf("\n[Em construcao] Rotina de Busca e Listagem de Clientes...\n");
                break;
            case 3:
                printf("\n[Em construcao] Rotina de Edicao de Cliente por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Rotina de Remocao de Cliente...\n");
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
                printf("\n[Em construcao] Cadastrando PC (ID, Nome, Jogo, Preco da Hora)...\n");
                break;
            case 2:
                printf("\n[Em construcao] Listando baias livres e ocupadas...\n");
                break;
            case 3:
                printf("\n[Em construcao] Atualizando preco ou jogo do computador...\n");
                break;
            case 4:
                printf("\n[Em construcao] Retirando computador para manutencao...\n");
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
                printf("\n[Em construcao] Cadastrando produto (ID, Nome, Preco, Estoque)...\n");
                break;
            case 2:
                printf("\n[Em construcao] Listando produtos em estoque...\n");
                break;
            case 3:
                printf("\n[Em construcao] Editando preco ou quantidade...\n");
                break;
            case 4:
                printf("\n[Em construcao] Baixa de produto vencido ou esgotado...\n");
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
                printf("\n[Em construcao] Lancamento de nova sessao...\n");
                break;
            case 2:
                printf("\n[Em construcao] Listagem do historico...\n");
                break;
            case 3:
                printf("\n[Em construcao] Edicao de sessao...\n");
                break;
            case 4:
                printf("\n[Em construcao] Estorno de sessao...\n");
                break;
            case 5:
                printf("\n[Em construcao] Relatorio do computador mais usado...\n");
                break;
            case 6:
                printf("\n[Em construcao] Relatorio do cliente VIP...\n");
                break;
            case 7:
                printf("\n[Em construcao] Relatorio de sessoes por cliente...\n");
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
