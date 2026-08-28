#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

/* Grafo não direcionado: cada aresta {u, v} aparece uma vez
   na lista de u e uma vez na lista de v. */

static int vertice_valido(GrafoLista *g, int v) {
    return g != NULL && v >= 0 && v < g->n;
}

static void inserir_no(No **cabeca, int destino) {
    No *novo = malloc(sizeof(No));
    if (!novo) return;
    novo->destino = destino;
    novo->prox = *cabeca;
    *cabeca = novo;
}

static void remover_no(No **cabeca, int destino) {
    No *atual = *cabeca;
    No *anterior = NULL;

    while (atual != NULL) {
        if (atual->destino == destino) {
            if (anterior == NULL) {
                *cabeca = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

GrafoLista *criar_grafo_lista(int n) {
    if (n <= 0) return NULL;

    GrafoLista *g = malloc(sizeof(GrafoLista));
    if (!g) return NULL;

    g->n = n;
    g->adj = malloc(n * sizeof(No *));
    if (!g->adj) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        g->adj[i] = NULL;
    }

    return g;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return;
    if (sao_adjacentes_lista(g, u, v)) return; // evita aresta duplicada

    inserir_no(&g->adj[u], v);
    if (u != v) {
        inserir_no(&g->adj[v], u);
    }
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return;

    remover_no(&g->adj[u], v);
    if (u != v) {
        remover_no(&g->adj[v], u);
    }
}

int grau_lista(GrafoLista *g, int v) {
    if (!vertice_valido(g, v)) return -1;

    int grau = 0;
    No *atual = g->adj[v];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return 0;

    No *atual = g->adj[u];
    while (atual != NULL) {
        if (atual->destino == v) return 1;
        atual = atual->prox;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *g) {
    if (!g) return;

    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual != NULL) {
            No *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

void imprimir_grafo_lista(GrafoLista *g) {
    if (!g) return;

    printf("Lista de adjacencia (%d vertices):\n", g->n);
    for (int i = 0; i < g->n; i++) {
        printf("%d:", i);
        No *atual = g->adj[i];
        while (atual != NULL) {
            printf(" -> %d", atual->destino);
            atual = atual->prox;
        }
        printf("\n");
    }
}