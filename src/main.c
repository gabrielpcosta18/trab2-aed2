#include <stdio.h>
#include <stdlib.h>
#include "vetorDinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"

typedef struct integer Integer;
typedef short (*TComparaInteger)(Integer*, Integer*);
typedef void (*TImprimirInteger)(Integer*);
typedef int (*TRecuperarChaveInteger)(Integer*);

struct integer {
	int value;
	TComparaInteger compara;
	TImprimirInteger imprimir;
	TRecuperarChaveInteger recuperarChave;
};

short ComparaInteger(Integer *e1, Integer *e2) {
	return e1->value == e2->value? 0: (e1->value < e2->value)? -1: 1;
}

void imprimirInt(Integer *i) {
	printf("%d", i->value);
}

int recuperarChave(Integer *i) {
	return i->value;
}

Integer* criarInt(int x) {
	Integer *e = malloc(sizeof(Integer));
	e->value = x;
	e->compara = ComparaInteger;
	e->imprimir = imprimirInt;
	e->recuperarChave = recuperarChave;

	return e;
}


int main() {
    //TVetorDinamico *v = CriarVetorDinamico(1);
    TListaEncadeada *v = CriarListaEncadeada();

    for(int i = 0; i < 4; i++) {
        v->inserir(v, criarInt(i));
    }

	v->imprimir_lista(v);
	printf("\n");
	v->remover(v, criarInt(0));
	v->remover(v, criarInt(1));
	v->remover(v, criarInt(2));
	v->remover(v, criarInt(3));
	v->remover(v, criarInt(4));

	/*
    for(int i = 0; i < 101; i++) {
        Integer *e = malloc(sizeof(Integer));
        e->value = i;
        e->compara = ComparaInteger;
        Integer *r = v->buscar(v, e);
        if(r != NULL)
            printf("Result: %d ", r->value);
        else printf(" Achou nao");
    }*/

    return 0;
}
