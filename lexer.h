#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

#define BUFFER_SIZE 15

extern char buffer[BUFFER_SIZE];
extern int posicao_atual;

extern enum TOKEN tokens[100][100];
extern int posicoes_em_tokens[100];
extern int linha;


enum TOKEN recognize_token(const char *str);
enum TOKEN recognize_identificador(const char *str);
const char* token_para_string(enum TOKEN token);

#endif