#include "dag.h"
#include <stdlib.h>
#include <string.h>

//Funções da fila

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

//===========================================================================

//Funções da pilha

Pilha *inicializarPilha(int capacidade) {
    //Aloca na heap uma única struct do tipo Pilha e retorna um ponteiro para ela
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    //Aloca na heap um vetor de inteiros com tamanho igual a capacidade da pilha
    p->dados = (int *)malloc(capacidade * sizeof(int));
    //Atribui a capacidade da pilha ao campo capacidade da struct Pilha
    p->capacidade = capacidade;
    /* Inicializa o topo como -1, indicando que a pilha está vazia*/
    p->topo = -1;
    return p;
}

void empilhar(Pilha *p, int valor) {

    // Verifica se a pilha está cheia antes de empilhar
    if (p->topo < p->capacidade - 1) {
        p->topo++;
        p->dados[p->topo] = valor;
    }
}

int desempilhar(Pilha *p) {
    if(p->topo >= 0){
        /*Praticamente o processo inverso de empilhar pois
        * pega o valor do topo da pilha e depois decrementa o topo
        */
        int valor = p->dados[p->topo];
        (p->topo)--;
        return valor;
    }
    return -1; // Retorna -1 se a pilha estiver vazia
}

void liberarPilha(Pilha *p) {
    //Libera a memória alocada para o vetor de dados da pilha
    free(p->dados);
    //Libera a memória alocada para a struct Pilha
    free(p);
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int n = g->numVertices;
    int *grau_entrada = (int *)calloc(n, sizeof(int));

    for (int u = 0; u < n; u++) {
        No *no = g->listaAdj[u];
        while (no != NULL) {
            grau_entrada[no->vertice]++;
            no = no->prox;
        }
    }

    Fila *fila = inicializarFila(n);
    for (int i = 0; i < n; i++) {
        if (grau_entrada[i] == 0) enfileirar(fila, i);
    }

    int *ordenacao = (int *)malloc(n * sizeof(int));
    int idx = 0;

    while (fila->tamanho > 0) {
        int u = desenfileirar(fila);
        ordenacao[idx++] = u;

        No *no = g->listaAdj[u];
        while (no != NULL) {
            int v = no->vertice;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) enfileirar(fila, v);
            no = no->prox;
        }
    }

    free(grau_entrada);
    liberarFila(fila);

    if (idx != n) {
        free(ordenacao);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = idx;
    return ordenacao;
}

int dfs_topologica(GrafoLista *g, int u, int *cor, Pilha *p) {
    cor[u] = 1; /* cinza: em processamento */

    No *atual = g->listaAdj[u];
    while (atual != NULL) {
        int v = atual->vertice;
        if (cor[v] == 1) {
            return 0; /* vizinho em processamento -> ciclo */
        }
        if (cor[v] == 0) {
            if (!dfs_topologica(g, v, cor, p)) {
                return 0; /* ciclo encontrado mais fundo na recursão */
            }
        }
        atual = atual->prox;
    }

    cor[u] = 2; /* preto: finalizado */
    empilhar(p, u); /* empilha na SAÍDA da DFS */
    return 1;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int n = g->numVertices;
    int *cor = (int *)calloc(n, sizeof(int)); /* tudo começa como 0 (branco) */
    Pilha *p = inicializarPilha(n);

    for (int i = 0; i < n; i++) {
        if (cor[i] == 0) {
            if (!dfs_topologica(g, i, cor, p)) {
                free(cor);
                liberarPilha(p);
                *tamanho = 0;
                return NULL;
            }
        }
    }

    free(cor);

    int *ordenacao = (int *)malloc(n * sizeof(int));
    int idx = 0;
    while (p->topo >= 0) {
        ordenacao[idx++] = desempilhar(p);
    }

    liberarPilha(p);

    *tamanho = idx;
    return ordenacao;
}

int eh_dag(GrafoLista *g) {
    int tamanho;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);

    if (ordem != NULL) {
        free(ordem);
        return 1; /* sem ciclo -> é DAG */
    }

    return 0; /* tem ciclo -> não é DAG */
}