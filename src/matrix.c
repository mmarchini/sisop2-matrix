#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
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

void matrixSave(MATRIX *matrix, char *filename){
    int row, column;
    FILE *f=fopen(filename, "w+");

    fprintf(f, "LINHAS = %d\n", matrix->rows);
    fprintf(f, "COLUNAS = %d\n", matrix->columns);

    for( row = 0; row<matrix->rows; row++ ){
        for (column = 0; column<matrix->columns; column++)
            fprintf(f, "%d ", matrixGet(matrix, row, column));
        fprintf(f,"\n");
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

void startProfiling(struct timeval *start){
    gettimeofday(start, NULL);
}

suseconds_t endProfiling(struct timeval *start){
    struct timeval end;
    suseconds_t elapsed;

    gettimeofday(&end, NULL);
    elapsed = end.tv_usec - start->tv_usec;

    return elapsed;
}

/*
 * Multiplica duas matrizes e retorna a matriz resultante. 
 */
MATRIX *matrixMultiply(MATRIX *m1, MATRIX *m2, int threads){
    MATRIX *matrix=NULL;
    struct timeval start; 
    suseconds_t elapsed;
    FILE *f=NULL;
    int requested_threads = threads;

    if(!m1 || !m2)
        return NULL;

    if(m1->columns!=m2->rows)
        return NULL;

    matrix = calloc(1, sizeof(int));
    matrix->rows = m1->rows;
    matrix->columns = m2->columns;
    matrix->matrix = calloc(m1->rows*m2->columns, sizeof(int));

    // Garante que o número de threads não extrapole o número de linhas
    threads = threads < m1->rows ? threads : m1->rows;

    startProfiling(&start);
    matrixMultiplyCore(m1, m2, matrix, threads);
    elapsed = endProfiling(&start);

    f=fopen("profiling.log", "w+");
    fprintf(f, "REQUESTED THREADS: %d\n", requested_threads);
    fprintf(f, "USED THREADS: %d\n", threads);
    fprintf(f, "in1.txt: (%d,%d)\n", m1->rows, m1->columns);
    fprintf(f, "in2.txt: (%d,%d)\n", m2->rows, m2->columns);
    fprintf(f, "out.txt: (%d,%d)\n", matrix->rows, matrix->columns);
    fprintf(f, "Elapsed Time(microseconds): %lu\n", elapsed);

    return matrix;
}

/*
 * Essa função deve ser implementada separadamente. Isso permite realizar testes de desempenho com diversas versões da aplicação. 
 * Ela que realiza a multiplicação própriamente dita.
 */
// void matrixMultiplyCore(MATRIX *m1, MATRIX *m2, MATRIX *result); 


