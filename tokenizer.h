#ifndef TOKENIZER_H
#define TOKENIZER_H

/*
 * tokenizer.h
 *
 * Essa parte do projeto foi feita por Dulce Maria.
 * Ela é responsável por abrir arquivos .txt e separar as palavras.
 *
 * Como os outros integrantes do grupo devem usar isso:
 *
 *   1. Coloque os arquivos tokenizer.h e tokenizer.c no projeto de vocês
 *   2. No começo do seu arquivo escreva:  #include "tokenizer.h"
 *   3. Chame a função tokenizar_arquivo() passando o nome do arquivo .txt
 *   4. Percorra a lista de palavras e insira cada uma na sua estrutura (AVL ou Hash)
 *   5. No final, chame liberar_lista() para liberar a memória
 *
 * Exemplo de uso:
 *
 *   ListaPalavras *lista = tokenizar_arquivo("livro.txt");
 *
 *   for (int i = 0; i < lista->quantidade; i++) {
 *       // lista->palavras[i] contém cada palavra, já em minúsculo e sem pontuação
 *       inserir(lista->palavras[i]); // chame a função de vocês aqui
 *   }
 *
 *   liberar_lista(lista); // sempre libere no final
 */

// Tamanho máximo que uma palavra pode ter
#define MAX_PALAVRA 100

/*
 * Essa estrutura guarda todas as palavras encontradas no arquivo.
 *
 * Para usar:
 *   - lista->palavras[i]  → a palavra na posição i
 *   - lista->quantidade   → total de palavras encontradas
 *   (não precisa mexer no campo "capacidade, ele é só controle interno)
 */
typedef struct {
    char **palavras;
    int quantidade;
    int capacidade;
} ListaPalavras;

// Lê um arquivo .txt e retorna a lista de palavras encontradas
// Retorna NULL se o arquivo não existir ou não puder ser aberto
ListaPalavras* tokenizar_arquivo(const char *caminho_arquivo);

// Lê vários arquivos .txt de uma vez e junta tudo numa lista só
// arquivos = array com os nomes dos arquivos, n = quantos arquivos são
ListaPalavras* tokenizar_arquivos(const char **arquivos, int n);

// Libera a memória da lista — sempre chame isso no final
void liberar_lista(ListaPalavras *lista);

// Imprime todas as palavras da lista no terminal — útil para testar
void imprimir_lista(const ListaPalavras *lista);

#endif