#include <stdio.h>
#include "tokenizer.h"
#include "stopwords.h"

int main() {
    // 1. carrega as stopwords 
    ListaStopwords *lista_exclusao = carregar_stopwords("stopwords.txt");
    if (!lista_exclusao) return 1;

    // 2. carrega o livro do teste anterior 
    ListaPalavras *lista_livro = tokenizar_arquivo("livro.txt");
    if (!lista_livro) {
        liberar_stopwords(lista_exclusao);
        return 1;
    }

    printf("=== TESTANDO FILTRO DE EXCLUSÃO ===\n\n");
    int palavras_aceitas = 0;

    for (int i = 0; i < lista_livro->quantidade; i++) {
        char *palavra = lista_livro->palavras[i];
        
        // uso da busca binária para decidir se a palavra passa no filtro
        if (eh_stopword(lista_exclusao, palavra)) {
            printf("Palavra '%s' -> [IGNORADA] (Esta na lista de exclusao)\n", palavra);
        } else {
            printf("Palavra '%s' -> [ACEITA] (Vai para a AVL/Hash)\n", palavra);
            palavras_aceitas++;
        }
    }

    printf("\nTotal processado: %d | Aceitas: %d\n", lista_livro->quantidade, palavras_aceitas);

    // limpeza de memória
    liberar_lista(lista_livro);
    liberar_stopwords(lista_exclusao);

    return 0;
}