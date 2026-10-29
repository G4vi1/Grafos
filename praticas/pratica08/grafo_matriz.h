/* Protege as declaracoes contra inclusoes repetidas. */
#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

/* Grafo nao direcionado com pesos. A presenca da aresta e separada
 * do peso para permitir pesos zero e negativos.
 */
typedef struct {
    int n; /* Numero de vertices e dimensao das matrizes. */
    int **adj; /* adj[u][v] guarda o peso quando a aresta existe. */
    unsigned char **presente; /* 1 indica aresta; 0 indica ausencia. */
} GrafoMatriz;

/* Cria matrizes vazias; retorna NULL para n invalido ou falha de alocacao. */
GrafoMatriz *criar_grafo_matriz(int n);
/* Arestas repetidas conservam o menor peso, adequado para a AGM. */
int inserir_aresta_matriz(GrafoMatriz *g, int u, int v, int peso);
/* Remove a ligacao nos dois sentidos. */
void remover_aresta_matriz(GrafoMatriz *g, int u, int v);
/* Conta as incidencias do vertice; retorna -1 para vertice invalido. */
int grau_matriz(GrafoMatriz *g, int v);
/* Retorna 1 se existe ligacao; 0 se nao existe ou os argumentos sao invalidos. */
int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v);
/* Libera todas as linhas e estruturas auxiliares. */
void liberar_grafo_matriz(GrafoMatriz *g);
/* Imprime pesos e usa ponto para celulas sem aresta. */
void imprimir_grafo_matriz(GrafoMatriz *g);

#endif
