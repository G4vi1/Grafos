#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H
#include "grafo_lista.h"

// Estrutura da fila 

typedef struct {
    int *dados; // Ponteiro para um vetor de inteiros que armazenará os elementos da fila
    int capacidade, inicio, fim, tamanho; // Capacidade máxima da fila, índice do início, índice do fim e tamanho atual da fila
} Fila;

//Funções da fila

Fila *inicializarFila(int capacidade);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void liberarFila(Fila *f);

//Funções da BFS

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);
int contar_componentes(GrafoLista *g);

#endif