/* João Vitor de Araújo Trindade - 10403255
** João Vitor de Almeida Reiss - 10723789
** Vinícius Pereira Rodrigues - 10729470
*/

#include <stdlib.h>
#include <stdio.h>

/*
*Exercício 1
*Escreva em C o algoritmo ex1 que compacta elementos contíguos repetidos do seguinte modo:
* ex1 " aaaaaaabbbbbaaaaaaaaaa "
* " a7−b5−a10 "
* ex1 " abcabc "
* " a1−b1−c1−a1−b1−c1 "
*/

int main(){
    // Variáveis para armazenar a string de entrada
    char *word = NULL;
    size_t len = 0;
    ssize_t read;

    // Lê uma linha da entrada padrão
    read = getline(&word, &len, stdin);

    // Índices para percorrer a string
    int i = 1;          // Posição atual
    int prev = 0;       // Posição anterior
    
    // Contador de repetições de uma letra
    int times_letter = 1;
    
    // Percorre toda a string
    while(i < len - 1 && word[i] != '\0'){

        // Conta quantas vezes a letra atual se repete
        while(word[i] == word[prev]){
            times_letter++;
            prev = i;
            i++;
        }

        // Imprime a letra e o número de repetições
        // Se não é o último elemento, adiciona hífen
        if(word[i+1] != '\0') printf("%c%d-", word[prev], times_letter);
        else printf("%c%d", word[prev], times_letter);
        
        // Reinicia o contador para a próxima sequência
        times_letter = 1;

        prev = i;
        i++;
    }

    free(word);

    return 0;
}
