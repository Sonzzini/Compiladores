/*
Compiladores - Projeto 1
Professor Fabio Lubacheski 

Alunos :
Laura C. Balbachan dos Santos | 10390823
Paulo Sonzzini Ribeiro de Souza | 10322918

*/

#ifndef SYNTACTIC_H
#define SYNTACTIC_H

#include "tokens.h"

extern enum TOKEN lookahead;
extern int token_line_index;
extern int token_pos_index;

enum TOKEN getNextToken();
void consome(enum TOKEN token);
void programa();
void bloco();
void declaracao_de_variaveis();
void tipo();
void lista_variavel();
void comando_composto();
void comando();
void comando_atribuicao();
void comando_condicional();
void comando_repeticao();
void comando_entrada();
void comando_saida();
void expressao();
void expressao_logica();
void expressao_relacional();
void op_relacional();
void expressao_simples();
void termo();
void fator();

#endif