#ifndef _TERMO_
#define _TERMO_
#include "stringaed.h"
#include "listaencadeada.h"

typedef struct termo TTermo;

typedef struct dado TDadoTermo;

typedef short (*TComparaTermo)(TTermo*, TTermo*);
typedef void (*TImprimirTermo)(TTermo*);
typedef int (*TRecuperarChaveTermo)(TTermo*);
typedef void (*TAtualizarTermo)(TTermo*, int);

double tf(TTermo *t, int pag, int n_total_palavras_pag);
int n_containing(TTermo *t);

struct dado {
    TStringAED *palavra;
    TListaEncadeada *ocorrencias;
};

struct termo {
    TDadoTermo *dado;
    TComparaTermo compara;
    TImprimirTermo imprimir;
    TRecuperarChaveTermo recuperarChave;
    TAtualizarTermo atualizar_termo;
};

TTermo* CriarTermo(char *palavra);
#endif
