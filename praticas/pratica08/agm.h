/* Guardas de inclusao evitam definir os mesmos tipos varias vezes. */
#ifndef AGM_H
#define AGM_H

/* DSU (Union-Find) representa conjuntos disjuntos para detectar ciclos.
 * pai[x] aponta para o ancestral de x; rank[x] orienta a uniao das raizes.
 * n e a quantidade de vertices alocados nos dois vetores. */
typedef struct {
    int *pai, *rank;
    int n;
} DSU;

/* Aresta ponderada: u e v sao as extremidades; peso e o custo da ligacao. */
typedef struct {
    int u, v, peso;
} Aresta;

/* Retorna 1 em caso de sucesso e 0 em caso de erro. */
int inicializar_dsu(DSU *d, int n);
/* Libera os vetores e zera os campos da DSU. */
void liberar_dsu(DSU *d);
/* Os vertices devem estar no intervalo [0, d->n). */
/* Retorna o representante e comprime o caminho percorrido. */
int find(DSU *d, int x);
/* Retorna 1 se uniu conjuntos distintos ou 0 se ja pertenciam ao mesmo conjunto. */
int unir(DSU *d, int x, int y);

/* Grafo nao direcionado, vertices de 0 a n-1, n > 0 e m >= 0.
 * O chamador reserva n-1 posicoes em agm (NULL permitido se n == 1).
 * Retornam a quantidade de arestas selecionadas, ou -1 em caso de erro.
 * Se o grafo for desconexo, produzem uma floresta geradora minima.
 * custo_total recebe a soma dos pesos; a entrada nao e modificada.
 */
/* Seleciona arestas ordenadas por peso, rejeitando ciclos com a DSU. */
int kruskal(const Aresta arestas[], int n, int m,
            Aresta agm[], long long *custo_total);
/* Usa lista de adjacencia e min-heap para expandir cada componente. */
int prim(const Aresta arestas[], int n, int m,
         Aresta agm[], long long *custo_total);

#endif
