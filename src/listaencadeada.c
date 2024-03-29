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
	int tamanho;
} TDado;

// For debug proposes. Remove later.
/*typedef struct integer Integer;

typedef short (*TComparaInteger)(Integer*, Integer*);

struct integer {
	int value;
	TComparaInteger compara;
};*/

static int Inserir(TListaEncadeada *l, void *e) {
    TDado *d = l->dado;
    TNo *inicio = d->inicio;

    TNo *novo = malloc(sizeof(TNo));
    novo->dado = e;
    novo->prox = NULL;

    if (inicio != NULL) {
        if (l->compara_elementos == NULL) {
            novo->prox = d->inicio;
            d->inicio = novo;
        }
        else {
            TNo *pesq;
            pesq = inicio;

            if (l->compara_elementos(novo->dado, inicio->dado) > 0) {
                novo->prox = d->inicio;
                d->inicio = novo;
            }
            else {
                if (d->inicio->prox == NULL) {
                    d->inicio->prox = novo;
                }
                else {
                    while(pesq->prox != NULL) {
                        if (l->compara_elementos(novo->dado, pesq->prox->dado) > 0) break;
                        pesq = pesq->prox;
                    }

                    novo->prox = pesq->prox;
                    pesq->prox = novo;
                }
            }
        }
    }
    else d->inicio = novo;

	d->tamanho++;
	return d->tamanho;
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

void* BuscarDebug(TListaEncadeada *l, void *e) {
    TDado *d = l->dado;
    TNo *viajante = d->inicio;
    TComparavel *c = e;
    int i = 1;


    while(viajante != NULL) {
        if(c->compara(viajante->dado, e) == 0) break;
        viajante = viajante->prox;
        i++;
    }

    printf("\n%d comparacoes\n", i);

    if (viajante == NULL) return NULL;
    else return viajante->dado;
}

static void ImprimirLista(TListaEncadeada *l) {
    TDado *d = l->dado;
    TNo *pesq = d->inicio;
    TComparavel *c;

    if (d->inicio == NULL) printf(" vazio ");
    else {
        while (pesq != NULL) {
            c = (TComparavel*) pesq->dado;
            c->imprimir(c);

            if (pesq->prox != NULL)
                printf(" -> ");
            pesq = pesq->prox;
        }
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
			d->tamanho--;
            free(atual);
            return 1;
        }

        antes = atual;
        atual = atual->prox;
    }

    return 0;
}

static void* RemoverPrimeiroElemento(TListaEncadeada *l) {
    TDado *d = l->dado;
	TNo *atual;

    atual = d->inicio;
    if(d->inicio != NULL) {
        d->inicio = d->inicio->prox;
        d->tamanho--;

        void *retorno = atual->dado;
        free(atual);
        return retorno;
    }

    return NULL;
}

void DestruirLista(TListaEncadeada *l) {
	TDado *d = l->dado;
	TNo *anterior, *atual;
	anterior = atual = d->inicio;

	while (atual != NULL) {
        anterior = atual;
		atual = atual->prox;
        free(anterior->dado);
		free(anterior);
	}

	free(d);
	free(anterior);
	free(atual);
	free(l);
}

static int Tamanho(TListaEncadeada *l) {
    TDado *d = l->dado;
    return d->tamanho;
}

static TNo* CriarNo() {
    TNo *n = malloc(sizeof(TNo));
    n->dado = NULL;
    n->prox = NULL;

    return n;
}

short VaziaListaEncadeada(TListaEncadeada *l) {
    TDado *d = l->dado;

    return d->inicio == NULL;
}

void reordenar_lista(TListaEncadeada **ll) {
    TListaEncadeada *l = *ll;
    TListaEncadeada *lord = CriarListaEncadeadaOrdenada(l->compara_elementos);

    TDado *d = l->dado;
    TNo *perc = d->inicio;

    while (perc != NULL) {
        lord->inserir(lord, perc->dado);
        perc = perc->prox;
    }

    free(l);
    free(*ll);

    *ll = lord;
}

void iterar_sobre(TListaEncadeada *l, void (*operacao)(void*, void*), void* params) {
    TDado *d = l->dado;
    TNo *viajante = d->inicio;

    while(viajante != NULL) {
        operacao(viajante->dado, params);
        viajante = viajante->prox;
    }
}

static void ImprimirListaN(TListaEncadeada *l, int n) {
    TDado *d = l->dado;
    TNo *pesq = d->inicio;
    TComparavel *c;
    int i = 0;

    if (d->inicio == NULL) printf(" vazio ");
    else {
        while (pesq != NULL && i < n) {
            c = (TComparavel*) pesq->dado;
            c->imprimir(c);

            if (pesq->prox != NULL)
                printf(" -> ");
            pesq = pesq->prox;
            i++;
        }
    }
}


TListaEncadeada* CriarListaEncadeada() {
    TListaEncadeada *l = malloc(sizeof(TListaEncadeada));
    TDado *d = malloc(sizeof(TDado));

	d->tamanho = 0;
    d->inicio = NULL;
    l->dado = d;

    l->inserir = Inserir;
    l->remover = Remover;
    l->buscar = Buscar;
    l->tamanho = Tamanho;
    l->imprimir_lista = ImprimirLista;
	l->destruir = DestruirLista;
    l->remover_primeiro_elemento = RemoverPrimeiroElemento;
	l->compara_elementos = NULL;
    l->vazia = VaziaListaEncadeada;
    l->imprimir_lista_n = ImprimirListaN;

    return l;
}

TListaEncadeada* CriarListaEncadeadaOrdenada(TComparaElementosListaEncadeada compara_elementos) {
    TListaEncadeada *l = CriarListaEncadeada();
    l->compara_elementos = compara_elementos;
    return l;
}
