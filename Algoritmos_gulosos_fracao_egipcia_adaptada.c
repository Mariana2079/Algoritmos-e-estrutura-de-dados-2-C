/*ENUNCIADO

Uma fração pode representada pela soma de um conjunto de frações unitárias, onde o numerador é igual a 1 (um). 
Exemplos:
8/11 é equivamente a 1/2 + 1/5 + 1/37 + 1/4070.
7/3 é equivamente a 2 + 1/3.
Essas frações unitárias podem ser geradas utilizando uma estratégia gulosa. Dado dois números inteiros: n (numerador) e d (demoninador).
Se d > n, o denominador da maior fração unitária é dada da seguinte forma: 1 / (d / n + 1). Após, pode ser feita uma chamada recursiva, cuja fração de entrada deve ser equivalente a (n / d) - (1 / (d / n + 1)), que é igual a uma outra fração: (n * (d / n + 1) - d) / (d * (d / n + 1)). Por exemplo, para o 8/11, a primeira fração unitária é 1 / (d / n + 1) = 1 / (11 / 8 + 1) = 1/2. Em seguida, pode ser feita uma chamada recursiva para 8/11 - 1/2 = 5/22, ou seja, (8 * (11/8 + 1) - 11) / ((11/8 + 1) * 11) = 5/22.
Se d < n, o resultado é um número inteiro mais uma fração resultante da chamada recursiva para seguinte fração: (n % d) / d. Por exemplo, para 7/3, o numerador é maior, ou seja, primeiro deverá ser impresso a parte inteira da divisão (2). Em seguinda, fazer uma chamada recursiva para (n % d) / n = (7 % 3) / 3 = 1/3.
Os critérios de parada são:
d % n == 0
n % d == 0
Implemente uma função que receba, pelo menos, dois números inteiros que represente uma fração. A função deverá imprimir o somatório de frações unitárias e/ou números inteiros cujo resultado é a fração de entrada.

Input Format
Ler dois números inteiros: numerador seguido do denominador.

Output Format
Imprimir o somatório.

Sample Input 0
8 11

Sample Output 0
1/2 + 1/5 + 1/37 + 1/4070

*/

#include <stdio.h>

void frac(int n, int d){
    int aux;
    if((n > 0) && (d > 0)){
        if((d % n) == 0){
            printf("1/%d", d / n);
        }else if (n % d == 0){
            printf("%d", n / d);
        }else if (n > d){
            printf("%d + ", n / d);
            frac(n % d, d);
        }else{
            aux = d / n + 1;
            printf("1/%d + ", aux);
            frac(n * aux - d, d * aux);
        }
    }
}

int main(void) {
    int n, d;
    scanf("%d %d", &n, &d);
    if(d <= 0) {
        printf("Erro\n");
        return 0;
    }
    frac(n, d);
    return 0;
}
