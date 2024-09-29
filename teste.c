#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 15

enum TOKEN {
    // Palavras reservadas
    TOKEN_PROGRAM,
    TOKEN_BEGIN,
    TOKEN_AND,
    TOKEN_BOOLEAN,
    TOKEN_ELIF,
    TOKEN_END,
    TOKEN_FALSE,
    TOKEN_FOR,
    TOKEN_IF,
    TOKEN_INTEGER,
    TOKEN_NOT,
    TOKEN_OF,
    TOKEN_OR,
    TOKEN_READ,
    TOKEN_SET,
    TOKEN_TO,
    TOKEN_TRUE,
    TOKEN_WRITE,

    // pontuadores
    TOKEN_ABRE_PARENTESES,
    TOKEN_FECHA_PARENTESES,


    // uuuhhhh
    TOKEN_IDENTIFICADOR,

    // comentários
    TOKEN_COMENTARIO,

    TOKEN_ERRO = -1
};

struct Token {
    enum TOKEN token;

};

// Variáveis globais
char buffer[BUFFER_SIZE];
int posicao_atual = 0;

enum TOKEN tokens[100][100] = {0};
int posicoes_em_tokens[100] = {0};
int linha = 1;


const char* token_para_string(enum TOKEN token) {
    switch (token) {
        case TOKEN_ERRO:
            return "TOKEN_ERRO";
        case TOKEN_PROGRAM:
            return "TOKEN_PROGRAM";
        case TOKEN_BEGIN:
            return "TOKEN_BEGIN";
        case TOKEN_AND:
            return "TOKEN_AND";
        case TOKEN_BOOLEAN:
            return "TOKEN_BOOLEAN";
        case TOKEN_ELIF:
            return "TOKEN_ELIF";
        case TOKEN_END:
            return "TOKEN_END";
        case TOKEN_FALSE:
            return "TOKEN_FALSE";
        case TOKEN_FOR:
            return "TOKEN_FOR";
        case TOKEN_IF:
            return "TOKEN_IF";
        case TOKEN_INTEGER:
            return "TOKEN_INTEGER";
        case TOKEN_NOT:
            return "TOKEN_NOT";
        case TOKEN_OF:
            return "TOKEN_OF";
        case TOKEN_OR:
            return "TOKEN_OR";
        case TOKEN_READ:
            return "TOKEN_READ";
        case TOKEN_SET:
            return "TOKEN_SET";
        case TOKEN_TO:
            return "TOKEN_TO";
        case TOKEN_TRUE:
            return "TOKEN_TRUE";
        case TOKEN_WRITE:
            return "TOKEN_WRITE";
        case TOKEN_IDENTIFICADOR:
            return "TOKEN_IDENTIFICADOR";
        case TOKEN_ABRE_PARENTESES:
            return "TOKEN_ABRE_PARENTESES";
        case TOKEN_FECHA_PARENTESES:
            return "TOKEN_FECHA_PARENTESES";
        case TOKEN_COMENTARIO:
            return "TOKEN_COMENTARIO";
        default:
            printf("token_num: %d", token);
            return "Nao reconhecido";
    }
}

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

void printTokens() {
    for (int i = 0; i < linha+1; ++i) {
        printf("%d: ", i);
        for (int j = 0; j < posicoes_em_tokens[i]; ++j) {
            printf("%s ", token_para_string(tokens[i][j]));
        }
        printf("\n");
    }
}

enum TOKEN recognize_identificador(const char *str) {
    int length = strlen(str);

    if (length > 15) {
        return TOKEN_ERRO;
    }

    if (!islower(str[0])) {
        return TOKEN_ERRO;
    }

    for (int i = 1; i < length; ++i) {
        if (!(islower(str[i]) || isdigit(str[i]) || str[i] == '_')) {
            return TOKEN_ERRO;
        }
    }
    
    return TOKEN_IDENTIFICADOR;
}

enum TOKEN recognize_token(const char *str) {
    if (strcmp(str, "program") == 0) {
        return TOKEN_PROGRAM;
    } else if (strcmp(str, "begin") == 0) {
        return TOKEN_BEGIN;
    } else if (strcmp(str, "end") == 0) {
        return TOKEN_END;
    } else if (strcmp(str, "and") == 0) {
        return TOKEN_AND;
    } else if (strcmp(str, "boolean") == 0) {
        return TOKEN_BOOLEAN;
    } else if (strcmp(str, "elif") == 0) {
        return TOKEN_ELIF;
    } else if (strcmp(str, "false") == 0) {
        return TOKEN_FALSE;
    } else if (strcmp(str, "for") == 0) {
        return TOKEN_FOR;
    } else if (strcmp(str, "if") == 0) {
        return TOKEN_IF;
    } else if (strcmp(str, "integer") == 0) {
        return TOKEN_INTEGER;
    } else if (strcmp(str, "not") == 0) {
        return TOKEN_NOT;
    } else if (strcmp(str, "of") == 0) {
        return TOKEN_OF;
    } else if (strcmp(str, "or") == 0) {
        return TOKEN_OR;
    } else if (strcmp(str, "read") == 0) {
        return TOKEN_READ;
    } else if (strcmp(str, "set") == 0) {
        return TOKEN_SET;
    } else if (strcmp(str, "to") == 0) {
        return TOKEN_TO;
    } else if (strcmp(str, "true") == 0) {
        return TOKEN_TRUE;
    } else if (strcmp(str, "write") == 0) {
        return TOKEN_WRITE;
    }

    // TODO: Verificação de identificadores
    else if (islower(str[0])) {
        return recognize_identificador(str);
    }
     
    else {
        return TOKEN_ERRO;
    }
}


void eatNextChar(const char c, FILE *arquivo) {
    static int inside_multiline_comment = 0;

    if ((c == ' ' || c == ';' || c == '\n' || c == '(' || c == ')' || c == '[' || c == ']' || c == '.') && (posicao_atual != 0)) { // TODO: Gerar token de chaves/colchetes
        enum TOKEN token = recognize_token(buffer);
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        // printf("%d", posicoes_em_tokens);
        emptyBuffer();
    }
    if (c == '(') {
        enum TOKEN token = TOKEN_ABRE_PARENTESES;
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        emptyBuffer();
    }
    if (c == ')') {
        enum TOKEN token = TOKEN_FECHA_PARENTESES;
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        emptyBuffer();
    }

    if (c == '#') {
        while((fgetc(arquivo)) != '\n'); 
        enum TOKEN token = TOKEN_COMENTARIO;
        printf("Token na linha %d: %s\n", linha, token_para_string(token));
        tokens[linha][posicoes_em_tokens[linha]] = token;
        posicoes_em_tokens[linha]++;
        linha++;  // Passa para a próxima linha
        return;  // Interrompe o processamento para esta linha
    }

    if (c == '{') {
        char next_char = fgetc(arquivo);
        if (next_char == '-') {
            inside_multiline_comment = 1;

            while(inside_multiline_comment) {

                while((fgetc(arquivo)) != '\n') {
                    enum TOKEN token = TOKEN_COMENTARIO;
                    printf("Token na linha %d: %s\n", linha, token_para_string(token));
                    tokens[linha][posicoes_em_tokens[linha]] = token;
                    posicoes_em_tokens[linha]++;
                    linha++;  // Passa para a próxima linha
                    return;  // Interrompe o processamento para esta linha
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

        eatNextChar(caractere, arquivo);
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

    printTokens();

    return 0;
}
