#ifndef _LISTA_ENCADEADA_
#define _LISTA_ENCADEADA_

typedef struct listaEncadeada TListaEncadeada;
typedef void (*TInserirListaEncadeada)(TListaEncadeada*, void*);
typedef void* (*TBuscarListaEncadeada)(TListaEncadeada*, void*);
typedef void (*TRemoverListaEncadeada)(TListaEncadeada*, void*);
typedef int (*TTamanhoListaEncadeada)(TListaEncadeada*);

struct listaEncadeada
{
    void *dado;

    TInserirListaEncadeada inserir;
    TRemoverListaEncadeada remover;
    TBuscarListaEncadeada buscar;
    TTamanhoListaEncadeada tamanho;
};

TListaEncadeada* CriarListaEncadeada();

#endif