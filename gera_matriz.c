#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "matriz.h"


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char **argv) {
	int **mat_c = NULL;
	FILE *fmat_c;
	int linha, coluna;
	char filename [100];

	if (argc != 3){
		printf ("ERRO: Numero de parametros %s <nr_linhas> <nr_colunas>", argv[0]);
		exit (1);
	}

	linha =  atoi(argv[1]);
	coluna = atoi(argv[2]);
	sprintf (filename, "%dx%d-mat.map", linha, coluna);

	fmat_c = fopen(filename,"w");
  if ((fmat_c == NULL)) {
		printf("Error: Na abertura dos arquivos.");
		exit(1);
  }

	mat_c = alocar_matriz(linha,coluna);
	gerar_matriz(mat_c, linha, coluna, -9999);
	if ((mat_c == NULL)) {
		printf("ERROR: Out of memory\n");
	}

	printf("\t\t**** PRINT mat_c NxM(%d,%d) **** \n", linha, coluna);
	//imprimir_matriz(mat_c, linha, coluna);
	fileout_matriz(mat_c, linha, coluna, fmat_c);
	liberar_matriz(mat_c, linha, coluna);
	printf("#####\n\n Arquivo com a matriz gerada (mat_out.map).\n");

	fclose(fmat_c);
  return 0;
}
