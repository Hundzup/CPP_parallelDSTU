#include <iostream>
#include "MatrixDense.h"

template<typename T>
MatrixDense<T>::MatrixDense(size_t rows, size_t cols): rows(rows), cols(cols){
    arr = new T*[rows];
    for (size_t i = 0; i < rows; i++){
        arr[i] = new T[cols];
        for (size_t j = 0; j < cols; j++){
            arr[i][j] = T();
        }
    }
}

template<typename T>
MatrixDense<T>::~MatrixDense(){
    for (size_t i = 0; i<rows; i++){
        delete[] arr[i];
    }
    delete[] arr;    
}

template<typename T>       
T& MatrixDense<T>::operator()(size_t row, size_t col){
    if (row < 0 || row > rows || col < 0 || col > cols){
        throw std::out_of_range("Index out of range");
    }
    return arr[row][col];
}

template<typename T>
const T& MatrixDense<T>::operator()(size_t row, size_t col) const{
    if (row < 0 || row > rows || col < 0 || col > cols){
        throw std::out_of_range("Index out of range");
    }
    return arr[row][col];
}

template<typename T>
MatrixDense<T> MatrixDense<T>::operator+(const MatrixDense<T>& other) const{
    if (rows != other.rows || cols != other.cols){
        throw std::invalid_argument("Cols and rows have incorrect size");
    }
    MatrixDense<T> rezult(rows, cols);
    for (size_t i = 0; i < rows; i ++){
        for (size_t j = 0; j < cols; j++){
            rezult(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return rezult;
}

template<typename T>
void MatrixDense<T>::print(){
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++){
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
MatrixDense<T> MatrixDense<T>::operator-(const MatrixDense<T>& other) const{
    if (rows != other.rows || cols != other.cols){
        throw std::invalid_argument("Cols and rows have incorrect size");
    }
    MatrixDense<T> rezult(rows, cols);
    for (size_t i = 0; i < rows; i ++){
        for (size_t j = 0; j < cols; j++){
            rezult(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return rezult;
}

template<typename T>
MatrixDense<T> MatrixDense<T>::operator*(const MatrixDense<T>& other) const{
    if (cols != other.rows){
        throw std::invalid_argument("Cols != other.rows unlucky");
    }
    MatrixDense<T> rezult(rows, other.cols);
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < other.cols; j++){
            rezult(i, j) = 0;
            for (size_t k = 0; k < cols; k++){
                rezult(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return rezult;
}