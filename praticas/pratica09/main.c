#include "cobertura.h"
#include <stdio.h>
#include <time.h>

#define MAX_VERTICES 15
#define MAX_ARESTAS (MAX_VERTICES * (MAX_VERTICES - 1) / 2)
#define REPETICOES 10000

static void mostrar(const char *nome, const int cobertura[], int n, int tamanho) {
    printf("%s: {", nome);
    const char *separador = "";
    for (int v = 0; v < n; v++) {
        if (cobertura[v]) {
            printf("%s%d", separador, v);
            separador = ", ";
        }
    }
    printf("} (tamanho %d)\n", tamanho);
}

/* Gera grafos simples reproduziveis, sem depender da semente de rand().
 * Um caminho garante conexidade; a formula acrescenta outras arestas. */
static int gerar_grafo(Aresta arestas[], int n) {
    int m = 0;
    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (v == u + 1 || (u * 17 + v * 31 + u * v) % 5 < 2) {
                arestas[m++] = (Aresta){u, v};
            }
        }
    }
    return m;
}

int main(void) {
    const int tamanhos[] = {5, 8, 10, 12, 15};
    printf("Cobertura de vertices: backtracking e maior grau restante\n");
    printf("Tempos medios de CPU em microssegundos (%d repeticoes).\n", REPETICOES);
    printf("O tempo do BT inclui a heuristica usada como limite inicial.\n");
    for (int i = 0; i < 5; i++) {
        int n = tamanhos[i];
        Aresta arestas[MAX_ARESTAS];
        int exata[MAX_VERTICES], gulosa[MAX_VERTICES];
        int m = gerar_grafo(arestas, n);
        GrafoMatriz *matriz = criar_grafo_matriz(n);
        GrafoLista *lista = criar_grafo(n);
        if (matriz == NULL || lista == NULL) {
            liberar_grafo_matriz(matriz);
            liberar_grafo(lista);
            return 1;
        }
        for (int a = 0; a < m; a++) {
            int u = arestas[a].u, v = arestas[a].v;
            if (!inserir_aresta_matriz(matriz, u, v, 1) ||
                !inserir_aresta(lista, u, v, 1) ||
                !inserir_aresta(lista, v, u, 1)) {
                liberar_grafo_matriz(matriz);
                liberar_grafo(lista);
                return 1;
            }
        }
        printf("\nn = %d, m = %d\n", n, m);
        for (int representacao = 0; representacao < 2; representacao++) {
            printf("Representacao: %s\n", representacao == 0 ? "matriz" : "lista");
            int tamanho_bt = -1, tamanho_gulosa = -1;
            clock_t inicio = clock();
            for (int r = 0; r < REPETICOES; r++) {
                tamanho_bt = representacao == 0
                    ? cobertura_minima_bt_matriz(matriz, exata)
                    : cobertura_minima_bt_lista(lista, exata);
                if (tamanho_bt < 0) {
                    liberar_grafo_matriz(matriz); liberar_grafo(lista); return 1;
                }
            }
            clock_t fim_bt = clock();
            for (int r = 0; r < REPETICOES; r++) {
                tamanho_gulosa = representacao == 0
                    ? cobertura_gulosa_matriz(matriz, gulosa)
                    : cobertura_gulosa_lista(lista, gulosa);
                if (tamanho_gulosa < 0) {
                    liberar_grafo_matriz(matriz); liberar_grafo(lista); return 1;
                }
            }
            clock_t fim_gulosa = clock();
            if (eh_cobertura_matriz(matriz, exata) != 1 ||
                eh_cobertura_lista(lista, gulosa) != 1) {
                fprintf(stderr, "Erro: cobertura invalida.\n");
                liberar_grafo_matriz(matriz); liberar_grafo(lista);
                return 1;
            }
            mostrar("Backtracking", exata, n, tamanho_bt);
            mostrar("Gulosa", gulosa, n, tamanho_gulosa);
            printf("Tempo BT: %.3f us | Tempo gulosa: %.3f us | Excesso guloso: %d\n",
                   1e6 * (double)(fim_bt - inicio) / CLOCKS_PER_SEC / REPETICOES,
                   1e6 * (double)(fim_gulosa - fim_bt) / CLOCKS_PER_SEC / REPETICOES,
                   tamanho_gulosa - tamanho_bt);
        }
        liberar_grafo_matriz(matriz);
        liberar_grafo(lista);
    }
    printf("\nBT garante o minimo; a gulosa pode selecionar mais vertices.\n");
    printf("Tempos dependem da maquina; zero pode indicar resolucao insuficiente.\n");
    return 0;
}
