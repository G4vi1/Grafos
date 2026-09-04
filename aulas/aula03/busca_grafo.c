#include "grafo_lista.h"
#include <stdlib.h>
#include <stdio.h>
#include "busca_grafo.h"

int topo = 0;

void dfs(GrafoLista *g, int u, int *p, int *visitado) {
    visitado[u] = 1;
    p[topo++] = u;
    No *no = g->lista[u];
    while(no != NULL) {
        int v = no->vertice;
        if (!visitado[u]) dfs(g, v, p, visitado);
        no = no->proximo;
    }
    topo--;
    printf("Desempilha %i\n", u+1);
    
}