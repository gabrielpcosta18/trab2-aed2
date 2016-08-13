#ifndef _VETOR_DINAMICO_
#define _VETOR_DINAMICO_

typedef struct vetorDinamico TVetorDinamico;

// declaração dos tipos Função/Método
typedef void (*TInserir)(TVetorDinamico*,void*, int);
typedef void* (*TAcessar)(TVetorDinamico*, int);
typedef int (*TTamanho)(TVetorDinamico*);
typedef void (*TImprimirVetorDinamico)(TVetorDinamico*);

void* BuscaVetorDinamico(TVetorDinamico* v, void* e);

//construtor
TVetorDinamico *CriarVetorDinamico(int);

//destrutor
void DestruirVetorDinamico(TVetorDinamico*);

struct vetorDinamico{
	void *dado;

	int tam;
	TInserir inserir;
	TAcessar acessar;
	TTamanho tamanho;
	TImprimirVetorDinamico imprimir;
};

#endif
