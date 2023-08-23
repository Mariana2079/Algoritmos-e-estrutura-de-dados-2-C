/*
Implemente o algoritmo de Prim. A função deve receber um grafo representado por uma lista de adjacência e construir uma árvore geradora mínima, que deve ser construída a partir do vértice "0".
Para a implementação, considere o grafo representado por lista de adjacências, conforme as estruturas apresentadas abaixo:

typedef struct {
   int V; // número de vértices
   int A; // número de arestas
   Lista **adj; // lista de adjacências
}GrafoLA;

typedef struct Cell Cell;

struct Cell{
    int key;
    Cell *next;
};


typedef struct{
    Cell *head;
}Lista;

Input Format
A primeira linha contém o número de vértices. A segunda linha contém a quantidade de arestas (A). Para cada uma das "A" próximas linhas devem der lidos dois números inteiros. sendo os 2 primeiros, a aresta, e o último, o peso da aresta.

Output Format
Imprimir a árvore geradora mínima. Cada linha deve ser impressa no seguinte formato: "v_i: pai[v_i]".
Para o vértice da árvore que não tiver "pai", deve ser impresso o caractere "-" (traço/sinal de menos). Como o algoritmo deve ser iniciada a partir do vértice "0", então a primeira linha sempre será "0: -"

Sample Input 0
9
28
0 1 4
0 7 8
1 0 4
1 2 8
1 7 11
2 1 8
2 3 7
2 5 4
2 8 2
3 2 7
3 4 9
3 5 14
4 3 9
4 5 10
5 2 4
5 3 14
5 4 10
5 6 2
6 5 2
6 7 1
6 8 6
7 0 8
7 1 11
7 6 1
7 8 7
8 2 2
8 6 6
8 7 7

Sample Output 0
0: -
1: 0
2: 1
3: 2
4: 3
5: 2
6: 5
7: 6
8: 2

Explanation 0
Na linha 3 da entrada, 0 e 1 forma uma aresta e o valor 4 é o respectivo peso dessa aresta.
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//agm = arvore geradora minima

typedef struct Cell Cell;

typedef struct {
    int V; // numero de vertices
    int A; // numero de arestas
    Cell** adj; // lista de adjacencias
} GrafoLA;

struct Cell {
    int chave;
    int peso_aresta;
    Cell* prox;
};

typedef struct {
    Cell* head;
} Lista;

void inserir(Cell** ref, int chave, int peso_aresta) {
    Cell* novaCell = (Cell*)malloc(sizeof(Cell));
    novaCell->chave = chave;
    novaCell->peso_aresta = peso_aresta;
    novaCell->prox = *ref;
    *ref = novaCell;
}

GrafoLA* criarGrafoLA(int V) {
    GrafoLA* grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
    grafo->V = V;
    grafo->A = 0;
    grafo->adj = (Cell**)malloc(V * sizeof(Cell*));
    for (int i = 0; i < V; i++) {
        grafo->adj[i] = NULL;
    }
    return grafo;
}

void adicionar_aresta(GrafoLA* grafo, int u, int v, int peso_aresta) {
    inserir(&(grafo->adj[u]), v, peso_aresta);
    inserir(&(grafo->adj[v]), u, peso_aresta);
    grafo->A++;
}

int encontrar_chave_min(int* chave, int* agm, int V) {
    int min = INT_MAX;
    int min_indice = -1; 
    for (int v = 0; v < V; v++) {
        if (!agm[v] && chave[v] < min) {
            min = chave[v];
            min_indice = v;
        }
    }
    return min_indice;
}

void prim(GrafoLA* grafo, int* pai) {
    int V = grafo->V;
    int* chave = (int*)malloc(V * sizeof(int));
    int* agm = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        chave[i] = INT_MAX;
        agm[i] = 0;
        pai[i] = -1;
    }

    chave[0] = 0;
    pai[0] = -1;
 
    for (int qtde = 0; qtde < V - 1; qtde++) {
        int u = encontrar_chave_min(chave, agm, V);
        agm[u] = 1;

        Cell* atual = grafo->adj[u];
        while (atual != NULL) {
            int v = atual->chave;
            int peso_aresta = atual->peso_aresta;

            if (!agm[v] && peso_aresta < chave[v]) {
                pai[v] = u;
                chave[v] = peso_aresta;
            }

            atual = atual->prox;
        }
    }

    free(chave);
    free(agm);
}

void imprimir(int* pai, int V) {
    for (int v = 0; v < V; v++) {
        printf("%d: ", v);
        if (pai[v] == -1) {
            printf("-\n");
        } else {
            printf("%d\n", pai[v]);
        }
    }
}

int main() {
    int V, A;
    scanf("%d", &V);
    scanf("%d", &A);

    GrafoLA* grafo = criarGrafoLA(V);
    for (int i = 0; i < A; i++) {
        int u, v, peso_aresta;
        scanf("%d %d %d", &u, &v, &peso_aresta);
        adicionar_aresta(grafo, u, v, peso_aresta);
    }

    int* pai = (int*)malloc(V * sizeof(int));
    prim(grafo, pai);
    imprimir(pai, V);

    free(pai);
    for (int i = 0; i < V; i++) {
        Cell* atual = grafo->adj[i];
        while (atual != NULL) {
            Cell* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(grafo->adj);
    free(grafo);

    return 0;
}