#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"

// A tabela usa o tamanho definido no header
NoHash *tabela[TAMANHO_HASH];

void inicializarTabela() {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabela[i] = NULL;
    }
}

// Função Hash clássica para Strings (DJB2)
unsigned long funcaoHash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TAMANHO_HASH;
}

// INSERÇÃO
void inserirHash(const char *palavra) {
    unsigned long indice = funcaoHash(palavra);
    NoHash *atual = tabela[indice];

    // Verifica se a palavra já existe na lista encadeada daquela posição
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            atual->ocorrencias++;
            return;
        }
        atual = atual->proximo;
    }

    // Se não existir, aloca um novo nó
    NoHash *novo = (NoHash*) malloc(sizeof(NoHash));
    if (!novo) return;
    
    strncpy(novo->palavra, palavra, 99);
    novo->palavra[99] = '\0';
    novo->ocorrencias = 1;
    
    // Insere no início da lista (colisão por encadeamento)
    novo->proximo = tabela[indice];
    tabela[indice] = novo;
}

// BUSCA (Retorna a quantidade de ocorrências)
int buscarHash(const char *palavra) {
    unsigned long indice = funcaoHash(palavra);
    NoHash *atual = tabela[indice];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            return atual->ocorrencias;
        }
        atual = atual->proximo;
    }
    return 0; // Não encontrada
}

// EXIBIÇÃO DA TABELA (Mostra os índices e as listas encadeadas)
void exibirTabela() {
    printf("\n===== ESTRUTURA INTERNA DA TABELA HASH =====\n");
    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela[i] == NULL) continue; // Pula os índices vazios para o print não ficar gigante
        
        printf("[%d] -> ", i);
        NoHash *atual = tabela[i];
        while (atual != NULL) {
            printf("%s(%d) -> ", atual->palavra, atual->ocorrencias);
            atual = atual->proximo;
        }
        printf("NULL\n");
    }
}

// FUNÇÃO DE LIMPEZA
void liberarTabela() {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        NoHash *atual = tabela[i];
        while (atual != NULL) {
            NoHash *aux = atual;
            atual = atual->proximo;
            free(aux);
        }
        tabela[i] = NULL;
    }
}