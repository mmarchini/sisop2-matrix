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
    matrix->rows = rows;
    matrix->columns = columns;

    return matrix;
}

void matrixPrint(MATRIX *matrix){
    int row, column;
    for( row = 0; row<matrix->rows; row++ ){
        printf("| ");
        for (column = 0; column<matrix->columns; column++)
            printf("%d ", matrixGet(matrix, row, column));
        printf("|\n");
    }
}

/*
 * Retorna o índice para acessar um elemento na matriz 
 */
int matrixIndex(MATRIX *matrix, int row, int column){
    return matrix->columns*row + column;
}

/*
 * Retorna o valor de um elemento na matriz em uma determinada posição 
 */
int matrixGet(MATRIX *matrix, int row, int column){
    return matrix->matrix[matrixIndex(matrix, row, column)];
}

/*
 * Insere um elemento em uma estrutura do tipo MATRIX 
 */
void matrixInsert(MATRIX *matrix, int row, int column, int value) {
    matrix->matrix[matrixIndex(matrix, row, column)] = value;
}

/*
 * Multiplica duas matrizes e retorna a matriz resultante. 
 */
MATRIX *matrixMultiply(MATRIX *m1, MATRIX *m2){
    MATRIX *matrix=NULL;

    if(!m1 || !m2)
        return NULL;

    if(m1->columns!=m2->rows)
        return NULL;

    matrix = calloc(1, sizeof(int));
    matrix->rows = m1->rows;
    matrix->columns = m2->columns;
    matrix->matrix = calloc(m1->rows*m2->columns, sizeof(int));

    matrixMultiplyCore(m1, m2, matrix);

    return matrix;
}

/*
 * Essa função deve ser implementada separadamente. Isso permite realizar testes de desempenho com diversas versões da aplicação. 
 * Ela que realiza a multiplicação própriamente dita.
 */
// void matrixMultiplyCore(MATRIX *m1, MATRIX *m2, MATRIX *result); 


