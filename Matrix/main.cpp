#include "MatrixDense.h"
#include <iostream>

int main(){
    MatrixDense<int> matrix(2,2);
    matrix(0,0) = 1;
    matrix(0,1) = 2;
    matrix(1,0) = 3;
    matrix(1,1) = 4;
    
    MatrixDense<int> arr(1,4);
    arr(0,0) = 2;
    arr(0,1) = 4;
    arr(0,2) = 0;
    arr(0,3) = 0;
    
    MatrixDense<int> vec1(1, 4);
    vec1(0, 0) = 0;
    vec1(0, 1) = 1;
    vec1(0, 2) = 2;
    vec1(0, 3) = 3;
    vec1.transpose().print();
    MatrixDense<int> B = arr.multiply(vec1);
    B.print();
    matrix.print();
    return 0;
}