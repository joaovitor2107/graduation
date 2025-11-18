/* João Vitor de Araújo Trindade - 10403255
** João Vitor de Almeida Reiss - 10723789
** Vinícius Pereira Rodrigues - 10729470
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
* Exercício 3
* Escreva em C o algoritmo ex3 que compacta elementos contíguos repetidos do seguinte modo:
* ex3 "ababababababababababab"
* "b1"
* ex3 "ababababababaaaaaaaaaaaaaaa"
* "b6−a1"
* ex3 "abcabcabcabcxyxyxyccccccc"
* "abc4−xy3−c7"
* ex3 "antonioantonioantoniocarloscarlos"
* "antonio3−carlos2"
*/


// Estrutura para armazenar informações sobre subsequências repetidas
typedef struct {
    int len_substring;    // Tamanho da subsequência
    int times_appeared;   // Número de vezes que aparece
}Substring;


// Função que conta quantas vezes uma subsequência se repete na string
int times_repeat(int pos_init, int pos_finish, char *word, int len){

    int i = pos_finish+1;                           // Posição após a primeira ocorrência
    int size_substr = pos_finish - pos_init + 1;    // Tamanho da subsequência
    int count=1;                                     // Contador (já conta a primeira ocorrência)

    // Procura por repetições da subsequência
    while(i+size_substr-1 < len){
        int j = 0;
        // Compara caractere por caractere
        while(j < size_substr){
            if(word[pos_init+j] != word[j+i]) return count;  // Se não coincidir, para
            j++;
        }

        count++;                // Encontrou uma repetição
        i += size_substr;       // Pula para a próxima posição possível
    }

    return count;
}

// Função que encontra a melhor subsequência repetida a partir de uma posição inicial
Substring biggest_sequence(int pos_init, char *word, int len){

    Substring response={1,1};  // Resposta padrão (1 caractere, 1 vez)
    int i = pos_init;
    int times_repeated=1;
    int current_size;

    // Testa subsequências de tamanhos crescentes
    // Condição: o tamanho da subsequência não pode ser maior que metade do espaço restante
    while(i < len && (i - pos_init + 1) * 2 <= len - pos_init){

        current_size = i - pos_init + 1;                    // Tamanho atual da subsequência
        times_repeated = times_repeat(pos_init, i, word, len);  // Quantas vezes se repete

        // Calcula a economia de cada opção
        int current_economy = (current_size * times_repeated) - current_size - 1;
        int best_economy = (response.len_substring* response.times_appeared) - response.len_substring - 1;

        // Se a subsequencia repete mais de 1 vez e economiza mais caracteres
        if(times_repeated > 1 && current_economy > best_economy){
            response.len_substring = current_size;
            response.times_appeared = times_repeated;
        }
        i++;
    }

    return response;
}




int main() {
    // Variáveis para armazenar a string de entrada
    char *word;
    size_t len_buffer = 0;
    ssize_t len;

    // Lê uma linha da entrada padrão
    len = getline(&word, &len_buffer, stdin);
    
    // Remove o caractere de nova linha se existir
    if (len > 0 && word[len-1] == '\n') {
        word[len-1] = '\0';
        len--;
    }
    
    Substring res;  // Estrutura para armazenar o resultado da busca

    // Percorre toda a string
    int i = 0;
    while(i < len){
        // Encontra a melhor subsequência repetida a partir da posição atual
        res = biggest_sequence(i, word, len);

        // Imprime a subsequência encontrada
        for(int j = i; j < (i+res.len_substring); j++){
            printf("%c",word[j]);
        }

        // Imprime o número de repetições (com hífen se não for o último)
        if(i+res.len_substring*res.times_appeared < len) printf("%d-", res.times_appeared);
        else printf("%d", res.times_appeared);
        
        // Pula todas as ocorrências da subsequência processada
        i+=res.len_substring*res.times_appeared;
    }

    free(word);
    return 0;
}
