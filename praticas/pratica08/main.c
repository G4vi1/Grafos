#include "agm.h"
#include "grafo_matriz.h"
#include <stdio.h>

/* Exibe as arestas escolhidas e seu custo. %lld corresponde ao tipo long long. */
static void mostrar(const char *nome, const Aresta agm[], int quantidade,
                    long long custo) {
    printf("%s\n", nome);
    for (int i = 0; i < quantidade; i++) {
        printf("%d -- %d (peso %d)\n", agm[i].u, agm[i].v, agm[i].peso);
    }
    printf("Custo total: %lld\n\n", custo);
}

/* Exemplo completo: representa um grafo e calcula sua AGM pelos dois algoritmos. */
int main(void) {
    /* Cada tripla contem origem, destino e peso de uma aresta nao direcionada.
     * const impede que este exemplo altere as arestas de entrada. */
    const Aresta arestas[] = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };
    const int n = 4;
    /* Divide o tamanho total do vetor pelo tamanho de um elemento para contar arestas. */
    const int m = (int)(sizeof(arestas) / sizeof(arestas[0]));
    /* Monta a representacao por matriz para visualizar o mesmo grafo. */
    GrafoMatriz *matriz = criar_grafo_matriz(n);
    if (matriz == NULL) {
        fprintf(stderr, "Erro ao criar a matriz.\n");
        return 1;
    }
    /* Insere cada aresta; em caso de erro, libera o grafo antes de encerrar. */
    for (int i = 0; i < m; i++) {
        if (!inserir_aresta_matriz(matriz, arestas[i].u, arestas[i].v,
                                  arestas[i].peso)) {
            liberar_grafo_matriz(matriz);
            return 1;
        }
    }
    imprimir_grafo_matriz(matriz);
    /* A matriz serviu para exibicao e ja pode ser liberada. Prim cria sua lista internamente. */
    liberar_grafo_matriz(matriz);
    printf("\n");
    /* Quatro vertices exigem no maximo tres arestas na AGM (n-1).
     * long long permite somar pesos int sem estourar um acumulador int. */
    Aresta agm[3];
    long long custo;
    /* Kruskal preenche agm e escreve a soma em custo por meio do endereco &custo. */
    int quantidade = kruskal(arestas, n, m, agm, &custo);
    /* Retorno negativo indica erro; stderr e o canal usado para a mensagem. */
    if (quantidade < 0) {
        fprintf(stderr, "Erro ao executar Kruskal.\n");
        return 1;
    }
    mostrar("Kruskal", agm, quantidade, custo);
    /* Reutiliza o vetor de saida para Prim. Neste exemplo, ambos devem custar 19;
     * a ordem das arestas pode ser diferente. */
    quantidade = prim(arestas, n, m, agm, &custo);
    if (quantidade < 0) {
        fprintf(stderr, "Erro ao executar Prim.\n");
        return 1;
    }
    mostrar("Prim", agm, quantidade, custo);
    /* Zero informa ao sistema operacional que a execucao terminou com sucesso. */
    return 0;
}
