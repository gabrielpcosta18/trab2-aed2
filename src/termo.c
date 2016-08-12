#include <stdlib.h>
#include "termo.h"
#include "preproc.h"

int n_containing(TTermo *t) {
    TListaEncadeada *l = t->dado->ocorrencias;
    return l->tamanho(l);
}

double tf(TTermo *t, int pag, int n_total_palavras_pag) {
    TListaEncadeada *l = t->dado->ocorrencias;
    TPreproc *aux = CriarPreproc(pag, 0, 0);

    TPreproc *p = l->buscar(l, aux);
    if (p != NULL) return ((double) p->dado->contagem / (double) n_total_palavras_pag);
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
    d->ocorrencias = CriarListaEncadeadaOrdenada(CompararTfidf);

    return d;
}

static short ComparaTermo(TTermo *t1, TTermo *t2) {
    TStringAED *s = t1->dado->palavra;
    return s->compara(s, t2->dado->palavra);
}

static unsigned long RecuperarChaveTermo(TTermo *t) {
    TStringAED *s = t->dado->palavra;
    return s->recuperarChave(s);
}

static void ImprimirTermo(TTermo *t) {
    TStringAED *s = t->dado->palavra;
    printf("\n----------------------------------\nPalavra: ");
    s->imprimir(s);
    TListaEncadeada *l = t->dado->ocorrencias;
    l->imprimir_lista(l);
    printf("\n----------------------------------\n\n");
}

static void AtualizarTermo(TTermo* t, int pag) {
    TDadoTermo *d = t->dado;
    TListaEncadeada *l = d->ocorrencias;

    TPreproc *novo = CriarPreproc(pag, 0, 0);
    TPreproc *aux = l->buscar(l, novo);

    if (aux != NULL) {
        aux->dado->contagem++;
    }
    else {
        novo->dado->contagem = 1;
        l->inserir(l, novo);
    }
}

TTermo* CriarTermo(char *palavra) {
    TTermo *t = malloc(sizeof(TTermo));
    t->dado = CriarDadoTermo(palavra);
    t->compara = ComparaTermo;
    t->recuperarChave = RecuperarChaveTermo;
    t->imprimir = ImprimirTermo;
    t->atualizar_termo = AtualizarTermo;
}
