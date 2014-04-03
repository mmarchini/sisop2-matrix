#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

/*
 * Inicializa uma estrutura do tipo MATRIX
 */
MATRIX *matrixInit(int rows, int columns) {
    
    MATRIX *matrix = NULL;

    if(rows*columns == 0)
        return matrix;

    matrix = calloc(1, sizeof(MATRIX));
    matrix->matrix = calloc(rows*columns, sizeof(int));

    return matrix;
}

int matrixIndex(MATRIX *matrix, int row, int column){
    return matrix->columns*row + column;
}

/*
 * Inicializa uma estrutura do tipo MATRIX
 */
void matrixInsert(MATRIX *matrix, int row, int column, int value) {
    matrix->matrix[matrixIndex(matrix, row, column)] = value;
}

int *matrixGetRow(MATRIX *matrix, int row) {

}

