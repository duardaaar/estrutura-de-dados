#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "stopwords.h"
#include "arvore_avl.h"

int main() {
    printf("==================================================\n");
    printf("      SISTEMA DE BUSCA DE PALAVRAS (VERSAO AVL)   \n");
    printf("==================================================\n\n");

    // 1. Carrega as Stopwords (Sua parte com Busca Binaria)
    printf("[1/3] Carregando lista de exclusao (Stopwords)...\n");
    ListaStopwords *lista_exclusao = carregar_stopwords("stopwords.txt");
    if (!lista_exclusao) {
        printf("Erro fatal ao carregar stopwords.txt\n");
        return 1;
    }
    printf("-> Sucesso! %d stopwords carregadas e ordenadas.\n\n", lista_exclusao->quantidade);

    // 2. Tokeniza o arquivo de texto (Parte da Dulce)
    printf("[2/3] Lendo e tokenizando o arquivo 'livro.txt'...\n");
    ListaPalavras *lista_livro = tokenizar_arquivo("livro.txt");
    if (!lista_livro) {
        printf("Erro fatal ao abrir ou processar 'livro.txt'. Verifique se o arquivo existe.\n");
        liberar_stopwords(lista_exclusao);
        return 1;
    }
    printf("-> Sucesso! %d palavras extraizadas do arquivo.\n\n", lista_livro->quantidade);

    // 3. Filtra as Stopwords e Insere na Arvore AVL (Parte do Victor + Sua busca binaria)
    printf("[3/3] Filtrando stopwords e alimentando a Arvore AVL...\n");
    No* raiz_avl = NULL;
    int palavras_inseridas = 0;
    int palavras_ignoradas = 0;

    for (int i = 0; i < lista_livro->quantidade; i++) {
        char *palavra = lista_livro->palavras[i];
        
        // Se a busca binária encontrar a palavra nas stopwords, ignora. Caso contrário, vai para a AVL
        if (eh_stopword(lista_exclusao, palavra)) {
            palavras_ignoradas++;
        } else {
            raiz_avl = inserir(raiz_avl, palavra);
            palavras_inseridas++;
        }
    }
    printf("-> Concluido!\n");
    printf("   Palavras aceitas e armazenadas na AVL: %d\n", palavras_inseridas);
    printf("   Palavras ignoradas (Stopwords): %d\n\n", palavras_ignoradas);

    // 4. Menu Interativo de Busca (Exigencia do Enunciado)
    printf("==================================================\n");
    printf("                MENU DE BUSCA (AVL)               \n");
    printf("==================================================\n");
    
    char termo_busca[100];
    while (1) {
        printf("\nDigite uma palavra para buscar (ou 'sair' para encerrar): ");
        scanf("%99s", termo_busca);

        // Condição de saída do programa
        if (strcmp(termo_busca, "sair") == 0) {
            break;
        }

        // Verifica primeiro se a palavra pesquisada era uma stopword filtrada
        if (eh_stopword(lista_exclusao, termo_busca)) {
            printf("A palavra '%s' faz parte da lista de exclusao (Stopword).\n", termo_busca);
            printf("Quantidade de ocorrencias no repositorio: 0\n");
        } else {
            // Realiza a busca na árvore AVL balanceada
            int qtd = buscar(raiz_avl, termo_busca);
            printf("A palavra '%s' foi encontrada %d vez(es) no texto.\n", termo_busca, qtd);
        }
    }

    // 5. Limpeza de memoria obrigatória antes de fechar o programa
    printf("\nLiberando memoria e encerrando o sistema...\n");
    liberar_lista(lista_livro);
    liberar_stopwords(lista_exclusao);
    liberarArvore(raiz_avl);

    printf("Sistema AVL finalizado com sucesso!\n");
    return 0;
}