#include "stringaed.h"
#include "comparavel.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

short ComparaStringAED(void *e1, void *e2) {
	return strcmp(((TStringAED*)e1)->string, ((TStringAED*)e2)->string);
}

void imprimirStringAED(TStringAED *i) {
	printf("%s", i->string);
}

int recuperarChavePJW(TStringAED *key) {
    const char *ptr;
    int val;
    val = 0;
    ptr = key->string;

    while (*ptr != '\0') {
        int tmp;
        val = (val << 4) + (*ptr);

        if ((tmp = (val & 0xf0000000))) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }

        ptr++;
    }

    return abs(val);
}

TStringAED* CriarStringAED(char *s) {
	TStringAED *e = malloc(sizeof(TStringAED));
	e->string = s;
	e->compara = ComparaStringAED;
	e->imprimir = imprimirStringAED;
	e->recuperarChave = recuperarChavePJW;

	return e;
}
