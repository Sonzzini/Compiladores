/*
Compiladores - Projeto 1
Professor Fabio Lubacheski 

Alunos :
Laura C. Balbachan dos Santos | 10390823
Paulo Sonzzini Ribeiro de Souza | 10322918

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tokens.h"
#include "lexer.h"
#include "syntactic.h"


void emptyBuffer() {
    for(int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = '\0';
    }
    posicao_atual = 0;
    printf("----------- ESVAZIANDO BUFFER -----------\n");
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

void printTokens() {
    for (int i = 0; i < linha+1; ++i) {
        printf("%d: ", i);
        for (int j = 0; j < posicoes_em_tokens[i]; ++j) {
            printf("%s ", token_para_string(tokens[i][j]));
        }
        printf("\n");
    }
}

void printTokensAsNums() {
    for (int i = 0; i < linha+1; ++i) {
        printf("%d: ", i);
        for (int j = 0; j < posicoes_em_tokens[i]; ++j) {
            printf("%d ", tokens[i][j]);
        }
        printf("\n");
    }
}

void printWholeTokensAsNums() {
    for (int i = 0; i < linha+1; ++i) {
        printf("%d: ", i);
        for (int j = 0; j < 100; ++j) {
            printf("%d ", tokens[i][j]);
        }
        printf("\n");
    }
}


void eatNextChar(const char c, FILE *arquivo) {
    static int inside_multiline_comment = 0;

    int can_go_into_buffer = 1;  // usado no '{' dos comentários e no ',' rs

    /*
        Todos esses 'c == X' são os caracteres que eu estou utilizando como delimitadores de palavra -> recognize_token(buffer)
        Eles estão sendo checados depois
    */
    if ((c == ' ' || c == ';' || c == '\n' || c == '(' || c == ')' || c == '[' || c == ']' || c == '.' || c == ',' || c == ':' || c == ';') && (posicao_atual != 0)) {
        enum TOKEN token = recognize_token(buffer);
        if (token == -1) { // token_erro
            printf("Erro encontrado na linha %d", linha);
            // Parar o programa
            exit(1);
        }
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        emptyBuffer();
    }
    if (c == '(') {
        enum TOKEN token = TOKEN_ABRE_PARENTESES;
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        emptyBuffer();
    }
    if (c == ')') {
        enum TOKEN token = TOKEN_FECHA_PARENTESES;
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        emptyBuffer();
    }

    if (c == '#') {
        while ((fgetc(arquivo)) != '\n'); 
        enum TOKEN token = TOKEN_COMENTARIO;
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        linha++;  // Passa para a próxima linha
        return;  // Interrompe o processamento para esta linha
    }

    if (c == ';') {
        enum TOKEN token = TOKEN_PONTO_VIRGULA;
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        emptyBuffer();
    }

    if (c == ',' || c == ':') {
        can_go_into_buffer = 0;
    }

    if (c == ',') {
        enum TOKEN token = TOKEN_VIRGULA;
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        emptyBuffer();
    }

    if (c == ':') {
        enum TOKEN token = TOKEN_DOIS_PONTOS;
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        emptyBuffer();
    }

    if (c == '{') {

        char next_char = fgetc(arquivo);

        if (next_char == '-') {

            inside_multiline_comment = 1;
            emptyBuffer();
            can_go_into_buffer = 0;

            while (inside_multiline_comment) {

                next_char = fgetc(arquivo);

                while (next_char != '\n' || next_char != '-') {
                    if (next_char == '-') {
                        if ((fgetc(arquivo)) != '}') {
                            inside_multiline_comment = 0;
                            enum TOKEN token = TOKEN_COMENTARIO;
                            printf("Token na linha %d: %s\n", linha, token_para_string(token));
                            tokens[linha][posicoes_em_tokens[linha]] = token;
                            posicoes_em_tokens[linha]++;
                            linha++;  // Passa para a próxima linha
                            break;
                        } else {
                            ungetc(next_char, arquivo);
                        }
                    } else if (next_char == '\n') {
                        enum TOKEN token = TOKEN_COMENTARIO;
                        printf("Token na linha %d: %s\n", linha, token_para_string(token));
                        tokens[linha][posicoes_em_tokens[linha]] = token;
                        posicoes_em_tokens[linha]++;
                        linha++;  // Passa para a próxima linha
                    }
                    next_char = fgetc(arquivo);
                }

                // te amo laura <3
            }

        } else {
            ungetc(next_char, arquivo);
        }
    }

    if (c == '\n') {
        linha++;
    }

    

    if (posicao_atual < BUFFER_SIZE && c != ' ' && c != ';' && c != '\n' && c != '(' && c != ')' && can_go_into_buffer) {
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

        eatNextChar(caractere, arquivo);

        printBufferAsArray();


        printf("Caractere: ");
        putchar(caractere);
        printf("\n");
    }



    printTokens();


    // MARK: LOOAKHEAD

    lookahead = getNextToken();

    // while(lookahead != TOKEN_END) {
    //     printf("%s\n", token_para_string(lookahead));
    //     lookahead = getNextToken();
    // }

    programa();
    
    // printf("lookahead = %s\n", token_para_string(lookahead));

    fclose(arquivo);

    return 0;
}
