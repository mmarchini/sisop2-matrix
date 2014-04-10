#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/matrix.h"

typedef struct _S_THREAD_PARAMETERS{
    MATRIX *m1;
    MATRIX *m2;
    MATRIX *result;
    int counter;
} S_THREAD_PARAMETERS;

typedef struct _THREAD_PARAMETERS{
    int row;
    int column;
    S_THREAD_PARAMETERS *tp;
} THREAD_PARAMETERS;

int partial(MATRIX *m1, MATRIX *m2, int row, int column){
    int i;
    int sum = 0;
    for ( i = 0 ; i < m2->rows ; i++ ){
            sum += matrixGet(m1, row, i) * matrixGet(m2, i, column);
    }

    return sum;
}

void *partialThread(void *args) {
    THREAD_PARAMETERS *dtp = (THREAD_PARAMETERS *)args;

    S_THREAD_PARAMETERS *tp = dtp->tp;
    matrixInsert(tp->result, dtp->row, dtp->column, partial(tp->m1, tp->m2, dtp->row, dtp->column));
    tp->counter = tp->counter-1;
}

void matrixMultiplyCore(MATRIX *m1, MATRIX *m2, MATRIX *result, int threads) {
    pthread_t token;
    int r, c;
    S_THREAD_PARAMETERS *tp = calloc(1, sizeof(S_THREAD_PARAMETERS));
    THREAD_PARAMETERS *dtp = NULL;

    tp->m1 = m1;
    tp->m2 = m2;
    tp->result = result;
    tp->counter = result->rows*result->columns;

    for( r=0 ; r < result->rows ; r++ ){
        for( c=0 ; c < result->columns ; c++ ){
            dtp = calloc(1, sizeof(THREAD_PARAMETERS));
            dtp->row=r;
            dtp->column=c;
            dtp->tp = tp;
            pthread_create(&token, NULL, &partialThread, (void *) dtp);
        }
    }
    while(tp->counter);
}
