#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "vetorDinamico.h"
#include "dicionariodinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"

#define RANDOMIC_VERIFICATION 371

typedef struct dado {
    TVetorDinamico *dado;

    double fatorAgrupamento;
    double fatorCarga;
    int ocupacao;
}TDado;

static TDado* CriarDado();

static TDicionarioDinamico* RecriarHash(TDicionarioDinamico *dict) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    
    TDicionarioDinamico *novoDict = CriarDicionarioDinamico(v->tamanho(v)*3);
    
    for(int i = 0; i < v->tamanho(v); i++) {
        TListaEncadeada *l = v->acessar(v, i);
        void* atual = l->remover_primeiro_elemento(l);
        while(atual != NULL) {
            novoDict->inserir(novoDict, atual);
            atual = l->remover_primeiro_elemento(l);
            novoDict->inserir(novoDict, atual);
        }
    }

    return novoDict;
}

static TDicionarioDinamico* verificarEstadoTabela(TDicionarioDinamico *dict) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    
    double calc = 0;
    for(int i = 0; i < v->tamanho(v); i++) {
        TListaEncadeada *l = v->acessar(v, i);
        calc += pow(l->tamanho(l), 2);
    }
    if(calc/(d->ocupacao - d->fatorCarga) >= 3)
        return RecriarHash(dict);
}

static int Hash(int chave, int tam) {
    return chave % tam;
}


static void* Inserir(TDicionarioDinamico *dict, void *e) {
    srand(time(NULL));

    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    TComparavel *c = e;

    int boolean = rand()%RANDOMIC_VERIFICATION == 0;
    int pos = Hash(c->recuperarChave(c), v->tamanho(v));

    TListaEncadeada *le = v->acessar(v, pos);
    int tam = le->inserir(le, e);

    if(boolean) {
        TDicionarioDinamico *ddict = verificarEstadoTabela(dict);
        if(ddict != NULL) {

        }
    }
        
    return e;
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
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    TComparavel *c = e;

    int pos = Hash(c->recuperarChave(c), v->tamanho(v));
    TListaEncadeada *le = v->acessar(v, pos); 
    le->remover(le, e);
}

static void DestruirDicionario(TDicionarioDinamico *dict) {
    TVetorDinamico *v = dict->dado;
    for(int i = 0; i < v->tamanho(v); i++) {
        TListaEncadeada *l = v->acessar(v, i);
        l->destruir(l);
    }
    //v->destruir(v);
    free(v);
    free(dict);
}

static TDado* CriarDado(int tam) {
    TDado *d = malloc(sizeof(TDado));
    TVetorDinamico *v = CriarVetorDinamico(tam);

    for(int i = 0; i < tam; i++)
        v->inserir(v, CriarListaEncadeada(), i);

    d->dado = v;
    d->fatorCarga = 1;
    d->fatorAgrupamento = 1;
    d->ocupacao = 0;

    return d;
}

TDicionarioDinamico* CriarDicionarioDinamico(int tam) {
    TDicionarioDinamico *dict = malloc(sizeof(TDicionarioDinamico));
    dict->dado = CriarDado(tam);

    dict->inserir = Inserir;
    dict->buscar = Buscar;
    dict->remover = Remover;
    dict->destruir = DestruirDicionario;

    return dict;
}
