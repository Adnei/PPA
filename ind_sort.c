#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "matrixUtils.h"

int **line_merge_sort(Matrix mtx, int nthreads);

int main(int argc, char** argv){

	if(argc != 3){
		printf("\nEnter with the mtx file and the number of threads you want.\n");
		printf("\nHave fun!\n");
	}
	const int N_TH = atoi(argv[2]);

	FILE *f_mtx, *f_sorted_mtx;
	Matrix mtx, sorted_mtx;

	struct timeval t_start, t_end;

	f_mtx = fopen(argv[1],"r");
	f_sorted_mtx = fopen("sortedIndMtx.map","w");

  //read matrix from file
	extrai_parametros_matriz(f_mtx, &(mtx.LINE), &(mtx.COLUMN), &(mtx.v_line), &(mtx.n_line));
  mtx.mtx = alloc_matrix(mtx.LINE, mtx.COLUMN);
  filein_matriz (mtx.mtx, mtx.LINE, mtx.COLUMN, f_mtx, mtx.v_line, mtx.n_line);

  //initialize LINE and COLUMN numbers
	sorted_mtx.LINE = mtx.LINE;
	sorted_mtx.COLUMN = mtx.COLUMN;
  //create a new matrix which will be sorted
  sorted_mtx.mtx = alloc_matrix(sorted_mtx.LINE, sorted_mtx.COLUMN);

	gettimeofday( &t_start, NULL );

  //TODO: Multithreading lines sort (?)
  //sort each line
  for(int i = 0; i < mtx.LINE; i++){
    sorted_mtx.mtx[i] = dummy_array_sort(mtx.mtx[i],mtx.COLUMN, N_TH);
  }
  //sort the whole matrix
	sorted_mtx.mtx = line_merge_sort(sorted_mtx,N_TH);

	gettimeofday( &t_end, NULL );
	printf("\nFucked up matrix sort finished\n");
	print_exectime(t_start,t_end);

	fileout_matriz(sorted_mtx.mtx, sorted_mtx.LINE, sorted_mtx.COLUMN, f_sorted_mtx);

	fclose(f_mtx);
	fclose(f_sorted_mtx);
	return 0;
}


int **line_merge_sort(Matrix mtx, int nthreads) {
	int **result_mtx = alloc_matrix(mtx.LINE, mtx.COLUMN);
	Sub_Set *sub_set = (Sub_Set *) malloc(mtx.LINE * sizeof(Sub_Set));

	for(int i=0; i<mtx.LINE; i++){
		sub_set[i].begin = 0;
		sub_set[i].end = mtx.COLUMN -1;
		sub_set[i].source_array = mtx.mtx[i];
		sub_set[i].partialSize = mtx.COLUMN;
	}

	int smaller = 9999, used_idx = -1;

	//O(n^3) --> This is quite damn fucked.
	//Thats why we sort a matrix by vectorizing it first.
	for(int mtx_i = 0; mtx_i < mtx.LINE; mtx_i++){
		for(int mtx_j = 0; mtx_j < mtx.COLUMN; mtx_j++){
			for(int line = 0; line < mtx.LINE; line++){
				if(sub_set[line].begin <= sub_set[line].end && mtx.mtx[line][sub_set[line].begin] <= smaller ){
					smaller = mtx.mtx[line][sub_set[line].begin];
					used_idx = line;
				}
			}
			result_mtx[mtx_i][mtx_j] = smaller;
			sub_set[used_idx].begin++;
			smaller = 9999;
		}
	}

	return result_mtx;
}
