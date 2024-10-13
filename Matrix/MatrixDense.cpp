#include <iostream>


template<typename T> 
class MatrixDense{
    private:
        T **arr;
        size_t rows;
        size_t cols;
    public:
        MatrixDense(size_t rows, size_t cols) : rows(rows), cols(cols){
            arr = new T*[rows];
            for (size_t i = 0; i < rows; i++){
                arr[i] = new T*[cols];
                for (size_t j = 0; j < cols; j++){
                    arr[i][j] = T();
                }
            }
        }
        
        ~MatrixDense(){
            for (size_t i = 0; i<rows; i++){
                delete[] arr[i];
            }
            delete[] arr;
        }

        T& operator()(size_t row, size_t col){
            if (row < 0 || row > rows || col < 0 || col > cols){
                throw std::out_of_range("Index out of range");
            }
            return arr[row][col];
        }

        const T& operator()(size_t row, size_t col){
            if (row < 0 || row > rows || col < 0 || col > cols){
                throw std::out_of_range("Index out of range");
            }
            return arr[row][col];
        }

        MatrixDense<T> operator+(const MatrixDense<T>) const{
            if (rows != other.rows || cols != other.cols){
                throw std::invalid_argument("Cols and rows have incorrect size");
            }
            MatrixDense<T> rezult(rows, cols);
            for (size_t i = 0; i < rows; i ++){
                for (size_t j = 0; j < cols; j++){
                    rezult(i, j) = arr[i][j] + other(i, j);
                }
            }
            return rezult;
        }

        void print(){
            for (size_t i = 0; i < rows; i++){
                for (size_t j = 0; j < cols; j++){
                    std::cout << arr[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
};