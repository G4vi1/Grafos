#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

// Estrutura de dados para representar um grafo usando lista de adjacência

typedef struct No {

    // Vertice do grafo
    int vertice;

    //Ponteiro do tipo No que aponta para o próximo nó da lista
    struct No *prox;
} No;


//LIsta de adjacência do grafo
typedef struct {

    // Número de vértices do grafo
    int numVertices;

    /* Lista de adjacência do grafo
     * Um vetor de ponteiros para a struct No, ou seja
     * lista[i], aí um ponteiro para o início da lista encadeada
     * vizinhos do vertice i. */

    No **listaAdj;
} GrafoLista;

GrafoLista* inicializarGrafo(int numVertices);
void inserirAresta(GrafoLista *g, int u, int v);
void liberarGrafo(GrafoLista *g);

#endif