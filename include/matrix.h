#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct _MATRIX {
    int rows;
    int columns;
    int *matrix;
} MATRIX;

MATRIX *matrixInit(int rows, int columns);

void matrixPrint(MATRIX *matrix);

int matrixIndex(MATRIX *matrix, int row, int column);

void matrixInsert(MATRIX *matrix, int row, int column, int value); 

MATRIX *matrixMultiply(MATRIX *m1, MATRIX *m2, int threads); 

void matrixMultiplyCore(MATRIX *m1, MATRIX *m2, MATRIX *result, int threads); 

#endif
