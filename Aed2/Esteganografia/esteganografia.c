#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HEADER_SIZE 128
#define TAM_MAX_STR 10

void esconder(char* image_file, char* mensagem, char* output_file);
void revela(char* image_file);

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Uso correto: ./esteganografia file.jpg\n");
        return 1;
    }

    char output_file[] = "output.jpg";
    char mensagem[TAM_MAX_STR];
    int choice;

    printf("1. Esconde mensagem\n");
    printf("2. Revela a mensagem\n");
    printf("Digite: (1, 2): ");
    scanf("%d", &choice);
    getchar(); 

    switch (choice) {
        case 1:
            printf("Digite o texto a ser escondido: ");
            fgets(mensagem, TAM_MAX_STR, stdin);
            mensagem[strcspn(mensagem, "\n")] = 0; 

            esconder(argv[1], mensagem, output_file);
            break;
        case 2:
            revela(argv[1]);
            break;
        default:
            printf("Escolha invalida.\n");
            return 1;
    }

    return 0;
}

void esconder(char* image_file, char* mensagem, char* output_file) {
    FILE *file, *output_fp;
    __uint8_t header[HEADER_SIZE];
    __uint8_t pixel;
    int msg_length, i = 0;

    file = fopen(image_file, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo da imagem");
        exit(1);
    }

    fread(header, sizeof(__uint8_t), HEADER_SIZE, file);

    output_fp = fopen(output_file, "wb");
    if (!output_fp) {
        printf("Erro ao abrir output");
        fclose(file);
        exit(1);
    }

    fwrite(header, sizeof(__uint8_t), HEADER_SIZE, output_fp);

    msg_length = strlen(mensagem);

    while (fread(&pixel, sizeof(__uint8_t), 1, file) == 1 && i < msg_length * 8) {
        pixel = (pixel & 0xFE) | ((mensagem[i / 8] >> (7 - i % 8)) & 0x01);
        fwrite(&pixel, sizeof(__uint8_t), 1, output_fp);
        i++;
    }

    while (fread(&pixel, sizeof(__uint8_t), 1, file) == 1) {
        fwrite(&pixel, sizeof(__uint8_t), 1, output_fp);
    }

    fclose(file);
    fclose(output_fp);

    printf("Mensagem escondida no arquivo: %s!\n", output_file);
}

void revela(char* image_file) {
    FILE *file;
    __uint8_t header[HEADER_SIZE];
    __uint8_t pixel;
    char mensagem[TAM_MAX_STR] = {0};
    int i = 0;

    file = fopen(image_file, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo da imagem");
        exit(1);
    }

    fread(header, sizeof(__uint8_t), HEADER_SIZE, file);

    while (fread(&pixel, sizeof(__uint8_t), 1, file) == 1 && i < TAM_MAX_STR * 8) {
        mensagem[i / 8] = (mensagem[i / 8] << 1) | (pixel & 0x01);
        if ((i % 8) == 7 && mensagem[i / 8] == '\0') {
            break;
        }
        i++;
    }

    fclose(file);
    printf("Mensagem escondida: %s\n", mensagem);
}