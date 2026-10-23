#include "bellman_ford.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

int bellman_ford(GrafoLista *g, int origem) {
    if (g == NULL || g->num_vertices <= 0 || g->num_vertices > MAX_VERTICES ||
        origem < 0 || origem >= g->num_vertices) return -1;

    /* Tipo mais amplo evita overflow nas somas de pesos int, inclusive
     * durante as relaxacoes de um ciclo negativo. */
    long long distancia[MAX_VERTICES];
    int pred[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) distancia[i] = LLONG_MAX;
    memset(pred, -1, sizeof(pred));
    distancia[origem] = 0;

    for (int i = 0; i < g->num_vertices - 1; i++) {
        int alteracao = 0;
        for (int u = 0; u < g->num_vertices; u++) {
            No *no = g->lista[u];
            while (no != NULL) {
                int v = no->vertice;
                int peso = no->peso;
                if (distancia[u] != LLONG_MAX && distancia[v] > distancia[u] + peso) {
                    distancia[v] = distancia[u] + peso;
                    pred[v] = u;
                    alteracao = 1;
                }
                no = no->proximo;
            }
        }
        if (!alteracao) break;
    }

    /* A n-esima passagem registra um vertice afetado e seus predecessores
     * para permitir reconstruir o ciclo, em vez de retornar imediatamente. */
    int vertice = -1;
    for (int u = 0; u < g->num_vertices; u++) {
        No *no = g->lista[u];
        while (no != NULL) {
            int v = no->vertice;
            int peso = no->peso;
            if (distancia[u] != LLONG_MAX && distancia[v] > distancia[u] + peso) {
                distancia[v] = distancia[u] + peso;
                pred[v] = u;
                vertice = v;
            }
            no = no->proximo;
        }
    }
    if (vertice != -1) {
        reconstruir_ciclo_negativo(vertice, pred, g->num_vertices);
        return 0;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        printf("Vertice %d: ", i);
        if (distancia[i] == LLONG_MAX) puts("inalcancavel");
        else printf("distancia = %lld; predecessor = %d\n", distancia[i], pred[i]);
    }
    return 1;
}

void reconstruir_ciclo_negativo(int vertice, int *pred, int num_vertices) {
    if (pred == NULL || num_vertices <= 0 || num_vertices > MAX_VERTICES) return;
    /* Retroceder n vezes garante que o vertice esteja dentro do ciclo. */
    for (int i = 0; i < num_vertices; i++) {
        if (vertice < 0 || vertice >= num_vertices) return;
        vertice = pred[vertice];
    }
    if (vertice < 0 || vertice >= num_vertices) return;

    int ciclo[MAX_VERTICES];
    int tamanho = 0;
    int u = vertice;
    do {
        if (u < 0 || u >= num_vertices || tamanho >= num_vertices) return;
        ciclo[tamanho++] = u;
        u = pred[u];
    } while (u != vertice);

    /* pred percorre as arestas ao contrario; imprimir em ordem inversa
     * apresenta o ciclo no sentido das arestas do grafo direcionado. */
    printf("Ciclo negativo: %d", vertice);
    for (int i = tamanho - 1; i >= 0; i--) printf(" -> %d", ciclo[i]);
    putchar('\n');
}
