#include <stdlib.h>
#include "vetorDinamico.h"
#include "dicionariodinamico.h"
#include "listaencadeada.h"

#define VETOR_INIT_SIZE 10000001

typedef struct dado {
    TVetorDinamico *dado;
    
    double fatorAgrupamento;
    double fatorCarga;
}TDado;

static TDado* CriarDado();

static TVetorDinamico* RecriarHash() {

}

static int Hash(int *chave, int tam) {
    
}

static void Inserir(TDicionarioDinamico *dict, void *e) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    TComparavel *c = e;

    int pos = Hash(c->recuperarChave(c), v->tamanho(v));

}

static void* Buscar(TDicionarioDinamico *dict, void *e) {

}

static void Remover(TDicionarioDinamico *dict, void *e) {

}

static TDado* CriarDado() {
    TDado *d = malloc(sizeof(TDado));
    TVetorDinamico *v = CriarVetorDinamico(VETOR_INIT_SIZE);
    
    d->dado = v;
    
    return d;
}

TDicionarioDinamico* CriarDicionarioDinamico() {
    TDicionarioDinamico *dict = malloc(sizeof(TDicionarioDinamico));
    dict->dado = CriarDado;

    dict->inserir = Inserir;
    dict->buscar = Buscar;
    dict->remover = Remover;

    return dict;
}