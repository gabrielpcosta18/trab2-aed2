typedef short(*TCompara)(void*, void*);

typedef struct {
  void *data;
  TCompara compara;
} TComparavel;