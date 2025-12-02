#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura do item
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== MOCHILA - NIVEL NOVATO =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            if (total >= MAX_ITENS) {
                printf("Mochila cheia!\n");
            } else {
                printf("Nome do item: ");
                scanf("%s", mochila[total].nome);

                printf("Tipo do item: ");
                scanf("%s", mochila[total].tipo);

                printf("Quantidade: ");
                scanf("%d", &mochila[total].quantidade);

                total++;
                printf("Item adicionado!\n");
            }
            break;

        case 2: {
            char nomeRemover[50];
            int encontrado = 0;

            printf("Digite o nome do item a remover: ");
            scanf("%s", nomeRemover);

            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                    encontrado = 1;

                    // Sobrescreve movendo todos uma posição para trás
                    for (int j = i; j < total - 1; j++) {
                        mochila[j] = mochila[j + 1];
                    }

                    total--;
                    printf("Item removido!\n");
                    break;
                }
            }

            if (!encontrado)
                printf("Item nao encontrado.\n");
            break;
        }

        case 3:
            if (total == 0) {
                printf("Mochila vazia!\n");
            } else {
                printf("\n--- Itens na mochila ---\n");
                for (int i = 0; i < total; i++) {
                    printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                           mochila[i].nome,
                           mochila[i].tipo,
                           mochila[i].quantidade);
                }
            }
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}