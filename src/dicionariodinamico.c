#include <stdlib.h>
#include "vetorDinamico.h"
#include "dicionariodinamico.h"

typedef struct tupla {
    void *chave;
    void *dado;
} TTupla;

typedef struct dado {
    TVetorDinamico *dado;
    
    double fatorEncadeamento;
    double fatorCarga;
}TDado;

static int Hash(void *chave, int tam) {

}


static void (*TInserirDicionarioDinamico)(TDicionarioDinamico *dict, void *chave, void *e) {

}

static void* (*TBuscarDicionarioDinamico)(TDicionarioDinamico *dict, void *chave) {

}

static void (*TRemoverDicionarioDinamico)(TDicionarioDinamico *dict, void *chave) {

}

TDicionarioDinamico* CriarDicionarioDinamico() {

}