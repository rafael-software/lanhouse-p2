# Lan House Anos 2000 — Controle de Baias e Consumo

Projeto Integrador (P2) — Algoritmos e Pensamento Computacional
Universidade Positivo — Engenharia de Software

Sistema de terminal em linguagem C para gerenciar uma Lan House dos anos 2000: clientes, computadores (baias), lanchonete e sessões de uso.

## Equipe

| Integrante | Módulo | Nome e RGM |
| --- | --- | --- |
| A | Clientes | Ytallo Naldi Marteli Nakayama — RGM 49282557 |
| B | Computadores / Baias | Daniel Eduardo Iaramenco Chagas — RGM 46825622 |
| C | Lanchonete / Consumo | Luiz Otavio Azevedo Rocha — RGM 49939921 |
| D | Sessões de Uso e Relatórios | Rafael Almeida Araujo — RGM 884737167 |

## Como funciona

Todo o sistema está em um único arquivo, `main.c`. Os dados ficam na memória RAM, em vetores de `struct` com 50 posições. Não há gravação em arquivo nesta etapa.

O menu principal roda em um `do-while` com `switch-case`. Cada opção abre o submenu de um integrante. Em todos os submenus, a opção `0` volta ao menu principal sem fechar o programa.

```
MENU PRINCIPAL
├── 1. Módulo de Clientes (Integrante A)
├── 2. Módulo de Computadores / Baias (Integrante B)
├── 3. Módulo da Lanchonete / Consumo (Integrante C)
├── 4. Módulo de Sessões e Relatórios (Integrante D)
└── 0. Encerrar o Sistema
```

## Estruturas de dados (structs)

| Módulo | Struct | Vetor | Campos |
| --- | --- | --- | --- |
| A | `Cliente` | `listaClientes[50]` | idCliente, nome, apelido, idade, saldoCredito, ativo |
| B | `Computador` | `listaComputadores[50]` | idComputador, nomeMaquina, jogoPrincipal, precoHora, ocupado |
| C | `Produto` | `estoqueLanchonete[50]` | idProduto, nomeProduto, precoVenda, quantidadeEstoque, disponivel |
| D | `Sessao` | `historicoSessoes[50]` | idSessao, idCliente, idComputador, minutosUsados, valorTotal, formaPagamento, ativa |

A `Sessao` liga os outros módulos: `idCliente` aponta para um cliente (módulo A) e `idComputador` para um computador (módulo B).

## Módulo D — Sessões e Relatórios

| Opção | O que faz |
| --- | --- |
| 1 | Registra uma nova sessão (cliente, computador, minutos e forma de pagamento) |
| 2 | Lista o histórico de sessões válidas |
| 3 | Edita os minutos e a forma de pagamento de uma sessão |
| 4 | Estorna uma sessão (marca como inativa, sem apagar do vetor) |
| 5 | Relatório: computador mais usado |
| 6 | Relatório: cliente VIP (maior número de sessões) |
| 7 | Relatório: todas as sessões de um cliente |

O valor da sessão é calculado por `(minutos / 60) * preço da hora`. O preço da hora é fixo em R$ 5,00 por enquanto; depois virá do módulo B.

## Status do Checkpoint 1

- [x] Repositório no GitHub
- [x] Structs globais por integrante, com vetores `[50]`
- [x] Menu principal em loop (`do-while` + `switch-case`)
- [x] Submenus com Cadastrar, Listar/Buscar, Editar e Remover
- [x] Funções `void` separadas, com `// Autor:` identificando cada parte
- [x] Módulo D completo e funcionando
- [x] Módulo A (Clientes): cadastrar, listar/buscar e editar prontos
- [ ] Módulo A: remover cliente em andamento
- [ ] Módulo B (Computadores): submenu pronto, rotinas em construção
- [ ] Módulo C (Lanchonete): submenu pronto, rotinas em construção

## Como compilar e executar

No Dev-C++: abra o `main.c` e aperte `F11`.

No terminal, com o GCC:

```
gcc main.c -o lanhouse
./lanhouse
```

No Windows, o executável é `lanhouse.exe`.

Digite apenas números nos menus.

## Regras do grupo

- Cada integrante edita somente as funções do próprio módulo.
- Antes de alterar uma `struct`, avisar o grupo.
- Baixar o `main.c` mais recente do GitHub antes de editar e compilar antes de cada commit.
- Fazer um commit por função, com título curto (menos de 50 caracteres).
- Usar apenas o conteúdo visto em aula.
