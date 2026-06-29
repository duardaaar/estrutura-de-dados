#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#define TAMANHO_HASH 53 // Um número primo ideal para mapear as palavras sem colidir tanto

typedef struct NoHash {
    char palavra[100];
    int ocorrencias;
    struct NoHash *proximo;
} NoHash;

void inicializarTabela();
void inserirHash(const char *palavra);
int buscarHash(const char *palavra);
void exibirTabela();
void liberarTabela();

#endif