/*
Compiladores - Projeto 1
Professor Fabio Lubacheski 

Alunos :
Laura C. Balbachan dos Santos | 10390823
Paulo Sonzzini Ribeiro de Souza | 10322918

*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "semantic.h"
#include "lexer.h"

Symbol symbolTable[TABLE_SIZE];
int symbolCount = 0;
int is_declaring_symbols = 1;

enum TOKEN last_type_token = TOKEN_ERRO;

int findSymbolIndex(const char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i; // Retorna o índice do identificador na tabela
        }
    }
    return -1; // Retorna -1 se não encontrar
}

int buscaTabelaSimbolos(const char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i; // Retorna o endereço do identificador
        }
    }
    if (strcmp(name, ".") != 0) {
        printf("Erro semântico: Identificador '%s' não declarado.\n", name);
        exit(1); // Finaliza a compilação
    }
}

int addSymbol(const char *name, enum TOKEN type, int value) {
    if (findSymbolIndex(name) != -1) {
        printf("Erro semântico: variável com nome %s já existente.", name);
        exit(1);
    }
    if (symbolCount < TABLE_SIZE && last_type_token != TOKEN_ERRO) {
        strcpy(symbolTable[symbolCount].name, name);
        symbolTable[symbolCount].type = type;
        symbolTable[symbolCount].value = value;

        symbolCount++;
        return symbolCount - 1; // Retorna o índice do símbolo adicionado
    } else {
        printf("Erro: Tabela de símbolos cheia.\n");
        return -1;
    }
}

void printSymbolTable() {
    printf("Tabela de Símbolos:\n");
    printf("Nome        Tipo              Valor\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%-11s %-17s %d\n",
               symbolTable[i].name,
               token_para_string(symbolTable[i].type),
               symbolTable[i].value);
    }
}

void printSymbolTableAddresses() {
    printf("TABELA DE SIMBOLOS\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%-10s | Endereco: %d",
            symbolTable[i].name,
            i
        );
    }
    
}

int proximoRotulo() {
    static int contador_rotulo = 0;
    return contador_rotulo++;
}