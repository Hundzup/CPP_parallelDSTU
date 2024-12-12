#include "Vector.h"
#include <iostream>
#include "TVector.h"
#include "Stat.h"


int main(){
    Stat A(10000000);
    int threads[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    A.create_stats(threads, sizeof(threads)/sizeof(int), "stat");
    return 0;
}