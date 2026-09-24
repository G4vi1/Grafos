#include "grafo_lista.h"
#include "busca_profundidade.h"
#include <stdlib.h>

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

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *tempo_inicio, int *tempo_fim, int *tempo_geral, Pilha *p) {
    visitado[u] = 1; // Marca o vértice u como visitado
    empilhar(p, u); // Empilha o vértice u na pilha
    // Incrementa o tempo geral e registra o tempo de início do vértice u
    (*tempo_geral)++;
    //quando o vértice u é visitado, o tempo de início é registrado
    tempo_inicio[u] = *tempo_geral;
    No *no = g->listaAdj[u]; // Obtém a lista de adjacência do vértice u
    while (no != NULL) {
        // Obtém o vértice adjacente
        int v = no->vertice; 
        if (!visitado[v]) {
            // Chamada recursiva para o vértice v
            dfs_recursiva(g, v, visitado, tempo_inicio, tempo_fim, tempo_geral, p); 
        }
        // Avança para o próximo nó da lista de adjacência
        no = no->prox; 
    }
    // Incrementa o tempo geral e registra o tempo de fim do vértice u
    (*tempo_geral)++;
    // Registra o tempo de fim do vértice u
    tempo_fim[u] = *tempo_geral; 
}

int dfs_ciclo(GrafoLista *g, int u, int *visitado, int pai) {
    visitado[u] = 1; // Marca o vértice u como visitado
    No *no = g->listaAdj[u]; // Obtém a lista de adjacência do vértice u
    while (no != NULL) {
        int v = no->vertice; // Obtém o vértice adjacente
        if (!visitado[v]) {
            // Chamada recursiva para o vértice v
            if (dfs_ciclo(g, v, visitado, u)) {
                return 1; // Retorna 1 se um ciclo for encontrado
            }
        } else if (v != pai) {
            return 1; // Retorna 1 se um ciclo for encontrado
        }
        no = no->prox; // Avança para o próximo nó da lista de adjacência
    }
    return 0; // Retorna 0 se nenhum ciclo for encontrado
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = (int *)calloc(g->numVertices, sizeof(int)); // Aloca e inicializa o vetor de visitados
    for (int i = 0; i < g->numVertices; i++) {
        if (!visitado[i]) {
            // Chamada para verificar ciclos a partir do vértice i
            if (dfs_ciclo(g, i, visitado, -1)) {
                free(visitado); // Libera a memória alocada para o vetor de visitados
                return 1; // Retorna 1 se um ciclo for encontrado
            }
        }
    }
    free(visitado); // Libera a memória alocada para o vetor de visitados
    return 0; // Retorna 0 se nenhum ciclo for encontrado
}
