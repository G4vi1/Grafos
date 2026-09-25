#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

static void testar_grafo_matriz(void) {
    printf("========== GRAFO COM MATRIZ DE ADJACENCIA ==========\n");

    GrafoMatriz *g = criar_grafo_matriz(5);

    inserir_aresta_matriz(g, 0, 1);
    inserir_aresta_matriz(g, 0, 4);
    inserir_aresta_matriz(g, 1, 2);
    inserir_aresta_matriz(g, 1, 3);
    inserir_aresta_matriz(g, 3, 4);

    imprimir_grafo_matriz(g);

    printf("\nGrau do vertice 1: %d\n", grau_matriz(g, 1));
    printf("0 e 1 sao adjacentes? %s\n", sao_adjacentes_matriz(g, 0, 1) ? "sim" : "nao");
    printf("2 e 4 sao adjacentes? %s\n", sao_adjacentes_matriz(g, 2, 4) ? "sim" : "nao");

    remover_aresta_matriz(g, 0, 1);
    printf("\nApos remover aresta (0, 1):\n");
    imprimir_grafo_matriz(g);
    printf("Grau do vertice 0: %d\n", grau_matriz(g, 0));

    liberar_grafo_matriz(g);
    printf("\n");
}

static void testar_grafo_lista(void) {
    printf("========== GRAFO COM LISTA DE ADJACENCIA ==========\n");

    GrafoLista *g = criar_grafo_lista(5);

    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 0, 4);
    inserir_aresta_lista(g, 1, 2);
    inserir_aresta_lista(g, 1, 3);
    inserir_aresta_lista(g, 3, 4);

    imprimir_grafo_lista(g);

    printf("\nGrau do vertice 1: %d\n", grau_lista(g, 1));
    printf("0 e 1 sao adjacentes? %s\n", sao_adjacentes_lista(g, 0, 1) ? "sim" : "nao");
    printf("2 e 4 sao adjacentes? %s\n", sao_adjacentes_lista(g, 2, 4) ? "sim" : "nao");

    remover_aresta_lista(g, 0, 1);
    printf("\nApos remover aresta (0, 1):\n");
    imprimir_grafo_lista(g);
    printf("Grau do vertice 0: %d\n", grau_lista(g, 0));

    liberar_grafo_lista(g);
    printf("\n");
}

int main(void) {
    testar_grafo_matriz();
    testar_grafo_lista();
    return 0;
}