Multithreading Matrix Handling #Tests Branch



All the matrices are generates by "matriz.c" (I'll be refactoring this code [one day]) and they're saved as NXM-mat.map.
  e.g.: 3x3-map.map, 10x10-mat.map...
Running "make matriz_map" will generate all the matrices specified in your Makefile.

Matrix multiplication is done by "matrix_multiply.c". It takes two matrices and thread number as parameter.
Run "make matrix_multiply matriz_map" to compile the multiply and generate the matrices, then do the multiplication as follows:
  ./matrix_multiply 1000x1000-mat.map 1000x1000-mat.map 6
  ./matrix_multiply 500x500-mat.map 500x500-mat.map 5

Matrix sorting is done by "matrix_sort.c" and "ind_sort.c". Both are 'ASC' only.
"matrix_sort.c" is way faster than "ind_sort", since it converts the matrix into an vector then sorts it.
"ind_sort.c" was made with the purpose of comparing the two approaches.

Executing matrix sorting:
  ./matrix_sort 1000 5; #it will sort a matrix 1000x1000 using 5 threads
  ./ind_sort 1000 5; #it will sort a matrix 1000x1000 using 5 threads

Testing matrix sorting:
  ./test_all.sh matrix_sort 10;
  ./test_all.sh ind_sort 10;
  #it will execute matrix_sort or ind_sort for matrices 100, 500, 1000, 1500 using 1,5,10,15,20,25,30 threads 10 times each execution

All of these implementations were made with academic purpose.


Rpple;
