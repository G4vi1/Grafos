#include "cobertura.h"
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

/* Extrai apenas uma orientacao de cada aresta nao direcionada.
 * A matriz usa presente, pois peso zero tambem representa uma aresta. */
static Aresta *arestas_matriz(const GrafoMatriz *g, int *m) {
    if (g == NULL || g->n <= 0 || g->presente == NULL) return NULL;
    *m = 0;
    for (int u = 0; u < g->n; u++) {
        if (g->presente[u] == NULL) return NULL;
        for (int v = u; v < g->n; v++) {
            if (g->presente[u][v]) {
                if (*m == INT_MAX) return NULL;
                (*m)++;
            }
        }
    }
    size_t quantidade = *m > 0 ? (size_t)*m : 1;
    if (quantidade > SIZE_MAX / sizeof(Aresta)) return NULL;
    Aresta *arestas = malloc(quantidade * sizeof(*arestas));
    if (arestas == NULL) return NULL;
    int i = 0;
    for (int u = 0; u < g->n; u++) {
        for (int v = u; v < g->n; v++) {
            if (g->presente[u][v]) arestas[i++] = (Aresta){u, v};
        }
    }
    return arestas;
}

static Aresta *arestas_lista(const GrafoLista *g, int *m) {
    if (g == NULL || g->num_vertices <= 0 || g->lista == NULL) return NULL;
    *m = 0;
    for (int u = 0; u < g->num_vertices; u++) {
        for (const No *no = g->lista[u]; no != NULL; no = no->proximo) {
            if (no->vertice < 0 || no->vertice >= g->num_vertices) return NULL;
            if (u <= no->vertice) {
                if (*m == INT_MAX) return NULL;
                (*m)++;
            }
        }
    }
    size_t quantidade = *m > 0 ? (size_t)*m : 1;
    if (quantidade > SIZE_MAX / sizeof(Aresta)) return NULL;
    Aresta *arestas = malloc(quantidade * sizeof(*arestas));
    if (arestas == NULL) return NULL;
    int i = 0;
    for (int u = 0; u < g->num_vertices; u++) {
        for (const No *no = g->lista[u]; no != NULL; no = no->proximo) {
            if (u <= no->vertice) arestas[i++] = (Aresta){u, no->vertice};
        }
    }
    return arestas;
}

/* Centraliza a execucao e a liberacao para manter os mesmos criterios
 * de cobertura, poda e desempate nas duas representacoes. */
static int executar(Aresta *arestas, int n, int m, int cobertura[], int exata) {
    if (arestas == NULL) return -1;
    int resultado = exata ? cobertura_minima_bt(arestas, n, m, cobertura)
                         : cobertura_gulosa(arestas, n, m, cobertura);
    free(arestas);
    return resultado;
}

int cobertura_minima_bt_matriz(const GrafoMatriz *g, int cobertura[]) {
    int m = 0;
    Aresta *arestas = arestas_matriz(g, &m);
    return executar(arestas, g ? g->n : 0, m, cobertura, 1);
}

int cobertura_gulosa_matriz(const GrafoMatriz *g, int cobertura[]) {
    int m = 0;
    Aresta *arestas = arestas_matriz(g, &m);
    return executar(arestas, g ? g->n : 0, m, cobertura, 0);
}

int cobertura_minima_bt_lista(const GrafoLista *g, int cobertura[]) {
    int m = 0;
    Aresta *arestas = arestas_lista(g, &m);
    return executar(arestas, g ? g->num_vertices : 0, m, cobertura, 1);
}

int cobertura_gulosa_lista(const GrafoLista *g, int cobertura[]) {
    int m = 0;
    Aresta *arestas = arestas_lista(g, &m);
    return executar(arestas, g ? g->num_vertices : 0, m, cobertura, 0);
}

int eh_cobertura_matriz(const GrafoMatriz *g, const int cobertura[]) {
    int m = 0;
    Aresta *arestas = arestas_matriz(g, &m);
    if (arestas == NULL || cobertura == NULL) { free(arestas); return -1; }
    int resultado = eh_cobertura(arestas, m, cobertura);
    free(arestas);
    return resultado;
}

int eh_cobertura_lista(const GrafoLista *g, const int cobertura[]) {
    int m = 0;
    Aresta *arestas = arestas_lista(g, &m);
    if (arestas == NULL || cobertura == NULL) { free(arestas); return -1; }
    int resultado = eh_cobertura(arestas, m, cobertura);
    free(arestas);
    return resultado;
}
