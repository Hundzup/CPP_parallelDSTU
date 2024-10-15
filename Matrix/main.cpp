#include "MatrixDense.h"
#include <iostream>

int main(){
    MatrixDense<int> matrix(2,2);
    matrix(0,0) = 1;
    matrix(0,1) = 1;
    matrix(1,0) = 1;
    matrix(1,1) = 1;
    
    MatrixDense<int> arr(2,2);
    arr(0,0) = 2;
    arr(1,0) = 2;
    arr(0,1) = 2;
    arr(1,1) = 2;
    arr.print();
    MatrixDense<int> rez =  matrix - arr;

    arr.print();
    matrix.print();
    rez.print();

    return 0;
}