#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <string.h>
#include "arvore.h"

// Realiza a impressão do menu na tela
// Pré-condição: nenhuma
// Pós-condição: menu impresso na tela
void imprime_menu();

// Imprime os dados de um livro na tela
// Pré-condição: Ponteiro válido para a estrutura de livro
// Pós-condição: Dados do livro impressos na tela
void imprimeLivro(LIVRO livro);

// recebe os dados do livro pelo usuario
// pre-condicao: nenhum
// pos-condicao: livro preenchido com dados infomados pelo usuario
// entrada: nenhum
// saida: livro preenchido com dados infomados pelo usuario
LIVRO recebeLivro();

// Insere um novo livro nos arquivos de índices e dados
// Pré-condição: Ponteiro válido para a estrutura de livro, ponteiros válidos para os arquivos de índices e dados
// Pós-condição: O livro é inserido nos arquivos de índices e dados
void insere_livro(LIVRO *p, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

// Realiza a busca por um livro nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os dados do livro são exibidos na tela, se encontrado
void busca_livro(ARQ_BIN* arq_index, ARQ_BIN* arq_dados);

// Inclui um lote de produtos a partir de um arquivo
// Pré-condição: Ponteiro válido para o arquivo, ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os produtos do lote são inseridos nos arquivos de índices e dados
void incluiLote(FILE* fr, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

// Carrega o caminho dos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: O caminho dos arquivos é carregado
void loadPath(ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

// Realiza a impressão dos produtos em ordem crescente de código
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, posição inicial
// Pós-condição: Os produtos são impressos na tela em ordem crescente de código
void in_ordem(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int pos);

// pré-requisitos:O arquivo arq_index deve conter uma árvore B válida, garantindo que as posições referenciadas sejam corretas.
// O parâmetro pos deve ser um índice válido do arquivo ou -1 para indicar um nó nulo.
// pós-requisitos:A função retorna corretamente a quantidade total de chaves da árvore B.
// Nenhuma estrutura da árvore é alterada, apenas a contagem é realizada.
int contar_chaves(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int pos);

// Lista todos os livros presentes nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os livros são listados na tela
void listar_livros(ARQ_BIN* arq_index, ARQ_BIN* arq_dados);

// Imprime as posições livres no arquivo de índices
// Pré-condição: Ponteiro válido para o arquivo de índices
// Pós-condição: As posições livres são impressas na tela
void imprime_livre_index(ARQ_BIN* arq);

// Imprime as posições livres no arquivo de dados
// Pré-condição: Ponteiro válido para o arquivo de dados
// Pós-condição: As posições livres são impressas na tela
void imprime_livre_dados(ARQ_BIN* arq);

// Função para gerenciar a remoção de um produto
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, código do produto
// Pós-condição: O produto é removido dos arquivos de índices e dados
void GerenciaRemocao(ARQ_BIN *arq_index, ARQ_BIN *arq_dados, int codigo);

#endif