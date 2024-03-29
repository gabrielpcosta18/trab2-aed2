#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "vetorDinamico.h"
#include "dicionariodinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"
#define RAZAO_AUREA 1.618033988
#define FATOR_DE_CARGA 3

typedef struct dado {
    TVetorDinamico *dadov;
    int ocupacao;
    int vezes_rehash;
}TDado;

static TDado* CriarDado();

void AnaliseDicionario(TDicionarioDinamico *dict) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dadov;
    TListaEncadeada *l;
    double fatorCargaAte10Maior = 0;
    double fatorCargaAte30Maior = 0;
    double fatorCargaMaior30 = 0;
    double fatorCargaAte10Menor = 0;
    double fatorCargaAte30Menor = 0;
    double fatorCargaMenor30 = 0;
    double fatorCarga = 0, calc = 0;

    printf("Ocupacao: %d, Tamanho da Tabela: %d, Numero de ReHashs: %d\n", d->ocupacao, v->tamanho(v), d->vezes_rehash);

    fatorCarga = ((double)d->ocupacao + 1)/(double)v->tamanho(v);


    int posicoes_vazias = 0;

    for (int i = 0; i < v->tamanho(v); i++) {
        l = v->acessar(v, i);
        posicoes_vazias += l->vazia(l);
    }

    printf("Fator de Carga: %f\nNum de posicoes vazias: %d, Porcentagem Util da Tabela Hash: %.2f%\n", fatorCarga, posicoes_vazias, (1.0 - (double) posicoes_vazias / (double)v->tamanho(v)) * 100.0);

    //printf("Tamanho da tabela: %d | Ocupacao: %d | Fator de Carga: %f\n", v->tamanho(v), d->ocupacao, fatorCarga);
    for(int i = 0; i < v->tamanho(v); i++) {
        l = v->acessar(v, i);

        calc = ((double) l->tamanho(l))/fatorCarga;
        //printf("Calc: %f Tamanho Lista encadeada: %d\n", calc, l->tamanho(l));
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

    printf("Fator Carga at%c 10% maior: %f\n", 130, fatorCargaAte10Maior/(v->tamanho(v)*1.0));
    printf("Fator Carga at%c 30% maior: %f\n", 130, fatorCargaAte30Maior/(v->tamanho(v)*1.0));
    printf("Fator Carga acima de 30%: %f\n", fatorCargaMaior30/(v->tamanho(v)*1.0));
    printf("Fator Carga at%c 10% menor: %f\n", 130, fatorCargaAte10Menor/(v->tamanho(v)*1.0));
    printf("Fator Carga at%c 30% menor: %f\n", 130, fatorCargaAte30Menor/(v->tamanho(v)*1.0));
    printf("Fator Carga menor 30%: %f\n\n", fatorCargaMenor30/(v->tamanho(v)*1.0));
}


static void DestruirDicionario(TDicionarioDinamico **dict) {
    TDado *d = (*dict)->dado;
    TVetorDinamico *v = d->dadov;
    TListaEncadeada *l;
    for(int i = 0; i < v->tamanho(v); i++) {
        l = v->acessar(v, i);
        l->destruir(l);
    }
    //v->destruir(v);
    //free(l);
    //free(v);
    DestruirVetorDinamico(d->dadov);
    //free(dict);
}

static int Hash(unsigned long chave, int tam) {
    return chave % tam;
}


static void* InserirSemReHash(TDicionarioDinamico **dict, void *e) {
    TDado *d = (*dict)->dado;
    TVetorDinamico *v = d->dadov;
    TComparavel *c = e;

    int pos = Hash(c->recuperarChave(c), v->tamanho(v));

    TListaEncadeada *le = v->acessar(v, pos);
    le->inserir(le, e);

    d->ocupacao++;
    return e;
}

static TDicionarioDinamico* RecriarHash(TDicionarioDinamico **dict) {
    TDado *d = (*dict)->dado;
    TVetorDinamico *v = d->dadov;
    d->vezes_rehash++;
    TDicionarioDinamico *novoDict = CriarDicionarioDinamico((int)(v->tamanho(v) * RAZAO_AUREA));
    TDado *dd = novoDict->dado;
    int toc = dd->dadov->tamanho(dd->dadov);
    void* atual;

    for(int i = 0; i < v->tamanho(v); i++) {
        TListaEncadeada *l = v->acessar(v, i);
        atual = l->remover_primeiro_elemento(l);

        while(atual != NULL) {
            InserirSemReHash(&novoDict, atual);
            atual = l->remover_primeiro_elemento(l);
        }
    }

    dd->vezes_rehash = d->vezes_rehash;
    DestruirDicionario(dict);
    //AnaliseDicionario(novoDict);
    return novoDict;
}

static TDicionarioDinamico* verificarEstadoTabela(TDicionarioDinamico **dict) {
    TDado *d = (*dict)->dado;
    TVetorDinamico *v = d->dadov;
    TListaEncadeada *l;

    double calc = 0;
    for(int i = 0; i < v->tamanho(v); i++) {
        l = v->acessar(v, i);
        calc += pow(l->tamanho(l), 2);
    }

    //double fatorCarga = (double)d->ocupacao/(double)v->tamanho(v);

    double criterio = 1.1;
    double agrupamento = (calc/d->ocupacao) - FATOR_DE_CARGA;
    //AnaliseDicionario(*dict);

    //printf("Agrupamento:%f Criterio: %f Fator Carga: %f\n", agrupamento, log(v->tamanho(v))*5, fatorCarga);
    //printf("Agrupamento:%f Criterio: %f Fator Carga: %f\n", agrupamento, criterio, fatorCarga);
    if(agrupamento >= criterio)
        return RecriarHash(dict);

    return NULL;
}

static void* Inserir(TDicionarioDinamico **dict, void *e) {
    TDado *d = (*dict)->dado;
    TVetorDinamico *v = d->dadov;
    TComparavel *c = e;

    int r = rand();
    //if (d->ocupacao < 50) printf("%d\n", r % RANDOMIC_VERIFICATION);
    //int boolean = (r % RANDOMIC_VERIFICATION) == 0;
    int boolean = d->ocupacao % FATOR_DE_CARGA;
    int pos = Hash(c->recuperarChave(c), v->tamanho(v));

    TListaEncadeada *le = v->acessar(v, pos);
    int tam = le->inserir(le, e);

    if(boolean) {
        TDicionarioDinamico *ddict = verificarEstadoTabela(dict);
        if(ddict != NULL) {
            //printf("Rehash\n");
            *dict = ddict;
            d = (*dict)->dado;
            v = d->dadov;
            //printf("Tam: %d\n", v->tamanho(v));
        }
    }

    d->ocupacao++;
    return e;
}

static void* Buscar(TDicionarioDinamico **dict, void *e) {
    TDado *d = (*dict)->dado;
    TVetorDinamico *v = d->dadov;
    TComparavel *c = e;

    int pos = Hash(c->recuperarChave(c), v->tamanho(v));
    TListaEncadeada *le = v->acessar(v, pos);

    return BuscarDebug(le, e);
}

static void Remover(TDicionarioDinamico *dict, void *e) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dadov;
    TComparavel *c = e;

    int pos = Hash(c->recuperarChave(c), v->tamanho(v));
    TListaEncadeada *le = v->acessar(v, pos);
    le->remover(le, e);
}

static TDado* CriarDado(int tam) {
    TDado *d = malloc(sizeof(TDado));
    TVetorDinamico *v = CriarVetorDinamico(tam);

    for(int i = 0; i < tam; i++)
        v->inserir(v, CriarListaEncadeada(), i);

    d->dadov = v;
    d->ocupacao = 0;
    d->vezes_rehash = 0;
    return d;
}

static void ImprimirDicionarioDinamico(TDicionarioDinamico *dict) {
    TDado *d = dict->dado;
    TVetorDinamico *v = d->dadov;
    TListaEncadeada *l;

    for (int i = 0; i < v->tamanho(v); i++) {
        printf("[%d] ", i);
        l = v->acessar(v, i);
        l->imprimir_lista(l);
        printf("\n");
    }
    printf("\n\n");
}

TDicionarioDinamico* CriarDicionarioDinamico(int tam) {
    TDicionarioDinamico *dict = malloc(sizeof(TDicionarioDinamico));
    dict->dado = CriarDado(tam);

    dict->inserir = Inserir;
    dict->buscar = Buscar;
    dict->remover = Remover;
    dict->destruir = DestruirDicionario;
    dict->imprimir = ImprimirDicionarioDinamico;
    return dict;
}
