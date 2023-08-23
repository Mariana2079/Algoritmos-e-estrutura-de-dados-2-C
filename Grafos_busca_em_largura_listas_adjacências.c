/*
Implemente o algoritmo de busca em largura para grafos. Esse algoritmo deve ter dois parâmetros: um grafo e um número inteiro, sendo este último o vértice raiz da árvore de busca em largura, ou seja, é o vértice a partir de onde deve ser iniciado a exploração do grafo. Após, para cada vértice, imprima os respectivos pai e distância.
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

Na última linha deve ser lido um número inteiro que representa um vértice do grafo para iniciar a aplicação do algoritmo de busca em largura.

Output Format
Na primeira linha deve ser impressa a seguinte sequência de caracteres: "v d p".
A partir da próxima linha, imprimir o vértice, o pai e a distância.
Para cada vértice que não tem pai, deve ser impresso "-" em sua respectiva linha.
Para cada vértice que não foi possível ser descoberto a partir do "vértice raiz", também deve ser impresso o caractere "-". Por exemplo: se o vértice x não pode ser descoberto, na sua linha deve ser impresso "x - -"

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
0

Sample Output 0
v d p
0 0 -
1 1 0
2 2 1
3 1 0
4 2 3
5 2 3
6 3 4
7 3 5

Sample Input 1
5
2 4 -1
-1
0 3 -1
2 4 -1
0 3 -1
1

Sample Output 1
v d p
0 - -
1 0 -
2 - -
3 - -
4 - -
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Cell {
    int key;
    struct Cell* next;
} Cell;

typedef struct {
    int A,pai,d;
    Cell* adj;
} Vertice;

void buscaEmLargura(Vertice grafo[], int V, int v_raiz) {
    int i, fila[V], inicio= 0, fim = 0;

    for (i = 0; i < V; i++) {
        if (i != v_raiz) {
            grafo[i].pai = -1;
            grafo[i].d = -1;
        }
    }

    grafo[v_raiz].pai = -1;
    grafo[v_raiz].d = 0;

    fila[fim++] = v_raiz;

    while (inicio!= fim) {
        int v_Atual = fila[inicio++];

        Cell* adjacente = grafo[v_Atual].adj;
        while (adjacente != NULL) {
            int v_Adjacente = adjacente->key;

            if (grafo[v_Adjacente].d == -1) {
                grafo[v_Adjacente].pai = v_Atual;
                grafo[v_Adjacente].d = grafo[v_Atual].d + 1;
                fila[fim++] = v_Adjacente;
            }

            adjacente = adjacente->next;
        }
    }
}

int main(void) {
    int V, i, v_raiz;
    scanf("%d", &V);

    Vertice grafo[V];

    for (i = 0; i < V; i++) {
        int adjacente;
        Cell* listaAdj = NULL;

        scanf("%d", &adjacente);

        while (adjacente != -1) {
            Cell* novaCell = (Cell*)malloc(sizeof(Cell));
            novaCell->key = adjacente;
            novaCell->next = NULL;

            if (listaAdj == NULL) {
                listaAdj = novaCell;
            } else {
                Cell* temp = listaAdj;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = novaCell;
            }

            scanf("%d", &adjacente);
        }

        grafo[i].adj = listaAdj;
        grafo[i].A = 0;
        Cell* temp = listaAdj;
        while (temp != NULL) {
            grafo[i].A++;
            temp = temp->next;
        }
    }

    scanf("%d", &v_raiz);

    buscaEmLargura(grafo, V, v_raiz);

    printf("v d p\n");

    for (i = 0; i < V; i++) {
        printf("%d ", i);

        if (grafo[i].pai == -1 && i != v_raiz) {
            printf("- -\n");
        } else {
            printf("%d ", grafo[i].d);

            if (grafo[i].pai == -1) {
                printf("-\n");
            } else {
                printf("%d\n", grafo[i].pai);
            }
        }
    }

    return 0;
}
