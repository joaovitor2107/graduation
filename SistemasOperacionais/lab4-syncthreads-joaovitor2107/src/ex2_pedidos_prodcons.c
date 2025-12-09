#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TAMANHO_BUFFER 10
#define NUM_PRODUTORES 3
#define NUM_CONSUMIDORES 2
#define PEDIDOS_POR_PRODUTOR 5

#define true 1
#define false 0

// Estrutura do pedido
typedef struct {
    int id;
    int cliente_id;
    int valor;
} Pedido;

// Buffer circular
typedef struct {
    Pedido pedidos[TAMANHO_BUFFER];
    int inicio;      // Índice do primeiro item
    int fim;         // Índice onde inserir próximo item
    int quantidade;  // Número de itens no buffer
} Buffer;

// Variáveis globais
Buffer buffer;
pthread_mutex_t mutex_buffer;
pthread_cond_t cond_buffer_nao_cheio;
pthread_cond_t cond_buffer_nao_vazio;
int proximo_pedido_id = 1;
int total_pedidos_produzidos = 0;
int total_pedidos_consumidos = 0;

int buffer_cheio = false;
int buffer_vazio = true;
int count_buffer_cheio = 0;
int count_buffer_vazio = 0;

// Inicializar buffer
void inicializar_buffer() {
    buffer.inicio = 0;
    buffer.fim = 0;
    buffer.quantidade = 0;
    
    // TODO: Inicializar mutex e variáveis de condição
    pthread_mutex_init(&mutex_buffer, NULL);
    pthread_cond_init(&cond_buffer_nao_cheio, NULL);
    pthread_cond_init(&cond_buffer_nao_vazio, NULL);
}

// Função do produtor (cliente fazendo pedido)
void* produtor(void* arg) {
    int produtor_id = *(int*)arg;

    for (int i = 0; i < PEDIDOS_POR_PRODUTOR; i++) {
        // Criar novo pedido
        pthread_mutex_lock(&mutex_buffer);
        Pedido novo_pedido;
        novo_pedido.cliente_id = produtor_id;
        novo_pedido.valor = rand() % 1000 + 1;  // Valor entre 1 e 1000

        // TODO: Adicionar pedido ao buffer com sincronização
        // Passos:
        // 1. Travar o mutex
        // 2. Enquanto buffer cheio, esperar com pthread_cond_wait
        // 3. Adicionar pedido ao buffer
        // 4. Atualizar índices e quantidade
        // 5. Sinalizar que buffer não está vazio
        // 6. Destravar o mutex


        if(buffer_cheio){
            printf("Buffer cheio !\n");
            count_buffer_cheio++;
        }
        while(buffer_cheio) pthread_cond_wait(&cond_buffer_nao_cheio, &mutex_buffer);

        novo_pedido.id = proximo_pedido_id++;
        buffer.pedidos[buffer.fim] = novo_pedido;
        buffer.fim = (buffer.fim + 1) % TAMANHO_BUFFER;
        buffer.quantidade++;
        total_pedidos_produzidos++;
        pthread_cond_signal(&cond_buffer_nao_vazio);

        buffer_vazio = false;
        if(buffer.quantidade == TAMANHO_BUFFER) buffer_cheio = true;

        printf("Produtor %d: Pedido #%d criado (valor: R$%d) [Buffer: %d/%d]\n", 
               produtor_id, novo_pedido.id, novo_pedido.valor, 
               buffer.quantidade, TAMANHO_BUFFER);
        
        // Simula tempo entre pedidos
        usleep(rand() % 100000);  // Até 100ms
        pthread_mutex_unlock(&mutex_buffer);
    }

    printf("Produtor %d: Finalizei meus pedidos\n", produtor_id);
    return NULL;
}

// Função do consumidor (sistema processando pedidos)
void* consumidor(void* arg) {
    int consumidor_id = *(int*)arg;
    int pedidos_processados = 0;

    while (1) {
        // TODO: Remover pedido do buffer com sincronização
        // Passos:
        // 1. Travar o mutex
        // 2. Enquanto buffer vazio e ainda há pedidos a processar, esperar
        // 3. Se não há mais pedidos a processar, sair
        // 4. Remover pedido do buffer
        // 5. Atualizar índices e quantidade
        // 6. Sinalizar que buffer não está cheio
        // 7. Destravar o mutex
        // 8. Processar pedido (fora da seção crítica)
        pthread_mutex_lock(&mutex_buffer);

        Pedido pedido;

        if(buffer_vazio){
            printf("Buffer vazio!");
            count_buffer_vazio++;
        }
        // adcionei total_pedidos_consumidos para caso chegasse em um resultado em que o buffer esta vazio mas nao tem mais elementos para serem processados ele não trave o cond
        while(buffer_vazio && total_pedidos_consumidos < NUM_PRODUTORES * PEDIDOS_POR_PRODUTOR)
            pthread_cond_wait(&cond_buffer_nao_vazio, &mutex_buffer);
        // Verificar se todos os pedidos foram processados
        if (total_pedidos_consumidos >= NUM_PRODUTORES * PEDIDOS_POR_PRODUTOR) {
            // pthread_mutex_unlock(&mutex_buffer);
            pthread_mutex_unlock(&mutex_buffer);
            break;
        }
        
        if (buffer.quantidade > 0) {
            pedido = buffer.pedidos[buffer.inicio];
            buffer.inicio = (buffer.inicio + 1) % TAMANHO_BUFFER;
            buffer.quantidade--;
            total_pedidos_consumidos++;
            pedidos_processados++;
            buffer_cheio = false;
            
            printf("Consumidor %d: Processando pedido #%d (valor: R$%d) [Buffer: %d/%d]\n", 
                   consumidor_id, pedido.id, pedido.valor, 
                   buffer.quantidade, TAMANHO_BUFFER);
            pthread_cond_signal(&cond_buffer_nao_cheio);
        }
        if(buffer.quantidade == 0) buffer_vazio = true;

        pthread_mutex_unlock(&mutex_buffer);
        // Simula tempo de processamento
        usleep(rand() % 150000);  // Até 150ms
    }
    
    printf("Consumidor %d: Processei %d pedidos\n", consumidor_id, pedidos_processados);
    return NULL;
}

int main() {
    pthread_t produtores[NUM_PRODUTORES];
    pthread_t consumidores[NUM_CONSUMIDORES];
    int ids_produtores[NUM_PRODUTORES];
    int ids_consumidores[NUM_CONSUMIDORES];
    
    srand(time(NULL));
    
    printf("=== Sistema de Pedidos Online ===\n");
    printf("Buffer: %d posições\n", TAMANHO_BUFFER);
    printf("Produtores: %d | Consumidores: %d\n", NUM_PRODUTORES, NUM_CONSUMIDORES);
    printf("Pedidos por produtor: %d\n", PEDIDOS_POR_PRODUTOR);
    printf("Total de pedidos esperados: %d\n\n", NUM_PRODUTORES * PEDIDOS_POR_PRODUTOR);
    
    inicializar_buffer();
    
    // Criar threads consumidoras
    for (int i = 0; i < NUM_CONSUMIDORES; i++) {
        ids_consumidores[i] = i;
        pthread_create(&consumidores[i], NULL, consumidor, &ids_consumidores[i]);
    }
    
    // Criar threads produtoras
    for (int i = 0; i < NUM_PRODUTORES; i++) {
        ids_produtores[i] = i;
        pthread_create(&produtores[i], NULL, produtor, &ids_produtores[i]);
    }
    
    // Aguardar produtores
    for (int i = 0; i < NUM_PRODUTORES; i++) {
        pthread_join(produtores[i], NULL);
    }
    
    printf("\n--- Todos os produtores finalizaram ---\n");
    
    // Acordar consumidores para processar pedidos restantes
    pthread_cond_broadcast(&cond_buffer_nao_vazio);
    
    // Aguardar consumidores
    for (int i = 0; i < NUM_CONSUMIDORES; i++) {
        pthread_join(consumidores[i], NULL);
    }
    
    // TODO: Destruir mutex e variáveis de condição
    pthread_mutex_destroy(&mutex_buffer);
    pthread_cond_destroy(&cond_buffer_nao_vazio);
    pthread_cond_destroy(&cond_buffer_nao_cheio);

    printf("\n=== Resultados ===\n");
    printf("Pedidos produzidos: %d\n", total_pedidos_produzidos);
    printf("Pedidos consumidos: %d\n", total_pedidos_consumidos);
    printf("Pedidos perdidos: %d\n", total_pedidos_produzidos - total_pedidos_consumidos);
    printf("Buffer cheio: %d\n", count_buffer_cheio);
    printf("Buffer vazio: %d\n", count_buffer_vazio);
    printf("Sistema funcionou corretamente? %s\n",
           (total_pedidos_produzidos == total_pedidos_consumidos) ? "SIM" : "NÃO");
    
    return 0;
}
