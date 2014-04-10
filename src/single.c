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
    int r, c;
    for( r=0 ; r < result->rows ; r++ ){
        for( c=0 ; c < result->columns ; c++ ){
            matrixInsert(result, r, c, partial(m1, m2, r, c));
        }
    }
}
