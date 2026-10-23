#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>
#include "grafo_lista.h"

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; /* vertice -> indice no heap; -1 quando ausente */
} MinHeap;

MinHeap *criar_min_heap(int capacidade);
int inserir_min_heap(MinHeap *heap, int vertice, int distancia);
/* Retorna {-1, INT_MAX} quando o heap esta vazio. */
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int distancia);
void liberar_min_heap(MinHeap *heap);

/* Exige grafo com pesos nao negativos; pred usa -1 para ausencia de predecessor.
 * Distancias >= INT_MAX permanecem infinitas. Em falha de alocacao, os
 * resultados permanecem inicializados com INT_MAX e -1.
 */
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
/* Imprime o caminho; pred deve ser o resultado de dijkstra para a mesma origem. */
void reconstruir_caminho(int origem, int destino, int *pred);

#endif
