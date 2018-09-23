// #define N_TH 2
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tools.h"
#include "matrixUtils.h"
#include "merge.h"

int *dummy_array_sort(int *mtx, const int size, int nthreads);
void *exec_sort(void *arg);

typedef struct {
	int LINE, COLUMN; // should be const
	int n_line;
	int *v_line;
	int **mtx;
} Matrix;

typedef struct {
	int begin, end, *source_array, *sorted_partial, *partial, partialSize;
} Sub_Set;

int main(int argc, char** argv){

	if(argc != 3){
		printf("\nEnter with the mtx file and the number of threads you want.\n");
		printf("\nHave fun!\n");
	}
	const int N_TH = atoi(argv[2]);

	FILE *f_mtx, *f_sorted_mtx;
	Matrix mtx, sorted_mtx;

	f_mtx = fopen(argv[1],"r");
	f_sorted_mtx = fopen("sortedMtx.map","w");

	extrai_parametros_matriz(f_mtx, &(mtx.LINE), &(mtx.COLUMN), &(mtx.v_line), &(mtx.n_line));
	mtx.mtx = alloc_matrix(mtx.LINE, mtx.COLUMN);
	filein_matriz (mtx.mtx, mtx.LINE, mtx.COLUMN, f_mtx, mtx.v_line, mtx.n_line);

	sorted_mtx.LINE = mtx.LINE;
	sorted_mtx.COLUMN = mtx.COLUMN;

	int *vectorized_mtx = vectorize(mtx.mtx,mtx.LINE,mtx.COLUMN);
	int *sorted_array = dummy_array_sort(vectorized_mtx, mtx.LINE * mtx.COLUMN, N_TH);

	sorted_mtx.mtx = array_to_mtx(sorted_array, mtx.LINE, mtx.COLUMN);
	fileout_matriz(sorted_mtx.mtx, sorted_mtx.LINE, sorted_mtx.COLUMN, f_sorted_mtx);

	fclose(f_mtx);
	fclose(f_sorted_mtx);
	// free(vectorized_mtx);
	// free(sorted_array);
	return 0;
}

int *dummy_array_sort(int *arr, const int size, int nthreads) {
	struct timeval t_start, t_end;
	pthread_t *threads = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
	Sub_Set *sub_set = (Sub_Set *) malloc(nthreads * sizeof(Sub_Set));
	int *sorted_vectorized_mtx = (int *) malloc((size) * sizeof(int));

	gettimeofday( &t_start, NULL );
	for(int i = 0; i < nthreads; i++){
		sub_set[i].begin = i * (size / nthreads);
		sub_set[i].end = (i+1) * (size / nthreads); //It could be ((i+1) * nthreads) -1, but it would imply an operation <=
		if( (i == nthreads-1) && (size % nthreads) >= 1)
			sub_set[i].end = sub_set[i].end + (size % nthreads) ;
		sub_set[i].source_array = arr;
		sub_set[i].partialSize = sub_set[i].end - sub_set[i].begin;
		//FIXME --> you better get rid of partial's
		sub_set[i].partial = (int *) malloc(sub_set[i].partialSize * sizeof(int));
		sub_set[i].sorted_partial = (int *) malloc(sub_set[i].partialSize * sizeof(int));
		// printf("\nbegin --> %d, \nend--> %d", sub_set[i].begin, sub_set[i].end);
		pthread_create( &threads[i], NULL, exec_sort, (void *) (sub_set+i) );
	}

	for (int i = 0; i < nthreads; i++)
	{
		 pthread_join(threads[i], NULL);
	}

	int smaller = 999999;
	int ss_increment = -1;

	for(int arr_count = 0; arr_count < size; arr_count++) {
		for(int ss_count = 0; ss_count < nthreads; ss_count++){
			if(sub_set[ss_count].begin < sub_set[ss_count].end && arr[sub_set[ss_count].begin] <= smaller){
				smaller = arr[sub_set[ss_count].begin];
				ss_increment = ss_count;
			}
		}
		sorted_vectorized_mtx[arr_count] = smaller;
		sub_set[ss_increment].begin ++;
		smaller = 999999; //smaller reset
	}

	gettimeofday( &t_end, NULL );
	printf("\nArray sort finished\n");
	print_exectime(t_start,t_end);

	// free(threads);
	// free(sub_set);

	return sorted_vectorized_mtx;
}

void *exec_sort(void *arg) {
	Sub_Set *sub_set = (Sub_Set *) arg;

	memcpy(sub_set->partial, &(sub_set->source_array[sub_set->begin]), sub_set->partialSize * sizeof(int));
	memcpy(sub_set->sorted_partial, &(sub_set->source_array[sub_set->begin]), sub_set->partialSize * sizeof(int));
	//FIXME --> creating the partial array is screwing up with the memory...
	// Try and change mergesort to be able to change the source_array without having to create a partial.
	// Inside the mergesort function --> use aux variables instead. It would minimize the memory usage.
	mergesort(sub_set->partial,sub_set->sorted_partial,0,sub_set->partialSize-1);
	memcpy(&(sub_set->source_array[sub_set->begin]), sub_set->sorted_partial, sub_set->partialSize * sizeof(int));

	return NULL;
}
