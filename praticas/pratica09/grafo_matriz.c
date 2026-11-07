#include "grafo_matriz.h"
#include <stdio.h>
#include <stdlib.h>

/* Auxiliar interna: valida o ponteiro e o intervalo de um indice. */
static int vertice_valido(GrafoMatriz *g, int v) {
    return g != NULL && v >= 0 && v < g->n;
}

/* Aloca duas matrizes n x n: pesos e presenca. Custo de espaco O(V^2). */
GrafoMatriz *criar_grafo_matriz(int n) {
    if (n <= 0) return NULL;
    /* Inicializa os campos antes de alocar os vetores de linhas. */
    GrafoMatriz *g = calloc(1, sizeof(*g));
    if (g == NULL) return NULL;
    g->n = n;
    /* Primeiro reserva os ponteiros das linhas, inicialmente zerados. */
    g->adj = calloc((size_t)n, sizeof(*g->adj));
    g->presente = calloc((size_t)n, sizeof(*g->presente));
    if (g->adj == NULL || g->presente == NULL) {
        liberar_grafo_matriz(g);
        return NULL;
    }
    /* Cada linha tem n colunas. Presenca zero indica ausencia de aresta. */
    for (int i = 0; i < n; i++) {
        g->adj[i] = calloc((size_t)n, sizeof(int));
        g->presente[i] = calloc((size_t)n, sizeof(unsigned char));
        if (g->adj[i] == NULL || g->presente[i] == NULL) {
            /* A limpeza aceita linhas ainda nao alocadas, desfazendo uma criacao parcial. */
            liberar_grafo_matriz(g);
            return NULL;
        }
    }
    return g;
}

/* Insere uma aresta nao direcionada em O(1), preenchendo as duas posicoes simetricas. */
int inserir_aresta_matriz(GrafoMatriz *g, int u, int v, int peso) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return 0;
    /* Entre arestas paralelas, conserva o menor peso, suficiente para calcular AGM. */
    if (!g->presente[u][v] || peso < g->adj[u][v]) {
        g->adj[u][v] = peso;
        g->adj[v][u] = peso;
    }
    /* Registra a existencia separadamente: peso zero tambem e uma aresta valida. */
    g->presente[u][v] = g->presente[v][u] = 1;
    return 1;
}

/* Apaga a presenca nos dois sentidos e zera o peso que deixou de ser usado. */
void remover_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return;
    g->presente[u][v] = g->presente[v][u] = 0;
    g->adj[u][v] = g->adj[v][u] = 0;
}

/* Conta incidencias na linha do vertice em O(V). Um laco contribui duas
 * vezes para o grau de um grafo nao direcionado. */
int grau_matriz(GrafoMatriz *g, int v) {
    if (!vertice_valido(g, v)) return -1;
    int grau = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->presente[v][i]) grau += (i == v ? 2 : 1);
    }
    return grau;
}

/* Consulta a presenca, e nao o peso, para reconhecer inclusive arestas de peso zero. */
int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v) {
    if (!vertice_valido(g, u) || !vertice_valido(g, v)) return 0;
    return g->presente[u][v];
}

/* Libera primeiro as linhas, depois os vetores de ponteiros e por fim o grafo.
 * Os testes de NULL permitem limpar tambem uma alocacao incompleta. */
void liberar_grafo_matriz(GrafoMatriz *g) {
    if (g == NULL) return;
    for (int i = 0; i < g->n; i++) {
        if (g->adj != NULL) free(g->adj[i]);
        if (g->presente != NULL) free(g->presente[i]);
    }
    free(g->adj);
    free(g->presente);
    free(g);
}

/* Mostra cada linha da matriz; o ponto distingue ausencia de aresta de peso zero. */
void imprimir_grafo_matriz(GrafoMatriz *g) {
    if (g == NULL) return;
    printf("Matriz de adjacencia (%d vertices; . = sem aresta):\n", g->n);
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (g->presente[i][j]) printf("%d ", g->adj[i][j]);
            else printf(". ");
        }
        printf("\n");
    }
}
