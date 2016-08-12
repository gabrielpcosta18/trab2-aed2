#include "preproc.h"

short comparar_pag(TPreproc *p1, TPreproc *p2) {
    int pg1 = p1->dado->pag, pg2 = p2->dado->pag;

    if (pg1 == pg2) return 0;
    else if (pg1 > pg2) return 1;
    else return -1;
}

short CompararTfidf(TPreproc *p1, TPreproc *p2) {
    double tfidf1 = p1->dado->tf_idf, tfidf2 = p2->dado->tf_idf;

    if (tfidf1 == tfidf2) return 0;
    else if (tfidf1 > tfidf2) return 1;
    else return -1; //COLOCAR UM CRIARPREPROC() AQUI
}

static void ImprimirPreproc(TPreproc *p) {
    TDadoPreproc *d = p->dado;

    printf("\n(Pagina: %d\t|\tContagem: %d\t|\tTF-IDF: %f)", d->pag, d->contagem, d->tf_idf);
}

TPreproc* CriarPreproc(int pag, int contagem, double tf_idf) {
    TDadoPreproc *dadopre = malloc(sizeof(TDadoPreproc));
    dadopre->pag = pag;
    dadopre->contagem = contagem;
    dadopre->tf_idf = tf_idf;

    TPreproc *pre = malloc(sizeof(TPreproc));
    pre->dado = dadopre;
    pre->compara = comparar_pag;
    pre->imprimir = ImprimirPreproc;

    return pre;
}
