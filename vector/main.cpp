#include "Vector.h"
#include <iostream>

int main(){
    Vector<double> V(10);
    Vector<double> B(10);
    V.initialize_by_const(2.7f);
    B.initialize_by_random(1, 12);
    std::cout << V.mean() << std::endl;
    std::cout << V.sum_elem() << std::endl;
    auto rezult = V.max();
    auto value = rezult.first;
    auto idx = rezult.second;
    std::cout << value << " " << idx << std::endl;
    std::cout << V.min().first << " " << V.min().second << std::endl;
    B.print();
    std::cout << V.multiply(B) << std::endl;
    std::cout << V.euclid_metric(B) << std::endl;
    B.export2file("new_file");
    V.print();
    V.importfromfile("new_file");
    V.print();
    
    return 0;
}