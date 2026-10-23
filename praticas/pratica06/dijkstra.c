#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

MinHeap *criar_min_heap(int capacidade) {
    if (capacidade <= 0) return NULL;
    MinHeap *heap = malloc(sizeof(*heap));
    if (heap == NULL) return NULL;
    heap->dados = calloc((size_t)capacidade, sizeof(*heap->dados));
    heap->posicao = calloc((size_t)capacidade, sizeof(*heap->posicao));
    if (heap->dados == NULL || heap->posicao == NULL) {
        liberar_min_heap(heap);
        return NULL;
    }
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    for (int i = 0; i < capacidade; i++) heap->posicao[i] = -1;
    return heap;
}

void liberar_min_heap(MinHeap *heap) {
    if (heap == NULL) return;
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

static void trocar(MinHeap *heap, int a, int b) {
    NoHeap temporario = heap->dados[a];
    heap->dados[a] = heap->dados[b];
    heap->dados[b] = temporario;
    heap->posicao[heap->dados[a].vertice] = a;
    heap->posicao[heap->dados[b].vertice] = b;
}

static void subir(MinHeap *heap, int indice) {
    while (indice > 0) {
        int pai = (indice - 1) / 2;
        if (heap->dados[pai].distancia <= heap->dados[indice].distancia) break;
        trocar(heap, pai, indice);
        indice = pai;
    }
}

int inserir_min_heap(MinHeap *heap, int vertice, int distancia) {
    if (heap == NULL || vertice < 0 || vertice >= heap->capacidade ||
        heap->tamanho == heap->capacidade || heap->posicao[vertice] != -1) return 0;
    int indice = heap->tamanho++;
    heap->dados[indice] = (NoHeap){vertice, distancia};
    heap->posicao[vertice] = indice;
    subir(heap, indice);
    return 1;
}

NoHeap extrair_minimo(MinHeap *heap) {
    if (heap == NULL || heap->tamanho == 0) return (NoHeap){-1, INT_MAX};
    NoHeap minimo = heap->dados[0];
    heap->posicao[minimo.vertice] = -1;
    heap->tamanho--;
    if (heap->tamanho == 0) return minimo;
    heap->dados[0] = heap->dados[heap->tamanho];
    heap->posicao[heap->dados[0].vertice] = 0;
    int indice = 0;
    /* Apenas indices anteriores a tamanho/2 possuem filhos. */
    while (indice < heap->tamanho / 2) {
        int esquerdo = 2 * indice + 1;
        int direito = esquerdo + 1;
        int menor = esquerdo;
        if (direito < heap->tamanho &&
            heap->dados[direito].distancia < heap->dados[esquerdo].distancia)
            menor = direito;
        if (heap->dados[indice].distancia <= heap->dados[menor].distancia) break;
        trocar(heap, indice, menor);
        indice = menor;
    }
    return minimo;
}

void diminuir_chave(MinHeap *heap, int vertice, int distancia) {
    if (heap == NULL || vertice < 0 || vertice >= heap->capacidade) return;
    int indice = heap->posicao[vertice];
    if (indice == -1 || distancia >= heap->dados[indice].distancia) return;
    heap->dados[indice].distancia = distancia;
    subir(heap, indice);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    if (g == NULL || dist == NULL || pred == NULL) return;
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    if (origem < 0 || origem >= g->num_vertices) return;
    MinHeap *heap = criar_min_heap(g->num_vertices);
    if (heap == NULL) return;
    dist[origem] = 0;
    for (int i = 0; i < g->num_vertices; i++) inserir_min_heap(heap, i, dist[i]);
    while (heap->tamanho > 0) {
        NoHeap atual = extrair_minimo(heap);
        if (atual.distancia == INT_MAX) break;
        int u = atual.vertice;
        for (Aresta *aresta = g->lista[u]; aresta != NULL; aresta = aresta->proximo) {
            int v = aresta->vertice;
            /* Evita overflow antes de somar o custo da aresta. */
            if (heap->posicao[v] != -1 && aresta->peso < INT_MAX - dist[u]) {
                int nova_distancia = dist[u] + aresta->peso;
                if (nova_distancia < dist[v]) {
                    dist[v] = nova_distancia;
                    pred[v] = u;
                    diminuir_chave(heap, v, nova_distancia);
                }
            }
        }
    }
    liberar_min_heap(heap);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (pred == NULL || origem < 0 || destino < 0) return;
    if (destino == origem) {
        printf("%d", origem);
    } else if (pred[destino] == -1) {
        printf("Nao existe caminho de %d para %d.\n", origem, destino);
        return;
    } else {
        reconstruir_caminho(origem, pred[destino], pred);
        printf(" -> %d", destino);
    }
}
