#ifndef OVECTOR_H
#define OVECTOR_H
#include "Vector.h"
#include <omp.h>
#include <cstddef>
#include "time.h"

template<typename T>
class OVector: public Vector<T>{
    private:
        size_t n;
        T* data;
        bool is_initialize = false;
    public:
        OVector(size_t n) : Vector<T>(n){}
        
        ~OVector(){
            delete[] data;
        }

        
};


#endif