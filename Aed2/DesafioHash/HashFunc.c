#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 1999
#define arquivo1 "numeros_aleatorios.txt"

typedef struct No{
    int num;
    struct No *proximo;
}No;

No *hash[TAM];

int colisoes_geral = 0;

void inicializa();
int func_hash(int rand_num);
void ler_arquivo_para_hash();
void insere(int num);
int busca(int pos, int num, int *passos);
void ler_arquivo_para_check(char *arquivo2);

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Uso correto: ./DesafioHash checkin.txt\n");
        return 1;
    }

    inicializa();
    ler_arquivo_para_hash();
    
    ler_arquivo_para_check(argv[1]);
    printf("Total de colisões: %d\n", colisoes_geral);

    return 0;
}

void inicializa(){
    for(int i = 0; i < TAM; i++){
        hash[i] = NULL;
    }
}

int func_hash(int rand_num){   
    
    int hash_code = (rand_num) % TAM;
    
    return hash_code;
}

void ler_arquivo_para_hash(){
    FILE *file = fopen(arquivo1 , "r");
    
    if(file == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    int temp;
    char linha[10];

    while(fgets(linha, sizeof(linha), file) != NULL){
        temp = atoi(linha);
        insere(temp);
    }

    fclose(file);

}

void insere(int num){
    
    int pos = func_hash(num);    
    
    if(hash[pos] != NULL){
        if(busca(pos, num, NULL) == 1){
            return;
        }
        else{
            colisoes_geral++;
        }
    }

    No *novo = malloc(sizeof(No));

    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        return;
    }

    novo->num = num;
    novo->proximo = NULL;

    if(hash[pos] == NULL){
        hash[pos] = novo;
    }
    else{
        No *aux = hash[pos];
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }


}


int busca(int pos, int num, int *passos){

    No *aux = hash[pos];
    int count = 0;

    while(aux != NULL){
        count++;
        if(aux->num == num){
            if(passos != NULL){
                *passos = count;
            }
            return 1;
        }
        aux = aux->proximo;
    }

    if(passos != NULL){
        *passos = count;
    }

    return 0;
}

void ler_arquivo_para_check(char *arquivo2){
    FILE *file = fopen(arquivo2, "r");    

    if(file == NULL){
        printf("Erro ao ler arquivo checkin\n");
        return;
    }

    int num, temp, hash_code, passos, passos_total;
    char linha[10];
    clock_t start, end;
    double cpu_time;
    
    start = clock();

    passos_total = 0;

    while(fgets(linha, sizeof(linha), file) != NULL){
        num = atoi(linha);
        hash_code = func_hash(num);
        temp = busca(hash_code, num, &passos);
        passos_total += passos;
        if(temp == 1){
            printf("Numero %d encontrado na localização %d em %d passos\n", num, hash_code, passos);
        }
        else if(temp == 0){
            printf("Numero %d não encontrado\n", num);
        }
    }

    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC; 
    printf("\nTempo para encontar os números: %f segundos\n", cpu_time);
    printf("Quantidade total de passos: %d\n", passos_total);

    fclose(file);

}