#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: Better separe those fn's...
//Maybe creating a new "utils shit" would be a good idea

//TODO: Fn to check if a matrix is sorted

typedef struct {
	int LINE, COLUMN; // should be const

  //Those two properties are needed bc "tools.h"
	int n_line;
	int *v_line;

	int **mtx;
} Matrix;

typedef struct {
	int begin, end, *source_array, *sorted_partial, *partial, partialSize;
} Sub_Set;

typedef struct {
    int row_start;
    int row_end;
    int *c_b;
    int **mtx_a;
    int **mtx_b;
    int **result_mtx;
} Multiply_thread_param;

int **create_matrix(int l, int c, int valor);
int **alloc_matrix(int l, int c);
void print_matrix(int **mtx, int l, int c);
void free_matrix(int **mtx, int l);
void print_exectime(struct timeval t_start, struct timeval t_end);

int *vectorize(int **mtx, int line, int column);
int **array_to_mtx(int *arr, int line, int column);

int *dummy_array_sort(int *mtx, const int size, int nthreads); //Multithreading array sort
void *exec_sort(void *arg); //Fn executed by each thread

int **matrix_multiplication(int **mtx_a, int **mtx_b, int l_a, int c_a); //l_a = lines of mtx_a and c_a = columns of mtx_a
int **matrix_multiplication_multi_thread(int **mtx_a, int **mtx_b, int l_a, int c_b, int nthreads);
void *exec_mult(void *arg);
