typedef short(*TCompara)(void*, void*);
typedef void (*TImprimir)(void*);
typedef unsigned long (*TRecuperarChave)(void*);

typedef struct {
  void *data;
  TCompara compara;
  TImprimir imprimir;
  TRecuperarChave recuperarChave;
} TComparavel;
