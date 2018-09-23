#include "matriz.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int gerar_matriz(int **matriz, int linha, int coluna, int valor){
	for (int i=0; i < linha; i++)
	  for (int j=0; j < coluna; j++)
			if (valor == -9999)
				matriz[i][j] = rand() % 100;
			else
				matriz[i][j] = valor;
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int zerar_matriz (int **matriz, int linha, int coluna){
	return gerar_matriz(matriz,linha,coluna,0);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int imprimir_matriz (int **matriz, int linha, int coluna){
	for (int j =0; j < coluna; j++)
		printf("\t(%d)", j);
	printf("\n");
	for (int i=0; i < linha; i++) {
		printf("(%d)", i);
	  for (int j=0; j < coluna; j++){
			printf("\t%d", matriz[i][j]);
		}
		printf("\n");
	}
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int **liberar_matriz (int **matriz, int linha, int coluna) {
	for (int i =0; i < linha; i++)
			free(matriz[i]);
	free(matriz);
	return NULL;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int **alocar_matriz (int linha, int coluna) {
	int **nova_a = NULL;

	nova_a = (int **) malloc(linha*sizeof(int *));
	if (!nova_a) {
		printf("ERROR: Out of memory\n");
		return NULL;
	}

  for (int i =0; i < linha; i++) {
			nova_a[i] = (int *) malloc(sizeof(int)*coluna);
			if (!nova_a) {
				printf("ERROR: Out of memory\n");
				return NULL;
			}
	}
	return nova_a;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int somar (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	// if ((N != M) || (N != L) || (L != M)) {
	// 	printf("ERRO: != NxMxL\n");
	// 	exit (1);
	// }
	for (int i=0; i < N; i++)
	  for (int j=0; j < M; j++)
				mat_c[i][j] = mat_a[i][j]+mat_b[i][j];
  return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicar (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++) {
			mat_c[i][j] = 0;
			for (int k=0; k < L; k++)
					mat_c[i][j] += mat_a[i][k]*mat_b[k][j];
		}
  return 0;
}
