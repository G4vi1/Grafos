/* Protege as declaracoes contra inclusoes repetidas. */
#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

/* No de uma lista encadeada: representa um vizinho de um vertice. */
typedef struct No {
    int vertice; /* Destino do arco armazenado neste no. */
    int peso; /* Custo da ligacao ate esse vizinho. */
    struct No *proximo; /* Proximo vizinho; NULL encerra a lista. */
} No;

/* O indice no vetor lista identifica a origem; cada elemento aponta para
 * o primeiro vizinho. A representacao ocupa O(V+E) de memoria. */
typedef struct {
    No **lista;
    int num_vertices;
} GrafoLista;

/* Retorna um grafo vazio ou NULL para tamanho invalido/falha de alocacao. */
GrafoLista *criar_grafo(int num_vertices);
/* Insere uma aresta direcionada; aceita pesos negativos.
 * Retorna 1 no sucesso ou 0 para argumentos invalidos/falha de alocacao.
 */
int inserir_aresta(GrafoLista *g, int origem, int destino, int peso);
/* Libera todos os nos, o vetor de listas e a estrutura do grafo. */
void liberar_grafo(GrafoLista *g);

#endif
