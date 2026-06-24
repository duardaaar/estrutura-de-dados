#include <stdio.h>
#include "tokenizer.h"

int main() {
    // Teste 1: lendo um único arquivo
    printf("=== Teste com livro.txt ===\n\n");
    ListaPalavras *lista = tokenizar_arquivo("livro.txt");
    if (!lista) return 1;

    imprimir_lista(lista);
    liberar_lista(lista);

    // Teste 2: lendo múltiplos arquivos
    printf("\n=== Teste com múltiplos arquivos ===\n\n");
    const char *arquivos[] = {"livro.txt", "livro2.txt"};
    ListaPalavras *lista2 = tokenizar_arquivos(arquivos, 2);
    if (!lista2) return 1;

    imprimir_lista(lista2);
    liberar_lista(lista2);

    return 0;
}