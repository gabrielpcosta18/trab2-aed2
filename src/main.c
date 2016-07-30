#include <stdio.h>
#include <stdlib.h>
#include "vetorDinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"

typedef struct integer Integer;
typedef short (*TComparaInteger)(Integer*, Integer*);

struct integer {
	int value;
	TComparaInteger compara;
};

short ComparaInteger(Integer *e1, Integer *e2) {
	return e1->value == e2->value? 0: (e1->value < e2->value)? -1: 1;
}

int main() {
    //TVetorDinamico *v = CriarVetorDinamico(1);    
    TListaEncadeada *v = CriarListaEncadeada();
    
    for(int i = 0; i < 100; i++) {
        Integer *e = malloc(sizeof(Integer));
        e->value = i;
        e->compara = ComparaInteger;
        v->inserir(v, e);
    }
    
    for(int i = 0; i < 101; i++) {
        Integer *e = malloc(sizeof(Integer));
        e->value = i;
        e->compara = ComparaInteger;
        Integer *r = v->buscar(v, e);
        if(r != NULL)
            printf("Result: %d ", r->value);
        else printf(" Achou nao");
    }

    return 0;    
}