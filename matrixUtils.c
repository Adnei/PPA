#include <pthread.h>
#include "matrixUtils.h"
#include "merge.h"

//@Deprecated --> The matrix is now created beforehand; The matrix is now stored in a file.
int **create_matrix(int l, int c, int valor) {
	int **new_mtx = alloc_matrix(l,c);

	if(!!new_mtx){
		for(int i = 0; i < l; i++){
			for(int j = 0; j < c; j ++){
				if(valor == -999)
					new_mtx[i][j] = rand() % 100;
				else
					new_mtx[i][j] = valor;
			}
		}
	}

	return new_mtx;
}

int **alloc_matrix(int l, int c) {
	int **new_mtx = NULL;
	new_mtx = (int **) malloc(l * sizeof(int *));
	if(!new_mtx){
		printf("ERROR executing alloc_matrix\n");
		return NULL;
	}

	for(int i = 0; i < l; i++){
		new_mtx[i] = (int *) malloc(c * sizeof(int));
		if(!new_mtx){
			printf("ERROR executing alloc_matrix\n");
			return NULL;
		}
	}

	return new_mtx;
}


void print_matrix(int **mtx, int l, int c) {
	for(int i = 0; i < l; i++){
		printf("|");
		for(int j = 0; j < c; j++){
			printf("%3d  ",mtx[i][j]);
		}
		printf("|\n");
	}
	printf("\n\n");

}

void free_matrix(int **mtx, int l) {
	for(int i = 0; i < l; i++){
		free(mtx[i]);
	}
	free(mtx);
}

void print_exectime(struct timeval t_start, struct timeval t_end) {
    double exectime;

    exectime = (t_end.tv_sec - t_start.tv_sec) * 1000.0; // sec to ms
    exectime += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms

    printf("%.6lf",exectime/1000.0);
}

int *vectorize(int **mtx, int line, int column) {
  int *result_vector = (int *) malloc((line * column) * sizeof(int));
  int global_count = 0;

  for(int i = 0; i < line; i++){
    for(int j = 0 ; j < column; j++){
      result_vector[global_count] = mtx[i][j];
      global_count ++;
    }
  }

  return result_vector;

}

int **array_to_mtx(int *arr, int line, int column) {
	int **result_mtx = alloc_matrix(line, column);
	int i = 0, j = 0;

	for(int arr_count = 0; arr_count < line * column; arr_count++){
		if(j >= column){
			j = 0;
			i++;
		}

		result_mtx[i][j] = arr[arr_count];
		j++;
	}

	return result_mtx;
}


int *dummy_array_sort(int *arr, const int size, int nthreads) {

	pthread_t *threads = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
	Sub_Set *sub_set = (Sub_Set *) malloc(nthreads * sizeof(Sub_Set));
	int *sorted_vectorized_mtx = (int *) malloc((size) * sizeof(int));

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


int **matrix_multiplication(int **mtx_a, int **mtx_b, int l_a, int c_a) {
	int **result_mtx = create_matrix(l_a,c_a,0);

	for(int i = 0; i < l_a; i++) {
		for(int j = 0; j < c_a; j++) {
			for(int result_l = 0; result_l < l_a; result_l++) {
				result_mtx[i][j] += mtx_a[i][result_l] * mtx_b[result_l][j];
			}
		}
	}

	return result_mtx;
}

int **matrix_multiplication_multi_thread(int **mtx_a, int **mtx_b, int l_a, int c_b, int nthreads) {
  int **result_mtx = create_matrix(l_a, c_b, 0);
  pthread_t *threads;
  Multiply_thread_param *args;

  threads = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
  args = (Multiply_thread_param *) malloc(nthreads * sizeof(Multiply_thread_param));

  for(int i = 0; i < nthreads; i++){
    args[i].row_start = i * (l_a / nthreads);
    args[i].row_end = ((i+1) * (l_a / nthreads));
    if( (i == nthreads-1) && (l_a % nthreads))
      args[i].row_end = args[i].row_end + (l_a % nthreads) ;
    args[i].c_b = &c_b; //should be l_a (?)
    args[i].mtx_a = mtx_a;
    args[i].mtx_b = mtx_b;
    args[i].result_mtx = result_mtx;
    pthread_create( &threads[i], NULL, exec_mult, (void *) (args+i) );
  }

  for (int i = 0; i < nthreads; i++)
  {
     pthread_join(threads[i], NULL);
  }

	return result_mtx;
}

void *exec_mult(void *arg) {
  Multiply_thread_param *param = (Multiply_thread_param *) arg;
  int cell_result;
  for(int i = param->row_start; i < param->row_end; i++) {
    for(int j = 0; j < *(param->c_b); j++){ //columns of mtx_b
      cell_result = 0; //initialize the sum (it will be the cell's value)
      for(int k = 0; k < *(param->c_b); k++) {
        cell_result += param->mtx_a[i][k] * param->mtx_b[k][j];
      }
      param->result_mtx[i][j] = cell_result;
    }
  }
  return NULL;
}
