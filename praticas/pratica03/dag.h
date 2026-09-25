#ifndef DAG_H
#define DAG_H

#include "grafo_lista.h"

//Estrutura da fila

typedef struct {
    int *dados; // Ponteiro para um vetor de inteiros que armazenará os elementos da fila
    int capacidade, inicio, fim, tamanho; // Capacidade máxima da fila, índice do início, índice do fim e tamanho atual da fila
} Fila;

typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

//Funções da fila

Fila *inicializarFila(int capacidade);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void liberarFila(Fila *f);

//FUnções da pilha

Pilha *inicializarPilha(int capacidade);
void empilhar(Pilha *p, int valor);
int desempilhar(Pilha *p);
void liberarPilha(Pilha *p);

//Ordenações

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int dfs_topologica(GrafoLista *g, int u, int *cor, Pilha *p);
int eh_dag(GrafoLista *g);

#endif