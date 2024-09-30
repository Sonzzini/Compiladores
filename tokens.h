/*
Compiladores - Projeto 1
Professor Fabio Lubacheski 

Alunos :
Laura C. Balbachan dos Santos | 10390823
Paulo Sonzzini Ribeiro de Souza | 10322918

*/

#ifndef TOKENS_H
#define TOKENS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
    TOKEN_MAIOR = 20,           // >
    TOKEN_MENOR = 21,           // <
    TOKEN_MULT = 22,            // *
    TOKEN_DIV = 23,             // /
    TOKEN_ADD = 24,             // +
    TOKEN_MENOS = 25,           // -
    TOKEN_MENOR_IGUAL = 26,     // <=
    TOKEN_DIV_IGUAL = 27,       // /=
    TOKEN_MAIOR_IGUAL = 28,     // >=
    TOKEN_IGUAL = 29,           // =
    TOKEN_VIRGULA = 30,         // ,
    TOKEN_DOIS_PONTOS = 31,     // :  
    TOKEN_PONTO_VIRGULA = 32,   // ;
    TOKEN_PONTO = 33,           // .

    // uuuhhhh
    TOKEN_IDENTIFICADOR = 34,

    // comentários
    TOKEN_COMENTARIO = 35,
    TOKEN_EOS = 36,

    TOKEN_ERRO = -1
};

// typedef struct {
//     TipoToken tipo;
//     char lexema[16]; // Para identificadores e números
//     int valor;       // Valor numérico para números
//     int linha;       // Número da linha do token
// } Token;

#endif