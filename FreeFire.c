#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Enum para escolher o tipo de ordenação
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} Criterio;

// Estrutura do item
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // 1 a 5
} Item;


// ------------------------------
// Função para exibir um item
// ------------------------------
void mostrarItem(Item i) {
    printf("\nNome: %s\n", i.nome);
    printf("Tipo: %s\n", i.tipo);
    printf("Quantidade: %d\n", i.quantidade);
    printf("Prioridade: %d\n", i.prioridade);
}


// ------------------------------
// Insertion Sort
// ------------------------------
int ordenar(Item v[], int n, Criterio criterio) {
    int comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Item atual = v[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;

            bool condicao = false;

            if (criterio == ORDENAR_NOME)
                condicao = strcmp(atual.nome, v[j].nome) < 0;
            else if (criterio == ORDENAR_TIPO)
                condicao = strcmp(atual.tipo, v[j].tipo) < 0;
            else if (criterio == ORDENAR_PRIORIDADE)
                condicao = atual.prioridade < v[j].prioridade;

            if (!condicao)
                break;

            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = atual;
    }

    return comparacoes;
}


// ------------------------------
// Verificar se está ordenado por nome
// ------------------------------
bool estaOrdenadoPorNome(Item v[], int n) {
    for (int i = 1; i < n; i++) {
        if (strcmp(v[i - 1].nome, v[i].nome) > 0)
            return false;
    }
    return true;
}


// ------------------------------
// Busca binária por nome
// ------------------------------
int buscaBinaria(Item v[], int n, char nome[]) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, v[meio].nome);

        if (cmp == 0)
            return meio;

        if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }

    return -1;
}


// ------------------------------
// PROGRAMA PRINCIPAL
// ------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n========= MOCHILA - NIVEL MESTRE =========\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar itens\n");
        printf("5. Busca binaria por nome\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: // Adicionar item
            if (total >= MAX_ITENS) {
                printf("Mochila cheia!\n");
            } else {
                printf("Nome: ");
                scanf("%s", mochila[total].nome);

                printf("Tipo: ");
                scanf("%s", mochila[total].tipo);

                printf("Quantidade: ");
                scanf("%d", &mochila[total].quantidade);

                do {
                    printf("Prioridade (1-5): ");
                    scanf("%d", &mochila[total].prioridade);
                } while (mochila[total].prioridade < 1 || mochila[total].prioridade > 5);

                total++;
                printf("Item adicionado!\n");
            }
            break;

        case 2: { // Remover
            char nomeRemover[50];
            int encontrado = 0;

            printf("Nome do item para remover: ");
            scanf("%s", nomeRemover);

            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                    encontrado = 1;
                    for (int j = i; j < total - 1; j++)
                        mochila[j] = mochila[j + 1];

                    total--;
                    printf("Item removido!\n");
                    break;
                }
            }

            if (!encontrado)
                printf("Item não encontrado.\n");

            break;
        }

        case 3: // Listar
            if (total == 0) {
                printf("Mochila vazia!\n");
            } else {
                printf("\n---------- ITENS ----------\n");
                for (int i = 0; i < total; i++) {
                    mostrarItem(mochila[i]);
                }
            }
            break;

        case 4: { // Ordenar
            int escolha;
            printf("\nOrdenar por:\n1. Nome\n2. Tipo\n3. Prioridade\nEscolha: ");
            scanf("%d", &escolha);

            int comparacoes = ordenar(mochila, total, escolha);
            printf("\nItens ordenados!\n");
            printf("Comparações realizadas: %d\n", comparacoes);
            break;
        }

        case 5: { // Busca binária
            if (!estaOrdenadoPorNome(mochila, total)) {
                printf("A mochila NÃO está ordenada por nome! Ordene antes.\n");
                break;
            }

            char nomeBusca[50];
            printf("Nome do item para buscar: ");
            scanf("%s", nomeBusca);

            int pos = buscaBinaria(mochila, total, nomeBusca);

            if (pos == -1)
                printf("Item não encontrado.\n");
            else {
                printf("\nItem encontrado:\n");
                mostrarItem(mochila[pos]);
            }

            break;
        }

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}