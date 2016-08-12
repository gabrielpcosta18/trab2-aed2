#ifndef _PREPROC_
#define _PREPROC_

typedef struct preproc TPreproc;

typedef short (*TComparaPreproc)(TPreproc*, TPreproc*);
typedef void (*TImprimirPreproc)(TPreproc*);

short CompararTfidf(TPreproc *p1, TPreproc *p2);

typedef struct {
    int pag;
    int contagem;
    double tf_idf;
} TDadoPreproc;

struct preproc {
    TDadoPreproc *dado;
    TComparaPreproc compara;
    TImprimirPreproc imprimir;
};



#endif
