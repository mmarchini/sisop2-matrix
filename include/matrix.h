#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct _MATRIX {
    int rows;
    int columns;
    int *matrix;
} MATRIX;

MATRIX *matrixInit(int rows, int columns);

int matrixIndex(MATRIX *matrix, int row, int column);

void matrixInsert(MATRIX *matrix, int row, int column, int value); 

int *matrixGetRow(MATRIX *matrix, int row); 

#endif
