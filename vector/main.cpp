#include "Vector.h"
#include <iostream>
#include "TVector.h"


int main(){
    // Vector<double> V(10);
    // Vector<double> B(10);
    // V.initialize_by_const(2.7f);
    // B.initialize_by_random(1, 12);
    // std::cout << V.mean() << std::endl;
    // std::cout << V.sum_elem() << std::endl;
    // auto rezult = V.max();
    // auto value = rezult.first;
    // auto idx = rezult.second;
    // std::cout << value << " " << idx << std::endl;
    // std::cout << V.min().first << " " << V.min().second << std::endl;
    // B.print();
    // std::cout << V.multiply(B) << std::endl;
    // std::cout << V.euclid_metric(B) << std::endl;
    // B.export2file("new_file");
    // V.print();
    // Vector<double> D(12);
    // V.importfromfile("new_file");
    // V.print();
    TVector<double> A(10);   
    TVector<double> B(120);
    A.initialize_by_random(1, 10);
    B.initialize_by_const(1);
    A.print();
    // std::cout << A(100) << std::endl;
    // std::cout << A.sum_elem(10) << std::endl;
    // std::cout << A.getN(); 
    // std::cout << A.getN() << std::endl;
    // std::cout << B.getN() << std::endl;
    auto sum_rez = A.min(9);
    std::cout << sum_rez.first.first << " " << sum_rez.first.second << " " << sum_rez.second;
    return 0;
}