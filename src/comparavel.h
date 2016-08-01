typedef short(*TCompara)(void*, void*);
typedef  void (*TImprimir)(void*);

typedef struct {
  void *data;
  TCompara compara;
  TImprimir imprimir;
} TComparavel;
