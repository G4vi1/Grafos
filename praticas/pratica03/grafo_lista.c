#include "grafo_lista.h"
#include <stdlib.h>

GrafoLista* inicializarGrafo(int numVertices) {
    /*
    * malloc(sizeof(GrafoLista)) aloca dinamicamente
    * sizeOf(GrafoLista) > quantos bytes a struct GrafoLista ocupa na memória.
    */
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));

    /*Acessa o campo numVertices do grafo dentro da struct apontada por g*/

    g->numVertices = numVertices;
    
    /*Acessa o campo listaAdj do grafo dentro da struct apontada por g
    * malloc(numVertices * sizeof(No *)) aloca dinamicamente
    * numVertices * sizeOf(No *) > quantos bytes o vetor de ponteiros 
    * para No ocupa na memória.
    */

    g->listaAdj = (No **)malloc(numVertices * sizeof(No *));

    /* Inicializa cada ponteiro da lista de adjacência como NULL */

    for(int i = 0; i < numVertices; i++) {
        g->listaAdj[i] = NULL;
    }
    return g;
}



void inserirAresta(GrafoLista *g, int u, int v) {
    /* Alocação de memória de um ponteiro do tipo No */
    No *novo = (No *)malloc(sizeof(No));
    // Inicializa o novo nó com o vértice v e aponta para o próximo nó da lista
    novo->vertice = v;
    // Insere o novo nó no inicio da lista de adjacencia do vértice u
    novo->prox = g->listaAdj[u];
    // Atualiza o ponteiro da lista de adjacência do vértice u para apontar para o novo nó
    g->listaAdj[u] = novo;
    // Aloca dinamicamente um novo nó da lista encadeada
    novo = (No *)malloc(sizeof(No));
    // Inicializa o novo nó com o vértice u e aponta para o próximo nó da lista
    novo->vertice = u;
    // Aloca dinamicamente um novo nó da lista encadeada
    novo->prox = g->listaAdj[v];
    // Insere o novo nó no inicio da lista de adjacencia do vértice v
    g->listaAdj[v] = novo;

}

void liberarGrafo(GrafoLista *g) {
    for(int i = 0; i < g->numVertices; i++) {
        No *atual = g->listaAdj[i];
        while(atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->listaAdj); // fora do for, libera o vetor uma única vez
    free(g);            // libera a própria struct GrafoLista
}

void inserirArco(GrafoLista *g, int u, int v) {
    // Aloca um novo nó representando o destino v
    No *novo = (No *)malloc(sizeof(No));
    novo->vertice = v;
    // Insere no início da lista de adjacência de u (só essa direção, u -> v)
    novo->prox = g->listaAdj[u];
    g->listaAdj[u] = novo;
}