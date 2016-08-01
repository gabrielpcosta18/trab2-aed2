#include <stdlib.h>
#include "dicionariaestatico.h"
#include "vetorDinamico.h"

typedef struct tupla {
    void *chave;
    void *dado;
} TTupla;

typedef struct dado {
    TVetorDinamico *dado;
}TDado;

static short Compara(void *e1, void *e2) {
    TComparavel *c = e1;
    
    return c->compara(e1, e2);
}

static void* Buscar(TDicionarioEstatico *dict, void *chave) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    
    int tam = v->tamanho(v);
    int inicio = 0, fim = tam - 1;
    int meio = (inicio + fim)/2;
    
    while(inicio <= fim) {
        TTupla *e = v->acessar(v, meio);
        short comp = Compara(chave, e->chave); 
        
        if( comp == 0) return e->dado;
        else if( comp < 0 ) fim = meio;
        else inicio = meio; 

        int meio = (inicio + fim)/2;
    }

    return NULL;
}


TDicionarioEstatico* CriarDicionarioEstatico(void **chaves, void **e,  int tam) {
    TDicionarioEstatico *dict = malloc(sizeof(TDicionarioEstatico));
    TDado *d = malloc(sizeof(TDado));
    TVetorDinamico *v = CriarVetorDinamico(tam);
    
    for(int i = 0; i < tam; i++) {
        TTupla *t = malloc(sizeof(TTupla));
        t->chave = chaves[i];
        t->dado = e[i];

        v->inserir(v, t, i);
    }

    d->dado = v;
    dict->dado = d;

    return dict;
}