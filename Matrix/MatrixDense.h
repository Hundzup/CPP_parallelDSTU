#ifndef MATRIXDENSE_H
#define MATRIXDENSE_H
#include <cstddef>

template<typename T>
class MatrixDense{
    private:
        T** arr;
        size_t rows;
        size_t cols;
    public:
        MatrixDense(size_t rows, size_t cols);
        ~MatrixDense();
        T& operator()(size_t row, size_t col);
        const T& operator()(size_t row, size_t col) const;
        MatrixDense<T> operator+(const MatrixDense<T>& other) const;
        void print();
        MatrixDense<T> operator-(const MatrixDense<T>& other) const;
        MatrixDense<T> operator*(const MatrixDense<T>& other) const;
};

#include "MatrixDense.tpp"
#endif