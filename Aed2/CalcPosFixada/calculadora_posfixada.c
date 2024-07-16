#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct Pilha {
    int numero;
    struct Pilha *prox;
} Pilha;

Pilha *topo = NULL;

void push(int operador) {
    Pilha *novo = malloc(sizeof(Pilha));

    if (novo) {
        novo->numero = operador;
        novo->prox = topo;
        topo = novo;
    } else {
        printf("erro ao alocar memoria");
    }
}

int pop() {
    if (topo == NULL) {
        printf("Pilha vazia.\n");
        exit(EXIT_FAILURE);
    }

    Pilha *aux = topo;
    int valor = aux->numero;
    topo = aux->prox;
    free(aux);
    return valor;
}

int main() {

    int n1, n2, result, operador;
    char *token, expressao[99];

    fgets(expressao, sizeof(expressao), stdin);

    token = strtok(expressao, " ");

    while (token != NULL) {
        if (isdigit(*token) || (*token == '-' && isdigit(*(token + 1)))) {
            operador = atoi(token);
            push(operador);
        } else {
            n2 = pop();
            n1 = pop();

            switch (*token) {
                case '+':
                    push(n1 + n2);
                    break;
                case '-':
                    push(n1 - n2);
                    break;
                case '*':
                    push(n1 * n2);
                    break;
                case '/':
                    push(n1 / n2);
                    break;
                case '^':
                    push(pow(n1, n2));
                    break;
                default:
                    printf("inválido: %c\n", *token);
                    exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }
    result = pop();

    printf("%d\n", result);

    return 0;
}