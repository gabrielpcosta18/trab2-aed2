#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "vetorDinamico.h"
#include "dicionariodinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"

#define RANDOMIC_VERIFICATION 371

typedef struct dado {
    TVetorDinamico *dado;
    int ocupacao;
}TDado;

static TDado* CriarDado();

static void AnaliseDicionario(TDicionarioDinamico *dict) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;

    double fatorCargaAte10Maior = 0;
    double fatorCargaAte30Maior = 0;
    double fatorCargaMaior30 = 0;
    double fatorCargaAte10Menor = 0;
    double fatorCargaAte30Menor = 0;
    double fatorCargaMenor30 = 0;
    double fatorCarga = 0, calc = 0;
    
    fatorCarga = ((double)d->ocupacao + 1)/(double)v->tamanho(v);
    printf("Tamanho da tabela: %d Ocupacao: %d\n", v->tamanho(v), d->ocupacao);     
    for(int i = 0; i < v->tamanho(v); i++) {
        TListaEncadeada *l = v->acessar(v, i);
        
        calc = ((double) l->tamanho(l))/fatorCarga;
        printf("Calc: %f Tamanho Lista encadeada: %d\n", calc, l->tamanho(l));
        if(calc > 1.0 && calc < 1.10)
            fatorCargaAte10Maior += 1.0;
        else if(calc > 1.0 && calc < 1.30)
            fatorCargaAte30Maior += 1.0;
        else if(calc > 1.30)
            fatorCargaMaior30 += 1.0;
        else if(calc < 1.0 && calc > 0.9)
            fatorCargaAte10Menor += 1.0;
        else if(calc < 1.0 && calc > 0.7)
            fatorCargaAte30Menor += 1.0;
        else if(calc < 0.7)
            fatorCargaMenor30 += 1.0;
    }

    printf("Fator Carga até 10 maior: %f\n", fatorCargaAte10Maior/(v->tamanho(v)*1.0));
    printf("Fator Carga até 30 maior: %f\n", fatorCargaAte30Maior/(v->tamanho(v)*1.0));
    printf("Fator Carga maior 30: %f\n", fatorCargaMaior30/(v->tamanho(v)*1.0));
    printf("Fator Carga até 10 menor: %f\n", fatorCargaAte10Menor/(v->tamanho(v)*1.0));
    printf("Fator Carga até 30 menor: %f\n", fatorCargaAte30Menor/(v->tamanho(v)*1.0));
    printf("Fator Carga menor 30: %f\n", fatorCargaMenor30/(v->tamanho(v)*1.0));
}

static TDicionarioDinamico* RecriarHash(TDicionarioDinamico *dict) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    
    TDicionarioDinamico *novoDict = CriarDicionarioDinamico(v->tamanho(v)*3);
    void* atual;

    for(int i = 0; i < v->tamanho(v); i++) {
        TListaEncadeada *l = v->acessar(v, i);
        atual = l->remover_primeiro_elemento(l);
        
        while(atual != NULL) {
            novoDict->inserir(novoDict, atual);
            //atual = l->remover_primeiro_elemento(l);
            atual = NULL;
        }
    }

    AnaliseDicionario(dict);
    //return novoDict;
    return NULL;
}

static TDicionarioDinamico* verificarEstadoTabela(TDicionarioDinamico *dict) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    
    double calc = 0;
    for(int i = 0; i < v->tamanho(v); i++) {
        TListaEncadeada *l = v->acessar(v, i);
        calc += pow(l->tamanho(l), 2);
    }

    double fatorCarga = ((double)d->ocupacao + 1)/(double)v->tamanho(v);
    
    if(calc/(d->ocupacao - fatorCarga) >= 3)
        return RecriarHash(dict);
    return NULL;
}

static int Hash(int chave, int tam) {
    return chave % tam;
}


static void* Inserir(TDicionarioDinamico *dict, void *e) { 
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dado;
    TComparavel *c = e;

    int boolean = (rand()%RANDOMIC_VERIFICATION) == 0;
    int pos = Hash(c->recuperarChave(c), v->tamanho(v));

    TListaEncadeada *le = v->acessar(v, pos);
    int tam = le->inserir(le, e);
    if(boolean) {
        TDicionarioDinamico *ddict = verificarEstadoTabela(dict);
        if(ddict != NULL) {
            dict = ddict;
        }
    }
    d->ocupacao++;
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
