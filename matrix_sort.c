#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "matrixUtils.h"

int main(int argc, char** argv){

	if(argc != 3){
		printf("\nEnter with the mtx file and the number of threads you want.\n");
		printf("\nHave fun!\n");
	}
	const int N_TH = atoi(argv[2]);
	struct timeval t_start, t_end;
	FILE *f_mtx, *f_sorted_mtx;
	Matrix mtx, sorted_mtx;

	f_mtx = fopen(argv[1],"r");
	f_sorted_mtx = fopen("sortedMtx.map","w");

	//read matrix from file
	extrai_parametros_matriz(f_mtx, &(mtx.LINE), &(mtx.COLUMN), &(mtx.v_line), &(mtx.n_line));
	mtx.mtx = alloc_matrix(mtx.LINE, mtx.COLUMN);
	filein_matriz (mtx.mtx, mtx.LINE, mtx.COLUMN, f_mtx, mtx.v_line, mtx.n_line);
	//initialize its LINE and COLUMN numbers
	sorted_mtx.LINE = mtx.LINE;
	sorted_mtx.COLUMN = mtx.COLUMN;

	//vectorize said matrix
	int *vectorized_mtx = vectorize(mtx.mtx,mtx.LINE,mtx.COLUMN);

	//sort it
	gettimeofday( &t_start, NULL );
	int *sorted_array = dummy_array_sort(vectorized_mtx, mtx.LINE * mtx.COLUMN, N_TH);
	gettimeofday( &t_end, NULL );

	printf("\nArray sort finished\n");
	print_exectime(t_start,t_end);

	//write the sorted matrix into the result file
	sorted_mtx.mtx = array_to_mtx(sorted_array, mtx.LINE, mtx.COLUMN);
	fileout_matriz(sorted_mtx.mtx, sorted_mtx.LINE, sorted_mtx.COLUMN, f_sorted_mtx);

	fclose(f_mtx);
	fclose(f_sorted_mtx);

	return 0;
}
