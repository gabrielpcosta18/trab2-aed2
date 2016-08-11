#include "stringaed.h"
#include "listaencadeada.h"

typedef struct termo TTermo;
typedef struct preproc TPreproc;
typedef struct dado TDadoTermo;

typedef short (*TComparaTermo)(TTermo*, TTermo*);
typedef void (*TImprimirTermo)(TTermo*);
typedef int (*TRecuperarChaveTermo)(TTermo*);

double tf(TTermo *t, int pag);
int n_containing(TTermo *t);

struct preproc {
    int pag;
    int tf;
    double tf_idf;
};

struct dado {
    TStringAED *palavra;
    TListaEncadeada *ocorrencias;
};

struct termo {
    TDadoTermo *dado;

};

