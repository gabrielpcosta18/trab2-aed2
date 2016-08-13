#ifndef _LISTA_ENCADEADA_
#define _LISTA_ENCADEADA_

typedef struct listaEncadeada TListaEncadeada;
typedef int (*TInserirListaEncadeada)(TListaEncadeada*, void*);
typedef void* (*TBuscarListaEncadeada)(TListaEncadeada*, void*);
typedef short (*TRemoverListaEncadeada)(TListaEncadeada*, void*);
typedef int (*TTamanhoListaEncadeada)(TListaEncadeada*);
typedef void (*TImprimirListaEncadeada)(TListaEncadeada*);
typedef void (*TImprimirListaEncadeadaN)(TListaEncadeada*, int);
typedef void (*TDestruirListaEncadeada)(TListaEncadeada*);
typedef void* (*TRemoverPrimeiroElemento)(TListaEncadeada*);
typedef short (*TVaziaListaEncadeada)(TListaEncadeada*);
typedef short (*TComparaElementosListaEncadeada)(void*, void*);

void reordenar_lista(TListaEncadeada **l);
void iterar_sobre(TListaEncadeada *l, void (*operacao)(void*, void*), void* params);
void* BuscarDebug(TListaEncadeada *l, void *e);

struct listaEncadeada
{
    void *dado;

    TInserirListaEncadeada inserir;
    TRemoverListaEncadeada remover;
    TBuscarListaEncadeada buscar;
    TTamanhoListaEncadeada tamanho;
    TImprimirListaEncadeada imprimir_lista;
    TImprimirListaEncadeadaN imprimir_lista_n;
	TDestruirListaEncadeada destruir;
    TRemoverPrimeiroElemento remover_primeiro_elemento;
	TComparaElementosListaEncadeada compara_elementos;
	TVaziaListaEncadeada vazia;
};

TListaEncadeada* CriarListaEncadeada();
TListaEncadeada* CriarListaEncadeadaOrdenada(TComparaElementosListaEncadeada);

#endif
