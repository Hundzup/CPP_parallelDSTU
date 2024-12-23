#include "MatrixDense.h"
#include <iostream>
#include "MatrixDiagonal.h"
#include "../vector/Vector.h"


int main(){
    // int *idx {new int[]{0,1,2,3}};
    size_t size = 5;
    Vector<int> idx(5);
    idx(0) = 0;
    idx(1) = 1;
    idx(2) = 2;
    idx(3) = 3;
    idx(4) = 4;
    MatrixDiagonal<size_t> arr(size, &idx);
    return 0;
}