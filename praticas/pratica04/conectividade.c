#include <stdio.h>
#include "conectividade.h"

void dfs_articulacoes(GrafoLista *g, int u, int pai, int *descoberta, int *low, int *visitado, int *tempo){
    int filhos = 0;
    int articulacao = 0;

    visitado[u] = 1;
    (*tempo)++;
    descoberta[u] = *tempo;
    low[u] = *tempo;

    No *adj = g->listaAdj[u];
    while(adj != NULL){
        int v = adj->vertice;
        if(!visitado[v]){
            filhos++;
            dfs_articulacoes(g, v, u, descoberta, low, visitado, tempo);
            if(low[v] < low[u]){
                low[u] = low[v];
            }
            if(pai != -1 && low[v] >= descoberta[u]){
                articulacao = 1;
            }
        } else if(v != pai){
            if(descoberta[v] < low[u]){
                low[u] = descoberta[v];
            }
        }
        adj = adj->prox;
    }
    if(pai == -1 && filhos > 1){
        articulacao = 1;
    }
    if(articulacao){
        printf("articulacao: %d\n", u);
    }
}

void detectar_pontes(GrafoLista *g, int u, int pai, int *descoberta, int *low, int *visitado, int *tempo){
    visitado[u] = 1;
    (*tempo)++;
    descoberta[u] = *tempo;
    low[u] = *tempo;
    No *adj = g->listaAdj[u];
    while(adj != NULL){
        int v = adj->vertice;
        if(!visitado[v]){
            detectar_pontes(g, v, u, descoberta, low, visitado, tempo);
            if(low[v] < low[u]){
                low[u] = low[v];
            }
            if(low[v] > descoberta[u]){
                printf("ponte: [%d, %d]\n", u, v);
            }
        } else if(v != pai){
            if(descoberta[v] < low[u]){
                low[u] = descoberta[v];
            }
        }
        adj = adj->prox;
    }
}