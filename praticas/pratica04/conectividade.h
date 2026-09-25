#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H
#include "grafo_lista.h"

void dfs_articulacoes(GrafoLista *g, int u, int pai, int *descoberta, int *low, int *visitado, int *tempo);
void detectar_pontes(GrafoLista *g, int u, int pai, int *descoberta, int *low, int *visitado, int *tempo);

#endif