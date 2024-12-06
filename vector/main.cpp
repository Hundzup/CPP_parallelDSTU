#include "Vector.h"
#include <iostream>

int main(){
    Vector<double> V(10);
    V.initialize_by_const(2.7f);
    std::cout << V.mean() << std::endl;
    std::cout << V.sum_elem() << std::endl;
    auto rezult = V.max();
    auto value = rezult.first;
    auto idx = rezult.second;
    std::cout << value << " " << idx << std::endl;
    std::cout << V.min().first << " " << V.min().second << std::endl;
    V.print();
    return 0;
}