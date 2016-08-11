#include <stdlib.h>
#include "String.h"
#include <math.h>

typedef struct dado {
	int tam;
	char *elementos;
	int ocupacao;
} TDado;

static void redimensionar(TString* v, int novoTam) {
	TDado *d = v->dado;
	d->tam = novoTam;
	d->elementos = realloc(d->elementos, sizeof(char) * novoTam);
}

static void Inserir(TString *v, char c) {
    TDado *d = v->dado;

    if(d->ocupacao + 1 >= dado->tam) {
		int calc = pow(2, floor(log2(d->ocupacao + 1)));
		redimensionar(v, calc);
	}

	d->elementos[d->ocupacao] = c;
	d->elementos[d->ocupacao + 1] = '\0';
	d->ocupacao++;
}

static char* RecuperarString(TString *v) {
    TDado *d = v->dado;
    return d->elementos;
}

static int Tamanho(TString* v) {
	return ((TDado*)v->dado)->ocupacao;
}

//construtor
TString* CriarString() {
	TString *v = malloc(sizeof(TString));
	TDado *d = malloc(sizeof(TDado));

	d->elementos = malloc(sizeof(char));
	d->elementos[0] = '\0';
	d->tam = 1;
	d->ocupacao = 0;
	v->dado = d;

	v->inserir = Inserir;
	v->recuperar_stirng = recuperarString;
	v->tamanho = Tamanho;
	return v;
}

//destrutor
void DestruirString(TString* v) {
	free(((TDado*)(v->dado))->elementos);
	free(v->dado);
	free(v);
}
