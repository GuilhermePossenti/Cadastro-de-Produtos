#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

struct Produto {
    int codigo;
    char nome[100];
    char categoria[50];
    int quantidadeEstoque;
    float precoUnitario;
    char fornecedor[100];
    char dataValidade[11]; // Formato: DD/MM/AAAA
    int ativo; // 1 para ativo, 0 para inativo/excluido
};

struct Produto listaProdutos[MAX_PRODUTOS];
int numProdutos = 0;

void cadastrarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    struct Produto novoProduto;
    novoProduto.codigo = numProdutos + 1; // Codigo gerado automaticamente
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
    
    printf("Digite a data de validade (DD/MM/AAAA) ou 'N/A' se nao aplicavel: ");
    scanf(" %[^\n]", novoProduto.dataValidade);
    
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
        if (listaProdutos[i].codigo == codigoBusca && listaProdutos[i].ativo) {
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
                    printf("Digite a nova data de validade (DD/MM/AAAA): ");
                    scanf(" %[^\n]", listaProdutos[i].dataValidade);
                    break;
                default:
                    printf("Opcao invalida.\n");
            }

            printf("Dados do produto alterados com sucesso!\n");
            return;
        }
    }

    printf("Produto nao encontrado ou ja excluido.\n");
}

void excluirProduto() {
    int codigoBusca;
    printf("Digite o codigo do produto a ser excluido: ");
    scanf("%d", &codigoBusca);

    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].codigo == codigoBusca && listaProdutos[i].ativo) {
            listaProdutos[i].ativo = 0; // Exclusao logica / inativacao
            printf("Produto inativado com sucesso!\n");
            return;
        }
    }

    printf("Produto nao encontrado ou ja excluido.\n");
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

    printf("Produto nao encontrado ou ja excluido.\n");
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

    printf("Produto nao encontrado ou ja excluido.\n");
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
    if (!encontrou) {
        printf("Nenhum produto encontrado nesta categoria.\n");
    }
}

void listarProdutos() {
    printf("Lista de produtos cadastrados:\n");
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].ativo) {
            printf("Codigo: %d, Nome: %s, Categoria: %s, Quantidade: %d, Preco: %.2f\n",
                   listaProdutos[i].codigo, listaProdutos[i].nome,
                   listaProdutos[i].categoria, listaProdutos[i].quantidadeEstoque,
                   listaProdutos[i].precoUnitario);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum produto cadastrado.\n");
    }
}

int main() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar novo produto\n");
        printf("2 - Editar dados de um produto\n");
        printf("3 - Inativar produto\n");
        printf("4 - Consultar produto por codigo\n");
        printf("5 - Consultar produto por nome\n");
        printf("6 - Consultar produto por categoria\n");
        printf("7 - Listar todos os produtos cadastrados\n");
        printf("8 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
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
                consultarProdutoPorCodigo();
                break;
            case 5:
                consultarProdutoPorNome();
                break;
            case 6:
                consultarProdutoPorCategoria();
                break;
            case 7:
                listarProdutos();
                break;
            case 8:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 8);

    return 0;
}


