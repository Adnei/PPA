#include "matrixUtils.h"

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

    printf("\nExecution time: %.3lf sec\n", exectime/1000.0);
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
