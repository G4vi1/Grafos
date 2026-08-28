#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

/* Grafo não direcionado: a matriz é mantida simétrica
   (adj[u][v] == adj[v][u]). */

static int vertice_valido(GrafoMatriz *g, int v) {
    return g != NULL && v >= 0 && v < g->n;
}

GrafoMatriz *criar_grafo_matriz(int n) {
    if (n <= 0) return NULL;

    GrafoMatriz *g = malloc(sizeof(GrafoMatriz));
    if (!g) return NULL;

    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    if (!g->adj) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        g->adj[i] = calloc(n, sizeof(int)); // inicia tudo em 0 (sem arestas)
        if (!g->adj[i]) {
            for (int k = 0; k < i; k++) free(g->adj[k]);
            free(g->adj);
            free(g);
            return NULL;
        }
    }

    return g;
}

void inserir_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return;
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

void remover_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return;
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

int grau_matriz(GrafoMatriz *g, int v) {
    if (!vertice_valido(g, v)) return -1;

    int grau = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->adj[v][i]) grau++;
    }
    return grau;
}

int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return 0;
    return g->adj[u][v];
}

void liberar_grafo_matriz(GrafoMatriz *g) {
    if (!g) return;

    for (int i = 0; i < g->n; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);
}

void imprimir_grafo_matriz(GrafoMatriz *g) {
    if (!g) return;

    printf("Matriz de adjacencia (%d vertices):\n", g->n);
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}