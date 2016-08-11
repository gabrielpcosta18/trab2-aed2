#ifndef _STRING_AED2_
#define _STRING_AED2_

typedef struct String TString;

// declaração dos tipos Função/Método
typedef void (*TInserir)(TString*,void*, int);
typedef void* (*TAcessar)(TString*, int);
typedef int (*TTamanho)(TString*);
//construtor
TString *CriarString(int);

//destrutor
void DestruirString(TString*);

struct String{
	void *dado;

	int tam;
	TInserir inserir;
	TAcessar acessar;
	TTamanho tamanho;
};

#endif
