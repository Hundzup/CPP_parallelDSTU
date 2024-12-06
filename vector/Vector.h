#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <utility>

template<typename T>
class Vector{
    private:
        size_t n;
        T* data;
        bool is_initialize;
    public:
        Vector(size_t n);
        ~Vector();
        void initialize_by_const(T value);
        void initialize_by_random(T start, T end);
        void export2file(char name);
        void importfromfile(char name);
        T sum_elem();
        T euclid_metric(const Vector<T>& other) const;
        T mean();
        T multiply(const Vector<T>& other) const;
        const T& operator()(size_t i) const;
        std::pair<T, size_t> max();
        std::pair<T, size_t> min();
        void print();
};

#include "Vector.tpp"
#endif