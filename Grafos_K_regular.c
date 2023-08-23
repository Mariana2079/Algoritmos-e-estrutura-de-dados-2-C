/*
Implemente uma função para verificar se um grafo representado por listas de ajacência é k-regular. Se o grafo for k-regular, a função deve retornar o valor de k. Se o grafo não for k-regular, a função deve retornar 0.

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

A primeira linha contém o número de vértices seguida pela respectiva lista de adjacência. 
Cada uma das seguintes linhas será referente a um vértice v_i, onde os vértices adjacentes devem ser lidos. Para cada linha, enquanto o número "-1" (menos um) não for lido, um vértice adjacente deve ser lido. Por exemplo, suponha que o i-ésimo vértice seja adjacente aos vértices 2 e 5, então a leitura deve seguir o seguinte formato:

2 5 -1

Caso o vértice não tenha adjacentes, basta ler -1 (menos 1). Exemplo:
-1

Output Format
Imprimir "grafo k-regular com k=valor" caso o grafo seja regular ou imprimir "grafo nao k-regular", caso contrário.

Sample Input 0
8
1 3 -1
0 2 -1
1 -1
0 4 5 -1
3 5 6 -1
3 4 6 7 -1
4 5 7 -1
5 6 -1

Sample Output 0
grafo nao k-regular

Sample Input 1
6
1 2 3 -1
0 2 3 -1
0 1 4 -1
1 4 5 -1
2 3 5 -1
0 3 4 -1

Sample Output 1
grafo k-regular com k=3

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Cell Cell;

struct Cell {
    int key;
    Cell *next;
};

typedef struct {
    int V; 
    int A; 
    Cell **adj; 
} GrafoLA;


int nAdjacentes(Cell *lista) {
    int contador = 0;
    Cell *celula = lista;
    
    while (celula != NULL && celula->key != -1) {
        contador++;
        celula = celula->next;
    }
    
    return contador;
}

int K_Regular(GrafoLA *grafo) {
    int k = -1; 
    int i;
    int grauAtual;
    
    for (i = 0; i < grafo->V; i++) {
        if (i == 0) {
            grauAtual = nAdjacentes(grafo->adj[i]);
            k = grauAtual; 
        } else {
            int grau = nAdjacentes(grafo->adj[i]);
            
            if (grau != k) {
                return 0;
            }
        }
    }
    
    return k; 
}

void liberarGrafo(GrafoLA *grafo) {
    int i;
    
    for (i = 0; i < grafo->V; i++) {
        Cell *celula = grafo->adj[i];
        
        while (celula != NULL) {
            Cell *proximo = celula->next;
            free(celula);
            celula = proximo;
        }
    }
    
    free(grafo->adj);
    free(grafo);
}

int main(void) {
    int n, i, k;
    int adjacente;

    scanf("%d", &n);
    
    GrafoLA *grafo = (GrafoLA *)malloc(sizeof(GrafoLA));
    grafo->V = n;
    grafo->A = 0;
    grafo->adj = (Cell **)malloc(n * sizeof(Cell *));
    
    for (i = 0; i < n; i++) {
        grafo->adj[i] = NULL;
        
        scanf("%d", &adjacente);
        
        Cell *celulaAtual = NULL;
        
        while (adjacente != -1) {
            Cell *novaCelula = (Cell *)malloc(sizeof(Cell));
            novaCelula->key = adjacente;
            novaCelula->next = NULL;
            
            if (grafo->adj[i] == NULL) {
                grafo->adj[i] = novaCelula;
                celulaAtual = novaCelula;
            } else {
                celulaAtual->next = novaCelula;
                celulaAtual = novaCelula;
            }
            
            scanf("%d", &adjacente);
        }
    }
    
    k = K_Regular(grafo);

    if (k == 0) { //Imprimir "grafo k-regular com k=valor" caso o grafo seja regular ou imprimir "grafo nao k-regular"
        printf("grafo nao k-regular\n");
    } else {
        printf("grafo k-regular com k=%d\n", k);
    }
    
    liberarGrafo(grafo);
    
    return 0;
}



