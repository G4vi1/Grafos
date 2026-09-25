#include "planaridade.h"
#include <stdio.h>

int eh_planar_euler(GrafoLista *g){
    int n = g->numVertices;
    int m = 0;
    if(n < 3){
      return 1;
    }
    for(int i = 0; i < n; i++){
        No *atual = g->listaAdj[i];
        while (atual != NULL){
            m++;
            atual = atual->prox;
        }
    }
    m = m / 2;
    if(n <= 10){
        printf("Teorema de Kuratowski\n");
    }
    if(m <= 3 * n - 6){
        return 1;
    }
    return 0;
}