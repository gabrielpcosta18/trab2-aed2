typedef struct termo TTermo;
typedef struct preproc TPreproc;



struct preproc {
    int pag;
    int contagem;
    double tf_idf;
};

struct termo {
    TStringAED *palavra;
    TListaEncadeada *ocorrencias;
};

