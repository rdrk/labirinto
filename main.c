#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

int main()
{
//    int size = 3;
//    int field[size][size];
//    int i;
//    for(i = 0; i < size; i++){
//        field[i][i] = 0;
//    }
//    printf("Hello world!\n");
//    printf("%d\n", size);
//    TFila * fila = InitFila(size);
//    insere(fila, 2);
//    insere(fila, 5);
//    int first = primeiro(fila);
//    printf("%d\n", first);
//    printf("%d\n", field[0][0]);
//    test();
//    int number;
//    number = scanNumber2();
//    printf("You entered:\n%d\n", number);
    labirinto();
    return 0;
}

int f = 5;

void test(){
    printf("test\n");
    printf("%d\n", f);
}

int scanNumber(){
    int number;
    printf("Enter a number\n");
    int ok = scanf("%d", &number);
    printf("%d\n", ok);
    if(ok == 0){
        number = scanNumber();
    }
    return number;
}

int scanNumber2(){
    int number;
    printf("Enter a number\n");
    number = getchar();
    if(number < 48 || number >  57){
        number = scanNumber2();
    }
    return number - 48;
}

typedef struct{
    int linha;
    int coluna;
}Ponto;

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

void inserirVizinhos(TFila * fila, Ponto ponto, int size, int maze[size][size]){
    int numero = convertePonto(ponto, size);
    Ponto vizinho;
    if(ponto.coluna + 1 < size && maze[ponto.linha][ponto.coluna + 1] == 0){
        vizinho.linha = ponto.linha;
        vizinho.coluna = ponto.coluna + 1;
        insere(fila, convertePonto(vizinho, size));
        maze[ponto.linha][ponto.coluna + 1] = numero;
    }
    if(ponto.linha + 1 < size && maze[ponto.linha + 1][ponto.coluna] == 0){
        vizinho.linha = ponto.linha + 1;
        vizinho.coluna = ponto.coluna;
        insere(fila, convertePonto(vizinho, size));
        maze[ponto.linha + 1][ponto.coluna] = numero;
    }
    if(ponto.coluna - 1 > 0 && maze[ponto.linha][ponto.coluna - 1] == 0){
        vizinho.linha = ponto.linha;
        vizinho.coluna = ponto.coluna - 1;
        insere(fila, convertePonto(vizinho, size));
        maze[ponto.linha][ponto.coluna - 1] = numero;
    }
    if(ponto.linha - 1 > 0 && maze[ponto.linha - 1][ponto.coluna] == 0){
        vizinho.linha = ponto.linha - 1;
        vizinho.coluna = ponto.coluna;
        insere(fila, convertePonto(vizinho, size));
        maze[ponto.linha - 1][ponto.coluna] = numero;
    }
}

void labirinto(){
    int size = 3;
    int maze[size][size];
    int linha;
    int coluna;
    for(linha = 0; linha < size; linha++){
        for(coluna = 0; coluna < size; coluna++){
            maze[linha][coluna] = 0;
        }
    }
    Ponto inicio;
    Ponto fim;
    inicio.linha = 0;
    inicio.coluna = 0;
    fim.linha = size;
    fim.coluna = size;
    TFila * fila = InitFila(size*size);

    imprimirLabirinto(size, maze);
    imprimirFila(fila);
    inserirVizinhos(fila, inicio, size, maze);
    imprimirLabirinto(size, maze);
    imprimirFila(fila);

//    Ponto p = converteNumero(7, size);
//    printf("Ponto\n");
//    printf("linha: %d ", p.linha);
//    printf("coluna: %d", p.coluna);
//    printf("\n");
//    printf("Numero: %d", convertePonto(p, size));
//    printf("\n");
//
//    inserirVizinhos(fila, inicio, size, maze);
//    imprimirLabirinto(size, maze);
//    imprimirFila(fila);

    Ponto pontoAtual = inicio;
    int numero;
    while(vazia(fila) == 0){
        numero = retira(fila);
        pontoAtual = converteNumero(numero, size);
        inserirVizinhos(fila, pontoAtual, size, maze);
        imprimirLabirinto(size, maze);
        imprimirFila(fila);
    }
}
