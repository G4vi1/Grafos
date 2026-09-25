#include <stdio.h>
#include "grafo_lista.h"
#include "coloracao.h"

int main(void) {
    GrafoLista *g = inicializarGrafo(6);

    inserirAresta(g, 0, 1);
    inserirAresta(g, 0, 2);
    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 4);
    inserirAresta(g, 3, 5);
    inserirAresta(g, 4, 5);

    int cores_gulosa;
    int cores_welsh;

    coloracao_gulosa(g, &cores_gulosa);
    coloracao_welsh_powell(g, &cores_welsh);

    printf("\nGrafo bipartido: %s\n",
           eh_bipartido(g) ? "sim" : "nao");

    liberarGrafo(g);

    return 0;
}