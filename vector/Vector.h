#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <fstream>
#include <string>



template<typename T>
class Vector{
    private:
        size_t n;
        T* data;;
        bool is_initialize;
    public:
        Vector(size_t n):n(n){
            data = new T[n];
            is_initialize = false;
        }

        ~Vector(){
            delete[] data;
        }

        void initialize_by_const(T value){
            is_initialize = true;
            for(size_t i=0; i<n; i++){
                data[i] = value;
            }
        }

        void initialize_by_random(T start, T end){
            is_initialize = true;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> distrib(start, end);
            for(size_t i=0; i<n; i++){
                data[i] = (T)distrib(gen);
            }
        }
        
        void export2file(const char* name){
            std::ofstream outFile(name);
            outFile << n << std::endl;
            for (size_t i=0; i<n; i++){
                outFile << data[i] << " ";
            }
            outFile.close();
        }

        void importfromfile(const char* name){
            std::ifstream inputFile(name);
            size_t n_tmp;
            inputFile >> n_tmp;
            if (n_tmp != n){
                throw std::invalid_argument("Not the same size of arrays");
            }

            for (size_t i=0; i<n; i++){
                inputFile >> data[i];
            }

            inputFile.close();
            is_initialize = true;
        }

        T sum_elem(){
            if (is_initialize == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T sum=0;
            for(size_t i=0; i<n; i++){
                sum = sum + data[i];
            }
            return sum;
        }

        T euclid_metric(const Vector<T>& other) const{
            if (is_initialize == false){
                throw std::runtime_error("You have to initialize arry");
            }
            if (n!=other.n){
                throw std::invalid_argument("Need the same size of vectors");
            }
            T rezult = 0;
            for(size_t i=0; i < n; i++){
                rezult += sqrt(pow(data[i] - other(i), 2));
            }
            return rezult;
        }

        T mean(){
            if (is_initialize == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T mean = 0;
            T count = n;
            for(size_t i=0; i<n; i++){
                mean = mean + data[i];
            }
            return mean/count;
        }

        T multiply(const Vector<T>& other) const{
            if (n != other.n){
                throw std::invalid_argument("Need the same size of vectors");
            }
            if (is_initialize == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T rezult = 0;
            for(size_t i = 0; i < n; i++){
                rezult += data[i] * other(i);
            }
            return rezult;
        }

        const T& operator()(size_t i) const{
            return data[i];
        }

        std::pair<T, size_t> max(){
            if (is_initialize == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T max = data[0];
            size_t ids = 0;
            for(size_t i=0; i<n; i++){
                if (data[i]>max){
                    max=data[i];
                    ids = i;
                }
            }
            return std::make_pair(max, ids);
        }
        
        std::pair<T, size_t> min(){
            if (is_initialize == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T min = data[0];
            size_t ids = 0;
            for(size_t i=0; i<n; i++){
                if (data[i]<min){
                    min=data[i];
                    ids = i;
                }
            }
            return std::make_pair(min, ids);
        }
        
        void print(){
            for(size_t i = 0; i < n; i++){
                if (i == n-1){
                    std::cout << data[i] << ".";
                    continue;
                }
                std::cout << data[i] << ", ";
            }
            std::cout<< std::endl;
        }

};

#endif