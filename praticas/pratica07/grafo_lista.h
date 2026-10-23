#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#define MAX_VERTICES 100

typedef struct No {
    int vertice;
    int peso;
    struct No *proximo;
} No;

typedef struct {
    No **lista;
    int num_vertices;
} GrafoLista;

GrafoLista *criar_grafo(int num_vertices);
/* Insere uma aresta direcionada; aceita pesos negativos.
 * Retorna 1 no sucesso ou 0 para argumentos invalidos/falha de alocacao.
 */
int inserir_aresta(GrafoLista *g, int origem, int destino, int peso);
void liberar_grafo(GrafoLista *g);

#endif
