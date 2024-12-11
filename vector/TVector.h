#ifndef VECTOR_T
#define VECTOR_T
#include <cstddef>
#include <utility>
#include "Vector.h"
#include <mutex>

template<typename T>
class TVector :public Vector<T>{
    private:
        std::mutex mtx;
        size_t n;
        T* data;;
        bool is_initialize;
    public:
        TVector(size_t n) : Vector<T>(n){}
        ~TVector(){}
        using Vector<T>::initialize_by_const;
        using Vector<T>::initialize_by_random;
        using Vector<T>::export2file;
        using Vector<T>::importfromfile;
        T sum_elem();
        T euclid_metric(const Vector<T>& other) const;
        T mean();
        T multiply(const Vector<T>& other) const;
        using Vector<T>::operator();
        std::pair<T, size_t> max();
        std::pair<T, size_t> min();
        using Vector<T>::print;

};


#endif