#include "agm.h"
#include "grafo_lista.h"

/* limits.h fornece LLONG_MAX; stdlib.h fornece alocacao e qsort;
 * string.h fornece memcpy para copiar as arestas. */
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* Cria n conjuntos separados. Cada vertice comeca como seu proprio
 * representante. Use uma DSU nova ou previamente liberada. */
int inicializar_dsu(DSU *d, int n) {
    if (d == NULL) return 0;
    /* O literal composto zera os campos, deixando a estrutura em estado conhecido. */
    *d = (DSU){0};
    if (n <= 0) return 0;
    /* Reserva os vetores; calloc inicia os ranks com zero. */
    d->pai = calloc((size_t)n, sizeof(int));
    d->rank = calloc((size_t)n, sizeof(int));
    /* Se uma alocacao falhar, libera inclusive a outra, caso tenha funcionado. */
    if (d->pai == NULL || d->rank == NULL) {
        liberar_dsu(d);
        return 0;
    }
    d->n = n;
    /* Uma raiz e identificada por pai[i] == i. */
    for (int i = 0; i < n; i++) d->pai[i] = i;
    return 1;
}

/* Devolve os dois vetores ao sistema e elimina os ponteiros antigos. */
void liberar_dsu(DSU *d) {
    if (d == NULL) return;
    free(d->pai);
    free(d->rank);
    *d = (DSU){0};
}

int find(DSU *d, int x) {
    /* Se x nao e raiz, busca a raiz recursivamente e grava o resultado em
     * pai[x]. Assim, as proximas consultas percorrem menos elementos.
     * Quando pai[x] == x, a recursao termina. */
    if (d->pai[x] != x) d->pai[x] = find(d, d->pai[x]);
    return d->pai[x];
}

/* Une dois conjuntos e retorna 1; retorna 0 se ja estavam unidos.
 * Em Kruskal, essa resposta indica se a aresta formaria um ciclo. */
int unir(DSU *d, int x, int y) {
    /* Compara representantes, pois vertices diferentes podem estar no mesmo conjunto. */
    int a = find(d, x);
    int b = find(d, y);
    if (a == b) return 0;
    /* Liga a raiz de menor rank a de maior rank para limitar a altura.
     * Rank e um limite para a altura, nao o numero de vertices. */
    if (d->rank[a] < d->rank[b]) {
        d->pai[a] = b;
    } else {
        d->pai[b] = a;
        /* O rank so aumenta quando as duas raizes tinham o mesmo rank. */
        if (d->rank[a] == d->rank[b]) d->rank[a]++;
    }
    return 1;
}

/* Funcao interna (static): confere argumentos antes de acessar os vetores.
 * A capacidade do vetor de saida e responsabilidade do chamador. */
static int validar(const Aresta arestas[], int n, int m,
                   Aresta agm[], long long *custo_total) {
    if (n <= 0 || m < 0 || custo_total == NULL ||
        (n > 1 && agm == NULL) || (m > 0 && arestas == NULL)) return 0;
    /* Cada extremidade precisa identificar um vertice existente. */
    for (int i = 0; i < m; i++) {
        if (arestas[i].u < 0 || arestas[i].u >= n ||
            arestas[i].v < 0 || arestas[i].v >= n) return 0;
    }
    return 1;
}

/* Comparador de qsort: recebe ponteiros genericos e interpreta-os como
 * arestas. Retorna -1, 0 ou 1 para ordenar por peso crescente. */
static int comparar(const void *a, const void *b) {
    const Aresta *x = a;
    const Aresta *y = b;
    /* Evita overflow ao comparar pesos extremos. */
    return (x->peso > y->peso) - (x->peso < y->peso);
}

/* Kruskal escolhe as arestas mais leves que conectam componentes distintas.
 * A ordenacao custa O(E log E); a inicializacao da DSU tambem custa O(V). */
int kruskal(const Aresta arestas[], int n, int m,
            Aresta agm[], long long *custo_total) {
    if (!validar(arestas, n, m, agm, custo_total)) return -1;
    *custo_total = 0;
    DSU d;
    if (!inicializar_dsu(&d, n)) return -1;
    /* Ordena uma copia para preservar a ordem do vetor recebido. */
    Aresta *ordenadas = NULL;
    if (m > 0) {
        ordenadas = calloc((size_t)m, sizeof(Aresta));
        if (ordenadas == NULL) {
            liberar_dsu(&d);
            return -1;
        }
        /* Copia m estruturas inteiras e ordena a copia pelo comparador de pesos. */
        memcpy(ordenadas, arestas, (size_t)m * sizeof(Aresta));
        qsort(ordenadas, (size_t)m, sizeof(Aresta), comparar);
    }
    /* Uma arvore com n vertices tem n-1 arestas. Se o grafo for desconexo,
     * o vetor termina antes e o resultado sera uma floresta minima. */
    int quantidade = 0;
    for (int i = 0; i < m && quantidade < n - 1; i++) {
        /* Aceita apenas arestas entre conjuntos diferentes, evitando ciclos. */
        if (unir(&d, ordenadas[i].u, ordenadas[i].v)) {
            agm[quantidade++] = ordenadas[i];
            *custo_total += ordenadas[i].peso;
        }
    }
    /* O resultado fica em agm; as estruturas auxiliares podem ser liberadas. */
    free(ordenadas);
    liberar_dsu(&d);
    return quantidade;
}

/* Heap binario minimo indexado: a raiz contem o vertice de menor chave.
 * vertices[i] informa quem ocupa a posicao i; posicao[v] faz o caminho inverso.
 * chave[v] guarda o menor peso conhecido para ligar v a arvore.
 * tamanho conta apenas os vertices ainda nao extraidos. */
typedef struct {
    int *vertices, *posicao;
    long long *chave;
    int tamanho;
} MinHeap;

/* Troca duas posicoes e atualiza o indice inverso. Sem essa atualizacao,
 * diminuir_chave poderia modificar a posicao de outro vertice. */
static void trocar(MinHeap *h, int a, int b) {
    int temp = h->vertices[a];
    h->vertices[a] = h->vertices[b];
    h->vertices[b] = temp;
    h->posicao[h->vertices[a]] = a;
    h->posicao[h->vertices[b]] = b;
}

/* Uma chave menor pode violar a ordem com o pai; sobe o vertice ate
 * restaurar o heap. Cada subida percorre no maximo O(log V) niveis. */
static void diminuir_chave(MinHeap *h, int v, long long valor) {
    h->chave[v] = valor;
    int i = h->posicao[v];
    while (i > 0) {
        /* Em um vetor iniciado em zero, esta e a posicao do pai no heap. */
        int pai = (i - 1) / 2;
        if (h->chave[h->vertices[pai]] <= h->chave[h->vertices[i]]) break;
        trocar(h, pai, i);
        i = pai;
    }
}

/* Remove a raiz e coloca o ultimo elemento em seu lugar. Depois desce
 * esse elemento, trocando com o menor filho, em O(log V). */
static int extrair_minimo(MinHeap *h) {
    int v = h->vertices[0];
    trocar(h, 0, h->tamanho - 1);
    h->tamanho--;
    h->posicao[v] = -1; /* Vertice ja incluido na floresta. */
    int i = 0;
    /* Apenas indices menores que tamanho/2 possuem filhos. */
    while (i < h->tamanho / 2) {
        /* O filho esquerdo fica em 2*i+1; o direito, quando existe, em 2*i+2. */
        int filho = 2 * i + 1;
        if (filho + 1 < h->tamanho &&
            h->chave[h->vertices[filho + 1]] < h->chave[h->vertices[filho]]) filho++;
        if (h->chave[h->vertices[i]] <= h->chave[h->vertices[filho]]) break;
        trocar(h, i, filho);
        i = filho;
    }
    return v;
}

/* Prim expande a arvore pela ligacao de menor peso. A lista permite
 * percorrer somente os vizinhos e o heap atualiza prioridades em O(log V),
 * resultando em O((V+E) log V), com memoria auxiliar O(V+E). */
int prim(const Aresta arestas[], int n, int m,
         Aresta agm[], long long *custo_total) {
    if (!validar(arestas, n, m, agm, custo_total)) return -1;
    *custo_total = 0;
    /* Converte as arestas em listas e reserva o pai de cada vertice na AGM.
     * Esse pai e independente do pai usado pela DSU de Kruskal. */
    GrafoLista *g = criar_grafo(n);
    int *pai = calloc((size_t)n, sizeof(int));
    MinHeap h = {
        .vertices = calloc((size_t)n, sizeof(int)),
        .posicao = calloc((size_t)n, sizeof(int)),
        .chave = calloc((size_t)n, sizeof(long long)),
        .tamanho = n
    };
    /* Mantem o codigo de erro ate todas as alocacoes e insercoes terminarem.
     * goto liberar centraliza a limpeza tambem em caso de falha parcial. */
    int quantidade = -1;
    if (g == NULL || pai == NULL || h.vertices == NULL ||
        h.posicao == NULL || h.chave == NULL) goto liberar;

    for (int i = 0; i < m; i++) {
        int u = arestas[i].u, v = arestas[i].v;
        /* A lista insere arcos; a AGM usa arestas nao direcionadas. */
        if (!inserir_aresta(g, u, v, arestas[i].peso) ||
            !inserir_aresta(g, v, u, arestas[i].peso)) goto liberar;
    }
    /* Inicialmente, nenhum vertice possui ligacao conhecida. LLONG_MAX e
     * maior que qualquer peso int, inclusive INT_MAX. Com chaves iguais,
     * a ordem inicial dos vertices ja satisfaz a propriedade do heap. */
    for (int v = 0; v < n; v++) {
        h.vertices[v] = v;
        h.posicao[v] = v;
        h.chave[v] = LLONG_MAX;
        pai[v] = -1;
    }
    /* Escolhe o vertice 0 como primeira raiz, sem custo de entrada. */
    diminuir_chave(&h, 0, 0);
    quantidade = 0;
    /* Cada extracao fixa um vertice. O laco tambem visita componentes isoladas. */
    while (h.tamanho > 0) {
        int u = extrair_minimo(&h);
        /* Se nao existe pai, u e a raiz de uma componente e nao adiciona
         * aresta nem custo. Depois da primeira componente, uma chave
         * infinita indica o inicio de outra componente desconexa. */
        if (pai[u] != -1) {
            agm[quantidade++] = (Aresta){pai[u], u, (int)h.chave[u]};
            *custo_total += h.chave[u];
        }
        /* Examina cada vizinho de u para procurar uma ligacao mais barata. */
        for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
            int v = no->vertice;
            /* Vertices extraidos nao voltam ao heap. Para os restantes, troca
             * a ligacao apenas se o peso melhorar a chave atual. */
            if (h.posicao[v] != -1 && no->peso < h.chave[v]) {
                pai[v] = u;
                diminuir_chave(&h, v, no->peso);
            }
        }
    }

/* Libera todos os recursos temporarios; agm pertence ao chamador. */
liberar:
    liberar_grafo(g);
    free(pai);
    free(h.vertices);
    free(h.posicao);
    free(h.chave);
    return quantidade;
}
