#include <stdio.h>
#include <stdlib.h>
#include "vetorDinamico.h"
#include "listaencadeada.h"
#include "comparavel.h"
#include "dicionarioestatico.h"
#include "dicionariodinamico.h"
#include <time.h>

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

int recuperarChaveJPW(const void *key) {
    const char *ptr;
    int val;
    val = 0;
    ptr = key;

    while (*ptr != '\0') {
        int tmp;
        val = (val << 4) + (*ptr);

        if (tmp = (val & 0xf0000000)) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }

        ptr++;
    }

    return abs(val);
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
    srand(time(NULL));
    TDicionarioDinamico *dict = CriarDicionarioDinamico(11);

    for(int i = 0; i < 100; i++) {
        Integer *in = criarInt(i);
        Integer *aux = dict->inserir(dict, in);
        //printf("%d ", aux->value);
    }
    Integer *in = criarInt(65);
    Integer *aux = dict->buscar(dict, in);
    printf("%d ", aux->value);

    return 0;
}
