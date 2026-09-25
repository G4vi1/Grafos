#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

void coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int n = g->numVertices;
    int *cores = malloc(n * sizeof(int));
    int *cor_usada = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        cores[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int c = 0; c < n; c++) {
            cor_usada[c] = 0;
        }

        No *no = g->listaAdj[i];

        while (no != NULL) {
            int v = no->vertice;

            if (cores[v] != -1) {
                cor_usada[cores[v]] = 1;
            }

            no = no->prox;
        }

        int c = 0;

        while (cor_usada[c]) {
            c++;
        }

        cores[i] = c;
    }

    int maior_cor = 0;

    for (int i = 0; i < n; i++) {
        if (cores[i] > maior_cor) {
            maior_cor = cores[i];
        }
    }

    *num_cores = maior_cor + 1;

    printf("\nColoracao Gulosa:\n");

    for (int i = 0; i < n; i++) {
        printf("Vertice %d -> Cor %d\n", i, cores[i]);
    }

    printf("Numero de cores: %d\n", *num_cores);

    free(cores);
    free(cor_usada);
}

static int grau(GrafoLista *g, int vertice) {
    int contador = 0;
    No *no = g->listaAdj[vertice];

    while (no != NULL) {
        contador++;
        no = no->prox;
    }

    return contador;
}

static void ordenarPorGrau(GrafoLista *g, int *vertices) {
    int n = g->numVertices;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (grau(g, vertices[j]) < grau(g, vertices[j + 1])) {
                int temp = vertices[j];
                vertices[j] = vertices[j + 1];
                vertices[j + 1] = temp;
            }
        }
    }
}

void coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int n = g->numVertices;
    int *vertices = malloc(n * sizeof(int));
    int *cores = malloc(n * sizeof(int));
    int *cor_usada = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        vertices[i] = i;
        cores[i] = -1;
    }

    ordenarPorGrau(g, vertices);

    for (int i = 0; i < n; i++) {
        for (int c = 0; c < n; c++) {
            cor_usada[c] = 0;
        }

        int u = vertices[i];
        No *no = g->listaAdj[u];

        while (no != NULL) {
            int v = no->vertice;

            if (cores[v] != -1) {
                cor_usada[cores[v]] = 1;
            }

            no = no->prox;
        }

        int c = 0;

        while (cor_usada[c]) {
            c++;
        }

        cores[u] = c;
    }

    int maior_cor = 0;

    for (int i = 0; i < n; i++) {
        if (cores[i] > maior_cor) {
            maior_cor = cores[i];
        }
    }

    *num_cores = maior_cor + 1;

    printf("\nColoracao Welsh-Powell:\n");

    for (int i = 0; i < n; i++) {
        printf("Vertice %d -> Cor %d\n", i, cores[i]);
    }

    printf("Numero de cores: %d\n", *num_cores);

    free(vertices);
    free(cores);
    free(cor_usada);
}

int eh_bipartido(GrafoLista *g) {
    int n = g->numVertices;
    int *cores = malloc(n * sizeof(int));
    int *fila = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        cores[i] = -1;
    }

    for (int inicio = 0; inicio < n; inicio++) {
        if (cores[inicio] != -1) {
            continue;
        }

        int inicioFila = 0;
        int fimFila = 0;

        cores[inicio] = 0;
        fila[fimFila++] = inicio;

        while (inicioFila < fimFila) {
            int u = fila[inicioFila++];
            No *no = g->listaAdj[u];

            while (no != NULL) {
                int v = no->vertice;

                if (cores[v] == -1) {
                    cores[v] = 1 - cores[u];
                    fila[fimFila++] = v;
                } else if (cores[v] == cores[u]) {
                    free(cores);
                    free(fila);
                    return 0;
                }

                no = no->prox;
            }
        }
    }

    free(cores);
    free(fila);

    return 1;
}