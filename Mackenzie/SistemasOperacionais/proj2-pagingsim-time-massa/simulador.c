#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 4096
#define HIT 1
#define MISS 2
#define MISS_MEMORY_FULL 3
#define FIFO 0
#define CLOCK 1

/* Struct de retorno de parse_config
** Em acesses[i*2] <PID>
** Em acesses[i*2+1] <tamanho_memoria_virtual>
*/
typedef struct{
    long num_frames;
    long size_page;
    long num_processes;
    long *pid_memory;
}Config;

/* Struct de retorno de parse_acess
** Em acesses[i*2] <PID>
** Em acesses[i*2+1] <endereco_virtual> */
typedef struct{
    int lines;
    long *acesses;
}Acesses;


typedef struct{
    int frame; // em qual frame a pagina esta carregada (-1 se não estiver)
    int valid_bit; // se a pagina esta ou nao na memoria fisica
    int r_bit; // se foi recentemente acessada
}PagesTable;

typedef struct{
    int process;
    int page;
}FrameInfo;

typedef struct{
    FrameInfo *frames;
    int full;
    int curr_pos;
    int size;
} Frame;



/* Implementa algoritmo FIFO para substituição de páginas
 *
 * Substitui a página mais antiga quando não há frames livres na memória física.
 * Remove a página no frame apontado por curr_pos e insere a nova página.
 *
 * Parâmetros - page: número da página a ser alocada
 *             process: PID do processo
 *             adress: endereço virtual sendo acessado
 *             shift: deslocamento dentro da página
 *             table: tabela de páginas de todos os processos
 *             frame: estrutura de controle dos frames físicos
 */
void fifo(int page, int process, int adress, int shift,
          PagesTable **table, Frame *frame){

    int last_process = frame->frames[frame->curr_pos].process;
    int last_page = frame->frames[frame->curr_pos].page;

    printf("Acesso: PID %d, Endereço %d (Página %d, Deslocamento %d) -> PAGE FAULT -> Memória cheia. Página %d (PID %d) (Frame %d) será desalocada. -> Página %d (PID %d) alocada no Frame %d\n",
           process, adress, page, shift, last_page, last_process, frame->curr_pos, page, process, frame->curr_pos);

    table[last_process][last_page].frame = -1;
    table[last_process][last_page].valid_bit = 0;
    table[last_process][last_page].r_bit = 0;

    table[process][page].frame = frame->curr_pos;
    table[process][page].valid_bit = 1;
    table[process][page].r_bit = 1;

    frame->frames[frame->curr_pos].process = process;
    frame->frames[frame->curr_pos].page = page;

    frame->curr_pos++;
    if(frame->curr_pos == frame->size){
        frame->curr_pos = 0;
    }

}

/* Implementa algoritmo CLOCK para substituição de páginas
 *
 * Percorre os frames procurando uma página com bit de referência 0.
 * Se encontrar bit 1, zera e continua. Se encontrar bit 0, substitui.
 *
 * Parâmetros - page: número da página a ser alocada
 *             process: PID do processo
 *             adress: endereço virtual sendo acessado
 *             shift: deslocamento dentro da página
 *             table: tabela de páginas de todos os processos
 *             frame: estrutura de controle dos frames físicos
 */
void clock(int page, int process, int adress, int shift,
          PagesTable **table, Frame *frame){
    int curr_process;
    int curr_page;

    while(1){
        curr_process = frame->frames[frame->curr_pos].process;
        curr_page = frame->frames[frame->curr_pos].page;

        if(table[curr_process][curr_page].r_bit == 0){

            frame->frames[frame->curr_pos].process = process;
            frame->frames[frame->curr_pos].page = page;

            table[curr_process][curr_page].frame = -1;
            table[curr_process][curr_page].valid_bit = 0;
            table[curr_process][curr_page].r_bit = 0;

            table[process][page].frame = frame->curr_pos;
            table[process][page].valid_bit = 1;
            table[process][page].r_bit = 1;

            printf("Acesso: PID %d, Endereço %d (Página %d, Deslocamento %d) -> PAGE FAULT -> Memória cheia. Página %d (PID %d) (Frame %d) será desalocada. -> Página %d (PID %d) alocada no Frame %d\n"
, process, adress, page, shift, curr_page, curr_process, frame->curr_pos, page, process, frame->curr_pos);

            frame->curr_pos++;
            if(frame->curr_pos == frame->size){
                frame->curr_pos = 0;
            }

            break;
        }
        else{
            table[curr_process][curr_page].r_bit = 0;

            frame->curr_pos++;
            if(frame->curr_pos == frame->size){
                frame->curr_pos = 0;
            }
        }
    }

}


/* Verifica o estado de uma página na tabela de páginas
 *
 * Verifica se a página está presente na memória física e retorna
 * o tipo de situação: HIT (presente), MISS (ausente com espaço livre)
 * ou MISS_MEMORY_FULL (ausente sem espaço livre)
 *
 * Parâmetros - page: número da página a verificar
 *             process: PID do processo
 *             num_frames: tamanho da memória física
 *             tables: tabela de páginas de todos os processos
 *             frame: estrutura de controle dos frames físicos
 *
 * Retorno - HIT se página presente, MISS se ausente com espaço,
 *          MISS_MEMORY_FULL se ausente sem espaço
 */
int check_table(int page, int process, int num_frames,
                PagesTable **tables, Frame *frame){

    if(tables[process][page].frame != -1){
        return HIT;
    }
    else if(frame->full){
        return MISS_MEMORY_FULL;
    }
    else{
        return MISS;
    }
}


/* Processa um HIT na tabela de páginas
 *
 * Atualiza o bit de referência da página e exibe mensagem de HIT.
 * Chamada quando a página solicitada já está na memória física.
 *
 * Parâmetros - page: número da página
 *             process: PID do processo
 *             adress: endereço virtual acessado
 *             shift: deslocamento dentro da página
 *             tables: tabela de páginas de todos os processos
 */
void hit(int page, int process, int adress, int shift, PagesTable **tables){
    tables[process][page].r_bit = 1;
    printf("Acesso: PID %d, Endereço %d (Página %d, Deslocamento %d) -> HIT: Página %d (PID %d) já está no Frame %d\n",
           process, adress, page, shift, page, process, tables[process][page].frame);
}

/* Processa um MISS com espaço livre na memória
 *
 * Aloca a página em um frame livre e atualiza as estruturas.
 * Chamada quando há page fault mas ainda existem frames livres.
 *
 * Parâmetros - page: número da página
 *             process: PID do processo
 *             adress: endereço virtual acessado
 *             shift: deslocamento dentro da página
 *             tables: tabela de páginas de todos os processos
 *             frame: estrutura de controle dos frames físicos
 */
void miss(int page, int process, int adress, int shift,
          PagesTable **tables, Frame *frame){

    tables[process][page].frame = frame->curr_pos;
    tables[process][page].r_bit = 1;
    tables[process][page].valid_bit = 1;

    frame->frames[frame->curr_pos].process = process;
    frame->frames[frame->curr_pos].page = page;

    frame->curr_pos++;
    if(frame->curr_pos == frame->size){
        frame->curr_pos = 0;
        frame->full = 1;
    }

    printf("Acesso: PID %d, Endereço %d (Página %d, Deslocamento %d) -> PAGE FAULT -> Página %d (PID %d) alocada no Frame livre %d\n",
           process, adress, page, shift, page, process, tables[process][page].frame);


}

/* Simula o acesso à memória virtual com paginação
 *
 * Processa todos os acessos do arquivo, convertendo endereços virtuais
 * em página e deslocamento, verificando presença na memória e aplicando
 * algoritmos de substituição quando necessário.
 *
 * Parâmetros - acess: estrutura com todos os acessos a serem processados
 *             conf: configurações do sistema (frames, tamanho página, etc)
 *             algorithm: algoritmo de substituição (FIFO ou CLOCK)
 *             frame: estrutura de controle dos frames físicos
 *             tables: tabela de páginas de todos os processos
 */
void translate_virtual_adress(const Acesses acess, const Config conf,
                              int algorithm, Frame *frame, PagesTable **tables){

    int page_faults = 0;
    for(int i = 0; i < acess.lines; i++){
        int page = acess.acesses[i*2+1]/ conf.size_page;
        int shift = acess.acesses[i*2+1] % conf.size_page;
        int process = acess.acesses[i*2];

        int memory_situation = check_table(page, process, conf.num_frames, tables, frame);

        if(memory_situation == HIT){
                hit(page, process, acess.acesses[i*2+1], shift, tables);
        }
        else if(memory_situation == MISS){
                miss(page, process, acess.acesses[i*2+1], shift, tables, frame);
            page_faults++;
        }
        else if(memory_situation == MISS_MEMORY_FULL){
                page_faults++;
            if(algorithm == FIFO) fifo(page, process, acess.acesses[i*2+1], shift, tables, frame);
            else if(algorithm == CLOCK) clock(page, process, acess.acesses[i*2+1], shift, tables, frame);
        }

    }

    if(algorithm == FIFO) {
        printf("--- Simulação Finalizada (Algoritmo: fifo)\nTotal de Acessos: %d\nTotal de Page Faults: %d\n",
                                  acess.lines, page_faults);
    }
    else {
        printf("--- Simulação Finalizada (Algoritmo: clock)\nTotal de Acessos: %d\nTotal de Page Faults: %d\n",
                                  acess.lines, page_faults);
    }
}



/* Cria tabelas de páginas para todos os processos
 *
 * Aloca memória para as tabelas de páginas de cada processo,
 * calculando o número de páginas baseado no tamanho da memória virtual
 * e inicializando todas as entradas.
 *
 * Parâmetros - num_processes: número total de processos
 *             pid_memory: array com PIDs e tamanhos de memória virtual
 *             size_page: tamanho de cada página
 *
 * Retorno - array de ponteiros para as tabelas de páginas
 */
PagesTable** create_table_processes(int num_processes, long *pid_memory, int size_page){
    PagesTable **table = (PagesTable**)malloc(sizeof(PagesTable*) * num_processes);
    if(table == NULL){
        perror("Erro ao alocar memoria");
        exit(1);
    }

    int num_pages;
    for(int i = 0; i < num_processes; i++){
        if(pid_memory[i*2+1]%size_page > 0)
            num_pages = (pid_memory[i*2+1]/size_page) + 1;
        else
            num_pages = (pid_memory[i*2+1]/size_page);

        table[i] = (PagesTable*)malloc(sizeof(PagesTable) * num_pages);


        if(table[i] == NULL){
            perror("Erro ao alocar memoria");
            exit(1);
        }

        for(int j = 0; j < num_pages; j++){
            table[i][j].frame = -1;
            table[i][j].r_bit = 0;
            table[i][j].valid_bit = 0;
        }

    }

    return table;
}

/* Processa o arquivo de configuração
 *
 * Recebe como entrada o buffer com os dados lidos do arquivo de configuração
 * e faz o parsing dessas variáveis
 *
 * Parametros - buffer_config - string com o conteudo lido no arquivo
 *
 * Retorno - retorna a struct Config conf que contem os dados de numero de frames
 * na variavel num_frames, tamanho da pagina na variavel size_page, numero de processos
 * na variavel num_processes e o numero pid e memoria usada no array pid_memory
 * */
Config parse_config(char *buffer_config){
    Config conf;
    conf.num_frames = 0;
    conf.size_page = 0;
    conf.num_processes = 0;
    conf.pid_memory = NULL;

    int i = 0;
    int lines=0;

    while(buffer_config[i] != '\0'){
        if(buffer_config[i] == '\n') lines++;
        i++;
    }


    i = 0;
    int pos = 0;
    char *end_ptr = buffer_config;
    char *prev_ptr;

    while(*end_ptr != '\0' && i < lines*2){
        prev_ptr = end_ptr;
        long num = strtol(end_ptr, &end_ptr, 10);

        if(prev_ptr == end_ptr){
            end_ptr++;
            continue;
        }


        if(i == 0){
            conf.num_frames = num;
        }
        else if(i == 1){
            conf.size_page = num;
        }
        else if(i == 2){
            conf.num_processes = num;
            //printf("Quantidade de processos: %ld\n", conf.num_processes);

            conf.pid_memory = (long*)malloc(conf.num_processes * 2 * sizeof(long));

            if(conf.pid_memory == NULL){
                fprintf(stderr ,"Erro ao alocar memoria");
                exit(1);
            }
        }
        else if(i > 2){
            conf.pid_memory[pos] = num;
            pos++;

            if(pos >= conf.num_processes*2) break;
        }


        i++;
    }

    /*
    printf("NUMEROS PARSEADOS CONFIGURACAO: \n");
    printf("%ld\n", conf.num_frames);
    printf("%ld\n", conf.size_page);
    printf("%ld\n", conf.num_processes);
    for(int i = 0; i < conf.num_processes; i++){
        printf("%ld ", conf.pid_memory[i*2]);
        printf("%ld\n", conf.pid_memory[(i*2)+1]);
    }
    */

    return conf;
}


/* Processa o arquivo de acessos
 *
 * Recebe como entrada o buffer com os dados lidos do arquivo de acesso
 * e faz o parsing dessas variáveis
 *
 * Parametros - buffer_acess - string com o conteudo lido no arquivo
 *
 * Retorno - Retorna a struct acess, que contem o numero de linhas na
 * variavel linha e todos os registros de acesso no array acesses
 * */
Acesses parse_acess(char *buffer_acess){
    Acesses acess;
    int i = 0;
    acess.lines =  0;
    while(buffer_acess[i] != '\0'){
        if(buffer_acess[i] == '\n') acess.lines++;
        i++;
    }
    acess.acesses = (long*)malloc(sizeof(long) * acess.lines * 2);

    char *end_ptr = buffer_acess;
    i = 0;
    while(*end_ptr != '\0' && i < acess.lines*2){
       long num = strtol(end_ptr, &end_ptr, 10);

       acess.acesses[i] = num;

       i++;
    }

    /*
    printf("\nNUMEROS PARSEADOS ACESSO: \n");
    for(int i = 0; i < acess.lines; i++){
        printf("%ld %ld\n", acess.acesses[i*2], acess.acesses[i*2+1]);
    }
    */

    return acess;
}

/* Libera memória das tabelas de páginas
 *
 * Desaloca a memória utilizada pelas tabelas de páginas de todos
 * os processos, evitando vazamentos de memória.
 *
 * Parâmetros - table: array de ponteiros para as tabelas de páginas
 *             num_processes: número total de processos
 */
void free_table_processes(PagesTable **table, long num_processes) {
    for(int i = 0; i < num_processes; i++){
        free(table[i]);
    }

    free(table);
}

/* Função principal do simulador de paginação
 *
 * Coordena toda a simulação: lê arquivos de configuração e acesso,
 * inicializa estruturas de dados, executa simulação e libera memória.
 *
 * Parâmetros - argc: número de argumentos da linha de comando
 *             argv: array com argumentos (algoritmo, arquivo config, arquivo acessos)
 *
 * Retorno - 0 se sucesso, 1 se erro
 */
int main(int argc, char *argv[]){

    if(argc != 4){
        fprintf(stderr, "ERRO: número incorreto de argumentos\n");
        fprintf(stderr, "uso correto: %s <algoritmo> <arquivo_config> <arquivo_acessos>\n", argv[0]);
        return 1;
    }

    char *algoritimo = argv[1];
    char *arquiv_conf = argv[2];
    char *arquiv_acess = argv[3];

    int fd = open(arquiv_conf, O_RDONLY);
    if(fd == -1){
        perror("Erro ao abrir arquivo de configuração");
        return 1;
    }
    char buffer_conf[BUFFER_SIZE];
    ssize_t bytes_lidos = read(fd, buffer_conf, sizeof(buffer_conf)-1);

    if(bytes_lidos == -1){
        perror("Erro ao ler arquivo de configuração");
        close(fd);
        return 1;
    }

    buffer_conf[bytes_lidos] = '\0';
    close(fd);

    Config conf = parse_config(buffer_conf);

    PagesTable **table = create_table_processes(conf.num_processes, conf.pid_memory, conf.size_page);

    Frame *frame = (Frame*)malloc(sizeof(Frame));
    frame->curr_pos = 0;
    frame->size = conf.num_frames;
    frame->frames = (FrameInfo*)malloc(sizeof(FrameInfo)*conf.num_frames);

    fd = open(arquiv_acess, O_RDONLY);
    if(fd == -1){
        perror("Erro ao abrir arquivo de acesso");
        free_table_processes(table, conf.num_processes);
        free(conf.pid_memory);
        free(frame->frames);
        free(frame);
        return 1;
    }

    char buffer_acess[BUFFER_SIZE];
    bytes_lidos = read(fd, buffer_acess, sizeof(buffer_acess)-1);

    if(bytes_lidos == -1){
        perror("Erro ao ler arquivo de acesso");
        close(fd);
        free_table_processes(table, conf.num_processes);
        free(conf.pid_memory);
        free(frame->frames);
        free(frame);
        return 1;
    }

    buffer_acess[bytes_lidos] = '\0';
    close(fd);

    Acesses acess = parse_acess(buffer_acess);


    int algo;
    if(strcmp(algoritimo, "fifo") == 0){
        algo = FIFO;
    }
    else if(strcmp(algoritimo, "clock") == 0){
        algo = CLOCK;
    }
    else{
        printf("Algoritimo Desconhecido");
        free_table_processes(table, conf.num_processes);
        free(conf.pid_memory);
        free(acess.acesses);
        free(frame->frames);
        free(frame);
        return 1;
    }

    translate_virtual_adress(acess, conf, algo, frame, table);

    free_table_processes(table, conf.num_processes);
    free(conf.pid_memory);
    free(acess.acesses);
    free(frame->frames);
    free(frame);

    return 0;
}
