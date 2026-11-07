#include "cobertura.h"
#include <stdlib.h>
#include <string.h>

/* Valida os indices antes de usa-los nos vetores de vertices. */
static int entrada_valida(const Aresta arestas[], int n, int m,
                          const int cobertura[]) {
    if (n < 0 || m < 0 || (n > 0 && cobertura == NULL) ||
        (m > 0 && arestas == NULL)) return 0;
    for (int i = 0; i < m; i++) {
        if (arestas[i].u < 0 || arestas[i].u >= n ||
            arestas[i].v < 0 || arestas[i].v >= n) return 0;
    }
    return 1;
}

/* Como no exemplo fornecido, basta uma extremidade de cada aresta.
 * Os indices devem ser validos para o vetor cobertura. */
int eh_cobertura(const Aresta arestas[], int m, const int cobertura[]) {
    if (m < 0 || (m > 0 && (arestas == NULL || cobertura == NULL))) return 0;
    for (int i = 0; i < m; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        if (u < 0 || v < 0 || (!cobertura[u] && !cobertura[v])) return 0;
    }
    return 1;
}

int cobertura_gulosa(const Aresta arestas[], int n, int m, int cobertura[]) {
    if (!entrada_valida(arestas, n, m, cobertura)) return -1;
    if (n == 0) return 0;
    int *grau = calloc((size_t)n, sizeof(*grau));
    if (grau == NULL) return -1;
    memset(cobertura, 0, (size_t)n * sizeof(*cobertura));
    int quantidade = 0;
    for (;;) {
        memset(grau, 0, (size_t)n * sizeof(*grau));
        /* Recalcula o grau usando apenas arestas ainda descobertas.
         * Lacos contam uma vez, pois basta selecionar seu unico vertice. */
        for (int i = 0; i < m; i++) {
            int u = arestas[i].u, v = arestas[i].v;
            if (!cobertura[u] && !cobertura[v]) {
                grau[u]++;
                if (u != v) grau[v]++;
            }
        }
        int escolhido = 0;
        for (int v = 1; v < n; v++) {
            if (grau[v] > grau[escolhido]) escolhido = v;
        }
        if (grau[escolhido] == 0) break;
        cobertura[escolhido] = 1;
        quantidade++;
    }
    free(grau);
    return quantidade;
}

/* Uma aresta descoberta exige u ou v. Explora ambas as escolhas e
 * desfaz cada inclusao ao retornar (backtracking). A melhor solucao
 * conhecida e o limite superior usado para podar a busca. */
static void buscar(const Aresta arestas[], int n, int m, int atual[],
                   int quantidade, int melhor[], int *limite) {
    if (quantidade >= *limite) return;
    int i = 0;
    while (i < m && (atual[arestas[i].u] || atual[arestas[i].v])) i++;
    if (i == m) {
        *limite = quantidade;
        memcpy(melhor, atual, (size_t)n * sizeof(*melhor));
        return;
    }
    int u = arestas[i].u, v = arestas[i].v;
    atual[u] = 1;
    buscar(arestas, n, m, atual, quantidade + 1, melhor, limite);
    atual[u] = 0;
    if (u != v) {
        atual[v] = 1;
        buscar(arestas, n, m, atual, quantidade + 1, melhor, limite);
        atual[v] = 0;
    }
}

int cobertura_minima_bt(const Aresta arestas[], int n, int m, int cobertura[]) {
    if (!entrada_valida(arestas, n, m, cobertura)) return -1;
    if (n == 0) return 0;
    int *atual = calloc((size_t)n, sizeof(*atual));
    if (atual == NULL) return -1;
    /* A heuristica fornece uma cobertura valida para iniciar a poda. */
    int limite = cobertura_gulosa(arestas, n, m, cobertura);
    if (limite >= 0) buscar(arestas, n, m, atual, 0, cobertura, &limite);
    free(atual);
    return limite;
}
