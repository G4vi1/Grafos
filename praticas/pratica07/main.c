#include "bellman_ford.h"
#include "grafo_lista.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    GrafoLista *g = criar_grafo(6);
    if (g == NULL) return EXIT_FAILURE;
    const int arestas[][3] = {
        {0, 1, 4}, {0, 2, 5}, {1, 2, -2},
        {1, 3, 6}, {2, 3, 3}, {3, 4, 2}
    };
    for (size_t i = 0; i < sizeof(arestas) / sizeof(arestas[0]); i++) {
        if (!inserir_aresta(g, arestas[i][0], arestas[i][1], arestas[i][2])) {
            liberar_grafo(g);
            return EXIT_FAILURE;
        }
    }

    puts("Grafo com peso negativo, sem ciclo negativo:");
    if (bellman_ford(g, 0) != 1) {
        liberar_grafo(g);
        return EXIT_FAILURE;
    }

    /* O ciclo 1 -> 2 -> 3 -> 4 -> 1 passa a ter custo -1. */
    if (!inserir_aresta(g, 4, 1, -4)) {
        liberar_grafo(g);
        return EXIT_FAILURE;
    }
    puts("\nGrafo com ciclo negativo alcancavel:");
    int resultado = bellman_ford(g, 0);
    liberar_grafo(g);
    return resultado == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
