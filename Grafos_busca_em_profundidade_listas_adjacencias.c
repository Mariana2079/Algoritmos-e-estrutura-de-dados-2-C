/*
Implemente o algoritmo de busca em profundidade para grafos. Para a representação do grafo, você pode usar matriz ou lista de adjacências. 
A aplicação do algoritmo deve começar pelo vértice 0.
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

A primeira linha contém o número de vértices seguida pela respectiva lista de adjacência. Cada uma das seguintes linhas será referente a um vértice v_i, onde os vértices adjacentes devem ser lidos. Para cada linha, enquanto o número "-1" (menos um) não for lido, um vértice adjacente deve ser lido. Por exemplo, suponha que o i-ésimo vértice seja adjacente aos vértices 2 e 5, então a leitura deve seguir o seguinte formato:

2 5 -1

Caso o vértice não tenha adjacentes, basta ler -1 (menos 1). Exemplo:

-1

Output Format
Na primeira linha deve ser impressa a seguinte sequência de caracteres: "v d f p".
Para cada uma das próximas linhas, imprimir um vértice (em ordem crescente), o momento da sua descoberta, o momento da sua finalização e o seu respectivo pai.
Para cada vértice que não tem pai, deve ser impresso "-" em sua respectiva linha.

Sample Input 0
4
1 3 -1
2 3 -1
-1
2 -1

Sample Output 0
v d f p
0 1 8 -
1 2 7 0
2 3 4 1
3 5 6 1
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Cell {
    int key;
    struct Cell* next;
} Cell;

typedef struct {
    int Vertice; 
    int A; 
    Cell** adj; 
} GrafoLA;

GrafoLA* criarGrafo(int Vertice) {
    GrafoLA* grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
    grafo->Vertice = Vertice;
    grafo->A = 0;
    grafo->adj = (Cell**)malloc(Vertice * sizeof(Cell*));

    int i;
    for (i = 0; i < Vertice; i++) {
        grafo->adj[i] = NULL;
    }

    return grafo;
}

void adicionarAresta(GrafoLA* grafo, int vertice1, int vertice2) {
    Cell* novaCell = (Cell*)malloc(sizeof(Cell));
    novaCell->key = vertice2;
    novaCell->next = grafo->adj[vertice1];
    grafo->adj[vertice1] = novaCell;
    grafo->A++;
}

void visitar(GrafoLA* grafo, int v, int* inicio, int* fim, int* pai, int* tempo) {
    inicio[v] = (*tempo)++;
    Cell* adjacente = grafo->adj[v];
    
    while (adjacente != NULL) {
        int v_adjacente = adjacente->key;
        
        if (inicio[v_adjacente] == -1) {
            pai[v_adjacente] = v;
            visitar(grafo, v_adjacente, inicio, fim, pai, tempo);
        }
        
        adjacente = adjacente->next;
    }
    
    fim[v] = (*tempo)++;
}

void busca_profundidade(GrafoLA* grafo) {
    int Vertice = grafo->Vertice;
    int inicio[Vertice];
    int fim[Vertice];
    int pai[Vertice];
    int tempo = 1;
    
    int i;
    for (i = 0; i < Vertice; i++) {
        inicio[i] = -1;
        fim[i] = -1;
        pai[i] = -1;
    }
    
    visitar(grafo, 0, inicio, fim, pai, &tempo);
    
    printf("v d f p\n");
    
    for (i = 0; i < Vertice; i++) {
        printf("%d %d %d ", i, inicio[i], fim[i]);
        
        if (pai[i] == -1) {
            printf("-\n");
        } else {
            printf("%d\n", pai[i]);
        }
    }
}

void liberarGrafo(GrafoLA* grafo) {
    int i;
    for (i = 0; i < grafo->Vertice; i++) {
        Cell* atual = grafo->adj[i];
        while (atual != NULL) {
            Cell* proximo = atual->next;
            free(atual);
            atual = proximo;
        }
    }
    free(grafo->adj);
    free(grafo);
}

int main(void) {
    int Vertice, i, adjacente;
    scanf("%d", &Vertice);

    GrafoLA* grafo = criarGrafo(Vertice);

    for (i = 0; i < Vertice; i++) {
        Cell* lista_adj = NULL;
        scanf("%d", &adjacente);

        while (adjacente != -1) {
            Cell* novaCell = (Cell*)malloc(sizeof(Cell));
            novaCell->key = adjacente;
            novaCell->next = NULL;

            if (lista_adj == NULL) {
                lista_adj = novaCell;
            } else {
                Cell* temp = lista_adj;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = novaCell;
            }

            scanf("%d", &adjacente);
        }

        grafo->adj[i] = lista_adj;
    }

    busca_profundidade(grafo);

    liberarGrafo(grafo);

    return 0;
}
