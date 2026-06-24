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