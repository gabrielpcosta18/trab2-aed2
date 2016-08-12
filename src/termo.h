#include "stringaed.h"
#include "listaencadeada.h"

typedef struct termo TTermo;
typedef struct preproc TPreproc;
typedef struct dado TDadoTermo;

typedef short (*TComparaPreproc)(TPreproc*, TPreproc*);
typedef void (*TImprimirPreproc)(TPreproc*);

typedef short (*TComparaTermo)(TTermo*, TTermo*);
typedef void (*TImprimirTermo)(TTermo*);
typedef int (*TRecuperarChaveTermo)(TTermo*);

double tf(TTermo *t, int pag, int n_total_palavras_pag);
int n_containing(TTermo *t);

typedef struct {
    int pag;
    int tf;
    double tf_idf;
} TDadoPreproc;

struct preproc {
    TDadoPreproc *dado;
    TComparaPreproc compara;
    TImprimirPreproc imprimir;
};

struct dado {
    TStringAED *palavra;
    TListaEncadeada *ocorrencias;
};

struct termo {
    TDadoTermo *dado;
    TComparaTermo compara;
    TImprimirTermo imprimir;
    TRecuperarChaveTermo recuperarChave;
};

