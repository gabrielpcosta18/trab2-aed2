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

	return strcmp(a->string, b->string);
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
    printf("Inicio\n");
    FILE *fw = fopen("../base/resultados.txt", "w");
    FILE *base = fopen("../base/baseGuarani", "r");
    int i = 0, n_pags_total = 0, n_palavras_pa = 0;
    char *pal;
    char *stopword = malloc(sizeof(char) * 30);

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

    TDicionarioDinamico *dict = CriarDicionarioDinamico(5);

    TVetorDinamico *palavras_por_pag = CriarVetorDinamico(300);
    int primeiraExec = 1;
	while(lerPalavra((FILE*)stdin, pal) != EOF){
        if (sw_dicio->buscar(sw_dicio, CriarStringAED(pal)) == NULL) {
            if (strcmp(pal, "pa") == 0) {
                if (!primeiraExec) {
                    palavras_por_pag->inserir(palavras_por_pag, CriarInteiro(n_palavras_pa) ,n_pags_total - 1);
                }
                else primeiraExec = 0;

                n_pags_total++;
                n_palavras_pa = 0;
            }
            else {
                //fprintf(fw, "%s\n", pal);

                TTermo *termonovo = CriarTermo(pal);
                TTermo *termobusca = dict->buscar(&dict, termonovo);

                if (termobusca == NULL) {
                    termonovo->atualizar_termo(termonovo, n_pags_total);
                    dict->inserir(&dict, termonovo);
                }
                else {
                    termobusca->atualizar_termo(termobusca, n_pags_total);
                }

                n_palavras_pa++;
            }
        }

        pal = malloc(sizeof(char) * 30);
	}

    //dict->imprimir(dict);

    fclose(fw);


    return 0;
}
