#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 256

typedef struct No{
    unsigned char caracter;
    int frequencia;
    struct No *proximo, *esq, *dir;
}No;

typedef struct{
    No *inicio;
    int tam;
}Lista;

void inicializa(unsigned int tab[]){
    int i;
    for(i = 0; i < TAM; i++){
        tab[i] = 0;
    }
}

void preenche_frequencia(unsigned char texto[], unsigned int tab[]){
    int i = 0;
    
    while(texto[i] != '\0'){
        tab[texto[i]]++;
        i++;
    }
}

void imprimi_tab(unsigned int tab[]){
    int i;
    
    printf("TABELA DE FREQUENCIA\n");
    for(i = 0; i < TAM; i++){
        if(tab[i] > 0){
        printf("%d = %d = %c\n", i, tab[i], i);
        }
    }
}

void criar_lista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no){
    No *aux;

    if(lista->inicio == NULL){
        lista->inicio = no;
        lista->tam++;
    }
    else if(no->frequencia < lista->inicio->frequencia){

        no->proximo = lista->inicio;
        lista->inicio = no;
        lista->tam++;
    }
    else{
        aux = lista->inicio;
        while(aux->proximo && aux->proximo->frequencia <= no->frequencia){
            aux = aux->proximo;
        }
        no->proximo = aux->proximo;
        aux->proximo = no;
        lista->tam++;
    }
}

void preencher_lista(unsigned int tab[], Lista *lista){
    No *novo;
    for(int i = 0; i < TAM; i++){
        if(tab[i] > 0){
            novo = malloc(sizeof(No));
            if(novo){
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;
                
                inserir_ordenado(lista, novo);
            }else{
                printf("Erro ao alocar memoria em preencher lista\n");
                break;
            }
        }
    }
}

void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;
    
    printf("\nLista ordenada: Tamanho : %d\n", lista->tam);
    while(aux){
        printf("Caracter: %c Frequencia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
}

No* remove_no_inicio(Lista *lista){
    No *aux = NULL;
    
    if(lista->inicio){
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }
    return aux;
}

No* cria_arvore(Lista *lista){
    No *primeiro, *segundo, *novo;
    while(lista->tam > 1){
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));
        
        if(novo){
            novo->caracter = ' ';
            novo->frequencia = (primeiro->frequencia + segundo->frequencia);
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;
            
            inserir_ordenado(lista, novo);
        }else{
            printf("\nErro ao alocar memoria em cria_arvore");
            break;
        }
    }
    
    return lista->inicio;
}

void imprimir_arvore(No *raiz, int tam){
    if(raiz->esq == NULL && raiz->dir == NULL){
        printf("Folha = %c Altura = %d\n", raiz->caracter, tam);
    }
    else{
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}   

int altura_arvore(No *raiz){
    int esq, dir;
    if(raiz == NULL){
        return -1;
    }
    else{
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;
        
        if(esq > dir){
            return esq;
        }
        else{
            return dir;
        }
    }
}

char** aloca_dicionario(int colunas){
    char **dicionario;
    
    dicionario = malloc(sizeof(char*) * TAM);
    
    for(int i = 0; i < TAM; i++){
        dicionario[i] = calloc(colunas, sizeof(char));
    }
    return dicionario;
}
    
void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];
    if(raiz->esq == NULL && raiz->dir ==NULL){
        strcpy(dicionario[raiz->caracter], caminho);
    }else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);
        
        strcat(esquerda, "0");
        strcat(direita, "1");
        
        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

void imprime_dicionario(char **dicionario){
   
   printf("\nDicionario: \n");
    for(int i = 0; i < TAM; i++){
        if(strlen(dicionario[i]) > 0)
            printf("%d : %s\n", i, dicionario[i]);
    }
}

int tamnho_da_string(char **dicionario, unsigned char *texto){
    int i = 0, tam = 0;
    while(texto[i] != '\0'){
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }    
    return tam + 1;
}

char * codificar(char **dicionario, unsigned char *texto){
    
    int i = 0, tam = tamnho_da_string(dicionario, texto);
    
    char *codigo = calloc(tam, sizeof(char));
    while(texto[i] != '\0'){
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }
    return codigo;
}

int main() {
        
    unsigned char teste[] = "Teste do algoritimo de huffman";
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    int colunas;
    char **dicionario;
    char *codificado;
    
    printf("Texto a ser codificado : %s\n", teste);
    
    //faz a tabela frequencia
    inicializa(tabela_frequencia);
    preenche_frequencia(teste, tabela_frequencia);
    imprimi_tab(tabela_frequencia);
    
    //faz a lista 
    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
    imprimir_lista(&lista); 
    
    //monta arvore
    arvore = cria_arvore(&lista);
    printf("\nArvore de huffman\n");
    imprimir_arvore(arvore, 0);
    
    //dicionario
    colunas = altura_arvore(arvore) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);
    imprime_dicionario(dicionario); 
    
    //faz o texto codificado
    codificado = codificar(dicionario, teste);
    printf("\nTexto codificado: %s\n", codificado);

    return 0;
}