#ifndef VIEW_C
#define VIEW_C

#include "view.h"

// Realiza a impressão do menu na tela
// Pré-condição: nenhuma
// Pós-condição: menu impresso na tela
void imprime_menu(){
    printf("\n\tMenu de Opcoes:\n\n");
    printf("1. Cadastrar livro\n");
    printf("2. Remover livro\n");
    printf("3. Imprimir informacoes de um livro\n");
    printf("4. Imprimir lista de todos os livro\n");
    printf("5. Imprimir arvore\n");
    printf("6. Imprimir lista de livres do arquivo de indices\n");
    printf("7. Imprimir lista de livres do arquivo de dados\n");
    printf("8. Realizar operacoes em lote\n");
    printf("9. Calcula total de livros\n");
    printf("0. Sair\n\n");

    printf("Digite a opcao desejada: ");
}

// imprime dados de um livro
// pre-condicao: nenhum
// pos-condicao: nenhum
// entrada: livro
// saida: nenhum
void imprimeLivro(LIVRO livro){
    printf("\nCodigo: %d\n", livro.cod);
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Editora: %s\n", livro.editora);
    printf("Edicao: %d\n", livro.edicao);
    printf("Ano: %d\n", livro.ano);
    printf("Preco: R$ %.2f\n", livro.preco);
    printf("Estoque: %d\n", livro.estoque);
}

// recebe os dados do livro pelo usuario
// pre-condicao: nenhum
// pos-condicao: livro preenchido com dados infomados pelo usuario
// entrada: nenhum
// saida: livro preenchido com dados infomados pelo usuario
LIVRO recebeLivro(){
    LIVRO livro;
    char tempPreco[50];

    printf("\nEntre com os dados do livro:\n\n");

    printf("Codigo: ");
    scanf("%d", &livro.cod);
    getchar(); // Consome o caractere de nova linha após a entrada do inteiro

    printf("Titulo: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    livro.autor[strcspn(livro.autor, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Editora: ");
    fgets(livro.editora, sizeof(livro.editora), stdin);
    livro.editora[strcspn(livro.editora, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Edicao: ");
    scanf("%d", &livro.edicao);

    printf("Ano: ");
    scanf("%d", &livro.ano);

    printf("Preco: ");
    getchar(); // Consome o caractere de nova linha após a entrada do inteiro
    fgets(tempPreco, sizeof(tempPreco), stdin);
    tempPreco[strcspn(tempPreco, "\n")] = '\0'; // Remove o caractere de nova linha
    for(int i = 0; i < strlen(tempPreco); i++){
        if(tempPreco[i] == ','){
            tempPreco[i] = '.';
        }
    }
    livro.preco = atof(tempPreco);

    printf("Estoque: ");
    scanf("%d", &livro.estoque);

    return livro;
}



// Insere um novo livro nos arquivos de índices e dados
// Pré-condição: Ponteiro válido para a estrutura de livro, ponteiros válidos para os arquivos de índices e dados
// Pós-condição: O livro é inserido nos arquivos de índices e dados
void insere_livro(LIVRO *p, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados){

    int pos_inserir = get_posicao_dados(arq_dados);
    arq_indices->cab.raiz = insere(arq_indices, arq_indices->cab.raiz, p->cod, pos_inserir);
    grava_cabecalho(arq_indices);
    grava_bloco(arq_dados, p, pos_inserir);
}

// Realiza a busca por um livro nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os dados do livro são exibidos na tela, se encontrado
void busca_livro(ARQ_BIN* arq_index, ARQ_BIN* arq_dados){
    if(arq_index->cab.raiz == -1){
        printf("Nenhum livro cadastrado ainda...\n");
        return;
    }

    int codigo;

    printf("Entre com o codigo do livro: ");
    scanf("%d%*c", &codigo);
    int posicao = busca(arq_index, arq_index->cab.raiz, codigo);
    if(posicao == -1){
        printf("Codigo nao cadastrado!\n");
        return;
    }
    LIVRO p;
    ler_bloco(arq_dados, posicao, &p);

    imprimeLivro(p);
}

//Realiza inclusoes em lote
//Pre-condicao: Arquivo txt com comandos e informacoes aberto
//Pos-condicao: Inclusoes do arquivo efetuadas
void incluiLote(FILE *fr, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados) {
    char text[300], *pt = NULL;
    LIVRO p;
    while (fscanf(fr, "%[^\n]%*c", text) != EOF) {
        char *token = strtok(text, ";");

        p.cod = atoi(token);
        strcpy(p.titulo, strtok(NULL, ";"));
        strcpy(p.autor, strtok(NULL, ";"));
        strcpy(p.editora, strtok(NULL, ";"));
        p.edicao = atoi(strtok(NULL, ";"));
        p.ano = atoi(strtok(NULL, ";"));
        p.preco = atof(strtok(NULL, ";"));
        p.estoque = atoi(strtok(NULL, ";"));

        // imprimeLivro(p);
        insere_livro(&p, arq_indices, arq_dados);
    }
    printf("Arquivo carregado com sucesso!\n");
    fclose(fr);
}

//Le o caminho do arquivo passado por input, e cadastra os itens nele
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Registro dos itens nos arquivos binarios
void loadPath(ARQ_BIN* arq_indices, ARQ_BIN* arq_dados){
    FILE *fr;
    char path[50];
    do{
        printf("Nome do arquivo:");
        scanf("%s%*c", path);
        fr = fopen(path, "r");
    }
    while(fr == NULL);
    incluiLote(fr, arq_indices, arq_dados);
    printf("\n");
    fclose(fr);
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//cabeçalho de indices gravado, a posição que um nó de árvore b se encontra e
//um ponteiro para um arquivo aberto de indices
//pós-requisitos: Imprime na tela os dados do arquivo de dados em ordem crescente de código
void in_ordem(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int pos){
    if(pos == -1 ) {
        return;
    }
    int i;
    LIVRO p;
    NO no;
    ler_bloco(arq_index, pos, &no);
    if(no.filho_esq != -1){
        in_ordem(arq_index, arq_dados, no.filho_esq);
    }

    ler_bloco(arq_dados, no.reg_esq, &p);
    imprimeLivro(p);

    if(no.filho_meio != -1){
        in_ordem(arq_index, arq_dados, no.filho_meio);
    }

    if(no.n == 2){
        ler_bloco(arq_dados, no.reg_dir, &p);
        imprimeLivro(p);
        if(no.filho_dir != -1){
            in_ordem(arq_index, arq_dados, no.filho_dir);
        }
    }
}

// pré-requisitos:O arquivo arq_index deve conter uma árvore B válida, garantindo que as posições referenciadas sejam corretas.
// O parâmetro pos deve ser um índice válido do arquivo ou -1 para indicar um nó nulo.
// pós-requisitos:A função retorna corretamente a quantidade total de chaves da árvore B.
// Nenhuma estrutura da árvore é alterada, apenas a contagem é realizada.
int contar_chaves(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int pos) {
    // if (pos == -1) {
    //     return 0;  // Caso base: nó nulo não contribui para a contagem
    // }

    // int i, total = 0;
    // NO r;

    // ler_bloco(arq_index, pos, &r);  // Lê o nó da árvore B na posição pos

    // for (i = 0; i < r.numChaves; i++) {
    //     total += contar_chaves(arq_index, arq_dados, r.filhos[i]);  // Conta à esquerda
    //     total += 1;  // Conta a chave atual
    // }

    // total += contar_chaves(arq_index, arq_dados, r.filhos[i]);  // Conta a subárvore direita
    // return total;
}

// Lista todos os livros presentes nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os livros são listados na tela
void listar_livros(ARQ_BIN* arq_index, ARQ_BIN* arq_dados){
    if(arq_index->cab.raiz == -1){
        printf("Nenhum livro cadastrado ainda...\n");
        return;
    }
    in_ordem(arq_index, arq_dados, arq_index->cab.raiz);
}

// Imprime as posições livres no arquivo de índices
// Pré-condição: Ponteiro válido para o arquivo de índices
// Pós-condição: As posições livres são impressas na tela
void imprime_livre_index(ARQ_BIN* arq){
    // if(arq->cab.livre == -1){
    //     printf("Lista de livres vazia!\n");
    //     return;
    // }

    // NO no;
    // int livre = arq->cab.livre;
    // while(livre != -1){
    //     printf("%d -> ", livre);
    //     ler_bloco(arq, livre, &no);
    //     livre = no.filhos[0];
    // }
    // printf("\n");
}

// Imprime as posições livres no arquivo de dados
// Pré-condição: Ponteiro válido para o arquivo de dados
// Pós-condição: As posições livres são impressas na tela
void imprime_livre_dados(ARQ_BIN* arq){
    if(arq->cab.livre == -1){
        printf("Lista de livres vazia!\n");
        return;
    }

    LIVRO p;
    int livre = arq->cab.livre;
    while(livre != -1){
        printf("%d -> ", livre);
        ler_bloco(arq, livre, &p);
        livre = p.cod;
    }
    printf("\n");
}

// Função para gerenciar a remoção de um livro
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, código do livro
// Pós-condição: O livro é removido dos arquivos de índices e dados
void GerenciaRemocao(ARQ_BIN *arq_index, ARQ_BIN *arq_dados, int codigo){
    // int pos, posArquivo;
    
    // posArquivo = busca(arq_index, arq_index->cab.raiz, codigo, &pos);
    // if(posArquivo == -1){
    //     printf("Codigo [%d] não encontrado\n", codigo);
    //     return;
    // }
    // NO r;
    // ler_bloco(arq_index, posArquivo, &r);
    // remover(arq_index, codigo);
    // LIVRO p;
    // ler_bloco(arq_dados, r.registro[pos], &p);
    // p.cod = arq_dados->cab.livre;
    // arq_dados->cab.livre = r.registro[pos];
    // grava_cabecalho(arq_dados);
    // grava_bloco(arq_dados, &p, r.registro[pos]);
    // printf("Codigo [%d] excluido com sucesso\n", codigo);
}

// imprime os dados de um no da arvore23
// pre-condicao: arvore existente
// pos-condicao: nenhum
// void imprime_no(NO* no){
//     if(no->n == 1){
//         printf("n = %d\n", no->n);
//         printf("[ %d |   ]\n", no->chave_esq);
//         printf("[ %d |   ]\n", no->reg_esq);
//         printf("[ %d | %d |   ]\n", no->filho_esq, no->filho_meio);
//     }else{
//         printf("n = %d\n", no->n);
//         printf("[ %d | %d ]\n", no->chave_esq, no->chave_dir);
//         printf("[ %d | %d ]\n", no->reg_esq, no->reg_dir);
//         printf("[ %d | %d | %d ]\n", no->filho_esq, no->filho_meio, no->filho_dir);
//     }
// }


#endif