#include "MatrixDense.h"
#include <iostream>
#include "MatrixDiagonal.h"


int main(){
    // int *idx {new int[]{0,1,2,3}};
    size_t size = 6;
    MatrixDense<int> idx(1, 5);
    idx(0, 0) = 0; 
    idx(0, 1) = 1;
    idx(0, 2) = 2;
    idx(0, 3) = -1;
    idx(0, 4) = 4;
    MatrixDiagonal<double> arr(size, &idx);
    // idx.print();
    arr.initialize_by_random(1, 4);
    // arr.initialize_by_arrange();
    arr.print();
    return 0;
}