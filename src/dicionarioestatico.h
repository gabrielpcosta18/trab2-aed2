#ifndef _DICIONARIO_ESTATICO_
#define _DICIONARIO_ESTATICO_

typedef struct dicionarioEstatico TDicionarioEstatico;
typedef void* (*TBuscarDicionarioEstatico)(TDicionarioEstatico*, void*);

struct dicionarioEstatico {
    void *dado;

    TBuscarDicionarioEstatico buscar;
};

TDicionarioEstatico* CriarDicionarioEstatico(void **e,  int tam);

#endif