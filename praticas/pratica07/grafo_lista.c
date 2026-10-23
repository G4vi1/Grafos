#include "grafo_lista.h"
#include <stdlib.h>

GrafoLista *criar_grafo(int num_vertices) {
    if (num_vertices <= 0 || num_vertices > MAX_VERTICES) return NULL;
    GrafoLista *g = malloc(sizeof(*g));
    if (g == NULL) return NULL;
    g->lista = calloc((size_t)num_vertices, sizeof(*g->lista));
    if (g->lista == NULL) {
        free(g);
        return NULL;
    }
    g->num_vertices = num_vertices;
    return g;
}

int inserir_aresta(GrafoLista *g, int origem, int destino, int peso) {
    if (g == NULL || origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices) return 0;
    No *no = malloc(sizeof(*no));
    if (no == NULL) return 0;
    *no = (No){destino, peso, g->lista[origem]};
    g->lista[origem] = no;
    return 1;
}

void liberar_grafo(GrafoLista *g) {
    if (g == NULL) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *no = g->lista[i];
        while (no != NULL) {
            No *proximo = no->proximo;
            free(no);
            no = proximo;
        }
    }
    free(g->lista);
    free(g);
}
