#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro {
    int matricula;
    char nome[50];
    char curso[50];
    float nota1;
    float nota2;
}Registro;

typedef struct No {
    struct Registro registros;
    struct No *prox;
    struct No *ant;
}No;
 
No *inicio = NULL;


struct No* criar_no(struct Registro novo) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }

    novo_no->registros = novo;
    novo_no->prox = NULL;
    novo_no->ant = NULL;

    return novo_no;
}

void create() {
    Registro novo;

    printf("Digite a matricula: ");
    scanf("%d", &novo.matricula);

    No *aux = inicio;
    while (aux != NULL) {
        if (aux->registros.matricula == novo.matricula) {
            printf("Matricula ja existe.\n");
            return;
        }
        aux = aux->prox;
        if (aux == inicio)
            break;
    }

    printf("Digite o nome: ");
    scanf("%s", novo.nome);

    printf("Digite o curso: ");
    scanf("%s", novo.curso);

    printf("Digite a nota 1: ");
    scanf("%f", &novo.nota1);

    printf("Digite a nota 2: ");
    scanf("%f", &novo.nota2);

    No *novo_no = criar_no(novo);

    if (inicio == NULL) {
        inicio = novo_no;
        inicio->prox = inicio;
        inicio->ant = inicio;
    } else {
        No *ultimo = inicio->ant;
        novo_no->prox = inicio;
        novo_no->ant = ultimo;
        inicio->ant = novo_no;
        ultimo->prox = novo_no;
    }
    printf("Registro criado com sucesso.\n");
}

void read() {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("Matricula\tNome\t\tCurso\t\tNota1\tNota2\tMedia\n");
    struct No *aux = inicio;
    do {

        float media = (aux->registros.nota1 + aux->registros.nota2) / 2.0;
        printf("Matricula : %d ", aux->registros.matricula);
        printf("\nAluno: %s ", aux->registros.nome);
        printf("\nCurso: %s ", aux->registros.curso);
        printf("\nNota 1 : %.2f Nota 2: %.2f", aux->registros.nota1, aux->registros.nota2);
        printf("\nMedia do aluno: %.2f\n", media);

        aux = aux->prox;
    } while (aux != inicio);
}

void update() {
    if (inicio == NULL) {
        printf("Lista vazia\n");
        return;
    }

    int matricula;
    printf("Digite a matricula do registro que quer mudar: ");
    scanf("%d", &matricula);

    struct No *aux = inicio;
    do {
        if (aux->registros.matricula == matricula) {
            printf("Digite o novo nome: ");
            scanf("%s", aux->registros.nome);

            printf("Digite o novo curso: ");
            scanf("%s", aux->registros.curso);

            printf("Digite a nova nota 1: ");
            scanf("%f", &aux->registros.nota1);
    
            printf("Digite a nova nota 2: ");
            scanf("%f", &aux->registros.nota2);
    

            printf("Registro atualizado\n");
            return;
        }
        aux = aux->prox;
    } while (aux != inicio);

    printf("Matricula nao encontrada.\n");
}

void delete() {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    int matricula;
    printf("Digite a matricula que vai excluir: ");
    scanf("%d", &matricula);

    struct No *aux = inicio;
    do {
        if (aux->registros.matricula == matricula) {
            char confirmacao;
            printf("Tem certeza que deseja excluir este registro? (S/N): ");
            scanf("%c", &confirmacao);
    
    
            if (confirmacao == 'S' || confirmacao == 's') {
                if (aux == inicio) {
                    inicio = inicio->prox;
                    if (inicio == aux) {
                        free(aux);
                        inicio = NULL;
                        printf("excluido\n");
                        return;
                    }
                }
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
                free(aux);
                printf("excluido\n");
            } else {
                printf("Cancelado\n");
            }
            return;
        }
        aux = aux->prox;
    } while (aux != inicio);
    printf("Matricula nao encontrada\n");
}


int main() {
    int opcao;


    do {
        printf("\nSelecione uma opcao:\n");
        printf("1. Criar Registro\n");
        printf("2. Ler Registros\n");
        printf("3. Atualizar Registro\n");
        printf("4. Excluir Registro\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);


        switch (opcao) {
            case 1:
                create();
                break;
            case 2:
                read();
                break;
            case 3:
                update();
                break;
            case 4:
                delete();
                break;
            case 0:
                printf("Saiu do programa\n");
                break;
            default:
                printf("invalido\n");
        }
    } while (opcao != 0);

    return 0;
}
