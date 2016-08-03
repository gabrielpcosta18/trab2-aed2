#include <stdlib.h>
#include "dicionarioestatico.h"
#include "vetorDinamico.h"
#include "comparavel.h"

typedef struct dado {
    TVetorDinamico *dado;
}TDado;

static short Compara(void *e1, void *e2) {
    TComparavel *c = e1;

    return c->compara(e1, e2);
}

static void* Buscar(TDicionarioEstatico *dict, void *e) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;

    int tam = v->tamanho(v);
    int inicio = 0, fim = tam - 1;
    int meio = (inicio + fim)/2;

    while(inicio <= fim) {
        void *elemento = v->acessar(v, meio);
        short comp = Compara(e, elemento);
        if( comp == 0) return e;
        else if( comp < 0 ) fim = meio - 1;
        else inicio = meio + 1;

        meio = (inicio + fim)/2;
    }

    return NULL;
}


TDicionarioEstatico* CriarDicionarioEstatico(void **e,  int tam) {
    TDicionarioEstatico *dict = malloc(sizeof(TDicionarioEstatico));
    TDado *d = malloc(sizeof(TDado));
    TVetorDinamico *v = CriarVetorDinamico(tam);

    for(int i = 0; i < tam; i++)
        v->inserir(v, e[i], i);

    d->dado = v;
    dict->dado = d;

    dict->buscar = Buscar;

    return dict;
}
