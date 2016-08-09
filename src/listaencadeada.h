#ifndef _LISTA_ENCADEADA_
#define _LISTA_ENCADEADA_

typedef struct listaEncadeada TListaEncadeada;
typedef int (*TInserirListaEncadeada)(TListaEncadeada*, void*);
typedef void* (*TBuscarListaEncadeada)(TListaEncadeada*, void*);
typedef short (*TRemoverListaEncadeada)(TListaEncadeada*, void*);
typedef int (*TTamanhoListaEncadeada)(TListaEncadeada*);
typedef void (*TImprimirListaEncadeada)(TListaEncadeada*);
typedef void (*TDestruirListaEncadeada)(TListaEncadeada*);
typedef void* (*TRemoverPrimeiroElemento)(TListaEncadeada*);
struct listaEncadeada
{
    void *dado;

    TInserirListaEncadeada inserir;
    TRemoverListaEncadeada remover;
    TBuscarListaEncadeada buscar;
    TTamanhoListaEncadeada tamanho;
    TImprimirListaEncadeada imprimir_lista;
	TDestruirListaEncadeada destruir;
    TRemoverPrimeiroElemento remover_primeiro_elemento;
};

TListaEncadeada* CriarListaEncadeada();

#endif
