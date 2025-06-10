#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_PRODUTOS 100

struct Produto {
    int codigo;
    char nome[100];
    char categoria[50];
    int quantidadeEstoque;
    float precoUnitario;
    char fornecedor[100];
    char dataValidade[11];
    int ativo;
    bool perecivel;
};

struct Produto listaProdutos[MAX_PRODUTOS];
int numProdutos = 0;
int proximoCodigo = 1; // Controla o próximo código a ser atribuído

int gerarNovoCodigo() {
    return proximoCodigo++;
}

void cadastrarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    struct Produto novoProduto;
    novoProduto.codigo = gerarNovoCodigo();
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", novoProduto.nome);

    printf("Digite a categoria do produto: ");
    scanf(" %[^\n]", novoProduto.categoria);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoProduto.quantidadeEstoque);

    do {
        printf("Digite o preco unitario: ");
        scanf("%f", &novoProduto.precoUnitario);
        if (novoProduto.precoUnitario < 0) {
            printf("O preco nao pode ser negativo. Tente novamente.\n");
        }
    } while (novoProduto.precoUnitario < 0);

    printf("Digite o fornecedor: ");
    scanf(" %[^\n]", novoProduto.fornecedor);

    char resposta[4];
    printf("O produto eh perecivel? (sim/nao): ");
    scanf(" %s", resposta);

    if (strcmp(resposta, "sim") == 0) {
        novoProduto.perecivel = true;
        printf("Digite a data de validade (DD/MM/AAAA): ");
        scanf(" %[^\n]", novoProduto.dataValidade);
    } else {
        novoProduto.perecivel = false;
        strcpy(novoProduto.dataValidade, "N/A");
    }

    novoProduto.ativo = 1; // Produto ativo por padrao

    listaProdutos[numProdutos] = novoProduto;
    numProdutos++;

    printf("Produto cadastrado com sucesso! Codigo: %d\n", novoProduto.codigo);
}

void editarProduto() {
    int codigoBusca;
    printf("Digite o codigo do produto a ser editado: ");
    scanf("%d", &codigoBusca);

    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].codigo == codigoBusca) {
            printf("Produto encontrado. O que voce deseja alterar?\n");
            printf("1. Nome\n");
            printf("2. Categoria\n");
            printf("3. Quantidade em estoque\n");
            printf("4. Preco unitario\n");
            printf("5. Fornecedor\n");
            printf("6. Data de validade\n");
            int opcao;
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf(" %[^\n]", listaProdutos[i].nome);
                    break;
                case 2:
                    printf("Digite a nova categoria: ");
                    scanf(" %[^\n]", listaProdutos[i].categoria);
                    break;
                case 3:
                    printf("Digite a nova quantidade em estoque: ");
                    scanf("%d", &listaProdutos[i].quantidadeEstoque);
                    break;
                case 4:
                    do {
                        printf("Digite o novo preco unitario: ");
                        scanf("%f", &listaProdutos[i].precoUnitario);
                        if (listaProdutos[i].precoUnitario < 0) {
                            printf("O preco nao pode ser negativo. Tente novamente.\n");
                        }
                    } while (listaProdutos[i].precoUnitario < 0);
                    break;
                case 5:
                    printf("Digite o novo fornecedor: ");
                    scanf(" %[^\n]", listaProdutos[i].fornecedor);
                    break;
                case 6:
                    if (listaProdutos[i].perecivel) {
                        printf("Digite a nova data de validade (DD/MM/AAAA): ");
                        scanf(" %[^\n]", listaProdutos[i].dataValidade);
                    } else {
                        printf("Este produto nao eh perecivel.\n");
                    }
                    break;
                default:
                    printf("Opcao invalida.\n");
            }

            printf("Dados do produto alterados com sucesso!\n");
            return;
        }
    }

    printf("Produto nao encontrado.\n");
}

void excluirProduto() {
    int codigoBusca;
    printf("Digite o codigo do produto a ser inativado: ");
    scanf("%d", &codigoBusca);

    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].codigo == codigoBusca && listaProdutos[i].ativo) {
            listaProdutos[i].ativo = 0; // Exclusao logica / inativacao
            printf("Produto inativado com sucesso!\n");
            return;
        }
    }

    printf("Produto ja inativo ou nao encontrado.\n");
}

void ativarProduto() {
    int codigoBusca;
    printf("Digite o codigo do produto a ser ativado: ");
    scanf("%d", &codigoBusca);

    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].codigo == codigoBusca && !listaProdutos[i].ativo) {
            listaProdutos[i].ativo = 1; // Ativa o produto
            printf("Produto ativado com sucesso!\n");
            return;
        }
    }

    printf("Produto ja ativo ou nao encontrado.\n");
}

void consultarProdutoPorCodigo() {
    int codigoBusca;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigoBusca);

    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].codigo == codigoBusca && listaProdutos[i].ativo) {
            printf("Codigo: %d\n", listaProdutos[i].codigo);
            printf("Nome: %s\n", listaProdutos[i].nome);
            printf("Categoria: %s\n", listaProdutos[i].categoria);
            printf("Quantidade em estoque: %d\n", listaProdutos[i].quantidadeEstoque);
            printf("Preco unitario: %.2f\n", listaProdutos[i].precoUnitario);
            printf("Fornecedor: %s\n", listaProdutos[i].fornecedor);
            printf("Data de validade: %s\n", listaProdutos[i].dataValidade);
            return;
        }
    }

    printf("Produto inativo ou nao encontrado.\n");
}

void consultarProdutoPorNome() {
    char nomeBusca[100];
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(listaProdutos[i].nome, nomeBusca) == 0 && listaProdutos[i].ativo) {
            printf("Codigo: %d\n", listaProdutos[i].codigo);
            printf("Nome: %s\n", listaProdutos[i].nome);
            printf("Categoria: %s\n", listaProdutos[i].categoria);
            printf("Quantidade em estoque: %d\n", listaProdutos[i].quantidadeEstoque);
            printf("Preco unitario: %.2f\n", listaProdutos[i].precoUnitario);
            printf("Fornecedor: %s\n", listaProdutos[i].fornecedor);
            printf("Data de validade: %s\n", listaProdutos[i].dataValidade);
            return;
        }
    }

    printf("Produto inativo ou nao encontrado.\n");
}

void consultarProdutoPorCategoria() {
    char categoriaBusca[50];
    printf("Digite a categoria do produto: ");
    scanf(" %[^\n]", categoriaBusca);

    printf("Produtos na categoria '%s':\n", categoriaBusca);
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(listaProdutos[i].categoria, categoriaBusca) == 0 && listaProdutos[i].ativo) {
            printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n",
                   listaProdutos[i].codigo, listaProdutos[i].nome,
                   listaProdutos[i].quantidadeEstoque, listaProdutos[i].precoUnitario);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto encontrado nesta categoria.\n");
    }
}

void consultarProdutoPorValidade() {
    char dataAtual[11];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dataAtual, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf("Produtos com validade ate %s:\n", dataAtual);
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].ativo && listaProdutos[i].perecivel) {
            if (strcmp(listaProdutos[i].dataValidade, dataAtual) <= 0) {
                printf("Codigo: %d, Nome: %s, Data de validade: %s\n",
                       listaProdutos[i].codigo, listaProdutos[i].nome,
                       listaProdutos[i].dataValidade);
                encontrou = 1;
            }
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto encontrado com validade ate a data atual.\n");
    }
}

void filtrarProdutosPorStatus() {
    int status;
    printf("Filtrar produtos:\n");
    printf("1 - Ativos\n");
    printf("2 - Inativos\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &status);

    if (status != 1 && status != 2) {
        printf("Opcao invalida.\n");
        return;
    }

    int encontrou = 0;
    printf("Produtos %s:\n", (status == 1) ? "ativos" : "inativos");
    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].ativo == (status == 1 ? 1 : 0)) {
            printf("Codigo: %d, Nome: %s, Categoria: %s, Quantidade: %d, Preco: %.2f, Data de validade: %s\n",
                listaProdutos[i].codigo, listaProdutos[i].nome, listaProdutos[i].categoria,
                listaProdutos[i].quantidadeEstoque, listaProdutos[i].precoUnitario,
                listaProdutos[i].dataValidade);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum produto %s encontrado.\n", (status == 1) ? "ativo" : "inativo");
    }
}

void listarProdutos() {
    printf("Lista de produtos cadastrados:\n");
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].ativo) {
            printf("Codigo: %d, Nome: %s, Categoria: %s, Quantidade: %d, Preco: %.2f, Data de validade: %s\n",
                   listaProdutos[i].codigo, listaProdutos[i].nome,
                   listaProdutos[i].categoria, listaProdutos[i].quantidadeEstoque,
                   listaProdutos[i].precoUnitario, listaProdutos[i].dataValidade);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto cadastrado.\n");
    }
}

int main() {
    int op;
    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar novo produto\n");
        printf("2 - Editar dados de um produto\n");
        printf("3 - Inativar produto\n");
        printf("4 - Ativar produto\n");
        printf("5 - Consultar produto por codigo\n");
        printf("6 - Consultar produto por nome\n");
        printf("7 - Consultar produto por categoria\n");
        printf("8 - Consultar produtos por validade\n");
        printf("9 - Filtrar produtos por ativo/inativo\n");
        printf("10 - Listar todos os produtos cadastrados\n");
        printf("11 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                editarProduto();
                break;
            case 3:
                excluirProduto();
                break;
            case 4:
                ativarProduto();
                break;
            case 5:
                consultarProdutoPorCodigo();
                break;
            case 6:
                consultarProdutoPorNome();
                break;
            case 7:
                consultarProdutoPorCategoria();
                break;
            case 8:
                consultarProdutoPorValidade();
                break;
            case 9:
                filtrarProdutosPorStatus();
                break;
            case 10:
                listarProdutos();
                break;
            case 11:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (op != 11);

    return 0;
}
