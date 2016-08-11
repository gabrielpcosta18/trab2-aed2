typedef struct stringaed TStringAED;
typedef short (*TComparaStringAED)(void*, void*);
typedef void (*TImprimirStringAED)(TStringAED*);
typedef int (*TRecuperarChaveStringAED)(TStringAED*);

struct stringaed {
	char *string;
	TComparaStringAED compara;
	TImprimirStringAED imprimir;
	TRecuperarChaveStringAED recuperarChave;
};

TStringAED* CriarStringAED(char *s);
short ComparaStringAED(void *e1, void *e2);
