/* João Vitor de Araújo Trindade - 10403255
** João Vitor de Almeida Reiss - 10723789
** Vinícius Pereira Rodrigues - 10729470
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
* Exercício 2
* Escreva em C o algoritmo ex2 que descompacta o que foi compactado no item anterior, conforme abaixo:
* ex2 "a7−b5−a10"
* "aaaaaaabbbbbaaaaaaaaaa"
* ex2 "a6−b15−c1−d1"
* "aaaaaabbbbbbbbbbbbbbbcd"
*/

int main(){
    // Variáveis para armazenar a string de entrada
    char *word = NULL;
    size_t len_buffer = 0;
    ssize_t len;

    // Lê uma linha da entrada padrão
    len = getline(&word, &len_buffer, stdin);

    // Percorre a string caractere por caractere
    int i = 0;
    while(i < len && word[i] != '\0'){

        // Verifica se é uma letra (A-Z ou a-z)
        if(word[i] >= 'A' && word[i] <= 'z'){

            char letter = word[i];  // Armazena a letra
            int num = 0;            // Número de repetições
            i++;
            
            // Lê os dígitos que seguem a letra para formar o número
            while(word[i] >= '0' && word[i] <= '9'){

                if(num == 0) num = word[i] - '0';  // Primeiro dígito
                else{
                    num *= 10;                      // Desloca casa decimal
                    num += (word[i] - '0');         // Adiciona novo dígito
                }
                i++;
            }

            // Imprime a letra o número especificado de vezes
            for(int j = 0; j < num; j++){
                printf("%c", letter);
            }

        }

        i++;
    }

    free(word);

    return 0;
}
