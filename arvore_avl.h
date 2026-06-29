#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

// Definição da estrutura para que os outros arquivos conheçam o "No"
typedef struct No {
    char palavra[100];
    int ocorrencias;
    int altura;
    struct No* esq;
    struct No* dir;
} No;

// "Cartão de visitas" das funções que o Victor criou
No* inserir(No* no, const char* palavra);
int buscar(No* no, const char* palavra);
void liberarArvore(No* no);

#endif