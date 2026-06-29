#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

// ESTRUTURA NOO
typedef struct No {

    int valor;
    int ocorrencias;

    struct No *proximo;

} No;

// TABELA 
No *tabela[TAMANHO];

void inicializarTabela() {

    for (int i = 0; i < TAMANHO; i++) {

        tabela[i] = NULL;

    }
}

int funcaoHash(int valor) {

    return valor % TAMANHO;

}

// INSERCAO
void inserir(int valor) {

    int indice = funcaoHash(valor);

    No *atual = tabela[indice];

    while (atual != NULL) {

        if (atual->valor == valor) {

            atual->ocorrencias++;

            return;
        }

        atual = atual->proximo;
    }

    No *novo = (No*) malloc(sizeof(No));

    novo->valor = valor;

    novo->ocorrencias = 1;

    novo->proximo = tabela[indice];

    tabela[indice] = novo;
}

// BUSCANDO
void buscar(int valor) {

    int indice = funcaoHash(valor);

    No *atual = tabela[indice];

    while (atual != NULL) {

        if (atual->valor == valor) {

            printf("\\nValor %d encontrado.\\n", valor);

            return;
        }

        atual = atual->proximo;
    }

    printf("\\nValor %d nao encontrado.\\n", valor);

}

// OCORRENCIAS 
void contarOcorrencias(int valor) {

    int indice = funcaoHash(valor);

    No *atual = tabela[indice];

    while (atual != NULL) {

        if (atual->valor == valor) {

            printf("\\nO valor %d aparece %d vez(es).\\n",
                   valor,
                   atual->ocorrencias);

            return;
        }

        atual = atual->proximo;
    }

    printf("\\nO valor %d nao existe na tabela.\\n", valor);

}

// EXIBICAO TABELA
void exibirTabela() {

    printf("\\n===== TABELA HASH =====\\n");

    for (int i = 0; i < TAMANHO; i++) {

        printf("[%d] -> ", i);

        No *atual = tabela[i];

        while (atual != NULL) {

            printf("%d(%d) -> ",
                   atual->valor,
                   atual->ocorrencias);

            atual = atual->proximo;
        }

        printf("NULL\\n");
    }
}

int main() {

    inicializarTabela();

    inserir(15);
    inserir(25);
    inserir(35);
    inserir(15);
    inserir(22);
    inserir(15);

    exibirTabela();

    buscar(25);
    buscar(100);

    contarOcorrencias(15);
    contarOcorrencias(22);
    contarOcorrencias(50);

    return 0;
}
