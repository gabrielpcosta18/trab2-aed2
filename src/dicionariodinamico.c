#include <stdlib.h>
#include "vetorDinamico.h"
#include "dicionariodinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"

#define VETOR_INIT_SIZE 10000001

typedef struct dado {
    TVetorDinamico *dado;

    double fatorAgrupamento;
    double fatorCarga;
}TDado;

static TDado* CriarDado();

static TVetorDinamico* RecriarHash() {

}

static void verificarEstadoTabela() {

}

static int Hash(int chave, int tam) {
    return chave % tam;
}


static void Inserir(TDicionarioDinamico *dict, void *e) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    TComparavel *c = e;

    int pos = Hash(c->recuperarChave(c), v->tamanho(v));
    TListaEncadeada *le = v->acessar(v, pos);
    le->inserir(le, e);

    verificarEstadoTabela(dict);
}

static void* Buscar(TDicionarioDinamico *dict, void *e) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    TComparavel *c = e;

    int pos = Hash(c->recuperarChave(c), v->tamanho(v));
    TListaEncadeada *le = v->acessar(v, pos);

    return le->buscar(le, e);
}

static void Remover(TDicionarioDinamico *dict, void *e) {

}

static TDado* CriarDado() {
    TDado *d = malloc(sizeof(TDado));
    TVetorDinamico *v = CriarVetorDinamico(VETOR_INIT_SIZE);

    for(int i = 0; i < VETOR_INIT_SIZE; i++)
        v->inserir(v, CriarListaEncadeada(), i);

    d->dado = v;
    d->fatorCarga = 0.8;

    return d;
}

TDicionarioDinamico* CriarDicionarioDinamico() {
    TDicionarioDinamico *dict = malloc(sizeof(TDicionarioDinamico));
    dict->dado = CriarDado();

    dict->inserir = Inserir;
    dict->buscar = Buscar;
    dict->remover = Remover;

    return dict;
}
