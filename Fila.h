typedef struct{
	int first, last;
	int N;
	int *elementos;
}TFila;

TFila * InitFila( int N );
void insere(TFila *F, int elemento);
int retira(TFila *F);
int vazia(TFila *F);
int cheia(TFila *F);
int primeiro(TFila *F);
