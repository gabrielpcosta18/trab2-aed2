#ifndef _TERMO_
#define _TERMO_
#include "stringaed.h"
#include "preproc.h"
#include "listaencadeada.h"

typedef struct termo TTermo;

typedef struct dado TDadoTermo;

typedef short (*TComparaTermo)(TTermo*, TTermo*);
typedef void (*TImprimirTermo)(TTermo*);
typedef unsigned long (*TRecuperarChaveTermo)(TTermo*);
typedef void (*TAtualizarTermo)(TTermo*, int);

void atribuir_tf_idf(TPreproc *p, int n_cont, int n_total_pag, int n_total_palavras_pag);
void calcular_tfidfs(TTermo *t);

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
