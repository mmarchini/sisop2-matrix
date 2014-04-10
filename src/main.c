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

int main(int argn, char *args[]) {
    MATRIX *m1, *m2, *result;
    int threads=0;

    m1 = parseFile("in1.txt");

    m2 = parseFile("in2.txt");

    if(argn>1){
        sscanf(args[1], "%d", &threads);
        
    } else{
        threads = 1;
    }

    result = matrixMultiply(m1, m2, threads);
    matrixSave(result, "out.txt");

    return 0;
}


