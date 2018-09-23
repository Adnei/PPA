#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **create_matrix(int l, int c, int valor);
int **alloc_matrix(int l, int c);
void print_matrix(int **mtx, int l, int c);
void free_matrix(int **mtx, int l);
void print_exectime(struct timeval t_start, struct timeval t_end);
int *vectorize(int **mtx, int line, int column);
int **array_to_mtx(int *arr, int line, int column);
