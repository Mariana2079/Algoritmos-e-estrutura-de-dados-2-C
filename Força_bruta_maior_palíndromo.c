/*ENUNCIADO:
Implemente uma função que receba, pelo menos, uma string como parâmetro. A função deverá procurar, utilizando a estratégia de força-bruta, o maior palíndromo possível dentro da string e imprimí-lo na saída.

Input Format
Leia uma string.

Output Format
Imprima o maior palíndromo encontrado dentro da string.

Sample Input 0:
caaabbaabc

Sample Output 0
aabbaa

Sample Input 1
abc

Sample Output 1
a

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int verifica_palindromo(char *str, int i, int j) {
    for (; i < j; i++, j--) {
        if (str[i] != str[j]) {
            return 0;
        }
    }
    return 1;
}
void encontra_palindromo(char *str) {
    int tam = strlen(str);
    int i, j, maior = 0, inicio = 0;

    for (i = 0; i < tam; i++) {
        for (j = tam - 1; j >= i; j--) {
            if (verifica_palindromo(str, i, j) && j-i+1 > maior) {
                maior = j-i+1;
                inicio = i;
                break; // interrompe o loop interno se encontrar um palindromo
            }
        }
        if (maior >= tam - i) {
            break;
        }
    }
    for (i = inicio; i < inicio + maior; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

int main() {
    char *string;
    
    string = malloc(sizeof(char) * 10);
    scanf("%s",string);

    encontra_palindromo(string);

    free(string);
    
    return 0;
}