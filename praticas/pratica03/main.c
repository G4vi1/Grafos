#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

int main(){

    GrafoLista *g1 = inicializarGrafo(6);
    inserirArco(g1, 0, 1);
    inserirArco(g1, 0, 2);
    inserirArco(g1, 1, 3);
    inserirArco(g1, 2, 3);
    inserirArco(g1, 3, 4);
    inserirArco(g1, 4, 5);

    printf("g1 e DAG? %d\n", eh_dag(g1));

    int t1;
    int *ordem_kahn = ordenacao_topologica_kahn(g1, &t1);
    
    printf("Kahn: ");
    if (ordem_kahn){
        for(int i = 0; i < t1; i++){
            printf("%d ", ordem_kahn[i]);
        };
        printf("\n");
        free(ordem_kahn);
    } else {
        printf("Ciclo detectado!\n");
    }

    liberarGrafo(g1);
    printf("\n");

    //Outro grafo para testar

    GrafoLista *g2 = inicializarGrafo(4);
    inserirAresta(g2, 0, 1);
    inserirAresta(g2, 1, 2);
    inserirAresta(g2, 2, 1);
    inserirAresta(g2, 3, 0);

    printf("g2 é DAG? %d\n", eh_dag(g2));

    int t3;
    int *kahn_ciclo = ordenacao_topologica_kahn(g2, &t3);
 
    printf("Kahn: ");
    if (kahn_ciclo){
        for(int i = 0; i < t3; i++){
            printf("%d ", kahn_ciclo[i]);
        };
        printf("\n");
        free(kahn_ciclo);
    } else {
        printf("Ciclo detectado!\n");
    }

    int t4;
    int *dfs_ciclo = ordenacao_topologica_dfs(g2, &t4);
    
    printf("DFS: ");
    if(dfs_ciclo){
        for(int i = 0; i < t4; i++){
            printf("%d ", dfs_ciclo[i]);
        };
        printf("\n");
        free(dfs_ciclo);
    } else {
        printf("Ciclo detectado\n");
    }
    liberarGrafo(g2);

    return 0;
}