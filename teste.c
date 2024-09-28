#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 15

enum TOKEN {
    TOKEN_PROGRAM,
    TOKEN_BEGIN,
    TOKEN_VARIAVEL,
    TOKEN_PALAVRA_RESERVADA,

    TOKEN_ERRO = -1
};


// Variáveis globais
char buffer[BUFFER_SIZE];
int posicao_atual = 0;

enum TOKEN tokens[100];
int linha = 1;


void emptyBuffer() {
    for(int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = '\0';
    }
    posicao_atual = 0;
}

void printBuffer() {
    printf("Conteúdo do buffer: %s\n", buffer);
}

void printBufferAsArray() {
    printf("Buffer: [");
    for(int i = 0; i < BUFFER_SIZE; ++i) {
        printf("%c", buffer[i]);
    }
    printf("]\n");
}

enum TOKEN recognize_token(const char *str) {
    if (strcmp(str, "program") == 0) {
        return TOKEN_PROGRAM;
    } else if (strcmp(str, "begin") == 0) {
        return TOKEN_BEGIN;
    } else {
        return TOKEN_ERRO;
    }
}

const char* token_para_string(enum TOKEN token) {
    switch (token) {
        case TOKEN_ERRO:
            return "TOKEN_ERRO";
        case TOKEN_PROGRAM:
            return "TOKEN_PROGRAM";
        case TOKEN_BEGIN:
            return "TOKEN_BEGIN";
        case TOKEN_PALAVRA_RESERVADA:
            return "TOKEN_PALAVRA_RESERVADA";
        default:
            return "Não reconhecido";
    }
}

void eatNextChar(const char c) {
    if ((c == ' ' || c == ';' || c == '\n') && (posicao_atual != 0)) {
        enum TOKEN token = recognize_token(buffer);
        printf("Token em %d: %s\n", linha, token_para_string(token));
        emptyBuffer();
    }
    if (c == '\n') {
        linha++;
    }
    if (posicao_atual < BUFFER_SIZE && c != ' ' && c != ';' && c != '\n') {
        buffer[posicao_atual++] = c;
    }
}


int main(int argc, char *argv[]) {
    FILE* arquivo;
    int caractere;

    buffer[0] = '\0';

    if (argc < 2) {
        printf("Uso: %s <fonte1.txt>\n", argv[0]);
        return 1;
    }

    // Abrir o arquivo de acordo com o nome fornecido por terminal
    arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo '%s'\n", argv[1]);
        return 1;
    }

    while ((caractere = fgetc(arquivo)) != EOF) {

        eatNextChar(caractere);
        printBufferAsArray();


        printf("Caractere: ");
        putchar(caractere);
        printf("\n");
    }


    // int i = 0;

    // while (i < bufferSize) {
    //     buffer[i] = "a";
    //     i++;
    // }



    // printBuffer();

    // emptyBuffer();

    // printBuffer();

    printBufferAsArray();

    return 0;
}
