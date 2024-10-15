#include "MatrixDense.h"
#include <iostream>

int main(){
    MatrixDense<int> matrix(2,2);
    matrix(0,0) = 1;
    matrix(0,1) = 2;
    matrix(1,0) = 3;
    matrix(1,1) = 4;
    
    MatrixDense<int> arr(2,2);
    arr(0,0) = 2;
    arr(1,0) = 3;
    arr(0,1) = 4;
    arr(1,1) = 5;
    MatrixDense<int> rez =  matrix * arr;

    arr.print();
    matrix.print();
    rez.print();

    return 0;
}