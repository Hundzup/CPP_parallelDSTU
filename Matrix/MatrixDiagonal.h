#ifndef MATRIXDIAGONAL_H
#define MATRIXDIAGONAL_H
#include <cstddef>
#include <random>
#include <iostream>
#include <fstream>
#include "MatrixDense.h"
#include <typeinfo>
#include <stdio.h>


//idx mean index of diag 
template<typename T>
class MatrixDiagonal{
    private:
        size_t size;
        MatrixDense<int>* idx;
        MatrixDense<T>* arr;
        size_t rows;
        
    public:
        MatrixDiagonal(size_t size, MatrixDense<int>* idx): size(size), idx(idx){
            if (idx->getRows() == 1){
                rows = idx->getCols();
            }else{
                if (idx->getCols() == 1){
                    rows = idx->getRows();
                }else{
                    throw std::invalid_argument("Error input dim of vector idx");
                }
            }
            MatrixDense<T>* tmp = new MatrixDense<T>(rows, size);
            arr = tmp;
            tmp->~MatrixDense();
        }

        ~MatrixDiagonal(){
            arr->~MatrixDense();
        }
        
        void initialize_by_random(int start, int end){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> distrib(start, end);
            for (size_t i=0; i < arr->getRows(); i++){
                for (size_t j=0; j < arr->getCols(); j++){
                    arr->operator()(i, j) = (T)distrib(gen);
                    // std::cout << arr->operator()(i, j) << " ";
                    
                }
                // std::cout << std::endl;
            }
        }

        void initialize_by_arrange(){
            for (size_t i=0; i < arr->getRows(); i++){
                for (size_t j=0; j < arr->getCols(); j++){
                    // std::cout << (T)(idx->operator()(0, i)) << " ";
                    arr->operator()(i, j) = (T)(idx->operator()(0, i));
                }
                // std::cout << std::endl;
            }
        }

        void print(){
            // std::cout << arr->getCols() << " " << arr->getRows() << std::endl;
            std::cout << "Rows - " << arr->getRows() << " Cols - " << arr->getCols() << std::endl;
            for (size_t i = 0; i < arr->getRows(); i++){
                for (size_t j=0; j < arr->getCols(); j++){
                    printf("%2d", operator()(i, j));
                    std::cout << " ";
                    // std::cout << operator()(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }

        T& operator()(size_t row, size_t col){
            if (row < 0 || row > arr->getRows()-1 || col < 0 || col > arr -> getCols() - 1){
                throw std::out_of_range("Index out of range: diag");
            }
            int idx_row, idx_col;
            idx_row = -1*(row - col);
            if (idx_row < 0){
                idx_col = idx_row+row;
            }else{
                idx_col = row;
            }
            for (size_t i=0; i<rows; i++){
                if (idx->operator()(0, i) == idx_row){
                    // std::cout << i << " " << idx_col << std::endl;
                    // std::cout << arr->operator()(i, idx_col) << " ";
                    return arr->operator()(i, idx_col);
                }
            }
            static T defaultVal = T();
            return defaultVal;
        }


        const T operator()(size_t row, size_t col) const{
            if (row < 0 || row > arr->getRows()-1 || col < 0 || col > arr -> getCols() - 1){
                throw std::out_of_range("Index out of range: diag");
            }
            int idx_row, idx_col;
            idx_row = -1*(row - col);
            if (idx_row < 0){
                idx_col = idx_row+row;
            }else{
                idx_col = row;
            }
            for (size_t i=0; i<rows; i++){
                if (idx->operator()(0, i) == idx_row){
                    // std::cout << arr->operator()(i, idx_col) << " ";
                    return arr->operator()(i, idx_col);
                }
            }
            return T();
        }
        
        // MatrixDiagonal<T> operator+(const MatrixDiagonal<T>& other) const{
        //     return;
        // }

        // MatrixDiagonal<T> operator-(const MatrixDiagonal<T>& other) const{

        // }

        // MatrixDiagonal<T> operator*(const MatrixDiagonal<T>& other) const{

        // }

        // MatrixDiagonal<T> transpose() const{
        //     return this*;
        // }   

        // void export2file(const char* name){

        // }   

        // void importfromfile(const char* name){

        // } 
};

#endif