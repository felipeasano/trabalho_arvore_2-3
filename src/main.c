#include "view.h"


void imprime_cab(ARQ_BIN* b){
    printf("raiz:  %d\n", b->cab.raiz);
    printf("topo:  %d\n", b->cab.topo);
    printf("livre: %d\n", b->cab.livre);
}

int main(){
    ARQ_BIN arq_indices;
    ARQ_BIN arq_dados;

    abre_arq_bin("../indices.bin", &arq_indices, sizeof(NO));
    abre_arq_bin("../dados.bin", &arq_dados, sizeof(LIVRO));

    int opcao;
    int info;
    LIVRO p;

    imprime_cab(&arq_dados);
    printf("\n");
    imprime_cab(&arq_indices);
    
    while(1){
        //system("cls");
        imprime_menu();
        scanf("%d", &opcao);

        //imprime_cab(&arq_indices);
        switch (opcao) {
            case 0:
                fecha_arq_bin(&arq_indices);
                fecha_arq_bin(&arq_dados);
                printf("Fim do Programa\n");
                return 0;
            case 1:
                p = recebeLivro();
                insere_livro(&p, &arq_indices, &arq_dados);
                puts("Livro inserido com sucesso!");
                break;
            case 2:
                //removerProduto();
                printf("Entre com o Codigo do produto a ser removido: ");
                scanf("%d*%c", &info);
                GerenciaRemocao(&arq_indices, &arq_dados, info);
                break;
            case 3:
                //imprimirInformacoesProduto();
                busca_livro(&arq_indices, &arq_dados);
                break;
            case 4:
                //imprimirListaProdutos();
                listar_livros(&arq_indices, &arq_dados);
                break;
            case 5:
                //imprimirArvore();
                imprime_por_niveis(&arq_indices);
                break;
            case 6:
                //imprimirListaLivresIndices();
                imprime_livre_index(&arq_indices);
                break;
            case 7:
                //imprimirListaLivresDados();
                imprime_livre_dados(&arq_dados);
                break;
            case 8:
                loadPath(&arq_indices, &arq_dados);
                break;
            case 9:
                printf("Total de livros: %d\n", contar_chaves(&arq_indices, &arq_dados, arq_indices.cab.raiz));
                break;
            default:
                printf("Entrada invalida\n");
                break;
        }
        system("pause");
    }
    
}