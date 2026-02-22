#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include "hash_utils.h"

/**
 * PROCESSO COORDENADOR - Mini-Projeto 1: Quebra de Senhas Paralelo
 * 
 * Este programa coordena múltiplos workers para quebrar senhas MD5 em paralelo.
 * O MD5 JÁ ESTÁ IMPLEMENTADO - você deve focar na paralelização (fork/exec/wait).
 * 
 * Uso: ./coordinator <hash_md5> <tamanho> <charset> <num_workers>
 * 
 * Exemplo: ./coordinator "900150983cd24fb0d6963f7d28e17f72" 3 "abc" 4
 * 
 * SEU TRABALHO: Implementar os TODOs marcados abaixo
 */

#define MAX_WORKERS 16
#define RESULT_FILE "password_found.txt"

/**
 * Calcula o tamanho total do espaço de busca
 * 
 * @param charset_len Tamanho do conjunto de caracteres
 * @param password_len Comprimento da senha
 * @return Número total de combinações possíveis
 */
long long calculate_search_space(int charset_len, int password_len) {
    long long total = 1;
    for (int i = 0; i < password_len; i++) {
        total *= charset_len;
    }
    return total;
}

/**
 * Converte um índice numérico para uma senha
 * Usado para definir os limites de cada worker
 * 
 * @param index Índice numérico da senha
 * @param charset Conjunto de caracteres
 * @param charset_len Tamanho do conjunto
 * @param password_len Comprimento da senha
 * @param output Buffer para armazenar a senha gerada
 */
void index_to_password(long long index, const char *charset, int charset_len, 
                       int password_len, char *output) {
    for (int i = password_len - 1; i >= 0; i--) {
        output[i] = charset[index % charset_len];
        index /= charset_len;
    }
    output[password_len] = '\0';
}

/**
 * Função principal do coordenador
 */
int main(int argc, char *argv[]) {
    // TODO 1: Validar argumentos de entrada
    // Verificar se argc == 5 (programa + 4 argumentos)
    // Se não, imprimir mensagem de uso e sair com código 1
    
    // IMPLEMENTE AQUI: verificação de argc e mensagem de erro
    if(argc != 5){
        printf("Erro! Número insuficiente de argumentos");
        return 1;
    }
    
    // Parsing dos argumentos (após validação)
    const char *target_hash = argv[1];
    int password_len = atoi(argv[2]);
    const char *charset = argv[3];
    int num_workers = atoi(argv[4]);
    int charset_len = strlen(charset);
    
    // TODO: Adicionar validações dos parâmetros
    // - password_len deve estar entre 1 e 10
    if(password_len > 10 || password_len < 1){
        printf("Erro! Tamanho de senha deve estar entre 1 e 10");
        return 1;
    }
    // - num_workers deve estar entre 1 e MAX_WORKERS
    if(num_workers < 1 || num_workers > MAX_WORKERS){
        printf("Erro! Tamanho de workers deve estar entre 1 e %d", MAX_WORKERS);
    }
    // - charset não pode ser vazio
    if(charset == 0){
        printf("Erro! Charset não pode ser vazio");
    }
    
    printf("=== Mini-Projeto 1: Quebra de Senhas Paralelo ===\n");
    printf("Hash MD5 alvo: %s\n", target_hash);
    printf("Tamanho da senha: %d\n", password_len);
    printf("Charset: %s (tamanho: %d)\n", charset, charset_len);
    printf("Número de workers: %d\n", num_workers);
    
    // Calcular espaço de busca total
    long long total_space = calculate_search_space(charset_len, password_len);
    printf("Espaço de busca total: %lld combinações\n\n", total_space);
    
    // Remover arquivo de resultado anterior se existir
    unlink(RESULT_FILE);
    
    // Registrar tempo de início
    time_t start_time = time(NULL);
    
    // TODO 2: Dividir o espaço de busca entre os workers
    // Calcular quantas senhas cada worker deve verificar
    // DICA: Use divisão inteira e distribua o resto entre os primeiros workers
    
    // IMPLEMENTE AQUI
    // long long passwords_per_worker = ?
    // long long remaining = ?
    long long passwords_per_worker = total_space/num_workers;
    long long remaining = total_space%num_workers;

    // Arrays para armazenar PIDs dos workers
    pid_t workers[MAX_WORKERS];
    
    // TODO 3: Criar os processos workers usando fork()
    printf("Iniciando workers...\n");

    int last=0;
    // IMPLEMENTE AQUI: Loop para criar workers
    for (int i = 0; i < num_workers; i++) {
        // TODO: Calcular intervalo de senhas para este worker
        // TODO: Converter indices para senhas de inicio e fim


        pid_t pid = fork(); // TODO 4: Usar fork() para criar processo filho
        long long start_index, end_index; // TODO 5: No processo pai: armazenar PID

        if (i == 0) {
            start_index = last;
            if(remaining != 0){
                end_index = passwords_per_worker;
                remaining--;
            }
            else end_index = passwords_per_worker - 1;
        }
        else {
            start_index = last;
            if(remaining!=0) {
                end_index = start_index + passwords_per_worker;
                remaining--;
            }
            else end_index = start_index + passwords_per_worker - 1;
        }

        last = end_index+1;

        if(pid < 0){
            perror("Erro ao iniciar worker!!");
            exit(1);
        }
        else if(pid == 0){
            char start[password_len+1];
            index_to_password(start_index, charset, charset_len, password_len, start);
            char end[password_len+1];
            index_to_password(end_index, charset, charset_len, password_len, end);

            char len_str[16], id_str[16];
            sprintf(len_str, "%d", password_len);
            sprintf(id_str, "%d", i);

            execl("./worker",
                  "worker",
                  target_hash,
                  start,
                  end,
                  charset,
                  len_str,
                  id_str,
                  NULL);

            perror("Erro ao executar execl");
            exit(1);
        }
        else{
            printf("Processo filho criado!! pid: %d \n", pid);
            workers[i] = pid;
        }
        // TODO 6: No processo filho: usar execl() para executar worker
        // TODO 7: Tratar erros de fork() e execl()

    }
    
    printf("\nTodos os workers foram iniciados. Aguardando conclusão...\n");
    
    // TODO 8: Aguardar todos os workers terminarem usando wait()
    // IMPORTANTE: O pai deve aguardar TODOS os filhos para evitar zumbis
    
    // IMPLEMENTE AQUI:
    // - Loop para aguardar cada worker terminar
    // - Usar wait() para capturar status de saída
    // - Identificar qual worker terminou
    // - Verificar se terminou normalmente ou com erro
    // - Contar quantos workers terminaram
    int workers_completed = 0;
    while(workers_completed < num_workers){
        int status;
        pid_t finished_pid = wait(&status);

        if(finished_pid == -1){
            perror("Erro com wait!");
            break;
        }

        int worker_id = -1;
        for(int i = 0; i < num_workers; i++){
            if(workers[i] == finished_pid){
                worker_id = i;
                break;
            }
        }

        if(worker_id != -1){
            workers_completed++;
            if(WIFEXITED(status)){
                printf("Worker  %d PID: %d Terminou com sucesso!\n", worker_id, finished_pid);
            }
            else{
                printf("Worker %d PID: %d Terminou com erro!\n", worker_id, finished_pid);
            }
        }
        else{
            printf("Pid %d não achado na lista de workers\n", finished_pid);
            workers_completed++;
        }

    }

    // Registrar tempo de fim
    time_t end_time = time(NULL);
    double elapsed_time = difftime(end_time, start_time);
    
    printf("\n=== Resultado ===\n");
    
    // TODO 9: Verificar se algum worker encontrou a senha
    // Ler o arquivo password_found.txt se existir

    // IMPLEMENTE AQUI:
    // - Abrir arquivo RESULT_FILE para leitura
    // - Ler conteúdo do arquivo
    // - Fazer parse do formato "worker_id:password"
    // - Verificar o hash usando md5_string()
    // - Exibir resultado encontrado
    int fd = open(RESULT_FILE, O_RDONLY);

    if(fd >= 0){
        char buffer[256];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer)-1);
        close(fd);

        if(bytes_read > 0){

            buffer[bytes_read] = '\0';
            char *colen;

            int iterator = 0;
            while(iterator < bytes_read && buffer[iterator]!=':'){
                iterator++;
            }
            if(buffer[iterator] == ':') {
                 colen = &buffer[iterator];
            }
            else{
                printf("Erro no parse! Não encontrado :\n");
                return 1;
            }

            *colen = '\0';

            char *id_parse = buffer;
            int id_finder = atoi(id_parse);
            char *password_parse = colen+1;
            int len = strlen(password_parse);

            while(len > 0 && (password_parse[len-1] == '\n' ||
                              password_parse[len-1] == '\r' ||
                              password_parse[len-1] == ' ')) {
                password_parse[len-1] = '\0';
                len--;
            }

            printf("SENHA:%s\n", password_parse);

            char verification_hash[33];
            md5_string(password_parse, verification_hash);

            printf("Hash calculado: %s\n", verification_hash);
            printf("Hash esperado:  %s\n", target_hash);

            if(strcmp(verification_hash, target_hash) == 0){
                printf("[Worker %d] encontrou a senha:%s!\n", id_finder, password_parse);
            }
            else{
                printf("Senha encontrada incorreta\n");
            }

        }
        else{
            printf("Erro ao ler arquivo resultado!\n");
        }


    }
    else{
            printf("ARQUIVO RESULTADO NÃO FOI CRIADO!\n");
    }

    // Estatísticas finais (opcional)
    // TODO: Calcular e exibir estatísticas de performance
    printf("-------------------------\n");
    printf("TEMPO TOTAL DE EXECUÇÃO: %.4lf\n", elapsed_time);

    return 0;
}
