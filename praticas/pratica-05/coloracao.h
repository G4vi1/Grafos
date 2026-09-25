#ifndef COLORACAO_H
#define COLORACAO_H

#include "grafo_lista.h"

void coloracao_gulosa(GrafoLista *g, int *num_cores);
void coloracao_welsh_powell(GrafoLista *g, int *num_cores);
int eh_bipartido(GrafoLista *g);

#endif