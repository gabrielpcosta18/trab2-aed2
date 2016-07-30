#include <stdio.h>
#include <stdlib.h>
#include "vetorDinamico.h"
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
    TVetorDinamico *v = CriarVetorDinamico(1);

    for(int i = 0; i < 100; i++) {
        Integer *e = malloc(sizeof(Integer));
        e->value = i;
        e->compara = ComparaInteger;
        v->inserir(v, e, i);
    }

    for(int i = 0; i < 100; i++) {
        printf("%d ", ((Integer*) v->acessar(v, i))->value);
    }
}