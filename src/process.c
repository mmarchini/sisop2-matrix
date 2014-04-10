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

void matrixMultiplyCore(MATRIX *m1, MATRIX *m2, MATRIX *result, int threads) {
    pid_t pid = 0;
    int index = 0;
    int r,c,i;
    int current_row=0;
    int rest = m1->rows%threads;

    int *counter = mmap(NULL, sizeof(int)*threads, PROT_READ | PROT_WRITE, 
                                MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    for(index==threads-1;index!=0;index--) counter[index]=0;

    // Troca o vetor da matriz resultante por um vetor presente na memória compartilhada;
    int *_result_matrix = mmap(NULL, sizeof(int)*result->rows*result->columns,
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    result->matrix = _result_matrix;

    for(i=0; i<threads; i++){
        pid = fork();
        if(pid == 0){
            if(rest){
                rest=1;
            }
            for(
                    r=current_row;
                    r<(current_row+(m1->rows/threads)+rest);
                    r++
            ) {
                for( c=0 ; c < result->columns ; c++ )
                    matrixInsert(result, r, c, partial(m1, m2, r, c));
            }
            counter[i]=1;
            exit(0);
        }
        else{
            current_row=current_row+(m1->rows/threads)+(rest ? 1 : 0);
            if(rest)
                rest--;
        }
    }

    while(index!=threads) while(index!=threads && counter[index]!=0) index++;
}

