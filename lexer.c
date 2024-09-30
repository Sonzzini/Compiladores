/*
Compiladores - Projeto 1
Professor Fabio Lubacheski 

Alunos :
Laura C. Balbachan dos Santos | 10390823
Paulo Sonzzini Ribeiro de Souza | 10322918

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

char buffer[BUFFER_SIZE] = {'\0'};
int posicao_atual = 0;
enum TOKEN tokens[100][100] = {-1};
int posicoes_em_tokens[100] = {-1};
int linha = 1;

const char* token_para_string(enum TOKEN token) {
    switch (token) {
        case TOKEN_ERRO:
            return "ERRO";
        case TOKEN_EOS:
            return "EOS";
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
        case TOKEN_MENOR_IGUAL:
            return "MENOR_IGUAL";
        case TOKEN_DIV_IGUAL:
            return "DIV_IGUAL";
        case TOKEN_MAIOR_IGUAL:
            return "MAIOR_IGUAL";
        case TOKEN_IGUAL:
             return "IGUAL";
        case TOKEN_VIRGULA:
            return "VIRGULA";
        case TOKEN_DOIS_PONTOS:
            return "DOIS_PONTOS";
        case TOKEN_PONTO_VIRGULA:
            return "PONTO_VIRGULA";
        case TOKEN_PONTO:
            return "PONTO";

        default:
            printf("token_num: %d", token);
            return "Nao reconhecido";
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

