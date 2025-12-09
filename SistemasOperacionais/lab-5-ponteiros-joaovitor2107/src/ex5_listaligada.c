#include <stdio.h>
#include <stdlib.h>
// Definição da estrutura do nó
typedef struct No {
    int valor;
    struct No * proximo ;
} No;
// Função para criar um novo nó

No* criar_no (int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if(novo == NULL){
        printf("Erro ao alocar memoria");
        exit(1);
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}
// Função para inserir no início da lista

No* inserir_inicio (No *cabeca , int valor) {
// Seu código aqui
    No *novo = criar_no(valor);
    novo->proximo = cabeca;
    return novo;
}
// Função para imprimir a lista

void imprimir_lista (No * cabeca ) {
    No* tmp;
    tmp = cabeca;
    while(tmp != NULL){
        if(tmp->proximo!=NULL)printf("%d, ", tmp->valor);
        else printf("%d", tmp->valor);
        tmp = tmp->proximo;
    }
    printf("\n");
// Seu código aqui
}
// Função para liberar a lista

void liberar_lista (No * cabeca ) {
    No *tmp = cabeca;
    while(tmp != NULL){
        tmp = tmp->proximo;
        free(cabeca);
        cabeca = tmp;
    }
// Seu código aqui
}

int main () {
    No *lista = NULL; // Lista vazia

// Inserir elementos
    lista = inserir_inicio (lista , 10);
    lista = inserir_inicio (lista , 20);
    lista = inserir_inicio (lista , 30);

// Imprimir a lista
    printf (" Lista : ");
    imprimir_lista (lista);

// Liberar a memória
    liberar_lista (lista);

    return 0;
}
