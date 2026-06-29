#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "stopwords.h"
#include "tabela_hash.h"

int main() {
    printf("==================================================\n");
    printf("    SISTEMA DE BUSCA DE PALAVRAS (VERSAO HASH)    \n");
    printf("==================================================\n\n");

    inicializarTabela();

    // 1. Carrega as Stopwords (Sua parte)
    ListaStopwords *lista_exclusao = carregar_stopwords("stopwords.txt");
    if (!lista_exclusao) return 1;

    // 2. Tokeniza o arquivo (Parte da Dulce)
    ListaPalavras *lista_livro = tokenizar_arquivo("livro.txt");
    if (!lista_livro) {
        liberar_stopwords(lista_exclusao);
        return 1;
    }

    // 3. Filtra usando sua busca binária e alimenta a Tabela Hash do Yam
    for (int i = 0; i < lista_livro->quantidade; i++) {
        char *palavra = lista_livro->palavras[i];
        if (!eh_stopword(lista_exclusao, palavra)) {
            inserirHash(palavra);
        }
    }
    printf("-> Arquivo processado e Tabela Hash alimentada com sucesso!\n");

    // Exibe a tabela organizada na tela (perfeito para tirar print pro PDF)
    exibirTabela();

    // 4. Menu Interativo de Busca
    char termo_busca[100];
    while (1) {
        printf("\n[HASH] Digite uma palavra para buscar (or 'sair'): ");
        scanf("%99s", termo_busca);

        if (strcmp(termo_busca, "sair") == 0) break;

        if (eh_stopword(lista_exclusao, termo_busca)) {
            printf("A palavra '%s' e uma Stopword filtrada (0 ocorrencias).\n", termo_busca);
        } else {
            int qtd = buscarHash(termo_busca);
            printf("A palavra '%s' aparece %d vez(es) na tabela hash.\n", termo_busca, qtd);
        }
    }

    // Limpeza
    liberar_lista(lista_livro);
    liberar_stopwords(lista_exclusao);
    liberarTabela();

    printf("Sistema Hash encerrado.\n");
    return 0;
}