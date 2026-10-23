#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "grafo_lista.h"

/* Usa vetores internos, como no exemplo do professor, e imprime o resultado.
 * Retorna 1 no sucesso, 0 para ciclo negativo alcancavel e -1 para entrada
 * invalida. Os vertices sao numerados de 0 a num_vertices - 1.
 */
int bellman_ford(GrafoLista *g, int origem);
/* vertice deve ter sido atualizado na n-esima passagem de Bellman-Ford. */
void reconstruir_ciclo_negativo(int vertice, int *pred, int num_vertices);

#endif
