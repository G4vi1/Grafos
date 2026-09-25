#include "busca_largura.h"
#include "grafo_lista.h"
#include <stdlib.h>
#include <stdio.h>


// Função para inicializar a fila, recebe a capacidade para alocar memória para a fila.
Fila* inicializarFila(int capacidade){
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->dados = (int *)malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

// Função para enfileirar um valor na fila,
void enfileirar(Fila *f, int valor){
    if(f->tamanho == f->capacidade) return;
    f->dados[f->fim++] = valor;
    if(f->fim == f->capacidade) f->fim = 0;
    f->tamanho++;
}

// Função para desenfileirar um valor da fila,
int desenfileirar(Fila *f){
    if(f->tamanho == 0) return -1;
    int valor = f->dados[f->inicio++];
    if(f->inicio == f->capacidade) f->inicio = 0;
    f->tamanho--;
    return valor;
}


// Função para liberar a memória alocada na fila.
void liberarFila(Fila *f){
    free(f->dados); 
    free(f);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred){
    
    // Inicializa a fila
    Fila *f = inicializarFila(g->numVertices);
    // Define a distância do vértice de origem como 0 e enfileira ele
    dist[origem] = 0;
    pred[origem] = -1; // O vértice de origem não tem pai
    // Enfileira o vértice de origem na fila
    enfileirar(f, origem);

    // Enquanto a fila não estiver vazia, continue a busca em largura

    while(f->tamanho > 0){
        int u = desenfileirar(f);
        No *no = g->listaAdj[u];
        while(no != NULL){
            int v = no->vertice;
            if(dist[v] == -1){ // Se o vértice ainda não foi visitado
                dist[v] = dist[u] + 1; // Atualiza a distância
                pred[v] = u; // Atualiza o predecessor
                enfileirar(f, v); // Enfileira o vértice
            }
            no = no->prox;
        }
    }
    liberarFila(f); // Libera a memória da fila após a execução da BFS
}

// Função para verificar se o grafo é bipartido usando BFS com 2-coloração
int eh_bipartido(GrafoLista *g){

    // -1 = sem cor ainda, 0 e 1 são as duas cores possíveis
    int *cor = (int *)malloc(g->numVertices * sizeof(int));
    for(int i = 0; i < g->numVertices; i++){
        cor[i] = -1;
    }

    // Precisa testar a partir de todo vértice não visitado,
    // pois o grafo pode ter vários componentes desconexos
    for(int inicio = 0; inicio < g->numVertices; inicio++){

        if(cor[inicio] != -1) continue; // já colorido, pula

        // BFS manual a partir de "inicio"
        Fila *f = inicializarFila(g->numVertices);
        cor[inicio] = 0; // primeira cor do componente
        enfileirar(f, inicio);

        while(f->tamanho > 0){
            int u = desenfileirar(f);
            No *no = g->listaAdj[u];

            while(no != NULL){
                int v = no->vertice;

                if(cor[v] == -1){
                    // ainda não colorido: pinta com a cor oposta de u
                    cor[v] = 1 - cor[u];
                    enfileirar(f, v);
                } else if(cor[v] == cor[u]){
                    // vizinho com a MESMA cor -> não é bipartido
                    liberarFila(f);
                    free(cor);
                    return 0;
                }

                no = no->prox;
            }
        }

        liberarFila(f);
    }

    free(cor);
    return 1; // passou por tudo sem conflito -> é bipartido
}

int contar_componentes(GrafoLista *g){
    int *dist = (int *)malloc(g->numVertices * sizeof(int));
    int *pred = (int *)malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; i++){
        dist[i] = -1;
        pred[i] = -1;
    }
    int componentes = 0;
    for (int i = 0; i < g->numVertices; i++){
        if (dist[i] == -1) {
            bfs(g, i, dist, pred);
            componentes++;
        }
    }
    free(dist);
    free(pred);
    return componentes;
}