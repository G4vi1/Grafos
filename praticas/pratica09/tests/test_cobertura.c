#include "../cobertura.h"
#include <assert.h>
#include <stdio.h>

/* Oraculo independente: enumera todos os subconjuntos de vertices. */
static int minimo_enum(const Aresta arestas[], int n, int m) {
    int melhor = n;
    for (unsigned conjunto = 0; conjunto < (1u << n); conjunto++) {
        int tamanho = 0, valido = 1;
        for (int v = 0; v < n; v++) tamanho += (conjunto >> v) & 1u;
        for (int i = 0; i < m; i++) {
            if (!(conjunto & (1u << arestas[i].u)) &&
                !(conjunto & (1u << arestas[i].v))) valido = 0;
        }
        if (valido && tamanho < melhor) melhor = tamanho;
    }
    return melhor;
}

static int contar(const int cobertura[], int n) {
    int total = 0;
    for (int v = 0; v < n; v++) total += cobertura[v] != 0;
    return total;
}

int main(void) {
    int exata[5], gulosa[5];
    unsigned casos = 0;
    for (int n = 0; n <= 5; n++) {
        Aresta possiveis[15], arestas[15];
        int quantidade = 0;
        for (int u = 0; u < n; u++) {
            for (int v = u; v < n; v++) possiveis[quantidade++] = (Aresta){u, v};
        }
        for (unsigned mascara = 0; mascara < (1u << quantidade); mascara++) {
            int m = 0;
            for (int i = 0; i < quantidade; i++) {
                if (mascara & (1u << i)) arestas[m++] = possiveis[i];
            }
            int bt = cobertura_minima_bt(arestas, n, m, exata);
            int gr = cobertura_gulosa(arestas, n, m, gulosa);
            assert(bt == minimo_enum(arestas, n, m));
            assert(gr >= bt && gr <= n);
            assert(contar(exata, n) == bt && contar(gulosa, n) == gr);
            assert(eh_cobertura(arestas, m, exata));
            assert(eh_cobertura(arestas, m, gulosa));
            casos++;
        }
    }
    Aresta invalida[] = {{0, 5}};
    Aresta repetidas[] = {{0, 1}, {0, 1}, {1, 0}, {2, 2}};
    assert(cobertura_minima_bt(repetidas, 5, 4, exata) == 2);
    assert(cobertura_gulosa(repetidas, 5, 4, gulosa) == 2);
    assert(cobertura_minima_bt(invalida, 5, 1, exata) == -1);
    assert(cobertura_gulosa(NULL, 5, 1, gulosa) == -1);
    assert(cobertura_minima_bt(NULL, 0, 0, NULL) == 0);
    assert(cobertura_gulosa(NULL, -1, 0, gulosa) == -1);
    assert(eh_cobertura(NULL, 0, NULL));
    assert(!eh_cobertura(NULL, 1, NULL));
    printf("OK: %u grafos e casos de entrada validados.\n", casos);
    return 0;
}
