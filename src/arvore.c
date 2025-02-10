#ifndef ARVORE_C
#define ARVORE_C

#include "arvore.h"

void imprime_no(NO* no){
    printf("n = %d\n", no->n);
    printf("[ %d | %d ]\n", no->chave_esq, no->chave_dir);
    printf("[ %d | %d ]\n", no->reg_esq, no->reg_dir);
    printf("[ %d | %d | %d ]\n\n", no->filho_esq, no->filho_meio, no->filho_dir);
}

// Verifica se o nó fornecido é folha
// Pré-condição: Ponteiro para manipulador de indices válido
// Pós-condição: Nenhuma
int eh_folha(NO* no){
    return (no->filho_esq == -1);
}

void adicionaChave(ARQ_BIN* arq_indice, NO* no, int pos, int chave, int reg, int novo_filho){
    if(no->chave_esq < chave){
        no->chave_dir = chave;
        no->reg_dir = reg;
        no->filho_dir = novo_filho;
    }else{
        no->chave_dir = no->chave_esq;
        no->reg_dir = no->reg_esq;
        no->chave_esq = chave;
        no->reg_esq = reg;
        no->filho_dir = no->filho_meio;
        no->filho_meio = novo_filho;
    }
    no->n = 2;
    grava_bloco(arq_indice, no, pos);
}

int get_posicao_dados(ARQ_BIN* arq){
    int pos;
    LIVRO* livro;
    if(arq->cab.livre != -1){
        pos = arq->cab.livre;
        ler_bloco(arq, arq->cab.livre, livro);
        arq->cab.livre = livro->cod;
        grava_cabecalho(arq);
    }else{
        pos = arq->cab.topo;
        arq->cab.topo++;
    }
    grava_cabecalho(arq);
    return pos;
}

int get_posicao_indices(ARQ_BIN* arq){
    int pos;
    NO* no;
    if(arq->cab.livre != -1){
        pos = arq->cab.livre;
        ler_bloco(arq, arq->cab.livre, no);
        arq->cab.livre = no->n;
    }else{
        pos = arq->cab.topo;
        arq->cab.topo++;
    }
    grava_cabecalho(arq);
    return pos;
}

int criaNO23(ARQ_BIN* arq_index, int chave_esq, int reg_esq, int chave_dir, int reg_dir, 
                int sub_esq, int sub_meio, int sub_dir, int n){

    int pos = get_posicao_indices(arq_index);
    
    NO* no = (NO*)malloc(sizeof(NO));
    no->chave_esq = chave_esq;
    no->reg_esq = reg_esq;
    no->chave_dir = chave_dir;
    no->reg_dir = reg_dir;
    no->filho_esq = sub_esq;
    no->filho_meio = sub_meio;
    no->filho_dir = sub_dir;
    no->n = 1;
    grava_bloco(arq_index, no, pos);
    free(no);
    return pos;
}

// cria uma fila
// Pré-condição: nenhuma
// Pós-condição: fila criada
FILA* cria_fila(){
    FILA *f = (FILA*)malloc(sizeof(FILA));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

//pré-requisitos: Recebe um ponteiro não nulo para fila
//pós-requisitos: Retorna 1 se a fila for vazio e 0 se não
int fila_vazia(FILA *f){
    return f->inicio == NULL;
}

//pré-requisitos: Um ponteiro não nulo para fila
//pós-requisitos: a quantidade de elementos na fila é retornado
int fila_tam(FILA *f){
    NO_FILA* aux = f->inicio;
    int i = 0;
    while(aux){
        i++;
        aux = aux->prox;
    }
    return i;
}

// enfileira uma chave na fila
// Pré-condição: fila existente e chave a ser inserida
// Pós-condição: fila atualizada com chave
void enqueue(FILA *f, int pos){
    NO_FILA* aux = (NO_FILA*)malloc(sizeof(NO_FILA));
    aux->pos = pos;
    aux->prox = NULL;
    if(fila_vazia(f)){
        f->inicio = aux;
    }else{
        f->fim->prox = aux;
    }
    f->fim = aux;
}

// desenfileira uma chave na fila
// Pré-condição: fila existente e chave a ser removida
// Pós-condição: fila atualizada sem a chave
int dequeue(FILA* f){
    NO_FILA* aux = f->inicio;
    int pos = f->inicio->pos;
    if(f->inicio == f->fim){
        f->fim = NULL;
    }
    f->inicio = f->inicio->prox;
    free(aux);
    return pos;
}

// Imprime um nó da árvore
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Nenhuma
void imprime_noB(NO* no){
    // printf("-[");
    // for(int i = 0; i < no->numChaves; i++){
    //     printf("%d", no->chaves[i]);
    //     if(i+1 < no->numChaves) printf("|");
    // }
    // printf("]-");
}

// Imprime a árvore por níveis
// Pré-condição: Arquivo de índices aberto e contendo pelo menos o cabeçalho gravado
// Pós-condição: Impressão da árvore por níveis
void imprime_por_niveis(ARQ_BIN* arq_index){

    // if(arq_index->cab.raiz == -1){
    //     printf("Nenhum livro cadastrado ainda...\n");
    //     return;
    // }

    // FILA* fila = cria_fila();
    // if (arq_index->cab.raiz == -1) {
    //     return;
    // }
    // enqueue(fila, arq_index->cab.raiz);
    // enqueue(fila, -1);
    // while (!fila_vazia(fila)) {
    //     int pos = dequeue(fila);
    //     if (pos == -1) {
    //         printf("\n");
    //         if (!fila_vazia(fila)) {
    //             enqueue(fila, -1);
    //         }
    //         continue;
    //     }
    //     NO no;
    //     ler_bloco(arq_index, pos, &no);
    //     imprime_noB(&no);
    //     if (!eh_folha(&no)) {
    //         int n = no.numChaves;
    //         for (int i=0; i<n+1; ++i) {
    //             enqueue(fila, no.filhos[i]);
    //         }
    //     }
    // }
    // free(fila);
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos 1 nó
//gravado e o cabeçalho
//pós-requisitos: A partir do no gravado na posição "posX" faz o split do nó e salva esse novo nó
//na posição "posY". Retorna "posY", além do elemento do meio do nó onde ocorreu o split
int split(ARQ_BIN* arq_index, int pos, int chave, int reg, int sub_arvore, int* chave_promovida, int* reg_promovido) {
    int aux;
    NO* no = (NO*)malloc(sizeof(NO));
    ler_bloco(arq_index, pos, no);
    if(chave > no->chave_dir){ // nova chave entra mais a direita, promove a chave direita
        *chave_promovida = no->chave_dir;
        *reg_promovido = no->reg_dir;
        aux = no->filho_dir;
        no->filho_dir = -1;
        no->n = 1;
        grava_bloco(arq_index, no, pos);
        free(no);
        return criaNO23(arq_index, chave, reg, -1, -1, aux, sub_arvore, -1, 1);
    }
    if(chave >= no->chave_esq){ // nova chave entra no meio, a nova chave e promovida
        *chave_promovida = chave;
        *reg_promovido = reg;
        aux = no->filho_dir;
        no->filho_dir = -1;
        no->n = 1;
        grava_bloco(arq_index, no, pos);
        free(no);
        return criaNO23(arq_index, no->chave_dir, no->reg_dir, -1, -1, sub_arvore, aux, -1, 1);
    }
    // nova chave entra mais a esquerda, promove a chave esquerda
    *chave_promovida = no->chave_esq;
    *reg_promovido = no->reg_esq;
    aux = criaNO23(arq_index, no->chave_dir, no->reg_dir, -1, -1, no->filho_meio, no->filho_dir, -1, 1);
    no->chave_esq = chave;
    no->reg_esq = reg;
    no->n = 1;
    no->filho_dir = -1;
    no->filho_meio = sub_arvore;
    grava_bloco(arq_index, no, pos);
    free(no);
    return aux;
}

// Realiza uma busca na árvore para encontrar a posição de um dado específico
// Pré-condição: Ponteiro para nó válido, informação a ser buscada, ponteiro para a variável que armazenará a posição encontrada
// Pós-condição: Retorna 1 se a informação foi encontrada, caso contrário retorna 0 e atualiza a posição
int buscaPos(NO* r, int info, int * pos) {
    // for((*pos)=0; (*pos) < r->numChaves; (*pos)++)
    //     if(info == r->chaves[(*pos)])
    //         return 1;
    //     else if(info < r->chaves[(*pos)])
    //         break;
    // return 0;
}

// Função auxiliar para inserção na árvore
// Pré-condição: Ponteiro para arquivo de índices válido, posição do arquivo onde ocorrerá a inserção,
// chave e ponteiro de dado a serem inseridos
// Pós-condição: Retorna a posição onde a inserção foi realizada
int insere_aux(ARQ_BIN* arq_index, int pos, int chave, int reg, int* chave_promovida, int* reg_promovido){
    NO* no = (NO*)malloc(sizeof(NO));
    ler_bloco(arq_index, pos, no);
    if(eh_folha(no)){
        if(no->n == 1){
            adicionaChave(arq_index, no, pos, chave, reg, -1);
            return -1;
        }
        return split(arq_index, pos, chave, reg, -1, chave_promovida, reg_promovido);
    }
    int aux;
    int chave_aux;
    int reg_aux;
    if(chave < no->chave_esq){
        aux = insere_aux(arq_index, no->filho_esq, chave, reg, &chave_aux, &reg_aux);
    }else if((no->n == 1) || (chave < no->chave_dir)){
        aux = insere_aux(arq_index, no->filho_meio, chave, reg, &chave_aux, &reg_aux);
    }else{
        aux = insere_aux(arq_index, no->filho_dir, chave, reg, &chave_aux, &reg_aux);
    }

    if(aux == -1){ // nao houve split
        return -1;
    }
    if(no->n == 1){
        adicionaChave(arq_index, no, pos, chave_aux, reg_aux, aux);
        return -1;
    }else{ // precisa fazer split
        return split(arq_index, pos, chave_aux, reg_aux, aux, chave_promovida, reg_promovido);
    }
}

// Insere um novo elemento na árvore
// Pré-condição: Ponteiro para arquivo de índices válido, chave e ponteiro de dado a serem inseridos
// Pós-condição: Retorna a posição onde a inserção foi realizada
int insere(ARQ_BIN* arq_index, int pos, int chave, int reg){
    
    if(arq_index->cab.raiz == -1){
        return criaNO23(arq_index, chave, reg, -1, -1, -1, -1, -1, 1);
    }
    int chave_promovida;
    int reg_promovido;
    int aux = insere_aux(arq_index, arq_index->cab.raiz, chave, reg, &chave_promovida, &reg_promovido);
    if(aux != -1){ // cria nova raiz

        return criaNO23(arq_index, chave_promovida, reg_promovido, -1, -1, pos, aux, -1, 1);
    }
    return pos;
}

// Realiza uma busca na árvore para encontrar a posição de um dado específico
// Pré-condição: Ponteiro para arquivo de índices válido, posição do arquivo onde inicia a busca,
// código a ser buscado, ponteiro para a variável que armazenará a posição encontrada
// Pós-condição: Retorna 1 se o código foi encontrado, caso contrário retorna 0 e atualiza a posição
int busca(ARQ_BIN* arq_index, int pos_arq, int chave){
    
    NO* no = (NO*)malloc(sizeof(NO));
    if(pos_arq == -1){
        return -1;
    }

    ler_bloco(arq_index, pos_arq, no);

    // se a chave esta no no
    if(no->chave_esq == chave){
        return no->reg_esq;
    }
    if(no->n == 2 && no->chave_dir == chave){
        return no->reg_dir;
    }

    if(eh_folha(no)) return -1; // estou na folha e nao achei

    // segue a busca
    if(chave < no->chave_esq){
        return busca(arq_index, no->filho_esq, chave);
    }
    if(no->n == 1){
        return busca(arq_index, no->filho_meio, chave);
    }
    if(chave < no->chave_dir){
        return busca(arq_index, no->filho_meio, chave);
    }
    return busca(arq_index, no->filho_dir, chave);
}

//pré-requisitos: Ponteiro não nulo para nó da árvoreB
//pós-requisitos: Faz o "shift-left" a partir da posição indicada e retorna o filho que não faz mais parte
int retiraEsquerda(NO *r, int pos){
    // int i;
    // int aux;
    // aux = r->filhos[pos];
    // for(i = pos; i < r->numChaves-1; i++){
    //     r->chaves[i] = r->chaves[i+1];
    //     r->registro[i] = r->registro[i+1];
    //     r->filhos[i] = r->filhos[i+1];
    // }
    // r->filhos[i] = r->filhos[i+1];
    // r->numChaves--;
    // return aux;
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//cabeçalho de indices gravado e uma posição valida para esse arquvo
//pós-requisitos: Retornar o valor mais a direita da arvoreB a partir da posição, e a posição para o arquivo
//de dados correspontende
int sucessor(ARQ_BIN *arq_index, int posArquivo, int *ptDados){
    // NO r;
    // ler_bloco(arq_index, posArquivo, &r);
    // int Vsucessor;
    // if(eh_folha(&r)){
    //     Vsucessor =  r.chaves[r.numChaves-1];
    //     *ptDados = r.registro[r.numChaves-1];
    // } else{
    //     Vsucessor = sucessor(arq_index, r.filhos[r.numChaves], ptDados);
    // }
    // return Vsucessor;
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//cabeçalho de indices gravado e uma posição valida para esse arquvo
//pós-requisitos: Retorna 1 se o nó está com underflow, 0 caso não esteja
int underflow(ARQ_BIN* arq_index, int posArquivo){
    // int isUndeflow;
    // NO r;
    // ler_bloco(arq_index, posArquivo, &r);
    // isUndeflow = (r.numChaves < ORDEM / 2);
    // return isUndeflow;
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//cabeçalho de indices gravado e uma posição valida para esse arquvo
//pós-requisitos: Retorna 1 se o nó pode emprestar, 0 caso não possa
int podeEmprestar(ARQ_BIN* arq_index, int posArquivo){
    // NO r;
    // ler_bloco(arq_index, posArquivo, &r);
    // int pode = r.numChaves > ((ORDEM/2));
    // return pode;
}

//pré-requisitos: Ponteiro não nulo para nó da árvoreB
//pós-requisitos: Adiciona os dados do parametro nas posição 0 da arvoreB, e empura os outros uma posição
void adicionaEsquerda(NO *r, int chave, int ptDados, int nova){
    // int i = 0;
    // for(i = r->numChaves; i > 0; i--){
    //     r->chaves[i] = r->chaves[i-1];
    //     r->registro[i] = r->registro[i-1];
    //     r->filhos[i+1] = r->filhos[i];
    // }
    // r->filhos[1] = r->filhos[0];
    // r->chaves[0] = chave;
    // r->registro[0] = ptDados;
    // r->filhos[0] = nova;
    // r->numChaves++;
}

//pré-requisitos: Ponteiros não nulos para nós da árvoreB
//pós-requisitos: Passo o valor da chave do nó sem_overflow para o pai, e do pai para o nó com underflow
void emprestaEsquerda(NO *raiz, int posUnderflow, NO *com_undeflow, NO *sem_underflow){
    // int chavePai, ptDadoPai, chaveSemUnder, ptDadoSemUnder, aux;
    // chavePai = raiz->chaves[posUnderflow-1];
    // ptDadoPai = raiz->registro[posUnderflow-1];
    // chaveSemUnder = sem_underflow->chaves[sem_underflow->numChaves - 1];
    // ptDadoSemUnder = sem_underflow->registro[sem_underflow->numChaves - 1];

    // aux = sem_underflow->filhos[sem_underflow->numChaves];

    // adicionaEsquerda(com_undeflow, chavePai, ptDadoPai, aux);
    // raiz->chaves[posUnderflow-1] = chaveSemUnder;
    // raiz->registro[posUnderflow-1] = ptDadoSemUnder;

    // sem_underflow->numChaves--;
}

//pré-requisitos: Ponteiros não nulos para nós da árvoreB
//pós-requisitos: Passo o valor da chave do nó sem_overflow para o pai, e do pai para o nó com underflow
void emprestaDireita(NO *raiz, int posUnderflow, NO *com_undeflow, NO *sem_underflow){
    // int chavePai, ptDadoPai, chaveSemUnder, ptDadoSemUnder, aux;
    // chavePai = raiz->chaves[posUnderflow];
    // ptDadoPai = raiz->registro[posUnderflow];
    // chaveSemUnder = sem_underflow->chaves[0];
    // ptDadoSemUnder = sem_underflow->registro[0];
    // aux = retiraEsquerda(sem_underflow, 0);

    // com_undeflow->chaves[com_undeflow->numChaves] = chavePai;
    // com_undeflow->registro[com_undeflow->numChaves] = ptDadoPai;
    // com_undeflow->filhos[com_undeflow->numChaves+1] = aux;
    // com_undeflow->numChaves++;
    // raiz->chaves[posUnderflow] = chaveSemUnder;
    // raiz->registro[posUnderflow] = ptDadoSemUnder;
}

//pré-requisitos: Ponteiro não nulo para nó da árvoreB, e arquivo aberto
//pós-requisitos: Retorna 1 se foi possivel emprestar, e 0 se não
int empresta(ARQ_BIN* arq_index, NO *r, int posUnderflow){
    //verifica se não é o mais a direita
    // if(posUnderflow - 1 >= 0 && podeEmprestar(arq_index, r->filhos[posUnderflow-1])){
    //     NO com_undeflow;
    //     ler_bloco(arq_index, r->filhos[posUnderflow-1], &com_undeflow);

    //     NO sem_underflow;
    //     ler_bloco(arq_index, r->filhos[posUnderflow-1], &sem_underflow);

    //     emprestaEsquerda(r, posUnderflow, &com_undeflow, &sem_underflow);

    //     grava_bloco(arq_index, &com_undeflow, r->filhos[posUnderflow]);
    //     grava_bloco(arq_index, &sem_underflow, r->filhos[posUnderflow-1]);

    //     return 1;
    // }
    // //verifica se não é o mais a direita
    // if(posUnderflow + 1 <= r->numChaves && podeEmprestar(arq_index, r->filhos[posUnderflow+1])){
    //     NO com_undeflow;
    //     ler_bloco(arq_index, r->filhos[posUnderflow], &com_undeflow);

    //     NO sem_underflow;
    //     ler_bloco(arq_index, r->filhos[posUnderflow+1], &sem_underflow);
    //     //Carregar os valore que vão sofre o empresta
    //     emprestaDireita(r, posUnderflow, &com_undeflow, &sem_underflow);
    //     grava_bloco(arq_index, &com_undeflow, r->filhos[posUnderflow]);

    //     grava_bloco(arq_index, &sem_underflow, r->filhos[posUnderflow+1]);
    //     return 1;
    // }
    // return 0;
}

//pré-requisitos: Ponteiros não nulos para nós da árvoreB
//pós-requisitos: Faz a operação de merge, onde o ponteiro da esquerda sempre recebe os dados da direita
void mergeAux(NO *raiz, int posUnderflow, NO *aDireita, NO *aEsquerda, int isEsq){
    int chavePai, ptDadosPai, i, j, aux;

//     chavePai = raiz->chaves[posUnderflow - isEsq];
//     ptDadosPai = raiz->registro[posUnderflow - isEsq];
//     aEsquerda->chaves[aEsquerda->numChaves] = chavePai;
//     aEsquerda->registro[aEsquerda->numChaves] = ptDadosPai;
//     aEsquerda->numChaves++;
//     j = aEsquerda->numChaves;
//     for(i = 0; i < aDireita->numChaves; i++){
//         aEsquerda->chaves[j] = aDireita->chaves[i];
//         aEsquerda->registro[j] = aDireita->registro[i];
//         aEsquerda->filhos[j] = aDireita->filhos[i];
//         aEsquerda->numChaves++;
//         j++;
//     }
//     aEsquerda->filhos[j] = aDireita->filhos[i];
//     aux = retiraEsquerda(raiz, posUnderflow-isEsq);
//    // free(aDireita);
//     //inserirLivre
//     raiz->filhos[posUnderflow-isEsq] = aux;
}

//pré-requisitos: Ponteiro não nulo para nó da árvoreB, e arquivo aberto
//pós-requisitos: A posição com underfow deixa de estar com underflow
void merge(ARQ_BIN* arq_index, NO *r, int posUnderflow){
    // if(posUnderflow - 1 >= 0){
    //     int posExcluido = r->filhos[posUnderflow];
    //     int posContinua = r->filhos[posUnderflow - 1];
    //     NO aDireita;
    //     ler_bloco(arq_index, r->filhos[posUnderflow], &aDireita);
    //     NO aEsquerda;
    //     ler_bloco(arq_index, r->filhos[posUnderflow-1], &aEsquerda);
    //     mergeAux(r, posUnderflow, &aDireita, &aEsquerda, 1);
    //     grava_bloco(arq_index, &aEsquerda, posContinua);
    //     aDireita.filhos[0] = arq_index->cab.livre;
    //     aDireita.filhos[1] = 1245;
    //     arq_index->cab.livre = posExcluido;
    //     grava_bloco(arq_index, &aDireita, posExcluido);
    //    // printf("Adicionando Livre = %d\n", posExcluido);
    //     return;
    // }
    // //verifica se não é o mais a direita
    // if(posUnderflow + 1 <= r->numChaves ){
    //     int posExcluido = r->filhos[posUnderflow + 1];
    //     int posContinua = r->filhos[posUnderflow];
    //     NO aDireita;
    //     ler_bloco(arq_index, r->filhos[posUnderflow+1], &aDireita);
    //     NO aEsquerda;
    //     ler_bloco(arq_index, r->filhos[posUnderflow], &aEsquerda);
    //     mergeAux(r, posUnderflow, &aDireita, &aEsquerda, 0);
    //     grava_bloco(arq_index, &aEsquerda, posContinua);
    //     aDireita.filhos[0] = arq_index->cab.livre;
    //     arq_index->cab.livre = posExcluido;
    //     grava_bloco(arq_index, &aDireita, posExcluido);
    //    // printf("Adicionando Livre = %d\n", posExcluido);
    //     return;
    // }
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//cabeçalho de indices gravado e uma posição valida para esse arquvo
//pós-requisitos: Info será removido da arvoreB
void removeAux(ARQ_BIN* arq_index, int posArquvio, int info){
    // if(posArquvio == -1){
    //     printf("Elemento não encontrado");
    //     return;
    // }
    // NO r;
    // ler_bloco(arq_index, posArquvio, &r);
    // int pos;
    // if(buscaPos(&r,info, &pos)){ // O elemento está no nó
    //     if(eh_folha(&r)){
    //         retiraEsquerda(&r, pos);
    //         r.filhos[0] = -1;
    //         grava_bloco(arq_index, &r, posArquvio);
    //         return;
    //     } else{
    //         int ptDados;
    //         r.chaves[pos] = sucessor(arq_index, r.filhos[pos], &ptDados);
    //         r.registro[pos] = ptDados;
    //         info = r.chaves[pos];
    //     }
    // }
    // removeAux(arq_index, r.filhos[pos], info);
    // if(underflow(arq_index, r.filhos[pos])){
    //     if(!empresta(arq_index, &r, pos)){
    //         merge(arq_index, &r, pos);
    //     }
    // }
    // grava_bloco(arq_index, &r, posArquvio);
}


//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//cabeçalho de indices gravado
//pós-requisitos: Info será removido da arvoreB
void remover(ARQ_BIN* arq_index, int info){
    // if(arq_index->cab.raiz == -1){
    //     printf("Arvore Vazia!\n");
    //     return;
    // }
    // //verificar
    // removeAux(arq_index, arq_index->cab.raiz, info);
    // NO r;
    // ler_bloco(arq_index, arq_index->cab.raiz, &r);
    // if(r.numChaves == 0){
    //     int aux = r.filhos[0];
    //     r.filhos[0] = arq_index->cab.livre;
    //     grava_bloco(arq_index, &r, arq_index->cab.raiz);
    //     arq_index->cab.livre = arq_index->cab.raiz;
    //     arq_index->cab.raiz = aux;
    // }
    // grava_cabecalho(arq_index);
}

#endif