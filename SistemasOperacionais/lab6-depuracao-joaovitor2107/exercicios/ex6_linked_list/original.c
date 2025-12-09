#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro: falha na alocação de memória\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Função para adicionar um nó no final da lista
void appendNode(Node** head, int value) {
    Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

// Função para imprimir a lista
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

// TODO: Implemente a função para liberar toda a lista
void freeList(Node* head) {
    // Sua implementação aqui
}

int main() {
    Node* list = NULL;

    // Adiciona 10 nós
    for (int i = 0; i < 10; i++) {
        appendNode(&list, i * 10);
    }

    printList(list);

    // TODO: Libere a memória da lista

    return 0;
}
