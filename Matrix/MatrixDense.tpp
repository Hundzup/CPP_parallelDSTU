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

template<typename T>
MatrixDense<T> MatrixDense<T>::multiply(T scalar) const{
    MatrixDense<T> rezult(rows, cols);
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++){
            rezult(i, j) = (*this)(i, j) * scalar;
        }
    }
    return rezult;
}

template<typename T>
MatrixDense<T> MatrixDense<T>::multiply(const MatrixDense<T>& other) const{
    //check vec2vec
    if (cols == 1 && other.cols == 1 || rows == 1 && other.rows == 1){
        MatrixDense<T> rezult(1, 1);
        rezult(0, 0) = (*this)(0, 0) * other(0, 0);

        if (cols == 1){
            for (size_t i = 1; i < rows; i++){
                rezult(0, 0) += (*this)(i, 0) * other(i, 0);
            }
        }
        if (rows == 1){
            for (size_t i = 1; i < cols; i++){
                rezult(0, 0) += (*this)(0, i) * other(0, i);
                // rezult.print();
            }
        } 
        return rezult;
    }
    if (cols != other.rows){
        throw std::invalid_argument("Cols != other.rows");
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

template<typename T>
MatrixDense<T> MatrixDense<T>::transpose() const{
    MatrixDense<T> rezult(cols, rows);
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++){
            rezult(j, i) = (*this)(i, j);
        }
    }
    return rezult;
}

template<typename T>
MatrixDense<T>::MatrixDense(const MatrixDense& other){
    rows = other.rows;
    cols = other.cols;
    arr = new T*[rows];
    for(size_t i = 0; i < rows; i++){
        arr[i] = new T[cols];
        for(size_t j = 0; j < cols; j++){
            arr[i][j] = other.arr[i][j];
        }
    }
}

template<typename T>
MatrixDense<T>& MatrixDense<T>::operator=(const MatrixDense<T>& other){
    if (this == &other){
        return *this;
    }
    for(size_t i = 0; i < rows; i++){
        delete[] arr[i];
    }
    delete[] arr;

    rows = other.rows;
    cols = other.cols;
    arr = new T*[rows];
    for(size_t i = 0; i < rows; i++){
        arr[i] = new T[cols];
        for(size_t j = 0; j < cols; j++){
            arr[i][j] = other(i, j);
        }
    }
    return *this;
}


