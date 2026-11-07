#include "grafo_lista.h"
#include <stdlib.h>

/* Cria o registro do grafo e um vetor de cabecas das listas, uma por vertice. */
GrafoLista *criar_grafo(int num_vertices) {
    if (num_vertices <= 0) return NULL;
    /* sizeof(*g) reserva o tamanho da estrutura apontada por g. */
    GrafoLista *g = malloc(sizeof(*g));
    if (g == NULL) return NULL;
    /* Zera o vetor: neste ambiente, cada lista comeca com ponteiro NULL, sem vizinhos. */
    g->lista = calloc((size_t)num_vertices, sizeof(*g->lista));
    /* Se o vetor nao puder ser criado, desfaz a alocacao da estrutura. */
    if (g->lista == NULL) {
        free(g);
        return NULL;
    }
    g->num_vertices = num_vertices;
    return g;
}

/* Adiciona somente origem -> destino, em O(1), no inicio da lista.
 * Para um grafo nao direcionado, o chamador insere tambem o sentido inverso. */
int inserir_aresta(GrafoLista *g, int origem, int destino, int peso) {
    /* Evita acessar uma lista inexistente ou um indice fora dos limites. */
    if (g == NULL || origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices) return 0;
    /* Cada aresta direcionada recebe um no com destino, peso e proximo. */
    No *no = malloc(sizeof(*no));
    if (no == NULL) return 0;
    /* O novo no aponta para a antiga cabeca; depois passa a ser a nova cabeca.
     * Arestas paralelas sao mantidas como nos separados. */
    *no = (No){destino, peso, g->lista[origem]};
    g->lista[origem] = no;
    return 1;
}

/* Percorre todas as listas para liberar cada no antes de liberar o vetor. */
void liberar_grafo(GrafoLista *g) {
    if (g == NULL) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *no = g->lista[i];
        while (no != NULL) {
            /* Guarda o proximo endereco antes de liberar no, que nao podera mais ser lido. */
            No *proximo = no->proximo;
            free(no);
            no = proximo;
        }
    }
    /* Depois dos nos, libera o vetor de cabecas e a estrutura externa. */
    free(g->lista);
    free(g);
}
