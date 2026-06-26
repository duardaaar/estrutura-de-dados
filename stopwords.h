#ifndef STOPWORDS_H
#define STOPWORDS_H

#define MAX_STOPWORD 50

typedef struct {
    char **palavras;
    int quantidade;
    int capacidade;
} ListaStopwords;

// carrega o arquivo de stopwords, armazena na lista e ja deixa ordenado
ListaStopwords* carregar_stopwords(const char *caminho_arquivo);

// efetua a busca binária. Retorna 1 se a palavra for uma stopword (deve excluir) ou 0 caso contrário
int eh_stopword(const ListaStopwords *lista, const char *palavra);

// Libera a memória alocada
void liberar_stopwords(ListaStopwords *lista);

#endif