#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/matrix.h"

typedef struct _S_THREAD_PARAMETERS{
    MATRIX *m1;
    MATRIX *m2;
    MATRIX *result;
    int *counter;
} S_THREAD_PARAMETERS;

typedef struct _THREAD_PARAMETERS{
    int row0;
    int row1;
    int index;
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
    int r,c;
    THREAD_PARAMETERS *dtp = (THREAD_PARAMETERS *)args;

    S_THREAD_PARAMETERS *tp = dtp->tp;
    for(
        r=dtp->row0;
        r<dtp->row1;
        r++
    ){
        for( c=0 ; c < tp->result->columns ; c++ )
            matrixInsert(tp->result, r, c, partial(tp->m1, tp->m2, r, c));
    }
    tp->counter[dtp->index] = 1;
}

void matrixMultiplyCore(MATRIX *m1, MATRIX *m2, MATRIX *result, int threads) {
    pthread_t token;
    int index = 0;
    int current_row=0;
    int i;
    int rest = m1->rows%threads;

    S_THREAD_PARAMETERS *tp = calloc(1, sizeof(S_THREAD_PARAMETERS));
    THREAD_PARAMETERS *dtp = NULL;

    tp->m1 = m1;
    tp->m2 = m2;
    tp->result = result;
    tp->counter = calloc(threads, sizeof(int));
    for(index=threads-1;index!=0;index--) tp->counter[index]=0;

    for(i=0; i<threads; i++){
        dtp = calloc(1, sizeof(THREAD_PARAMETERS));
        dtp->row0=current_row;
        dtp->row1=(current_row+(m1->rows/threads)+rest);
        dtp->index=i;
        dtp->tp = tp;
        pthread_create(&token, NULL, &partialThread, (void *) dtp);

        current_row=current_row+(m1->rows/threads)+(rest ? 1 : 0);
        if(rest)
            rest--;

    }

    while(index!=threads) while(index!=threads && tp->counter[index]!=0) index++;
}
