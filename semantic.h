/*
Compiladores - Projeto 1
Professor Fabio Lubacheski 

Alunos :
Laura C. Balbachan dos Santos | 10390823
Paulo Sonzzini Ribeiro de Souza | 10322918

*/

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "tokens.h"

#define TABLE_SIZE 100

typedef struct {
    char name[16];    // Nome do identificador
    enum TOKEN type;  // Tipo do identificador como token
    int value;        // Valor associado (se aplicável)
} Symbol;

Symbol symbolTable[TABLE_SIZE];
int symbolCount;
int is_declaring_symbols;
enum TOKEN last_type_token;

int findSymbolIndex(const char *name);
int buscaTabelaSimbolos(const char *name);
int addSymbol(const char *name, enum TOKEN type, int value);
void printSymbolTable();
void printSymbolTableAddresses();
int proximoRotulo();

#endif