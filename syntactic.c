#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "syntactic.h"
#include "lexer.h"

enum TOKEN lookahead = TOKEN_ERRO;
int token_line_index = 0;
int token_pos_index = -1;

// MARK: SINTÁTICO 
enum TOKEN getNextToken() {
    do {
        token_pos_index++;

        // Verifica se chegou ao fim dos tokens da linha atual
        if (token_pos_index >= posicoes_em_tokens[token_line_index]) {
            token_line_index++;
            token_pos_index = 0;

            // // Verifica se chegou ao fim dos tokens de todas as linhas
            // if (token_line_index >= linha) {
            //     return TOKEN_EOS; // Retorna TOKEN_EOS se não houver mais tokens
            // }
        }
    } while (tokens[token_line_index][token_pos_index] == TOKEN_COMENTARIO);

    return tokens[token_line_index][token_pos_index];
}

void consome(enum TOKEN token_esperado) {
    printf("%d: %s\n", token_line_index, token_para_string(token_esperado));
    if (lookahead == token_esperado) {
        lookahead = getNextToken();
    } else {
        printf("Erro sintatico na linha %d: esperado %s, encontrado %s\n",
               token_line_index + 1,
               token_para_string(token_esperado),
               token_para_string(lookahead));
        exit(1);
    }
}
void programa() {
    consome(TOKEN_PROGRAM);
    consome(TOKEN_IDENTIFICADOR);
    consome(TOKEN_PONTO_VIRGULA);
    bloco();
    consome(TOKEN_PONTO);
}

void bloco() {
    while (lookahead == TOKEN_INTEGER || lookahead == TOKEN_BOOLEAN) {
        declaracao_de_variaveis();
    }
    comando_composto();
}

void declaracao_de_variaveis() {
    tipo();
    lista_variavel();
    consome(TOKEN_PONTO_VIRGULA);
}

void tipo() {
    if(lookahead == TOKEN_INTEGER) {
        consome(TOKEN_INTEGER);
    } 
    else if(lookahead == TOKEN_BOOLEAN) {
        consome(TOKEN_BOOLEAN);
    }
}

void lista_variavel() {
    consome(TOKEN_IDENTIFICADOR);
    while(lookahead == TOKEN_VIRGULA) {
        consome(TOKEN_VIRGULA);
        consome(TOKEN_IDENTIFICADOR);
    }
}

void comando_composto() {
    consome(TOKEN_BEGIN);
    comando();
    while(lookahead == TOKEN_PONTO_VIRGULA) {
        consome(TOKEN_PONTO_VIRGULA);
        comando();
    }
    consome(TOKEN_END);
}

void comando() {
    if (lookahead == TOKEN_READ) {
        comando_entrada();
        return;
    }
    if (lookahead == TOKEN_SET) {
        comando_atribuicao();
        return;
    }
    if (lookahead == TOKEN_IF) {
        comando_condicional();
        return;
    }
    if (lookahead == TOKEN_WRITE) {
        comando_saida();
        return;
    }
    if (lookahead == TOKEN_FOR) {
        comando_repeticao();
        return;
    }
    else {
        printf("CAIU NO ELSE\n");
        comando_composto();
        return;
    }
}

void comando_atribuicao() {
    consome(TOKEN_SET);
    consome(TOKEN_IDENTIFICADOR);
    consome(TOKEN_TO);
    expressao();
}

void comando_condicional() {
    consome(TOKEN_IF);
    expressao();
    consome(TOKEN_DOIS_PONTOS);
    comando();
    if(lookahead == TOKEN_ELIF) {
        comando();
    }
}

void comando_repeticao() {
    consome(TOKEN_FOR);
    consome(TOKEN_IDENTIFICADOR);
    consome(TOKEN_OF);
    expressao();
    consome(TOKEN_TO);
    expressao();
    consome(TOKEN_DOIS_PONTOS);
}

void comando_entrada() {
    consome(TOKEN_READ);
    consome(TOKEN_ABRE_PARENTESES);
    lista_variavel();
    consome(TOKEN_FECHA_PARENTESES);
}

void comando_saida() {
    consome(TOKEN_WRITE); // isso aqui também
    consome(TOKEN_ABRE_PARENTESES);
    expressao();
    while(lookahead == TOKEN_VIRGULA) { // conferir isso aqui 
        consome(TOKEN_VIRGULA);
        expressao();
    }
    consome(TOKEN_FECHA_PARENTESES);
}

void expressao() {
    expressao_logica();
    while(lookahead == TOKEN_OR) {
        consome(TOKEN_OR);
        expressao_logica();
    }
}

void expressao_logica() {
    expressao_relacional();
    while(lookahead == TOKEN_AND) {
        consome(TOKEN_AND);
        expressao_relacional();
    }
}

void expressao_relacional() {
    expressao_simples();
    if (lookahead == TOKEN_MENOR || lookahead == TOKEN_MENOR_IGUAL || lookahead == TOKEN_IGUAL || lookahead == TOKEN_MAIOR || lookahead == TOKEN_MAIOR_IGUAL) {
        op_relacional();
        expressao_simples();
    }
}

void op_relacional() {
    if(lookahead == TOKEN_MENOR) {
        consome(TOKEN_MENOR);
    } 
    else if(lookahead == TOKEN_MENOR_IGUAL) {
        consome(TOKEN_MENOR_IGUAL);
    }
    else if(lookahead == TOKEN_IGUAL) {
        consome(TOKEN_IGUAL);
    }
    else if(lookahead == TOKEN_MAIOR) {
        consome(TOKEN_MAIOR);
    }
    else if(lookahead == TOKEN_MAIOR_IGUAL) {
        consome(TOKEN_MAIOR_IGUAL);
    }
}

void expressao_simples() {
    termo();
    while(lookahead == TOKEN_ADD || lookahead == TOKEN_MENOS){
        consome(lookahead);
    }
    termo();
}

void termo() {
    fator();
    while(lookahead == TOKEN_MULT || lookahead == TOKEN_DIV) {
        consome(lookahead);
    }
    fator();
}

void fator() {
    if(lookahead == TOKEN_IDENTIFICADOR || isdigit(lookahead) || lookahead == TOKEN_TRUE || lookahead == TOKEN_FALSE) {
        consome(lookahead);
    } 
    else if(lookahead == TOKEN_NOT) { //?????? isso parece estar muito errado 
        fator();
    }
    else {
        consome(TOKEN_ABRE_PARENTESES);
        expressao();
        consome(TOKEN_FECHA_PARENTESES);
    }
}
