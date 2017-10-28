#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

// TODO
// Problema com Inicio = Fim
// Entradas (arquivo e ponto inicio e ponto fim)
// Melhorar a sa�da

// Struct para armazenar um ponto de maneira que parece mais natural (linha e coluna).
// Utilizo como primeira linha 0 e primeira coluna 0.
typedef struct{
    int linha;
    int coluna;
}Ponto;

// Fun��es principais para resolu��o do problema.
// Fun��o principal para resolver o problema, recebe o tamanho do labirinto, o labirinto e os dois pontos, in�cio e fim.
void resolverLabirinto(int size, int maze[size][size], Ponto inicio, Ponto fim);
// Fun��o que coloca na fila os vizinhos que ainda n�o foram visitados de um dado ponto do lbarinto e marca no labirinto esses vizinhos com o ponto que leva at� eles.
void inserirVizinhos(TFila * fila, Ponto ponto, int size, int maze[size][size], Ponto inicio);

// Fun��es suporte.
// Dado a representa��o num�rica de um ponto converte ele na representa��o linha x coluna.
Ponto converteNumero(int numero, int size);
// Dado um ponto representado por linha x coluna devolve a representa��o num�rica do ponto.
int convertePonto(Ponto ponto, int size);

// Fun��es de entrada e saida.
int scanNumber();
void imprimirFila(TFila * fila);
void imprimirLabirinto(int size, int maze[size][size]);
void imprimirLabirintoComReferencia(int size, int maze[size][size]);
void imprimirPonto(Ponto ponto);

int main()
{
	// Define o tamanho do labirinto.
    int size = 3;
    
    // Cria o labirinto e inicializa os pontos.
    // ( o labirinto est� sendo feito com todos os pontos poss�veis ( 0 em todas as posi��es ).
    int maze[size][size];
    int linha;
    int coluna;
    for(linha = 0; linha < size; linha++){
        for(coluna = 0; coluna < size; coluna++){
            maze[linha][coluna] = 0;
        }
    }
    maze[1][0] = -1;
    maze[1][1] = -1;
    
    // Define o ponto inicial no labirinto.
	Ponto inicio;
	inicio.linha = 0;
    inicio.coluna = 0;
    printf("Ponto inicial\n");
    imprimirPonto(inicio);
    
    // Define o ponto de destino no labirinto.
    Ponto fim;
    fim.linha = 2;
    fim.coluna = 2;
    printf("Ponto final\n");
    imprimirPonto(fim);
    
    printf("\n");
    // Resolve o labirinto.
    resolverLabirinto(size, maze, inicio, fim);
    
    // Encontrei o menor caminho.
    if (maze[fim.linha][fim.coluna] != 0){
    	printf("\n");
    	printf("Menor caminho encontrado:\n");
    	// Imprime o menor caminho.
    	imprimirPonto(fim);
    	int a;
    	a = maze[fim.linha][fim.coluna];
    	int tamanhoCaminho = 1;
    	while(a != 0){
    		Ponto anterior;
    		anterior = converteNumero(a, size);
    		imprimirPonto(anterior);
    		tamanhoCaminho = tamanhoCaminho + 1;
    		a = maze[anterior.linha][anterior.coluna];
		}
		
		printf("O menor caminho percorre %d pontos.\n", tamanhoCaminho);
    	
	}else{
		printf("Nao existe caminho entre os pontos fornecidos\n");
		printf("Ponto inicial\n");
		imprimirPonto(inicio);
		printf("Ponto final\n");
		imprimirPonto(fim);
	}
    
    return 0;
}

void resolverLabirinto(int size, int maze[size][size], Ponto inicio, Ponto fim){
	// Cria a fila usada no algoritmo.
    TFila * fila = InitFila(size*size);

	// Exibe o estado inicial do labirinto e da fila.
    imprimirLabirinto(size, maze);
    imprimirFila(fila);
    
    // Processa o ponto inicial.
    inserirVizinhos(fila, inicio, size, maze, inicio);
    
    // Exibe o estado do labirinto e da fila.
    imprimirLabirinto(size, maze);
    imprimirFila(fila);

	// Come�a o loop em busca do menor caminho at� o ponto final
    Ponto pontoAtual = inicio;
    int numero;
    // Enquanto a fila n�o est� vazia e eu ainda n�o atingi o meu ponto final busco pelo caminho mais curto.
    while(vazia(fila) != 1 && maze[fim.linha][fim.coluna] == 0 ){
    	// Retiro a forma num�rica de um ponto da fila e processo os seus vizinhos.
        numero = retira(fila);
        pontoAtual = converteNumero(numero, size);
        inserirVizinhos(fila, pontoAtual, size, maze, inicio);
        
        // Imprimo o estado do labirinto e da fila.
        imprimirLabirinto(size, maze);
        imprimirFila(fila);
    }
}

void inserirVizinhos(TFila * fila, Ponto ponto, int size, int maze[size][size], Ponto inicio){
	// Converte o ponto de refer�ncia na sua forma num�rica.
    int numero = convertePonto(ponto, size);
    
    
    // Pega o vizinho da direita
    Ponto vizinho;
    vizinho.linha = ponto.linha;
    vizinho.coluna = ponto.coluna + 1;
    // Verifica se o vizinho da direita do ponto existe, n�o � o ponto inicial, o ponto est� livre e ainda n�o foi visitado.
    if(vizinho.coluna < size && (vizinho.linha != inicio.linha || vizinho.coluna != inicio.coluna) && maze[vizinho.linha][vizinho.coluna] == 0){
    	// Insere na fila e coloca a forma num�rica do ponto de refer�ncia no vizinho da direita.
        insere(fila, convertePonto(vizinho, size));
        maze[vizinho.linha][vizinho.coluna] = numero;
    }
    
    // Repete o processo para o vizinho de baixo, depois o da esquerda e depois o de cima.
    vizinho.linha = ponto.linha + 1;
    vizinho.coluna = ponto.coluna;
    if(vizinho.linha < size && (vizinho.linha != inicio.linha || vizinho.coluna != inicio.coluna) && maze[vizinho.linha][vizinho.coluna] == 0){
        insere(fila, convertePonto(vizinho, size));
        maze[vizinho.linha][vizinho.coluna] = numero;
    }
    
    vizinho.linha = ponto.linha;
    vizinho.coluna = ponto.coluna - 1;
    if(vizinho.coluna >= 0 && (vizinho.linha != inicio.linha || vizinho.coluna != inicio.coluna) && maze[vizinho.linha][vizinho.coluna] == 0){
        insere(fila, convertePonto(vizinho, size));
        maze[vizinho.linha][vizinho.coluna] = numero;
    }
    
    vizinho.linha = ponto.linha - 1;
    vizinho.coluna = ponto.coluna;
    if(vizinho.linha >= 0 && (vizinho.linha != inicio.linha || vizinho.coluna != inicio.coluna) && maze[vizinho.linha][vizinho.coluna] == 0){
        insere(fila, convertePonto(vizinho, size));
        maze[vizinho.linha][vizinho.coluna] = numero;
    }
}

int convertePonto(Ponto ponto, int size){
    return ponto.linha * size + ponto.coluna + 1;
}

Ponto converteNumero(int numero, int size){
    int n = numero - 1;
    Ponto ponto;
    ponto.linha = n / size;
    ponto.coluna = n % size;
    return ponto;
}

int scanNumber(){
    int number;
    printf("Enter a number\n");
    number = getchar();
    if(number < 48 || number >  57){
        number = scanNumber();
    }
    return number - 48;
}

void imprimirFila(TFila * fila){
    int i;
    printf("Fila \n");
    for(i = fila->first; i < fila->last; i++){
        printf("%d ", fila->elementos[i]);
    }
    printf("\n");
}

void imprimirLabirinto(int size, int maze[size][size]){
    int linha;
    int coluna;
    printf("Labirinto \n");
    for(linha = 0; linha < size; linha++){
        for(coluna = 0; coluna < size; coluna++){
            printf("%d\t", maze[linha][coluna]);
        }
        printf("\n");
    }
}

void imprimirLabirintoComReferencia(int size, int maze[size][size]){
    int linha;
    int coluna;
    printf("Labirinto \n");
    for(linha = 0; linha < size; linha++){
        for(coluna = 0; coluna < size; coluna++){
            printf("%d\t", maze[linha][coluna]);
        }
        printf("\n");
    }
}

void imprimirPonto(Ponto ponto){
	printf("Ponto: linha %d, coluna %d\n", ponto.linha, ponto.coluna);
}
