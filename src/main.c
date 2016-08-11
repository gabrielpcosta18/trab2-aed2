#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "vetorDinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"
#include "dicionarioestatico.h"
#include "stringaed.h"

short caracterEhValido(char c) {
    return (97 <= c && c <= 122) //a-z
        || (65 <= c && c <= 90) //A-Z
        || (48 <= c && c <= 57) //números 0-9
        || (45 == c)
        || (128 <= c && c <= 154) //caracteres especiais (1)
        || (160 <= c && c <= 165)
        || (181 <= c && c <= 183)
        || (198 <= c && c <= 199)
        || (224 == c || 229 == c) // Ó, Õ
        || (233 == c);
}

int lerPalavra(FILE *fp, char *word)
{
	short typing=1;
    char c;
	//auxiliares do tipo char;
	char *del = " \t\r\n`~!@#$%^&*()-_+=\\|][{}'\":;/?.>,<\“\”1234567890";

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
} TInteger;

int main() {
    //TVetorDinamico *v = CriarVetorDinamico(1);
    //TListaEncadeada *v = CriarListaEncadeada();
    //FILE *fw = fopen("../base/resultados.txt", "w");
    int i = 0, n_docs_total = 0, n_palavras_pa = 0;
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

    //fclose(fw);
    fclose(fstop);
    free(stopword);

    i = 0;
    pal = malloc(sizeof(char) * 30);

	while(lerPalavra((FILE*)stdin, pal) != EOF){
        if (sw_dicio->buscar(sw_dicio, CriarStringAED(pal)) == NULL) {
            if (strcmp(pal, "pa") == 0) {
                n_docs_total++;
                n_palavras_pa = 0;
            }
            else {
                n_palavras_pa = 0;
            }
        }

        //free(pal);
        //pal = malloc(sizeof(char) * 300);
	}

	printf("%d paginas", n_docs_total);

	/*int tam = 10;
	Integer **inteiros = malloc(sizeof(Integer)*tam);

    for(int i = 0; i < tam; i++) {
		inteiros[i] = criarInt(i);
    }

	TDicionarioEstatico *dict = CriarDicionarioEstatico(inteiros, tam);

	for(int i = 0; i < tam*2; i++) {
		Integer *e = dict->buscar(dict, criarInt(i));
    	if(e != NULL)
			printf("%d ", e->value);
	}*/


	/*v->imprimir_lista(v);
	printf("\n");
	v->remover(v, criarInt(0));
	v->remover(v, criarInt(1));
	v->remover(v, criarInt(2));
	v->remover(v, criarInt(3));
	v->remover(v, criarInt(4));
	*/
	/*
    for(int i = 0; i < 101; i++) {
        Integer *e = malloc(sizeof(Integer));
        e->value = i;
        e->compara = ComparaInteger;
        Integer *r = v->buscar(v, e);
        if(r != NULL)
            printf("Result: %d ", r->value);
        else printf(" Achou nao");
    }*/
    return 0;
}
