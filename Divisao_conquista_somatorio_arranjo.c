/*ENUNCIADO

Implemente uma função que faz o somatório, utilizando divisão e conquista, de todos os elementos de um vetor de números inteiros. 
Antes da divisão, a partição do vetor analizada deve ser impressa caso a mesma tiver, no mínimo, dois elementos.

Input Format
Na primeira linha deve ser lido o tamanho do vetor.
Na segunda linha deve ser lido o conteúdo do vetor.

Output Format
Nas primeiras linhas devem ser impressas as partições antes da sua respectiva "divisão".
Na última linha, deve ser impresso o resultado do somatório seguindo o seguinte padrão:
"soma: resultado do somatorio"

Sample Input 0
8
1 2 3 4 5 6 7 8

Sample Output 0
1 2 3 4 5 6 7 8
1 2 3 4
1 2
3 4
5 6 7 8
5 6
7 8
soma: 36

Sample Input 1
7
1 2 3 4 5 6 7

Sample Output 1
1 2 3 4 5 6 7
1 2 3 4
1 2
3 4
5 6 7
5 6
soma: 28

*/

#include <stdio.h>
#include <stdlib.h>

int soma_divisao_conquista(int vetor[], int inicio, int fim) {
    int soma = 0;
    int meio;

    if (fim - inicio >= 1) {
        for (int i = inicio; i <= fim; i++) {
            printf("%d ", vetor[i]);
        }
        printf("\n");
    }else if (inicio == fim) {
        return vetor[inicio];
    }

    meio = (inicio + fim) / 2;
    soma = soma + soma_divisao_conquista(vetor, inicio, meio);
    soma = soma + soma_divisao_conquista(vetor, meio + 1, fim);

    return soma;
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    int vetor[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }
    
    printf("soma: %d\n", soma_divisao_conquista(vetor, 0, n - 1));
}
