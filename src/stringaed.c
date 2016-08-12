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

unsigned long recuperarChavePJW(TStringAED *key) {
    const unsigned char *ptr;
    unsigned long val;
    val = 0;
    ptr = key->string;

    while (*ptr != '\0') {
        unsigned long tmp;
        val = (val << 4) + (*ptr);

        if ((tmp = (val & 0xf0000000))) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }

        ptr++;
    }

    return val;
}

unsigned long recuperarChaveDJB2(TStringAED *key) //
{
    unsigned char *str = key->string;
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


TStringAED* CriarStringAED(char *s) {
	TStringAED *e = malloc(sizeof(TStringAED));
	e->string = s;
	e->compara = ComparaStringAED;
	e->imprimir = imprimirStringAED;
	e->recuperarChave = recuperarChaveDJB2;

	return e;
}
