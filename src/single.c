#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

int partial(MATRIX *m1, MATRIX *m2, int row, int column){
    for ( int r = 0 ; r < m2->rows ; r++ ){
        for ( int c = 0 ; c < m2->columns ; c++ ) {
        }
    }
}

void matrixMultiplyCore(MATRIX *m1, MATRIX *m2, MATRIX *result) {
    int sum=0;
    for( int r=0 ; r < result->rows ; r++ ){
        for( int c=0 ; c < result->columns ; c++ ){
            sum=0;

            matrixInsert(result, r, c, sum);
        }
    }
}
