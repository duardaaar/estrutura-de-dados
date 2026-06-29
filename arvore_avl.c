#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===================== ESTRUTURA =====================

typedef struct No {
    char palavra[100];
    int ocorrencias;
    int altura;
    struct No* esq;
    struct No* dir;
} No;

// ===================== AUXILIARES ====================

int altura(No* no) {
    return no ? no->altura : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int fatorBalanceamento(No* no) {
    return no ? altura(no->esq) - altura(no->dir) : 0;
}

void atualizarAltura(No* no) {
    if (no)
        no->altura = 1 + max(altura(no->esq), altura(no->dir));
}

No* criarNo(const char* palavra) {
    No* no = (No*)malloc(sizeof(No));
    strncpy(no->palavra, palavra, 99);
    no->palavra[99] = '\0';
    no->ocorrencias = 1;
    no->altura = 1;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

// ===================== ROTACOES ======================

No* rotacaoDireita(No* y) {
    No* x  = y->esq;
    No* T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y  = x->dir;
    No* T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    atualizarAltura(x);
    atualizarAltura(y);
    return y;
}

// ===================== BALANCEAR =====================

No* balancear(No* no) {
    atualizarAltura(no);
    int fb = fatorBalanceamento(no);

    // Left-Left
    if (fb > 1 && fatorBalanceamento(no->esq) >= 0)
        return rotacaoDireita(no);

    // Left-Right
    if (fb > 1 && fatorBalanceamento(no->esq) < 0) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    // Right-Right
    if (fb < -1 && fatorBalanceamento(no->dir) <= 0)
        return rotacaoEsquerda(no);

    // Right-Left
    if (fb < -1 && fatorBalanceamento(no->dir) > 0) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

// ===================== INSERCAO ======================

No* inserir(No* no, const char* palavra) {
    if (!no)
        return criarNo(palavra);

    int cmp = strcmp(palavra, no->palavra);

    if (cmp < 0)
        no->esq = inserir(no->esq, palavra);
    else if (cmp > 0)
        no->dir = inserir(no->dir, palavra);
    else
        no->ocorrencias++;  // palavra ja existe: incrementa

    return balancear(no);
}

// ===================== BUSCA =========================

int buscar(No* no, const char* palavra) {
    if (!no) return 0;  // nao encontrada

    int cmp = strcmp(palavra, no->palavra);

    if (cmp == 0) return no->ocorrencias;
    if (cmp < 0)  return buscar(no->esq, palavra);
    else          return buscar(no->dir, palavra);
}
