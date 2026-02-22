#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Registro{
    int matricula;
    char nome[50];
    char curso[50];
    float nota1;
    float nota2;
};

struct Registro matriz[50];
int registros = 0;

void create(){
    if(registros >= 50){
        printf("Número maximo de registros alcançado");
        return;
    }
    
    struct Registro aux;
    
    printf("Numero de matricula: ");
    scanf("%d", &aux.matricula);
    
    for(int i = 0; i < registros; i++){
        if(matriz[i].matricula == aux.matricula){
            printf("Matricula ja existe.\n");
            return;
        }
    }
    
    printf("Nome do aluno: ");
    scanf("%s", aux.nome);
    
    printf("Curso do aluno: ");
    scanf("%s", aux.curso);
    
    printf("Nota 1: ");
    scanf("%f", &aux.nota1);
    
    printf("Nota 2: ");
    scanf("%f", &aux.nota2);
    
    matriz[registros++] = aux;
    
}

void read(){
    int aux;
    printf("Digite o numero de matricula do estudante: ");
    scanf("%d", &aux);
    for(int i = 0; i < registros ;i++){
        if(aux = matriz[i].matricula){
            
            float media;
            media = (matriz[i].nota1 + matriz[i].nota2)/2.0;

            printf("Matricula : %d ", matriz[i].matricula);
            printf("\nAluno: %s ", matriz[i].nome);
            printf("\nCurso: %s ", matriz[i].curso);
            printf("\nNota 1 : %.2f Nota 2: %.2f", matriz[i].nota1, matriz[i].nota2);
            printf("\nMedia do aluno: %.2f\n", media);
            return;
        }
    }
    
    printf("Matricula não encontrada\n");
    
}

void update(){
    int aux;
    printf("Digite a matricula do registro que quer alterar: ");
    scanf("%d", &aux);
    
    for(int i = 0; i < registros ;i++){
        if(matriz[i].matricula == aux){
            printf("Digite novo nome: ");
            scanf("%s", matriz[i].nome);
            
            printf("Digite novo curso: ");
            scanf("%s",  matriz[i].curso);
            
            printf("Digite nova nota1: ");
            scanf("%f",  &matriz[i].nota1);
            
            printf("Digite nova nota2: ");
            scanf("%f",  &matriz[i].nota2);
            
            return;
        }
    
    }
    
    printf("Matricula não encontrada\n");
    
}

void delete(){
    int aux;
    printf("Digite a matricula do registro que deseja deletar: ");
    scanf("%d", &aux);
    
    for(int i = 0; i < registros; i++){
        if(matriz[i].matricula == aux){
            char verificacao;
            printf("Deseja excluir esse registro? (S/N): ");
            scanf("%c", &verificacao);
            if(verificacao == 'S' || verificacao == 's'){
                for(int j = i; j < registros - 1; j++){
                    matriz[i] = matriz[i + 1];
                }
                registros = registros - 1;
                printf("Registro excluido");
            }else{
                printf("Operação cancelada");
            }
            return;
        }
    }

    printf("Matricula não encontrada\n");
    
}

int main() {

    int opcao;

    do {
        printf("\nSelecione uma opcao:");
        printf("\n1. Criar Registro");
        printf("\n2. Ler Registros");
        printf("\n3. Atualizar Registro");
        printf("\n4. Excluir Registro");
        printf("\n0. Sair");
        printf("\nOpcao: ");
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
                printf("Saiu do Programa\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    
    return 0;
}
