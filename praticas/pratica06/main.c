#include "dijkstra.h"
#include "grafo_lista.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    GrafoLista *g = criar_grafo(6);
    if (g == NULL) return EXIT_FAILURE;
    const int arestas[][3] = {
        {0, 1, 10}, {0, 2, 3}, {2, 1, 1}, {1, 3, 2},
        {2, 3, 8}, {2, 4, 2}, {4, 3, 1}
    };
    for (size_t i = 0; i < sizeof(arestas) / sizeof(arestas[0]); i++) {
        if (!inserir_aresta(g, arestas[i][0], arestas[i][1], arestas[i][2])) {
            liberar_grafo(g);
            return EXIT_FAILURE;
        }
    }
    dijkstra(g, 0);
    liberar_grafo(g);
    return EXIT_SUCCESS;
}
