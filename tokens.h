#ifndef TOKENS_H
#define TOKENS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    // Palavras reservadas
    TOKEN_PROGRAM,
    TOKEN_BEGIN,
    TOKEN_END,
    TOKEN_INTEGER,
    TOKEN_BOOLEAN,
    TOKEN_IF,
    TOKEN_ELIF,
    TOKEN_FOR,
    TOKEN_READ,
    TOKEN_WRITE,
    TOKEN_SET,
    TOKEN_TO,
    TOKEN_OF,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,

    // Símbolos e operadores
    TOKEN_PONTO_VIRGULA,
    TOKEN_VIRGULA,
    TOKEN_ABRE_PAR,
    TOKEN_FECHA_PAR,
    TOKEN_DOIS_PONTOS,
    TOKEN_PONTO,
    TOKEN_OP_RELACIONAL,
    TOKEN_OP_ARITMETICO,

    // Outros tokens
    TOKEN_IDENTIFICADOR,
    TOKEN_NUMERO,
    TOKEN_COMENTARIO,
    TOKEN_FIM_ARQUIVO,
    TOKEN_ERRO

} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[16]; // Para identificadores e números
    int valor;       // Valor numérico para números
    int linha;       // Número da linha do token
} Token;

#endif