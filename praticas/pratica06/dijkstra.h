#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo_lista.h"

/* Calcula e imprime distancias e caminhos. -1 indica vertice inalcancavel.
 * Exige pesos nao negativos e no maximo MAX_VERTICES vertices.
 */
void dijkstra(GrafoLista *g, int origem);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif
