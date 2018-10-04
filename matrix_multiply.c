#define RND  -999
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "matrixUtils.h"

int main(int argc, char **argv) {

	if(argc != 4) {
		printf("Ow meu consagrado! Preciso de 4 parametros...\n");
    printf("./executaDiabo FILE_MTX_A FILE_MTX_B 2\n");
		return 0;
	}

  if(!atoi(argv[3]) || atoi(argv[3]) < 0 ){
    printf("\nERROR. Verify your last parameter\n");
  }

  FILE *fmat_a, *fmat_b, *fmat_c, *fmat_d;
  Matrix mtx_a,  mtx_b, mtx_c, mtx_d;
  fmat_a = fopen(argv[1],"r");
  fmat_b = fopen(argv[2],"r");
  fmat_c = fopen("resultThread.map","w");
  fmat_d = fopen("resultSeq.map","w");

  struct timeval t_start_seq, t_end_seq, t_start_th, t_end_th;;

  extrai_parametros_matriz(fmat_a, &(mtx_a.LINE), &(mtx_a.COLUMN), &(mtx_a.v_line), &(mtx_a.n_line));
  extrai_parametros_matriz(fmat_b, &(mtx_b.LINE), &(mtx_b.COLUMN), &(mtx_b.v_line), &(mtx_b.n_line));

  mtx_a.mtx = alloc_matrix(mtx_a.LINE, mtx_a.COLUMN);
  mtx_b.mtx = alloc_matrix(mtx_b.LINE, mtx_b.COLUMN);

  filein_matriz (mtx_a.mtx, mtx_a.LINE, mtx_a.COLUMN, fmat_a, mtx_a.v_line, mtx_a.n_line);
  filein_matriz (mtx_b.mtx, mtx_b.LINE, mtx_b.COLUMN, fmat_b, mtx_b.v_line, mtx_b.n_line);

  mtx_c.LINE = mtx_a.LINE;
  mtx_c.COLUMN = mtx_b.COLUMN;
  mtx_c.mtx = create_matrix(mtx_c.LINE, mtx_c.COLUMN,0); //used to allocate the matrix and fill it with 0's;

  mtx_d.LINE = mtx_a.LINE;
  mtx_d.COLUMN = mtx_b.COLUMN;
  mtx_d.mtx = create_matrix(mtx_d.LINE, mtx_d.COLUMN,0); //used to allocate the matrix and fill it with 0's;

  gettimeofday( &t_start_th, NULL );
	//matrix_multiplication_omp
  // mtx_c.mtx = matrix_multiplication_multi_thread(mtx_a.mtx, mtx_b.mtx , mtx_a.LINE, mtx_b.COLUMN , atoi(argv[3]));
	mtx_c.mtx = matrix_multiplication_omp(mtx_a.mtx, mtx_b.mtx , mtx_a.LINE, mtx_b.COLUMN , atoi(argv[3]));
  gettimeofday( &t_end_th, NULL );
  printf("\nThreads\n");
  print_exectime(t_start_th,t_end_th);

  gettimeofday( &t_start_seq, NULL );
  mtx_d.mtx = matrix_multiplication(mtx_a.mtx, mtx_b.mtx, mtx_a.LINE, mtx_b.COLUMN);
  gettimeofday( &t_end_seq, NULL );
  printf("\nSequencial!\n");
  print_exectime(t_start_seq,t_end_seq);

  fileout_matriz(mtx_c.mtx, mtx_c.LINE, mtx_c.COLUMN, fmat_c);
  fileout_matriz(mtx_d.mtx, mtx_d.LINE, mtx_d.COLUMN, fmat_d);

	return 0;
}
