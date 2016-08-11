#include <stdio.h>
#include <stdlib.h>
#include "vetorDinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"
#include "dicionarioestatico.h"
#include "stringaed.h"
#include <string.h>


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

char *ler_linha(char *line, int size, FILE* f) {
    char c;
    int count = -1;

    while((c = fgetc(f)) != EOF) {
        count++;
        if(c == '\n') break;
        if (count < size - 1) {
            line[count] = c;
        }
        else break;

    }

    line[count] = '\0';

    if (c == EOF) return NULL;
    else return line;
}

int compara_string_aed(const void *e1, const void *e2) {
    TStringAED *a = *(TStringAED**) e1;
    TStringAED *b = *(TStringAED**) e2;

	return strcmp(a->string, b->string);
}

// a b c d e f g h i j k l m n o p q r s t u v w x y z

int main() {
    TListaEncadeada *l = CriarListaEncadeadaOrdenada(ComparaStringAED);
    l->inserir(l, CriarStringAED("g"));
    l->inserir(l, CriarStringAED("j"));
    l->inserir(l, CriarStringAED("k"));
    l->inserir(l, CriarStringAED("e"));
    l->inserir(l, CriarStringAED("q"));

    l->imprimir_lista(l);
    //TVetorDinamico *v = CriarVetorDinamico(1);
    //TListaEncadeada *v = CriarListaEncadeada();
    /*FILE *fw = fopen("../base/resultados.txt", "w");
    FILE *fstop = fopen("../base/stopwords_pt", "r");
    int i = 0;
    char *pal;
    char *stopword = malloc(sizeof(char) * 30);

    TStringAED **stopwords = malloc(sizeof(TStringAED) * 392);
    TDicionarioEstatico *sw_dicio;

    for (;lerPalavra(fstop, stopword) != EOF; i++) {
        stopwords[i] = CriarStringAED(stopword);
        stopword = malloc(sizeof(char) * 30);
    }

    qsort(stopwords, 392, sizeof(void*), compara_string_aed);

    sw_dicio = CriarDicionarioEstatico((void**)stopwords, 392);

    fclose(fw);
    fclose(fstop);
    free(stopword);

    i = 0;
    pal = malloc(sizeof(char) * 300);

	while(lerPalavra((FILE*)stdin, pal) != EOF){
        if (sw_dicio->buscar(sw_dicio, CriarStringAED(pal)) == NULL) {
            if (strcmp(pal, "PA") == 0) {

            }
        }

        free(pal);
        pal = malloc(sizeof(char) * 300);

	}

	printf("%d stopwords", i);

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
