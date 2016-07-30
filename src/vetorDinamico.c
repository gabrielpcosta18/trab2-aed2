#include <stdlib.h>
#include "vetorDinamico.h"
#include <math.h>

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

//construtor
TVetorDinamico* CriarVetorDinamico(int tam) {
	TVetorDinamico *v = malloc(sizeof(TVetorDinamico));
	TDado *d = malloc(sizeof(TDado));

	d->elementos = malloc(sizeof(void*)*tam);
	d->tam = tam;
	v->dado = d;

	v->inserir = Inserir;
	v->acessar = Acessar;
	v->tamanho = Tamanho;
	return v;
}

//destrutor
void DestruirVetorDinamico(TVetorDinamico* v) {
	free(((TDado*)(v->dado))->elementos);
	free(v->dado);
	free(v);
}