#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H
#include "grafo_lista.h"


//Pilha (LIFO) para a DFS iterativa

typedef struct {
    
    /* Ponteiro para um vetor(alocado dinamicamente como malloc)
     * onde os elementos da pilha ficam armazenados de fato.
     *vetor int pois no contexto de grafos, a pilha guardará vértices
    */
    int *dados;

    /* Indice que indica a posição do último elemento inserido
    * Exemplo: topo = -1, aí vai ser uma pilha vazia.
    * Ao empilhar: topo++ e depois dados[topo] = valor
    * Ao desempilhar: pega dados[topo] e depois topo--
    * Em suma, ele começa -1 e vai ter uma soma que aumenta a 
    * medida que empilha, e ao desempilhar o indice é subtraído
    */

    int topo; 

    /* Tamanho máximo da pilha/vetor(usado para checar se
     * a pilha está cheia antes de empilhar)
     * exemplo: (topo == capacidade - 1) + saber quanto malloc 
     * precisa alocar na inicialização.
    */

    int capacidade;
} Pilha;


/* Funções para inicializar a pilha, recebe 
a capacidade para alocar memória para pilha.*/

Pilha *inicializarPilha(int capacidade);

/* Função para empilhar um valor na pilha, 
recebe o ponteiro da pilha e o valor a ser empilhado.*/

void empilhar(Pilha *p, int valor);

/*Função para desempilhar um valor da pilha, 
recebe o ponteiro da pilha e retorna o valor desempilhado.*/

int desempilhar(Pilha *p);

// Função para liberar a memória alocada na pilha.
void liberarPilha(Pilha *p);

//Funções da DFS

void dfs_recursiva(
    //Ponteiro do tipo GrafoLista que representa o grafo
    GrafoLista *g, 
    //Vértice atual da DFS
    int  u, 
    int *visitado, 
    int *tempo_inicio, 
    int *tempo_fim, 
    int *tempo_geral, 
    Pilha *p
);

int dfs_ciclo(GrafoLista *g, int u, int *visitado, int pai);

int tem_ciclo(GrafoLista *g);

#endif