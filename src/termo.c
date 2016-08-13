#include <stdlib.h>
#include <stdio.h>
#include "termo.h"
#include "preproc.h"

static double tf(int contagem, int n_total_palavras_pag) {
    return ((double) contagem / (double) n_total_palavras_pag);
}

static double idf(int n_total_pag, int n_cont) {
    return ((double) n_total_pag / (double)n_cont);
}

void atribuir_tf_idf(TPreproc *p, int n_cont, int n_total_pag, int n_total_palavras_pag) {

    p->dado->tf_idf = tf(p->dado->contagem, n_total_palavras_pag) * idf(n_total_pag, n_cont);


    //tf(t, pag, n_total_palavras_pag) * idf(t, n_total_pag);
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
    l->imprimir_lista_n(l, 5);
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

    return t;
}
