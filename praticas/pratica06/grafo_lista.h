#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

/* Vertices sao numerados de 0 a n-1. */
typedef struct Aresta {
    int vertice;
    int peso;
    struct Aresta *proximo;
} Aresta;

typedef struct {
    Aresta **lista;
    int num_vertices;
} GrafoListaPonderado;

GrafoListaPonderado *criar_grafo(int num_vertices);
/* Insere uma aresta direcionada. Retorna 0 para argumentos invalidos ou falha. */
int inserir_aresta(GrafoListaPonderado *g, int origem, int destino, int peso);
void liberar_grafo(GrafoListaPonderado *g);

#endif
