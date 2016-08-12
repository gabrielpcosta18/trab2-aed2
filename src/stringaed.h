#ifndef _STRINGAED_
#define _STRINGAED_

typedef struct stringaed TStringAED;
typedef short (*TComparaStringAED)(void*, void*);
typedef void (*TImprimirStringAED)(TStringAED*);
typedef unsigned long (*TRecuperarChaveStringAED)(TStringAED*);

struct stringaed {
	unsigned char *string;
	TComparaStringAED compara;
	TImprimirStringAED imprimir;
	TRecuperarChaveStringAED recuperarChave;
};

TStringAED* CriarStringAED(char *s);
short ComparaStringAED(void *e1, void *e2);

#endif
