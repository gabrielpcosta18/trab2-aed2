#include <stdlib.h>
#include "vetorDinamico.h"
#include <math.h>
#include "comparavel.h"
#include "stdio.h"

typedef struct dado {
	int tam;
	void** elementos;
} TDado;

static void redimensionar(TVetorDinamico* v, int novoTam) {
	TDado *d = malloc(sizeof(TDado));
	d->tam = novoTam;
	d->elementos = malloc(sizeof(void*)*novoTam);

	int i;
	for(i = 0; i < ((TDado*)(v->dado))->tam; i++) {
		d->elementos[i] = ((TDado*)(v->dado))->elementos[i];
	}

	free(v->dado);
	v->dado = d;
}

// declaração dos tipos Função/Método
static void Inserir(TVetorDinamico* v, void* d, int pos) {
	TDado *dado = v->dado;
	if(pos >= dado->tam) {
        printf("VETOR REDIMENSIONOU");
		int calc = pow(2, floor(log2(pos) + 2));
		redimensionar(v, calc);
	}
	((TDado*)(v->dado))->elementos[pos] = d;
}

static void* Acessar(TVetorDinamico* v, int pos) {
	if(pos < ((TDado*)(v->dado))->tam) {
		return ((TDado*)(v->dado))->elementos[pos];
	}

	return NULL;
}

static int Tamanho(TVetorDinamico* v) {
	return ((TDado*)v->dado)->tam;
}
static void Imprimir(TVetorDinamico *v) {
    TDado *d = v->dado;
    TComparavel *c;
    for (int i = 0; i < d->tam; i++) {
        c = d->elementos[i];
        c->imprimir(c);
        printf("\n");
    }
}


//construtor
TVetorDinamico* CriarVetorDinamico(int tam) {
	TVetorDinamico *v = malloc(sizeof(TVetorDinamico));
	TDado *d = malloc(sizeof(TDado));

	d->elementos = malloc(sizeof(void*)*tam);

	for (int i = 0; i < tam; i++) {
        d->elementos[i] = NULL;
	}

	d->tam = tam;
	v->dado = d;

	v->inserir = Inserir;
	v->acessar = Acessar;
	v->tamanho = Tamanho;
	v->imprimir = Imprimir;
	return v;
}

//destrutor
void DestruirVetorDinamico(TVetorDinamico* v) {
	TDado *d = v->dado;
	
	for(int i = 0; i < d->tam; i++) {
		//free(d->elementos[i]);
	}
	free(d->elementos);
	free(d);
	free(v);
}
