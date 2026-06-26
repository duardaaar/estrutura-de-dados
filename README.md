TOKENIZER - Leitura e separação de palavras
Feito por:  Dulce Maria : 1240207412

=========================================
O QUE ESSA PARTE FAZ
=========================================

Lê um ou mais arquivos .txt e separa todas as palavras encontradas,
devolvendo uma lista pronta para ser usada na AVL ou na Hash.

As palavras já vêm:
  - Em minúsculo (ex: "Mundo" vira "mundo")
  - Sem pontuação (ex: "olá," vira "ola")
  - Sem números
  - Sem palavras com apenas 1 letra

=========================================
ARQUIVOS
=========================================

  tokenizer.h  → header, inclua esse no seu código com #include "tokenizer.h"
  tokenizer.c  → implementação, adicione esse na hora de compilar

=========================================
COMO USAR NO SEU CÓDIGO
=========================================

1. Copie tokenizer.h e tokenizer.c para a pasta do seu projeto

2. No seu arquivo .c, inclua o header no topo:
     #include "tokenizer.h"

3. Para ler um arquivo:
     ListaPalavras *lista = tokenizar_arquivo("livro.txt");

4. Para ler vários arquivos de uma vez:
     const char *arquivos[] = {"livro1.txt", "livro2.txt"};
     ListaPalavras *lista = tokenizar_arquivos(arquivos, 2);

5. Para percorrer as palavras e inserir na sua estrutura:
     for (int i = 0; i < lista->quantidade; i++) {
         // lista->palavras[i] é a palavra atual
         sua_funcao_de_insercao(lista->palavras[i]);
     }

6. Para liberar a memória no final:
     liberar_lista(lista);

=========================================
COMO COMPILAR
=========================================

Inclua o tokenizer.c junto com os outros arquivos na compilação:

  gcc -o programa seu_arquivo.c tokenizer.c


=========================================
OBSERVAÇÃO IMPORTANTE
=========================================

Os arquivos .txt usados como entrada NÃO devem conter acentos.
Palavras como "clássico", "história" e "ação" devem ser escritas
como "classico", "historia" e "acao".

Isso é necessário porque o sistema lê os arquivos em modo binário
e o tratamento de acentos em UTF-8 exigiria uma biblioteca externa.

Se o arquivo original tiver acentos, basta abri-lo em qualquer
editor de texto e fazer um "localizar e substituir" das letras
acentuadas antes de usar no sistema.

=============================================
STOPWORDS - Lista de Exclusão e Busca Binária
Feito por: Maria Eduarda de Araújo Luiz
=============================================
O QUE ESSA PARTE FAZ

Lê o arquivo de lista de exclusão (`stopwords.txt`), armazena as palavras na memória de forma estritamente ORDENADA e disponibiliza uma função de busca rápida usando o algoritmo de BUSCA BINÁRIA.
Sempre que uma palavra for lida pelo tokenizer, ela deve passar por esse módulo para verificar se deve ser ignorada ou aceita no repositório final.

========================================= 
ARQUIVOS

stopwords.h   → header, inclua no seu código com #include "stopwords.h"
stopwords.c   → implementação da ordenação (qsort) e busca binária
stopwords.txt → arquivo de texto contendo as palavras a serem excluídas (uma por linha)

========================================= 
COMO USAR NO CÓDIGO

1. No início do programa principal, carregue a lista de exclusão:
   ListaStopwords *lista_exclusao = carregar_stopwords("stopwords.txt");

2. Ao percorrer as palavras do tokenizer, use a busca binária para filtrar:
   for (int i = 0; i < lista->quantidade; i++) {
       char *palavra = lista->palavras[i];

       if (eh_stopword(lista_exclusao, palabra)) {
           // A palavra está na lista de exclusão! Não faz nada (ignora)
       } else {
           // A palavra é válida! Pode inserir na sua estrutura
           inserir_na_avl_ou_hash(palavra);
       }
   }

3. No final do programa, libere a memória alocada:
   liberar_stopwords(lista_exclusao);

========================================= 
COMO COMPILAR

Inclua o `stopwords.c` junto com os outros arquivos na compilação do projeto:
gcc -o programa seu_arquivo.c tokenizer.c stopwords.c