#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo(int n) {
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->lista = (No **)malloc(sizeof(No)*n);
    for(int i=0; i < n; i++) {
        g->lista[i] = (No *)malloc(sizeof(No));
        g->lista[i]->vertice = i;
        g->lista[i]->proximo = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {

    No *proximo = g->lista[u];
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->proximo = proximo;
    g->lista[u] = no;

    proximo = g->lista[v];
    no = (No *)malloc(sizeof(No));
    no->vertice = u;
    no->proximo = proximo;
    g->lista[v] = no;
        
    
}