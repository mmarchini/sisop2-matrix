#include <stdio.h>
#include "../include/matrix.h"

MATRIX *parseFile(char filename[100]){
    int rows=0, columns=0, r, c, aux;
    FILE *file ;
    MATRIX *matrix=NULL;

    file = fopen(filename, "r");

    fscanf(file, "LINHAS = %i\nCOLUNAS = %i\n", &rows, &columns);

    matrix = matrixInit(rows, columns);

    for( r=0; r<rows; r++ )
        for ( c=0; c<columns; c++ ) {
            fscanf(file, "%d", &aux);
            matrixInsert(matrix, r, c, aux);
        }

    return matrix;
}

int main() {
    MATRIX *m1, *m2, *result;

    m1 = parseFile("in1.txt");
    matrixPrint(m1);

    m2 = parseFile("in2.txt");
    matrixPrint(m2);

    result = matrixMultiply(m1, m2);
    matrixPrint(result);

    return 0;
}


