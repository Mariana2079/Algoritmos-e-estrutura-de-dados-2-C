/*
Implemente o algoritmo de Dijkstra. 
A função deve receber um grafo representado por uma lista de adjacência e construir uma árvore de caminhos mínimos, que deve ser construída a partir do vértice "0".
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

A primeira linha contém o número de vértices. A segunda linha contém a quantidade de arestas (A). 
Para cada uma das "A" próximas linhas devem der lidos dois números inteiros. sendo os 2 primeiros, a aresta, e o último, o peso da aresta.

Output Format
Imprimir a árvore de caminhos mínimos. Cada linha deve ser impressa no seguinte formato: "v_i: pai[v_i]".
Para o vértice da árvore que não tiver "pai", deve ser impresso o caractere "-" (traço/sinal de menos). Como o algoritmo deve ser iniciada a partir do vértice "0", então a primeira linha sempre será "0: -"

Sample Input 0
6
12
0 1 10
0 2 5
1 2 2
1 3 1
2 1 3
2 3 9
2 4 2
3 4 4
3 5 2
4 0 7
4 3 6
4 5 5

Sample Output 0
0: -
1: 2
2: 0
3: 1
4: 2
5: 3

Explanation 0
Na linha 3 da entrada, 0 e 1 forma uma aresta e o valor 10 é o respectivo peso dessa aresta
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Cell Cell;

struct Cell {
    int key;
    int peso_aresta;
    Cell* next;
};

typedef struct {
    int num_vertices;
    int num_arestas;
    Cell** adj;
} GrafoLA;

typedef struct {
    int* pai;
    int* chave;
    int* tree;
} CaminhoMinimo;

Cell* criar_celula(int key, int peso_aresta) {
    Cell* c = (Cell*) malloc(sizeof(Cell));
    c->key = key;
    c->peso_aresta = peso_aresta;
    c->next = NULL;
    return c;
}

void inserir_adj(GrafoLA* G, int origem, int destino, int peso_aresta) {
    Cell* novo = criar_celula(destino, peso_aresta);
    novo->next = G->adj[origem];
    G->adj[origem] = novo;
}

GrafoLA* iniciar_grafoLA(int num_vertices, int num_arestas) {
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));
    G->num_vertices = num_vertices;
    G->num_arestas = num_arestas;
    G->adj = (Cell**) calloc(num_vertices, sizeof(Cell*));
    return G;
}

CaminhoMinimo* iniciar_caminho_minimo(int num_vertices) {
    CaminhoMinimo* cm = (CaminhoMinimo*) malloc(sizeof(CaminhoMinimo));
    cm->pai = (int*) malloc(num_vertices * sizeof(int));
    cm->chave = (int*) malloc(num_vertices * sizeof(int));
    cm->tree = (int*) malloc(num_vertices * sizeof(int));
    return cm;
}

void imprimir(CaminhoMinimo* cm, int num_vertices) {
    int i;
    for (i = 0; i < num_vertices; i++) {
        printf("%d: ", i);
        if (cm->pai[i] != -1)
            printf("%d\n", cm->pai[i]);
        else
            printf("-\n");
    }
}

int pegar_min(CaminhoMinimo* cm, int num_vertices) {
    int vertice_menor = -1;
    int i;
    int chave_minima = INT_MAX;

    for (i = 0; i < num_vertices; i++) {
        if (!cm->tree[i] && cm->chave[i] < chave_minima) {
            chave_minima = cm->chave[i];
            vertice_menor = i;
        }
    }

    if (vertice_menor != -1)
        cm->tree[vertice_menor] = 1;

    return vertice_menor;
}

void Dijkstra(GrafoLA* G, int origem) {
    int vertice_atual, vertice_adjacente, peso_aresta;
    Cell* temp;
    CaminhoMinimo* cm = iniciar_caminho_minimo(G->num_vertices);

    for (vertice_atual = 0; vertice_atual < G->num_vertices; vertice_atual++) {
        cm->pai[vertice_atual] = -1;
        cm->chave[vertice_atual] = INT_MAX;
        cm->tree[vertice_atual] = 0;
    }

    cm->chave[origem] = 0;

    while ((vertice_atual = pegar_min(cm, G->num_vertices)) != -1) {
        temp = G->adj[vertice_atual];
        while (temp != NULL) {
            vertice_adjacente = temp->key;
            peso_aresta = temp->peso_aresta;
            if (!cm->tree[vertice_adjacente] && cm->chave[vertice_atual] + peso_aresta < cm->chave[vertice_adjacente]) {
                cm->chave[vertice_adjacente] = cm->chave[vertice_atual] + peso_aresta;
                cm->pai[vertice_adjacente] = vertice_atual;
            }
            temp = temp->next;
        }
    }

    imprimir(cm, G->num_vertices);
}

int main(void) {
    int i, num_vertices, num_arestas, origem, destino, peso_aresta;
    GrafoLA* G;

    scanf("%d", &num_vertices);
    scanf("%d", &num_arestas);

    G = iniciar_grafoLA(num_vertices, num_arestas);

    for (i = 0; i < num_arestas; i++) {
        scanf("%d %d %d", &origem, &destino, &peso_aresta);
        inserir_adj(G, origem, destino, peso_aresta);
    }

    Dijkstra(G, 0);

    return 0;
}
