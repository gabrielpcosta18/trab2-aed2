#include <stdlib.h>
#include <stdio.h>
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

void ImprimirLista(TListaEncadeada *l) {
    TDado *d = l->dado;
    TNo *pesq = d->inicio;
    TComparavel *c;
    while (pesq != NULL) {
        c = (TComparavel*) pesq->dado;
        c->imprimir(c);

        if (pesq->prox != NULL)
            printf(" -> ");
        pesq = pesq->prox;
    }
}

static short Remover(TListaEncadeada *l, void *e) {
	TDado *d = l->dado;
	TNo *antes, *atual;
    TComparavel *c = (TComparavel*) e;
	atual = antes = d->inicio;

    while (atual != NULL) {
        if (c->compara(c, atual->dado) == 0) {
            if (atual != d->inicio) antes->prox = atual->prox;
            else d->inicio = d->inicio->prox;

            free(atual);
            return 1;
        }

        antes = atual;
        atual = atual->prox;
    }

    return 0;
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
    l->imprimir_lista = ImprimirLista;

    return l;
}
