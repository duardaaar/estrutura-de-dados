#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

#define CAPACIDADE_INICIAL 1000

// Cria uma lista vazia
static ListaPalavras* criar_lista() {
    ListaPalavras *lista = malloc(sizeof(ListaPalavras));
    if (!lista) return NULL;

    lista->palavras = malloc(sizeof(char*) * CAPACIDADE_INICIAL);
    if (!lista->palavras) { free(lista); return NULL; }

    lista->quantidade = 0;
    lista->capacidade = CAPACIDADE_INICIAL;
    return lista;
}

// Adiciona uma palavra na lista, expandindo se necessário
static void adicionar_palavra(ListaPalavras *lista, const char *palavra) {
    // Ignora palavras vazias
    if (!palavra || strlen(palavra) == 0) return;

    // Expande o array se necessário (dobra a capacidade)
    if (lista->quantidade >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->palavras = realloc(lista->palavras,
                                  sizeof(char*) * lista->capacidade);
    }

    // Copia a palavra para o array
    lista->palavras[lista->quantidade] = malloc(strlen(palavra) + 1);
    strcpy(lista->palavras[lista->quantidade], palavra);
    lista->quantidade++;
}

// Converte char para minúsculo considerando acentuação básica (ISO-8859)
static char para_minusculo(unsigned char c) {
    // Letras maiúsculas acentuadas comuns em português
    // (funcionam com arquivos salvos em Latin-1/ISO-8859-1)
    if (c >= 0xC0 && c <= 0xD6) return c + 0x20; // À-Ö → à-ö
    if (c >= 0xD8 && c <= 0xDE) return c + 0x20; // Ø-Þ → ø-þ
    return tolower(c);
}

// Verifica se o caractere faz parte de uma palavra
// Aceita letras (incluindo acentuadas)
static int eh_letra(unsigned char c) {
    // Letras ASCII normais
    if (isalpha(c)) return 1;
    // Letras acentuadas (Latin-1: 0xC0 a 0xFF, exceto 0xD7 × e 0xF7 ÷)
    if (c >= 0xC0 && c != 0xD7 && c != 0xF7) return 1;
    return 0;
}

// Tokeniza o conteúdo de um arquivo já aberto e adiciona à lista
static void processar_arquivo(FILE *arquivo, ListaPalavras *lista) {
    char buffer[MAX_PALAVRA];
    int pos = 0;
    int c;

    while ((c = fgetc(arquivo)) != EOF) {
        unsigned char ch = (unsigned char)c;

        // Ignora bytes de BOM e caracteres de controle UTF-16
        if (ch == 0xFF || ch == 0xFE || ch == 0x00) continue;

        if (eh_letra(ch)) {
            // Acumula letras convertidas para minúsculo
            if (pos < MAX_PALAVRA - 1) {
                buffer[pos++] = para_minusculo(ch);
            }
        } else {
            // Fim de palavra — salva se tiver pelo menos 2 caracteres
            if (pos > 1) {
                buffer[pos] = '\0';
                adicionar_palavra(lista, buffer);
            }
            pos = 0;
        }
    }

    // Salva a última palavra se o arquivo não terminar com separador
    if (pos > 1) {
        buffer[pos] = '\0';
        adicionar_palavra(lista, buffer);
    }
}

// --- Funções públicas (exportadas pelo header) ---

ListaPalavras* tokenizar_arquivo(const char *caminho_arquivo) {
    FILE *arquivo = fopen(caminho_arquivo, "rb");
    if (!arquivo) {
        fprintf(stderr, "Erro: não foi possível abrir '%s'\n", caminho_arquivo);
        return NULL;
    }

    ListaPalavras *lista = criar_lista();
    if (!lista) { fclose(arquivo); return NULL; }

    processar_arquivo(arquivo, lista);
    fclose(arquivo);
    return lista;
}

ListaPalavras* tokenizar_arquivos(const char **arquivos, int n) {
    ListaPalavras *lista = criar_lista();
    if (!lista) return NULL;

    for (int i = 0; i < n; i++) {
        FILE *arquivo = fopen(arquivos[i], "rb");
        if (!arquivo) {
            fprintf(stderr, "Aviso: não foi possível abrir '%s', pulando...\n",
                    arquivos[i]);
            continue;
        }
        processar_arquivo(arquivo, lista);
        fclose(arquivo);
    }

    return lista;
}

void liberar_lista(ListaPalavras *lista) {
    if (!lista) return;
    for (int i = 0; i < lista->quantidade; i++) {
        free(lista->palavras[i]);
    }
    free(lista->palavras);
    free(lista);
}

void imprimir_lista(const ListaPalavras *lista) {
    if (!lista) { printf("Lista nula.\n"); return; }
    printf("Total de palavras: %d\n", lista->quantidade);
    for (int i = 0; i < lista->quantidade; i++) {
        printf("[%d] %s\n", i, lista->palavras[i]);
    }
}