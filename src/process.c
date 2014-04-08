#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

int partial(MATRIX *m1, MATRIX *m2, int row, int column){
    int i;
    int sum = 0;
    for ( i = 0 ; i < m2->rows ; i++ ){
            sum += matrixGet(m1, row, i) * matrixGet(m2, i, column);
    }

    return sum;
}

void matrixMultiplyCore(MATRIX *m1, MATRIX *m2, MATRIX *result) {
    pid_t pid = 0;
    int r, c;
    int *counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
                                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Troca o vetor da matriz resultante por um vetor presente na memória compartilhada;
    int *_result_matrix = mmap(NULL, sizeof(int)*result->rows*result->columns,
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    result->matrix = _result_matrix;

    *counter = result->rows*result->columns;

    for( r=0 ; r < result->rows ; r++ ){
        for( c=0 ; c < result->columns ; c++ ){
            pid = fork();
            if(pid == 0){
                matrixInsert(result, r, c, partial(m1, m2, r, c));
                *counter = *counter-1;
                exit(0);
            }
            else{
            }
        }
    }

    while(*counter);
}
