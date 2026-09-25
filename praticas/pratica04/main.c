#include <stdio.h>
#include <stdlib.h>

#include "grafo_lista.h"
#include "conectividade.h"
#include "planaridade.h"

int main(){

    // Número de vértices do grafo
    int n = 11;

    // Inicializa um grafo com 11 vértices, numerados de 0 até 10
    GrafoLista *g = inicializarGrafo(11);

    /*
     * Insere as arestas do grafo.
     *
     * Como inserirAresta() cria a conexão nos dois sentidos,
     * o grafo é não direcionado.
     *
     * As três primeiras arestas formam um ciclo:
     * 0 -> 1 -> 2 -> 0
     */
    inserirAresta(g, 0, 1);
    inserirAresta(g, 0, 2);
    inserirAresta(g, 1, 2);

    /*
     * Conecta o primeiro ciclo ao segundo conjunto de vértices.
     *
     * As arestas 3-4, 4-5 e 5-3 formam outro ciclo.
     */
    inserirAresta(g, 1, 3);
    inserirAresta(g, 3, 4);
    inserirAresta(g, 4, 5);
    inserirAresta(g, 5, 3);

    /*
     * Conecta o segundo ciclo ao terceiro.
     *
     * As arestas 6-7, 7-8 e 8-6 formam um terceiro ciclo.
     */
    inserirAresta(g, 4, 6);
    inserirAresta(g, 6, 7);
    inserirAresta(g, 7, 8);
    inserirAresta(g, 8, 6);

    /*
     * Cria uma sequência de vértices depois do terceiro ciclo:
     *
     * 8 -- 9 -- 10
     *
     * Essas conexões são importantes para testar a detecção
     * de pontes e articulações.
     */
    inserirAresta(g, 8, 9);
    inserirAresta(g, 9, 10);

    /*
     * Aloca os vetores utilizados pelo algoritmo de Tarjan.
     *
     * descoberta[u] = momento em que o vértice u foi descoberto
     * low[u]        = menor valor de descoberta alcançável a partir de u
     * visitado[u]   = indica se o vértice já foi visitado
     */
    int *descoberta = calloc(n, sizeof(int));
    int *low = calloc(n, sizeof(int));
    int *visitado = calloc(n, sizeof(int));

    // Contador utilizado para registrar a ordem de descoberta dos vértices
    int tempo = 0;

    /*
     * Procura os vértices de articulação.
     *
     * Começamos pelo vértice 0.
     * O valor -1 indica que 0 é a raiz da DFS e não possui pai.
     */
    printf("Articulações:\n");

    dfs_articulacoes(
        g,
        0,
        -1,
        descoberta,
        low,
        visitado,
        &tempo
    );

    /*
     * Antes de executar uma nova DFS para encontrar pontes,
     * precisamos zerar as informações utilizadas pela DFS anterior.
     */
    tempo = 0;

    for (int i = 0; i < n; i++) {

        // Reinicia o momento de descoberta de cada vértice
        descoberta[i] = 0;

        // Reinicia o valor de low de cada vértice
        low[i] = 0;

        // Marca todos os vértices novamente como não visitados
        visitado[i] = 0;
    }

    /*
     * Procura as pontes do grafo utilizando novamente
     * o algoritmo baseado em DFS e nos valores de low.
     */
    printf("\nPontes:\n");

    detectar_pontes(
        g,
        0,
        -1,
        descoberta,
        low,
        visitado,
        &tempo
    );

    /*
     * Verifica a planaridade do grafo utilizando
     * a função eh_planar_euler().
     */
    printf("\nPlanaridade:\n");

    int planar = eh_planar_euler(g);

    if(planar){
        // O teste considerou o grafo planar
        printf("grafo planar\n");
    } else{
        // O teste considerou o grafo não planar
        printf("grafo nao planar\n");
    }

    /*
     * Libera os vetores alocados dinamicamente
     * para os algoritmos de conectividade.
     */
    free(descoberta);
    free(low);
    free(visitado);

    /*
     * Libera toda a memória utilizada pelo grafo:
     * listas de adjacência, vetor de listas e a struct do grafo.
     */
    liberarGrafo(g);

    return 0;
}