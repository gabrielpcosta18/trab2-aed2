#include <stdlib.h>
#include "listaencadeada.h"
#include "comparavel.h"

typedef struct No {
    void *dado;
    struct No *prox;
}TNo;

typedef struct dado {
    TNo *inicio;
    TNo *fim;
} TDado;

// For debug proposes. Remove later.
/*typedef struct integer Integer;

typedef short (*TComparaInteger)(Integer*, Integer*);

struct integer {
	int value;
	TComparaInteger compara;
};*/

static void Inserir(TListaEncadeada *l, void *e) {
    TDado *d = l->dado;
    TNo *inicio = d->inicio, *fim = d->fim;
    
    TNo *novo = malloc(sizeof(TNo));
    novo->prox = NULL;
    novo->dado = e;

    if(inicio != NULL) {           
        d->fim->prox = novo;
        d->fim = novo;
    }
    else {
        d->inicio = d->fim = novo;
    }    
}

static void* Buscar(TListaEncadeada *l, void *e) {
    TDado *d = l->dado;  
    TNo *viajante = d->inicio;
    TComparavel *c = e;
    while(viajante != NULL) {
        if(c->compara(viajante->dado, e) == 0) return viajante->dado;
        viajante = viajante->prox;
    }

    return viajante;
}

static void Remover(TListaEncadeada *l, void *e) {

}

static int Tamanho(TListaEncadeada *l) {
    TDado *d = l->dado;  
    TNo *viajante = d->inicio;
    
    int tam = 0;
    while(viajante != NULL) {
        viajante = viajante->prox;
        tam++;
    }

    return tam;
}

static TNo* CriarNo() {
    TNo *n = malloc(sizeof(TNo));
    n->dado = NULL;
    n->prox = NULL;

    return n;
}

TListaEncadeada* CriarListaEncadeada() {
    TListaEncadeada *l = malloc(sizeof(TListaEncadeada));
    TDado *d = malloc(sizeof(TDado));

    d->inicio = d->fim = NULL;
    l->dado = d;
    
    l->inserir = Inserir;
    l->remover = Remover;
    l->buscar = Buscar;
    l->tamanho = Tamanho;

    return l;
}
