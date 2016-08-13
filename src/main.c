#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "vetorDinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"
#include "dicionarioestatico.h"
#include "stringaed.h"
#include "dicionariodinamico.h"
#include <time.h>
#include "termo.h"

short caracterEhValido(char c) {
    return (97 <= c && c <= 122) //a-z
        || (65 <= c && c <= 90) //A-Z
        || (48 <= c && c <= 57) //n�meros 0-9
        || (45 == c)
        || (128 <= c && c <= 154) //caracteres especiais (1)
        || (160 <= c && c <= 165)
        || (181 <= c && c <= 183)
        || (198 <= c && c <= 199)
        || (224 == c || 229 == c) // �, �
        || (233 == c);
}

int lerPalavra(FILE *fp, char *word)
{
	short typing=1;
    char c;
	//auxiliares do tipo char;
	char *del = " \t\r\n`~!@#$%^&*()-_+=\\|][{}'\":;/?.>,<1234567890";

	int i = 0; word[i] = '\0';
	do{
		c = fgetc(fp);
		c = tolower(c);
		if (strchr(del, c)==NULL){
			word[i++] = c;
		}else if(c == '-' && i){
			word[i++]=c;
		}else if(c == '\n'){
			word[i] = '\0'; typing=0;
		}else if(c == ' ' && i ){
			word[i] = '\0'; typing=0;
		}else if(c == EOF){
			word[i] = '\0'; typing=0;
		}
	}while(typing && c != EOF);

	return c;
}

int compara_string_aed(const void *e1, const void *e2) { // compara strings armazenadas especificamente em um array de ponteiros void (void**)
    TStringAED *a = *(TStringAED**) e1;
    TStringAED *b = *(TStringAED**) e2;

	return strcmp((char*)a->string, (char*) b->string);
}

typedef struct {
    int x;
} TInteiro;

TInteiro *CriarInteiro(int x) {
    TInteiro *i = malloc(sizeof(TInteiro));
    i->x = x;

    return i;
}

int main() {
    FILE *base = fopen("../base/baseParalelismo", "r");


    int i = 0, n_pags_total = -1, n_palavras_pa = 0;
    char *pal;
    char *stopword = malloc(sizeof(char) * 30);
    srand(time(NULL));
    TStringAED **stopwords = malloc(sizeof(TStringAED) * 392);
    TDicionarioEstatico *sw_dicio;

    FILE *fstop = fopen("../base/stopwords_pt", "r");

    for (;lerPalavra(fstop, stopword) != EOF; i++) {
        stopwords[i] = CriarStringAED(stopword);
        stopword = malloc(sizeof(char) * 30);
    }

    qsort(stopwords, 392, sizeof(void*), compara_string_aed);

    sw_dicio = CriarDicionarioEstatico((void**)stopwords, 392);

    fclose(fstop);
    free(stopword);

    i = 0;
    pal = malloc(sizeof(char) * 30);

    TDicionarioDinamico *dict = CriarDicionarioDinamico(307);

    TVetorDinamico *palavras_por_pag = CriarVetorDinamico(300);
    TVetorDinamico *array_pre = CriarVetorDinamico(5000);
    //->
    int i_array_pre = 0;

	while(lerPalavra((FILE*)base, pal) != EOF){
        if (sw_dicio->buscar(sw_dicio, CriarStringAED(pal)) == NULL) {
            if (strcmp(pal, "pa") == 0) {
                palavras_por_pag->inserir(palavras_por_pag, CriarInteiro(0) ,n_pags_total + 1);
                n_pags_total++;
            }
            else {
                //fprintf(fw, "%s\n", pal);
                TInteiro *ii = palavras_por_pag->acessar(palavras_por_pag, n_pags_total);
                ii->x++;
                TTermo *termonovo = CriarTermo(pal);
                TTermo *termobusca = BuscaVetorDinamico(array_pre, termonovo);

                if (termobusca == NULL) {
                    termonovo->atualizar_termo(termonovo, n_pags_total);
                    array_pre->inserir(array_pre, termonovo, i_array_pre);
                    i_array_pre++;
                }
                else {
                    termobusca->atualizar_termo(termobusca, n_pags_total);
                }
            }
        }

        pal = malloc(sizeof(char) * 30);
	}

    for (int i = 0; i < i_array_pre; i++) {
        TTermo *t = array_pre->acessar(array_pre, i);
        TListaEncadeada *l = t->dado->ocorrencias;
        int tamanho_lista = l->tamanho(l);
        TListaEncadeada *lord = CriarListaEncadeadaOrdenada(CompararTfidf);


        TPreproc *pesq = l->remover_primeiro_elemento(l);

        while (pesq != NULL) {
            TInteiro *inteiro = palavras_por_pag->acessar(palavras_por_pag, pesq->dado->pag);
            atribuir_tf_idf(pesq, tamanho_lista, n_pags_total, inteiro->x);

            lord->inserir(lord, pesq);

            pesq = l->remover_primeiro_elemento(l);
        }

        free(l);
        free(t->dado->ocorrencias);
        t->dado->ocorrencias = lord;

        dict->inserir(&dict, t);
    }

    DestruirVetorDinamico(array_pre);

    char option = 'a';
    int exit = 0;

    while (1) {
        printf("1) Pesquisar por palavra no dicionario.\n2) Exibir estatisticas do dicionario.\n3) Sair do programa.\n\nInsira sua opcao: ");

        option = getchar();
        fflush(stdin);
        system("cls");

        switch(option){
            case '1':
                printf("Digite a palavra que deseja buscar (max 29 caracteres): ");
                char palavrabusca[30];
                gets(palavrabusca);
                fflush(stdin);
                strlwr(palavrabusca);
                TTermo *termobusca = CriarTermo(palavrabusca);
                TTermo *termoaux = dict->buscar(&dict, termobusca);

                if (termoaux != NULL) {

                    termoaux->imprimir(termoaux);
                }
                else {
                    printf("Palavra nao encontrada.");
                }
                break;
            case '2':
                AnaliseDicionario(dict);
                break;
            case '3':
                exit = 1;
                break;
            default:
                printf("Opcao Invalida. Escolha novamente.\n\n");
        }

        if(exit) break;

        printf("\nPressione qualquer tecla para voltar ao menu principal.");
        getch();

        system("cls");
    }

    return 0;
}
