#include "grafo_lista.h"
#include <stdlib.h>

GrafoListaPonderado *criar_grafo(int num_vertices) {
    if (num_vertices <= 0) return NULL;
    GrafoListaPonderado *g = malloc(sizeof(*g));
    if (g == NULL) return NULL;
    g->lista = calloc((size_t)num_vertices, sizeof(*g->lista));
    if (g->lista == NULL) {
        free(g);
        return NULL;
    }
    g->num_vertices = num_vertices;
    return g;
}

int inserir_aresta(GrafoListaPonderado *g, int origem, int destino, int peso) {
    if (g == NULL || origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices || peso < 0) return 0;
    Aresta *aresta = malloc(sizeof(*aresta));
    if (aresta == NULL) return 0;
    *aresta = (Aresta){destino, peso, g->lista[origem]};
    g->lista[origem] = aresta;
    return 1;
}

void liberar_grafo(GrafoListaPonderado *g) {
    if (g == NULL) return;
    for (int i = 0; i < g->num_vertices; i++) {
        Aresta *aresta = g->lista[i];
        while (aresta != NULL) {
            Aresta *proximo = aresta->proximo;
            free(aresta);
            aresta = proximo;
        }
    }
    free(g->lista);
    free(g);
}

