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
int proximoCodigo = 1;

int gerarNovoCodigo() {
    return proximoCodigo++;
}

int buscarProdutoPorCodigo(int codigoBusca) {
    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].codigo == codigoBusca && listaProdutos[i].ativo != -1) {
            return i;
        }
    }
    return -1;
}

int buscarProdutoPorNome(const char nomeBusca[100]) {
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(listaProdutos[i].nome, nomeBusca) == 0 && listaProdutos[i].ativo != -1) {
            return i;
        }
    }
    return -1;
}

int cadastrarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return -1;
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

    getchar(); 

    printf("Digite o fornecedor: ");
    scanf(" %[^\n]", novoProduto.fornecedor); 

    char resposta[4];
    printf("O produto e perecivel? sim/nao: ");
    scanf("%3s", resposta);
    getchar();

    if (strcmp(resposta, "sim") == 0) {
        novoProduto.perecivel = true;
        printf("Digite a data de validade DD/MM/AAAA: ");
        scanf(" %[^\n]", novoProduto.dataValidade); 
    } else {
        novoProduto.perecivel = false;
        strcpy(novoProduto.dataValidade, "N/A");
    }

    novoProduto.ativo = 1;
    listaProdutos[numProdutos++] = novoProduto;

    printf("Produto cadastrado com sucesso! Codigo: %d\n", novoProduto.codigo);
    return novoProduto.codigo;
}

int consultarProdutoPorFornecedor() {
    char fornecedorBusca[100];
    printf("Digite o nome do fornecedor: ");
    scanf(" %[^\n]", fornecedorBusca); 

    printf("Produtos do fornecedor '%s':\n", fornecedorBusca);
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        char statusTexto[15]; 
        if (listaProdutos[i].ativo == 1) {
            strcpy(statusTexto, "Ativo");
        } else {
            strcpy(statusTexto, "Inativo");
        }
        printf("Codigo: %d, Nome: %s, Categoria: %s, Quantidade: %d, Preco: %.2f, Validade: %s, Status: %s, Fornecedor: %s\n",
            listaProdutos[i].codigo, listaProdutos[i].nome, listaProdutos[i].categoria,
            listaProdutos[i].quantidadeEstoque, listaProdutos[i].precoUnitario,
            listaProdutos[i].dataValidade, statusTexto, listaProdutos[i].fornecedor);
        encontrou++;
    }
    if (encontrou == 0) {
        printf("Nenhum produto encontrado para esse fornecedor.\n");
    }
    return encontrou;
}

int editarProduto() {
    int codigoBusca;
    printf("Digite o codigo do produto a ser editado: ");
    scanf("%d", &codigoBusca);
    getchar();

    int idx = buscarProdutoPorCodigo(codigoBusca);
    if (idx == -1) {
        printf("Produto nao encontrado ou excluido.\n");
        return 0;
    }

    printf("Produto encontrado. O que voce deseja alterar?\n");
    printf("1. Nome\n2. Categoria\n3. Quantidade em estoque\n4. Preco unitario\n5. Fornecedor\n6. Data de validade\n");
    int opcao;
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("Digite o novo nome: ");
            scanf(" %[^\n]", listaProdutos[idx].nome);
            break;
        case 2:
            printf("Digite a nova categoria: ");
            scanf(" %[^\n]", listaProdutos[idx].categoria);
            break;
        case 3:
            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &listaProdutos[idx].quantidadeEstoque);
            break;
        case 4:
            do {
                printf("Digite o novo preco unitario: ");
                scanf("%f", &listaProdutos[idx].precoUnitario);
                if (listaProdutos[idx].precoUnitario < 0) {
                    printf("O preco nao pode ser negativo. Tente novamente.\n");
                }
            } while (listaProdutos[idx].precoUnitario < 0);
            break;
        case 5:
            printf("Digite o novo fornecedor: ");
            scanf(" %[^\n]", listaProdutos[idx].fornecedor); 
            break;
        case 6:
            if (listaProdutos[idx].perecivel) {
                printf("Digite a nova data de validade (DD/MM/AAAA): ");
                scanf(" %[^\n]", listaProdutos[idx].dataValidade); 
            } else {
                printf("Este produto nao eh perecivel.\n");
                return -1;
            }
            break;
        default:
            printf("Opcao invalida.\n");
            return -1;
    }

    printf("Dados do produto alterados com sucesso!\n");
    return 1;
}

int excluirProduto() {
    int codigoBusca;
    printf("Digite o codigo do produto a ser inativado: ");
    scanf("%d", &codigoBusca);
    getchar();

    int idx = buscarProdutoPorCodigo(codigoBusca);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return 0;
    }

    if (listaProdutos[idx].ativo == 1) {
        listaProdutos[idx].ativo = 0;
        printf("Produto inativado com sucesso!\n");
        return 1;
    } else if (listaProdutos[idx].ativo == 0) {
        printf("Produto ja esta inativo.\n");
        return 0;
    } else {
        printf("Produto excluido, nao pode ser inativado.\n");
        return -1;
    }
}

int ativarProduto() {
    int codigoBusca;
    printf("Digite o codigo do produto a ser ativado: ");
    scanf("%d", &codigoBusca);
    getchar();

    int idx = buscarProdutoPorCodigo(codigoBusca);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return 0;
    }

    if (listaProdutos[idx].ativo == 0) {
        listaProdutos[idx].ativo = 1;
        printf("Produto ativado com sucesso!\n");
        return 1;
    } else if (listaProdutos[idx].ativo == 1) {
        printf("Produto ja esta ativo.\n");
        return 0;
    } else {
        printf("Produto excluido, nao pode ser ativado.\n");
        return -1;
    }
}

int excluirProdutoDefinitivamente() {
    int codigoBusca;
    printf("Digite o codigo do produto para exclusao definitiva: ");
    scanf("%d", &codigoBusca);
    getchar();

    int idx = buscarProdutoPorCodigo(codigoBusca);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return 0;
    }

    if (listaProdutos[idx].ativo == -1) {
        printf("Produto ja foi excluido definitivamente.\n");
        return -1;
    }

    listaProdutos[idx].ativo = -1;
    printf("Produto excluido definitivamente (codigo preservado)!\n");
    return 1;
}

int consultarProdutoPorCodigo() {
    int codigoBusca;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigoBusca);
    getchar();

    int idx = buscarProdutoPorCodigo(codigoBusca);
    if (idx == -1) {
        printf("Produto nao encontrado ou excluido.\n");
        return 0;
    }

    struct Produto prod = listaProdutos[idx];
    printf("Codigo: %d\nNome: %s\nCategoria: %s\nQuantidade em estoque: %d\nPreco unitario: %.2f\nFornecedor: %s\nData de validade: %s\nStatus: %s\n",
           prod.codigo, prod.nome, prod.categoria, 
           prod.quantidadeEstoque, prod.precoUnitario, 
           prod.fornecedor, prod.dataValidade,
           prod.ativo == 1 ? "Ativo" : "Inativo");
    return 1;
}

int consultarProdutoPorNome() {
    char nomeBusca[100];
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", nomeBusca); 

    int idx = buscarProdutoPorNome(nomeBusca);
    if (idx == -1) {
        printf("Produto nao encontrado ou excluido.\n");
        return 0;
    }

    struct Produto prod = listaProdutos[idx];
    printf("Codigo: %d\nNome: %s\nCategoria: %s\nQuantidade em estoque: %d\nPreco unitario: %.2f\nFornecedor: %s\nData de validade: %s\nStatus: %s\n",
           prod.codigo, prod.nome, prod.categoria, 
           prod.quantidadeEstoque, prod.precoUnitario, 
           prod.fornecedor, prod.dataValidade,
           prod.ativo == 1 ? "Ativo" : "Inativo");
    return 1;
}

int consultarProdutoPorCategoria() {
    char categoriaBusca[50];
    printf("Digite a categoria do produto: ");
    scanf(" %[^\n]", categoriaBusca); 

    printf("Produtos na categoria '%s':\n", categoriaBusca);
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(listaProdutos[i].categoria, categoriaBusca) == 0 && listaProdutos[i].ativo != -1) {
            printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f, Fornecedor: %s, Status: %s\n",
                   listaProdutos[i].codigo, listaProdutos[i].nome,
                   listaProdutos[i].quantidadeEstoque, listaProdutos[i].precoUnitario,
                   listaProdutos[i].fornecedor, listaProdutos[i].ativo == 1 ? "Ativo" : "Inativo");
            encontrou++;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto encontrado nesta categoria.\n");
    }
    return encontrou;
}

int filtrarProdutosPorStatus() {
    int status;
    printf("Filtrar produtos:\n");
    printf("1 - Ativos\n2 - Inativos\n3 - Excluidos\nEscolha uma opcao: ");
    scanf("%d", &status);
    getchar();

    if (status < 1 || status > 3) {
        printf("Opcao invalida.\n");
        return 0;
    }

    char statusTexto[15]; 
    if (status == 1) {
        strcpy(statusTexto, "ativos");
    } else if (status == 2) {
        strcpy(statusTexto, "inativos");
    } else {
        strcpy(statusTexto, "excluidos");
    }
    printf("Produtos %s:\n", statusTexto);

    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (listaProdutos[i].ativo == (status == 1 ? 1 : (status == 2 ? 0 : -1))) {
            printf("Codigo: %d, Nome: %s, Categoria: %s, Quantidade: %d, Preco: %.2f, Data de validade: %s, Fornecedor: %s\n",
                   listaProdutos[i].codigo, listaProdutos[i].nome, listaProdutos[i].categoria,
                   listaProdutos[i].quantidadeEstoque, listaProdutos[i].precoUnitario,
                   listaProdutos[i].dataValidade, listaProdutos[i].fornecedor);
            encontrou++;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto %s encontrado.\n", statusTexto);
    }
    return encontrou;
}

int listarProdutos() {
    printf("Lista completa de produtos cadastrados (Ativos, Inativos e Excluidos):\n");
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        char statusTexto[15]; 
        if (listaProdutos[i].ativo == 1) strcpy(statusTexto, "Ativo");
        else if (listaProdutos[i].ativo == 0) strcpy(statusTexto, "Inativo");
        else if (listaProdutos[i].ativo == -1) strcpy(statusTexto, "Excluido");

        printf("Codigo: %d, Nome: %s, Categoria: %s, Quantidade: %d, Preco: %.2f, Data de validade: %s, Status: %s, Fornecedor: %s\n",
               listaProdutos[i].codigo, listaProdutos[i].nome, listaProdutos[i].categoria,
               listaProdutos[i].quantidadeEstoque, listaProdutos[i].precoUnitario,
               listaProdutos[i].dataValidade, statusTexto, listaProdutos[i].fornecedor);
        encontrou++;
    }
    if (encontrou == 0)
        printf("Nenhum produto cadastrado.\n");
    return encontrou;
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
        printf("8 - Consultar produto por fornecedor\n");
        printf("9 - Filtrar produtos por ativo/inativo/excluido\n");
        printf("10 - Listar todos os produtos cadastrados\n");
        printf("11 - Excluir produto definitivamente\n");
        printf("12 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);
        getchar();

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
                consultarProdutoPorFornecedor();
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
    } while (op != 12);

    return 0;
}

