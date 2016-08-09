#ifndef _DICIONARIO_DINAMICO_
#define _DICIONARIO_DINAMICO_

typedef struct dicionarioDinamico TDicionarioDinamico;
typedef void* (*TInserirDicionarioDinamico)(TDicionarioDinamico*, void*);
typedef void* (*TBuscarDicionarioDinamico)(TDicionarioDinamico*, void*);
typedef void (*TRemoverDicionarioDinamico)(TDicionarioDinamico*, void*);
typedef void (*TDestruirDicionarioDinamico)(TDicionarioDinamico*);

struct dicionarioDinamico {
    void *dado;

    TInserirDicionarioDinamico inserir;
    TBuscarDicionarioDinamico buscar;
    TRemoverDicionarioDinamico remover;
    TDestruirDicionarioDinamico destruir;
};

TDicionarioDinamico* CriarDicionarioDinamico(int tam);
#endif