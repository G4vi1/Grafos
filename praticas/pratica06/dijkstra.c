#include "dijkstra.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

void dijkstra(GrafoLista *g, int origem) {
    if (g == NULL || g->num_vertices <= 0 || g->num_vertices > MAX_VERTICES ||
        origem < 0 || origem >= g->num_vertices) return;

    int distancia[MAX_VERTICES];
    int pred[MAX_VERTICES];
    int processado[MAX_VERTICES];
    memset(distancia, -1, sizeof(distancia));
    memset(pred, -1, sizeof(pred));
    memset(processado, 0, sizeof(processado));
    distancia[origem] = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        int u = -1;
        int menor = -1;
        for (int j = 0; j < g->num_vertices; j++) {
            /* Distancia -1 significa que o vertice ainda nao foi alcancado. */
            if (!processado[j] && distancia[j] != -1 &&
                (menor == -1 || distancia[j] < menor)) {
                menor = distancia[j];
                u = j;
            }
        }
        /* A busca precisa terminar antes de verificar se encontrou um vertice. */
        if (u == -1) break;

        processado[u] = 1;
        No *no = g->lista[u];
        while (no != NULL) {
            int v = no->vertice;
            int peso = no->peso;
            /* Verifica o limite antes da soma para evitar overflow de int. */
            if (!processado[v] && distancia[u] != -1 &&
                peso <= INT_MAX - distancia[u] &&
                (distancia[v] == -1 || distancia[v] > distancia[u] + peso)) {
                distancia[v] = distancia[u] + peso;
                pred[v] = u;
            }
            no = no->proximo;
        }
    }

    for (int destino = 0; destino < g->num_vertices; destino++) {
        printf("Vertice %d: ", destino);
        if (distancia[destino] == -1) {
            puts("inalcancavel");
        } else {
            printf("distancia = %d; caminho = ", distancia[destino]);
            reconstruir_caminho(origem, destino, pred);
            putchar('\n');
        }
    }
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (pred == NULL || origem < 0 || destino < 0) return;
    if (destino == origem) {
        printf("%d", origem);
    } else if (pred[destino] == -1) {
        printf("Nao existe caminho de %d para %d.\n", origem, destino);
        return;
    } else {
        reconstruir_caminho(origem, pred[destino], pred);
        printf(" -> %d", destino);
    }
}
