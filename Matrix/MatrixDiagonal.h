#ifndef MATRIXDIAGONAL_H
#define MATRIXDIAGONAL_H
#include <cstddef>
#include <iostream>
#include <fstream>
#include "../vector/Vector.h"
#include "MatrixDense.h"
#include <typeinfo>


template<typename T>
class MatrixDiagonal{
    private:
        size_t size;
        Vector<int>* idx;
        MatrixDense<T>* arr;
    public:
        MatrixDiagonal(size_t size, Vector<int>* idx){
            std::cout << idx->getN() << std::endl;
            std::cout << typeid(T).name();
            
        }

        // ~MatrixDiagonal(){

        // }

        // T& operator()(size_t row, size_t col){

        // }
        
        // MatrixDiagonal<T> operator+(const MatrixDiagonal<T>& other) const{

        // }

        // MatrixDiagonal<T> operator-(const MatrixDiagonal<T>& other) const{

        // }

        // MatrixDiagonal<T> operator*(const MatrixDiagonal<T>& other) const{

        // }

        // MatrixDiagonal<T> transpose() const{

        // }   

        // void export2file(const char* name){

        // }   

        // void importfromfile(const char* name){

        // } 
};

#endif