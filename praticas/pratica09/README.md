# Pratica 09 - Cobertura de vertices

Implementacao da [issue #18](https://github.com/G4vi1/Grafos/issues/18).
Segue a organizacao modular da pratica 08 e usa um vetor de `Aresta`,
com vertices numerados de zero a n-1, conforme o codigo fornecido.
Inclui `grafo_matriz.c/.h` e `grafo_lista.c/.h` da pratica 08, preservando
seus tipos e operacoes. Cobertura ignora os pesos e considera a presenca
das arestas, inclusive quando o peso e zero.

As funcoes com sufixos `_matriz` e `_lista` recebem essas estruturas e
extraem um vetor de arestas para reutilizar a implementacao comum.
A extracao custa O(n^2) na matriz e O(n+m) na lista, com memoria O(m).
A lista deve conter ambos os sentidos de cada aresta nao direcionada;
um laco precisa de apenas um no. A matriz conserva apenas uma aresta
por par de vertices, enquanto a lista preserva arestas repetidas.

## Algoritmos

- `eh_cobertura`: verifica se cada aresta possui ao menos uma extremidade
  selecionada, em O(m). O chamador deve fornecer indices dentro do vetor.
- `cobertura_gulosa`: recalcula os graus das arestas descobertas e seleciona
  o maior, desempatando pelo menor indice. Custo O(n(n+m)), memoria O(n).
  Produz uma cobertura valida, sem garantia de tamanho minimo.
- `cobertura_minima_bt`: parte da solucao gulosa como limite superior.
  Para uma aresta descoberta (u,v), tenta incluir u e depois v, desfazendo
  cada escolha ao retornar. Toda cobertura precisa conter uma dessas
  extremidades. Ramos que ja atingiram o melhor tamanho sao podados.
  Custo exponencial no pior caso, O(2^n (n+m)), memoria auxiliar O(n).

As buscas validam a entrada, aceitam grafos desconexos, vertices isolados,
lacos e arestas repetidas e retornam -1 para erro. Arestas repetidas contam
separadamente na heuristica. Cada chamada mantem seu proprio estado,
sem vetores globais ou limite fixo de vertices na biblioteca.

## Execucao

```sh
make
make run
make test
```

No Windows com MSYS2 UCRT64, use `mingw32-make` e `./main.exe`.
O GCC precisa estar no PATH. A compilacao usa C11 e trata avisos como erros.

O programa gera um grafo simples reproduzivel para cada n = 5, 8, 10, 12, 15,
monta a matriz e a lista e executa ambos os algoritmos nas duas estruturas.
Exibe as duas coberturas, seus tamanhos, a diferenca de qualidade e os tempos
medios de CPU de 10000 execucoes. Os tempos incluem a extracao das arestas;
o tempo exato tambem inclui a heuristica inicial.
Os tempos variam com a maquina e a resolucao de `clock()`; estes exemplos
nao representam todos os grafos de cada tamanho.

O teste compara o backtracking com enumeracao independente de subconjuntos
em todos os 33867 grafos nao direcionados de zero a cinco vertices,
incluindo lacos. Para n > 0, verifica tambem os adaptadores de matriz e lista
contra os mesmos resultados, usando pesos zero.
Tambem verifica validade e tamanho das duas coberturas,
arestas repetidas e entradas invalidas.
