#ifndef COBERTURA_H
#define COBERTURA_H

/* Grafo nao direcionado, com vertices numerados de 0 a n-1. */
typedef struct {
    int u;
    int v;
} Aresta;

/* cobertura[v] diferente de zero indica um vertice selecionado.
 * O chamador reserva n posicoes em cobertura. A entrada nao e alterada.
 * As funcoes de busca retornam o tamanho da cobertura ou -1 em caso de erro.
 * Aceitam n == 0 e m == 0; arestas pode ser NULL quando m == 0.
 */
/* No verificador, os indices das arestas devem caber em cobertura. */
int eh_cobertura(const Aresta arestas[], int m, const int cobertura[]);
int cobertura_gulosa(const Aresta arestas[], int n, int m, int cobertura[]);
int cobertura_minima_bt(const Aresta arestas[], int n, int m, int cobertura[]);

#endif
