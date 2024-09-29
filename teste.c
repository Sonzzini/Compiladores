#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 15

enum TOKEN {
    // Palavras reservadas
    TOKEN_PROGRAM = 0,
    TOKEN_BEGIN = 1,
    TOKEN_AND = 2,
    TOKEN_BOOLEAN = 3,
    TOKEN_ELIF = 4,
    TOKEN_END = 5,
    TOKEN_FALSE = 6,
    TOKEN_FOR = 7,
    TOKEN_IF = 8,
    TOKEN_INTEGER = 9,
    TOKEN_NOT = 10,
    TOKEN_OF = 11,
    TOKEN_OR = 12,
    TOKEN_READ = 13,
    TOKEN_SET = 14,
    TOKEN_TO = 15,
    TOKEN_TRUE = 16,
    TOKEN_WRITE = 17,

    // pontuadores
    TOKEN_ABRE_PARENTESES = 18,
    TOKEN_FECHA_PARENTESES = 19,

    // operadores
    TOKEN_MAIOR = 20,
    TOKEN_MENOR = 21,
    TOKEN_MULT = 22,
    TOKEN_DIV = 23,
    TOKEN_ADD = 24,
    TOKEN_MENOS = 25,

    // uuuhhhh
    TOKEN_IDENTIFICADOR = 26,

    // comentários
    TOKEN_COMENTARIO = 27,

    TOKEN_ERRO = -1
};


enum ERRO_COMPILADOR {
    NORMAL = 0,

    ERRO_NAO_FECHOU_PARENTESES = 1,

    ERRO_GENERICO = -1,
};

// Não está sendo utilizada
struct Token {
    enum TOKEN token;

};

// Variáveis globais
char buffer[BUFFER_SIZE];
int posicao_atual = 0;

enum TOKEN tokens[100][100] = {0};
int posicoes_em_tokens[100] = {0};
int linha = 1;

enum ERRO_COMPILADOR estado_compilador = NORMAL;


const char* token_para_string(enum TOKEN token) {
    switch (token) {
        case TOKEN_ERRO:
            return "ERRO";
        case TOKEN_PROGRAM:
            return "PROGRAM";
        case TOKEN_BEGIN:
            return "BEGIN";
        case TOKEN_AND:
            return "AND";
        case TOKEN_BOOLEAN:
            return "BOOLEAN";
        case TOKEN_ELIF:
            return "ELIF";
        case TOKEN_END:
            return "END";
        case TOKEN_FALSE:
            return "FALSE";
        case TOKEN_FOR:
            return "FOR";
        case TOKEN_IF:
            return "IF";
        case TOKEN_INTEGER:
            return "INTEGER";
        case TOKEN_NOT:
            return "NOT";
        case TOKEN_OF:
            return "OF";
        case TOKEN_OR:
            return "OR";
        case TOKEN_READ:
            return "READ";
        case TOKEN_SET:
            return "SET";
        case TOKEN_TO:
            return "TO";
        case TOKEN_TRUE:
            return "TRUE";
        case TOKEN_WRITE:
            return "WRITE";
        case TOKEN_IDENTIFICADOR:
            return "IDENTIFICADOR";
        case TOKEN_ABRE_PARENTESES:
            return "ABRE_PARENTESES";
        case TOKEN_FECHA_PARENTESES:
            return "FECHA_PARENTESES";
        case TOKEN_COMENTARIO:
            return "COMENTARIO";
        case TOKEN_MAIOR:
            return "MAIOR";
        case TOKEN_MENOR:
            return "MENOR";
        case TOKEN_MULT:
            return "MULT";
        case TOKEN_DIV:
            return "DIV";
        case TOKEN_ADD:
            return "ADD";
        case TOKEN_MENOS:
            return "MENOS";

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
    } else if (strcmp(str, ">") == 0) {
        return TOKEN_MAIOR;
    } else if (strcmp(str, "<") == 0) {
        return TOKEN_MENOR;
    } else if (strcmp(str, "+") == 0) {
        return TOKEN_ADD;
    } else if (strcmp(str, "-") == 0) {
        return TOKEN_MENOS;
    } else if (strcmp(str, "*") == 0) {
        return TOKEN_MULT;
    } else if (strcmp(str, "/") == 0) {
        return TOKEN_DIV;
    }

    // TODO: Verificação de identificadores
    else if (islower(str[0])) {
        return recognize_identificador(str);
    }
     
    else {
        return TOKEN_ERRO;
    }
}

void check_compiler_state() {
    switch (estado_compilador) {
    case NORMAL:
        break;
    case ERRO_NAO_FECHOU_PARENTESES:
        printf("Erro na linha %d: ')' esperado", linha);
        exit(1);
    case ERRO_GENERICO:
        printf("Erro generico encontrado, encerrando o programa...");
        exit(1);
    default:
        printf("Não faço ideia kkkkkkk");
        exit(1);
    }
}


void eatNextChar(const char c, FILE *arquivo) {
    static int inside_multiline_comment = 0;

    int can_go_into_buffer = 1;  // usado no '{' dos comentários e no ',' rs

    /*
        Todos esses 'c == X' são os caracteres que eu estou utilizando como delimitadores de palavra -> recognize_token(buffer)
        Eles estão sendo checados depois
    */
    if ((c == ' ' || c == ';' || c == '\n' || c == '(' || c == ')' || c == '[' || c == ']' || c == '.' || c == ',' || c == ':') && (posicao_atual != 0)) {
        enum TOKEN token = recognize_token(buffer);
        if (token == -1) { // token_erro
            printf("Erro encontrado na linha %d", linha);
            // Parar o programa
            check_compiler_state();
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
        estado_compilador = ERRO_NAO_FECHOU_PARENTESES; // vai para estado de erro até encontrar outro parênteses
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

    if (c == ',' || c == ':') {
        can_go_into_buffer = 0;
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
        check_compiler_state(); // ------------> ERRADO, ISSO É TRABALHO DO SINTÁTICO, VER LISTA DE TOKENS GERADOS
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
