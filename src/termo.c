#include "termo.h"

int n_containing(TTermo *t) {
    TListaEncadeada *l = t->dado->ocorrencias;
    return l->tamanho(l);
}

static short comparar_termo_pag(TTermo *t1, TTermo *t2) {
    TPreproc *p1 = t1->dado, *p2 = t2->dado;
    int pg1 = p1->p
}

double tf(TTermo *t, int pag) {
    TListaEncadeada *l = t->dado->ocorrencias;

}
