#include <stdlib.h>
#include "termo.h"

int n_containing(TTermo *t) {
    TListaEncadeada *l = t->dado->ocorrencias;
    return l->tamanho(l);
}

static short comparar_pag(TPreproc *p1, TPreproc *p2) {
    int pg1 = p1->dado->pag, pg2 = p2->dado->pag;

    if (pg1 == pg2) return 0;
    else if (pg1 > pg2) return 1;
    else return -1;
}

double tf(TTermo *t, int pag, int n_total_palavras_pag) {
    TListaEncadeada *l = t->dado->ocorrencias;
    TPreproc *aux = malloc(sizeof(TPreproc));
    aux->dado->pag = pag;
    aux->compara = comparar_pag;

    TPreproc *p = l->buscar(l, aux);
    if (p != NULL) return ((double) p->dado->tf / (double) n_total_palavras_pag);
    else return 0.0;
}

double idf(TTermo *t, int n_total_pag) {
    return ((double) n_total_pag / n_containing(t));
}

double tf_idf(TTermo *t, int pag, int n_total_pag) {

}

