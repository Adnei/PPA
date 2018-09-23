# GNU Makefile

CC = gcc
CCFLAGS = -pthread -Wall -g -O3 -std=gnu99
LDFLAGS =
TARGET = matrix_sort gera_matriz matriz_map ind_sort matrix_multiply
EXE = ./gera_matriz

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

matrix_sort: matrix_sort.c tools.o matrixUtils.o merge.o
	$(CC) $(CCFLAGS)  matrixUtils.o merge.o tools.o matrix_sort.c -o $@ $(LDFLAGS)

ind_sort: ind_sort.c tools.o matrixUtils.o merge.o
	$(CC) $(CCFLAGS)  matrixUtils.o merge.o tools.o ind_sort.c -o $@ $(LDFLAGS)

gera_matriz: matriz.o tools.o gera_matriz.c
	$(CC) $(CCFLAGS) matriz.o tools.o gera_matriz.c -o $@ $(LDFLAGS)

matrix_multiply: matrix_multiply.c tools.o matrixUtils.o merge.o
	$(CC) $(CCFLAGS)  matrixUtils.o merge.o tools.o matrix_multiply.c -o $@ $(LDFLAGS)

matriz_map: gera_matriz
	$(EXE) 3 3 > /dev/null
	$(EXE) 4 4 > /dev/null
	$(EXE) 10 10 > /dev/null
	$(EXE) 100 100 > /dev/null
	$(EXE) 500 500 > /dev/null
	$(EXE) 1000 1000 > /dev/null

clean:
	rm -f *.o *~ $(TARGET) *.map
