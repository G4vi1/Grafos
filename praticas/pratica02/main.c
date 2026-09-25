#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main(){

    int numVertices = 5;
    GrafoLista *g = inicializarGrafo(numVertices);

    //Grafos Simples para o teste:

    inserirAresta(g, 0, 1);
    inserirAresta(g, 0, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);

    printf("Componentes conexos: %d\n", contar_componentes(g));
    printf("Bipartido: %d\n", eh_bipartido(g));
    printf("Tem ciclo: %d\n\n", tem_ciclo(g));

    // BFS
    int *dist = malloc(numVertices * sizeof(int));
    int *pred = malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    bfs(g, 0, dist, pred);
    printf("Teste BFS:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("v: %d, dist: %d, pred: %d\n", i, dist[i], pred[i]);
    }

    // DFS
    int *visitado = calloc(numVertices, sizeof(int));
    int *t_in = calloc(numVertices, sizeof(int));
    int *t_out = calloc(numVertices, sizeof(int));
    int tempo = 0;
    Pilha *p = inicializarPilha(numVertices);

    dfs_recursiva(g, 0, visitado, t_in, t_out, &tempo, p);
    printf("\nTeste DFS:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("v: %d, in: %d, out: %d\n", i, t_in[i], t_out[i]);
    }

    // forcando um ciclo pra ver se as funcoes atualizam certo
    printf("\nAdicionando aresta (3,4) para criar um ciclo\n");
    inserirAresta(g, 3, 4);

    printf("Bipartido: %d\n", eh_bipartido(g));
    printf("Tem ciclo: %d\n", tem_ciclo(g));

    free(dist);
    free(pred);
    free(visitado);
    free(t_in);
    free(t_out);
    liberarPilha(p);
    liberarGrafo(g);
    return 0;
}