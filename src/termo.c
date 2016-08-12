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

static short comparar_tfidf(TPreproc *p1, TPreproc *p2) {
    double tfidf1 = p1->dado->tf_idf, tfidf2 = p2->dado->tf_idf;

    if (tfidf1 == tfidf2) return 0;
    else if (tfidf1 > tfidf2) return 1;
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

static TDadoTermo* CriarDadoTermo(char *palavra) {
    TDadoTermo *d = malloc(sizeof(TDadoTermo));
    d->palavra = CriarStringAED(palavra);
    d->ocorrencias = CriarListaEncadeadaOrdenada(comparar_tfidf);

    return d;
}

static short ComparaTermo(TTermo *t1, TTermo *t2) {
    TStringAED *s = t1->dado->palavra;
    return s->compara(s, t2->dado->palavra);
}

static int RecuperarChaveTermo(TTermo *t) {
    TStringAED *s = t->dado->palavra;
    return s->recuperarChave(s);
}

static void ImprimirTermo(TTermo *t) {
    TStringAED *s = t->dado->palavra;
    return s->imprimir(s);
}

TTermo* CriarTermo(char *palavra) {
    TTermo *t = malloc(sizeof(TTermo));
    t->dado = CriarDadoTermo(palavra);
    t->compara = ComparaTermo;
    t->recuperarChave = RecuperarChaveTermo;
    t->imprimir = ImprimirTermo;
}
