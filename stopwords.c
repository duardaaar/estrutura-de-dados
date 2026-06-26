#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stopwords.h"

#define CAPACIDADE_INICIAL_STOP 100

// função auxiliar para o qsort comparar as strings alfabeticamente
static int comparar_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

ListaStopwords* carregar_stopwords(const char *caminho_arquivo) {
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro: não foi possível abrir a lista de exclusão '%s'\n", caminho_arquivo);
        return NULL;
    }

    ListaStopwords *lista = malloc(sizeof(ListaStopwords));
    lista->quantidade = 0;
    lista->capacidade = CAPACIDADE_INICIAL_STOP;
    lista->palavras = malloc(sizeof(char*) * lista->capacidade);

    char buffer[MAX_STOPWORD];
    // lê palavra por palavra do arquivo de exclusão
    while (fscanf(arquivo, "%49s", buffer) == 1) {
        if (lista->quantidade >= lista->capacidade) {
            lista->capacidade *= 2;
            lista->palavras = realloc(lista->palavras, sizeof(char*) * lista->capacidade);
        }
        lista->palavras[lista->quantidade] = strdup(buffer);
        lista->quantidade++;
    }
    fclose(arquivo);

    // ordena a lista para permitir a busca binária
    qsort(lista->palavras, lista->quantidade, sizeof(char*), comparar_strings);

    return lista;
}

// implementação da busca binária requisitada
int eh_stopword(const ListaStopwords *lista, const char *palavra) {
    if (!lista || lista->quantidade == 0) return 0;

    int inicio = 0;
    int fim = lista->quantidade - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int comp = strcmp(palavra, lista->palavras[meio]);

        if (comp == 0) {
            return 1; // encontrou na lista de exclusão
        } else if (comp < 0) {
            fim = meio - 1; // procura na metade esquerda
        } else {
            inicio = meio + 1; // procura na metade direita
        }
    }

    return 0; // não é stopword (pode adicionar no repositório)
}

void liberar_stopwords(ListaStopwords *lista) {
    if (!lista) return;
    for (int i = 0; i < lista->quantidade; i++) {
        free(lista->palavras[i]);
    }
    free(lista->palavras);
    free(lista);
}