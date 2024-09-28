#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

// Variáveis globais do lexer
static FILE *arquivoFonte;
static int linhaAtual = 1;
static int caractereAtual;

// Função para inicializar o lexer
void inicializaLexer(FILE *arquivo) {
    arquivoFonte = arquivo;
    linhaAtual = 1;
    caractereAtual = fgetc(arquivoFonte);
}

// Função para avançar para o próximo caractere
static void avancarCaractere() {
    if (caractereAtual == '\n') {
        linhaAtual++;
    }
    caractereAtual = fgetc(arquivoFonte);
}

// Função principal do lexer
Token obter_atomo() {
    Token token;
    token.linha = linhaAtual;

    // Ignorar espaços em branco e controlar linhas
    while (isspace(caractereAtual)) {
        avancarCaractere();
    }

    // Verificar se é o fim do arquivo
    if (caractereAtual == EOF) {
        token.tipo = TOKEN_FIM_ARQUIVO;
        return token;
    }

    // Implementar aqui a lógica para reconhecer comentários,
    // identificadores, palavras reservadas, números, etc.

    // Exemplo simplificado para identificar identificadores e palavras reservadas
    if (isalpha(caractereAtual)) {
        // Reconhecer identificador ou palavra reservada
        char lexema[16] = {0};
        int indice = 0;

        while (isalnum(caractereAtual) || caractereAtual == '_') {
            if (indice < 15) {
                lexema[indice++] = caractereAtual;
            } else {
                // Identificador com mais de 15 caracteres
                // Tratar erro
                token.tipo = TOKEN_ERRO;
                fprintf(stderr, "# %d: erro léxico, identificador muito longo\n", linhaAtual);
                // Consumir o resto do identificador
                while (isalnum(caractereAtual) || caractereAtual == '_') {
                    avancarCaractere();
                }
                return token;
            }
            avancarCaractere();
        }
        lexema[indice] = '\0';
        strcpy(token.lexema, lexema);

        // Verificar se o lexema é uma palavra reservada
        if (strcmp(lexema, "program") == 0) {
            token.tipo = TOKEN_PROGRAM;
        } else if (strcmp(lexema, "begin") == 0) {
            token.tipo = TOKEN_BEGIN;
        }
        // Adicione as outras palavras reservadas aqui
        else {
            token.tipo = TOKEN_IDENTIFICADOR;
        }
        return token;
    }

    // Implementar o reconhecimento de números, comentários, operadores, etc.

    // Caso nenhum token seja reconhecido
    token.tipo = TOKEN_ERRO;
    fprintf(stderr, "# %d: erro léxico, caractere não reconhecido '%c'\n", linhaAtual, caractereAtual);
    avancarCaractere();
    return token;
}