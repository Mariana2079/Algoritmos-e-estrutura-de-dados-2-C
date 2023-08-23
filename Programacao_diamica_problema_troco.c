/* ENUNCIADO

Dado um conjunto de moedas e um valor de troco que deve ser dado utilizando essas moedas. 
Em vez de tentarmos obter a quantidade mínima de moedas, dessa vez, o nosso interesse poderia ser definir as formas 
a quantidade de formas possíveis para devolvermos o troco. Por exemplo, para o troco de valor 5 e o conjunto de moedas {1,2,3,4} existem 6 formas diferentes para retornarmos o troco: {1,1,1,1,1}, {1,1,1,2}, {1,1,3}, {1,4}, {1,2,2}, {2,3}.
Em uma estratégia parecida com a da mochila binária, podemos utilizar a programação dinâmica para encontrarmos a quantidade possíveis de formas para devolvermos o troco a partir de um conjunto de moedas. Implemente uma função, utilizando programação dinâmica, que retorne a quantidade de possibilidades para retornar um valor de troco utilizando um conjunto de moedas.

Input Format
A primeira linha deve conter o valor do troco (T).
A segunda linha deve conter a quantidade de moedas (N).
Na terceira linha, ler o conjunto de N moedas.

Output Format
Imprimir a quantidade de formas possíveis que o valor do troco T pode ser devolvido a partir do conjunto de moedas.

Sample Input 0
5
4
1 2 3 4

Sample Output 0
6

*/

#include <stdio.h>
#include <stdlib.h>

int troco_possivel(int troco, int moedas[], int num_moedas) {
    int tabela_cache[troco + 1][num_moedas];
    for (int i = 0; i <= troco; i++) {
        for (int j = 0; j < num_moedas; j++) {
            tabela_cache[i][j] = 0;
        }
    }
    
    for (int i = 0; i < num_moedas; i++) {
        tabela_cache[0][i] = 1;
    }
    
    for (int i = 1; i <= troco; i++) {
        if (i % moedas[0] == 0) {
            tabela_cache[i][0] = 1;
        } else {
            tabela_cache[i][0] = 0;
        }
    }

    for (int i = 1; i <= troco; i++) {
        for (int j = 1; j < num_moedas; j++) {
            tabela_cache[i][j] = tabela_cache[i][j - 1];
            if (i >= moedas[j]) {
                tabela_cache[i][j] += tabela_cache[i - moedas[j]][j];
            }
        }
    }
    
    return tabela_cache[troco][num_moedas - 1];
}

int main() {
    int T, N,opcoes;
    scanf("%d%d", &T, &N); //troco T, num_moedas N
    
    int moedas[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &moedas[i]);
    }
    
    opcoes = troco_possivel(T, moedas, N);
    printf("%d\n", opcoes);
    
    return 0;
}
