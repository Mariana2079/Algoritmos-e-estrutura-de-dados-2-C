/*
ENUNCIADO
Implemente uma função que receba uma árvore binária de busca. A função deverá retornar a soma entre todos os nós folhas.

Input Format
Na primeira linha deve ser lido o número inteiro N, que é referente à quantidade de nós da árvore binária de busca. 
Em seguida, em cada linha deve ser lido um número inteiro para ser inserido como nó na árvore (fazer isso até que N números sejam lidos).

Constraints
Usar o TAD de árvores binárias disponilibilizado em aula

Output Format
Resultado da soma dos nós folhas.

Sample Input 0
13
28
12
8
3
10
9
15
16
45
36
41
59
48

Sample Output 0
117

*/
#include <stdio.h>
#include <stdlib.h>

// TAD material
typedef struct node {
    int item;
    struct node *left;
    struct node *right;
} Node;

Node* criar(int item){
    Node * tree = (Node *) malloc(sizeof(Node));
    
    tree->item = item;
    tree->left = NULL;
    tree->right = NULL;
        
    return tree;
}

Node* inserir_node(int item, Node** tree){
    if (*tree == NULL)
        *tree = criar(item);
    else if (item < (*tree)->item)
        (*tree)->left = inserir_node(item, &((*tree)->left));
    else if (item > (*tree)->item)
        (*tree)->right = inserir_node(item, &((*tree)->right));
        
    return *tree;
}

int somar_nos_folhas(Node *tree) {
    if (tree == NULL) {
        return 0;
    } else if (tree->left == NULL && tree->right == NULL) {
        return tree->item;
    } else {
        return somar_nos_folhas(tree->left) + somar_nos_folhas(tree->right);
    }
}

int liberar_arvore(Node *tree){
    if (tree != NULL){
        liberar_arvore(tree->left);
        liberar_arvore(tree->right);
        free(tree);
        return 1;
    }
    return 0;
}


int main() {
    Node *tree = NULL;
    int n, item;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &item);
        inserir_node(item, &tree);
    }
    
    printf("%d\n", somar_nos_folhas(tree));
    
    liberar_arvore(tree);
    
    return 0;
}
