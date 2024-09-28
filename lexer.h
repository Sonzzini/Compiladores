#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

void inicializaLexer(FILE *arquivo);
Token obter_atomo();

#endif