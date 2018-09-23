#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gerar_matriz(int **matriz, int linha, int coluna, int valor);
int zerar_matriz (int **matriz, int linha, int coluna);
int imprimir_matriz (int **matriz, int linha, int coluna);
int **liberar_matriz (int **matriz, int linha, int coluna);
int **alocar_matriz (int linha, int coluna);
int somar (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);
int multiplicar (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);
